// https://www.pololu.com/docs/0J73/15.5

// Uses POSIX serial port functions to send and receive data from a Jrk G2.
// NOTE: The Jrk's input mode must be "Serial / I2C / USB".
// NOTE: The Jrk's serial mode must be set to "USB dual port" if you are
//   connecting to it directly via USB.
// NODE: The Jrk's serial mode must be set to "UART" if you are connecting to
//   it via is TX and RX lines.
// NOTE: You might need to change the 'const char * device' line below to
//   specify the correct serial port.

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <termios.h>
#include <string.h>
#include <pthread.h>
#include "aciga/log.h"

#include "gpio.h"
#include "common_hdr.h"

// Opens the specified serial port, sets it up for binary communication,
// configures its read timeouts, and sets its baud rate.
// Returns a non-negative file descriptor on success, or -1 on failure.
int open_serial_port(const char *device, uint32_t baud_rate)
{
    int fd = open(device, O_RDWR | O_NOCTTY);
    if (fd == -1) {
        perror(device);
        return -1;
    }

    // Flush away any bytes previously read or written.
    // yyy:
    int result = tcflush(fd, TCIOFLUSH);
    if (result) {
        perror("tcflush failed"); // just a warning, not a fatal error
    }

    // Get the current configuration of the serial port.
    struct termios options;
    result = tcgetattr(fd, &options);
    if (result) {
        perror("tcgetattr failed");
        close(fd);
        return -1;
    }

    // Turn off any options that might interfere with our ability to send and
    // receive raw binary bytes.
    options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
    options.c_oflag &= ~(ONLCR | OCRNL);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

    // Set up timeouts: Calls to read() will return as soon as there is
    // at least one byte available or when 100 ms has passed.
    // options.c_cc[VTIME] = 1;
    options.c_cc[VTIME] = 30; // yyy: set timeout value to 3 seconds.
    options.c_cc[VMIN] = 0;

    // This code only supports certain standard baud rates. Supporting
    // non-standard baud rates should be possible but takes more work.
    switch (baud_rate) {
    case 4800:
        cfsetospeed(&options, B4800);
        break;
    case 9600:
        cfsetospeed(&options, B9600);
        break;
    case 19200:
        cfsetospeed(&options, B19200);
        break;
    case 38400:
        cfsetospeed(&options, B38400);
        break;
    case 115200:
        cfsetospeed(&options, B115200);
        break;
    default:
        fprintf(stderr, "warning: baud rate %u is not supported, using 9600.\n", baud_rate);
        cfsetospeed(&options, B9600);
        break;
    }
    cfsetispeed(&options, cfgetospeed(&options));

    result = tcsetattr(fd, TCSANOW, &options);
    if (result) {
        perror("tcsetattr failed");
        close(fd);
        return -1;
    }

    return fd;
}

// Writes bytes to the serial port, returning 0 on success and -1 on failure.
int write_port(int fd, uint8_t *buffer, size_t size)
{
    aciga_log_info("write data to serial port, size=%d\n", size);

    ssize_t result = write(fd, buffer, size);
    if (result != (ssize_t)size) {
        perror("failed to write to port");
        return -1;
    }
    return 0;
}

// Reads bytes from the serial port.
// Returns after all the desired bytes have been read, or if there is a
// timeout or other error.
// Returns the number of bytes successfully read into the buffer, or -1 if
// there was an error reading.
ssize_t read_port(int fd, uint8_t *buffer, size_t size)
{
    aciga_log_info("read data from serial port, want size=%d\n", size);

    size_t received = 0;
    while (received < size) {
        ssize_t r = read(fd, buffer + received, size - received);
        if (r < 0) {
            perror("failed to read from port,");
            return -1;
        }
        if (r == 0) {
            // Timeout
            perror(">read from port, timeout occurs");
            break;
        }

        // aciga_log_info("internal read got %d bytes", r);
        received += r;
    }

    aciga_log_info("read data from serial port, recvd=%d\n", received);
    aciga_debug_hex(buffer, received);

    return received;
}

// Sets the target, returning 0 on success and -1 on failure.
//
// For more information about what this command does, see the "Set Target"
// command in the "Command reference" section of the Jrk G2 user's guide.
int jrk_set_target(int fd, uint16_t target)
{
    if (target > 4095) {
        target = 4095;
    }
    uint8_t command[2];
    command[0] = 0xC0 + (target & 0x1F);
    command[1] = (target >> 5) & 0x7F;
    return write_port(fd, command, sizeof(command));
}

// Gets one or more variables from the Jrk (without clearing them).
// Returns 0 for success, -1 for failure.
int jrk_get_variable(int fd, uint8_t offset, uint8_t *buffer, uint8_t length)
{
    uint8_t command[] = {0xE5, offset, length};
    int result = write_port(fd, command, sizeof(command));
    if (result) {
        return -1;
    }
    ssize_t received = read_port(fd, buffer, length);
    if (received < 0) {
        return -1;
    }
    if (received != length) {
        fprintf(stderr, "read timeout: expected %u bytes, got %zu\n", length, received);
        return -1;
    }
    return 0;
}

// Gets the Target variable from the jrk or returns -1 on failure.
int jrk_get_target(int fd)
{
    uint8_t buffer[2];
    int result = jrk_get_variable(fd, 0x02, buffer, sizeof(buffer));
    if (result) {
        return -1;
    }
    return buffer[0] + 256 * buffer[1];
}

// Gets the Feedback variable from the jrk or returns -1 on failure.
int jrk_get_feedback(int fd)
{
    // 0x04 is the offset of the feedback variable in the "Variable reference"
    // section of the Jrk user's guide.  The variable is two bytes long.
    uint8_t buffer[2];
    int result = jrk_get_variable(fd, 0x04, buffer, sizeof(buffer));
    if (result) {
        return -1;
    }
    return buffer[0] + 256 * buffer[1];
}

#if 0
int main()
{
    // Choose the serial port name.  If the Jrk is connected directly via USB,
    // you can run "jrk2cmd --cmd-port" to get the right name to use here.
    // Linux USB example:          "/dev/ttyACM0"  (see also: /dev/serial/by-id)
    // macOS USB example:          "/dev/cu.usbmodem001234562"
    // Cygwin example:             "/dev/ttyS7"
    const char *device = "/dev/ttyACM0";

    // Choose the baud rate (bits per second).  This does not matter if you are
    // connecting to the Jrk over USB.  If you are connecting via the TX and RX
    // lines, this should match the baud rate in the Jrk's serial settings.
    uint32_t baud_rate = 9600;

    int fd = open_serial_port(device, baud_rate);
    if (fd < 0) {
        return 1;
    }

    int feedback = jrk_get_feedback(fd);
    if (feedback < 0) {
        return 1;
    }

    printf("Feedback is %d.\n", feedback);

    int target = jrk_get_target(fd);
    if (target < 0) {
        return 1;
    }
    printf("Target is %d.\n", target);

    int new_target = (target < 2048) ? 2248 : 1848;
    printf("Setting target to %d.\n", new_target);
    int result = jrk_set_target(fd, new_target);
    if (result) {
        return 1;
    }

    close(fd);
    return 0;
}
#endif

int reply_485_result(int is_success);
void send_485_serial_reply();

#define DEV_485 "/dev/ttyS0"
#define BAUDRATE_485 9600

#define EXPECTED_LEN 5
uint8_t expected_reply[EXPECTED_LEN] = {0xAA, 0x03, 0x92, 0x01, 0xFF};

int serial_fd = -1;
pthread_t t_485_reader;
int t_485_running = 0;
int kill_485_reader = 0;
int is_waiting_reply = 0;

void *read_485(void *arg)
{
    aciga_log_info("start 485 reader thread");

    if (serial_fd < 0) {
        aciga_log_err("serial_fd is wrong, serial_fd=%d", serial_fd);
    }

    uint8_t reply_buffer[EXPECTED_LEN] = {0};
    int fail_cnt = 0;

    while (kill_485_reader == 0) {
        t_485_running = 1;

        // wait response.
        int n = read_port(serial_fd, reply_buffer, EXPECTED_LEN);
        if (n != EXPECTED_LEN) {
            aciga_log_err("start_485_test: failed to get all data in 3 seconds, want:%d get:%d", EXPECTED_LEN, n);

            if (!is_waiting_reply) {
                fail_cnt = 0;
                continue; // not under test, ignore received data.
            }

            ++fail_cnt;
            if( fail_cnt >= 3 ) {
                is_waiting_reply = 0;
                aciga_log_err("Failed to get reply 3 times, exit this testing");

                reply_485_result(0);
            }
            continue;
        }

        if (!is_waiting_reply) {
            fail_cnt = 0;
            continue; // not under test, ignore received data.
        }

        expected_reply[4] = 0xFF & (reply_buffer[1] + reply_buffer[2] + reply_buffer[3]);

        if (0 != memcmp(reply_buffer, expected_reply, EXPECTED_LEN)) {
            aciga_log_err("reply buffer was not expected(len=%d) :", n);

            #define MAX_LEN 64
            char tmp[MAX_LEN * 4];  //store output string of reply_buffer
            int len = 0;
            for (int i = 0; i < n && i < MAX_LEN; i++) {
                len += sprintf(tmp + len, "%2x ", reply_buffer[i] & 0xFF);
            }
            aciga_log_err("%s", tmp);

            ++fail_cnt;
            if (fail_cnt >= 3) {
                aciga_log_err("Failed 3 times, exit this testing, reply with failed.");

                reply_485_result(0);

                is_waiting_reply = 0;
                fail_cnt = 0;
            }
        } else {
            aciga_log_err(" reply buffer was ok, test success");

            reply_485_result(1);

            send_485_serial_reply();

            is_waiting_reply = 0;
        }
    }

    t_485_running = 0;
    aciga_log_info("485 reader thread exit");

    return NULL;
}

void start_485_read_thread()
{
    if (!t_485_running) {
        pthread_create(&t_485_reader, NULL, read_485, NULL);
    }
}

void send_485_serial_reply()
{
    uint8_t buffer[] = {0xAA, 0x03, 0x81, 0x01, 0xFF};

    int size = sizeof(buffer);
    int n = write_port(serial_fd, buffer, size);
    if (n != 0) { // return 0 on success.
        aciga_log_err(" failed to write seiral port");
    }
}



#ifdef PLATFORM_P5
#define DIR_485_GPIO   132
#endif

void set_485_as_tx_direction(int tx_enable)
{
    static int export_gpio_once = 0;
    if( !export_gpio_once ) {
        aciga_log_info("export 485_direction GPIO:%d", DIR_485_GPIO );
        gpio_export(DIR_485_GPIO);
        gpio_direction(DIR_485_GPIO, "out");
        export_gpio_once = 1;
    }

    if( tx_enable) {
        aciga_log_info("set 485_direction TX,  GPIO high");
        gpio_write(DIR_485_GPIO, 1);
    }else {
        aciga_log_info("set 485_direction RX,  GPIO low");
        gpio_write(DIR_485_GPIO, 0);
    }
}

int send_data_by_485(uint8_t *data, int size)
{
    set_485_as_tx_direction(1);

    int n = write_port(serial_fd, data, size);
    if (n != 0) { // return 0 on success.
        aciga_log_err(" failed to write seiral port. serial_fd=%d", serial_fd);
    }

    usleep(1000*1000);
    set_485_as_tx_direction(0);

    return n;
}

int start_485_test()
{
    if (serial_fd < 0) {
        serial_fd = open_serial_port(DEV_485, BAUDRATE_485);
        if (serial_fd < 0) {
            aciga_log_err(" failed to open seiral port : %s , baud: %d", DEV_485, BAUDRATE_485);
            return -1;
        }

        aciga_log_info("open serial port [%s] success\n", DEV_485);
    } else {
        aciga_log_info("serial port already opened");
    }

    is_waiting_reply = 1;
    start_485_read_thread();

    return 1;
}