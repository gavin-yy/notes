#include "gpio.h"

//标准Linux系统的gpio控制方式，通过/sys/class/gpio

#if !defined(MT8175)

/**
 * @brief : gpio 导出
 * @param : pin
 * @retval: 0 成功; -1失败
 */
int gpio_export(const int pin)
{
    int fd, len;
    char buffer[64];
    char path[64];

    sprintf(&path[0], "/sys/class/gpio/gpio%d", pin);
    /* 文件不存在时，导出gpio*/
    if (access(path, F_OK) != 0)
    {
        memset(path, 0, 64);
        sprintf(&path[0], "/sys/class/gpio/export");
        open_gpio_file(path, O_WRONLY, fd);
        len = snprintf(buffer, sizeof(buffer), "%d", pin);

        if (write(fd, buffer, len) < 0)
        {
            err_out("write failed to export gpio!\n");
            return -1;
        }
        close(fd);
    }
    return 0;
}
/**
 * @brief : gpio 卸载
 * @param : pin
 * @retval: 0 成功; -1失败
 */
int gpio_unexport(const int pin)
{
    int fd, len;
    char buffer[64];
    char path[64];

    sprintf(&path[0], "/sys/class/gpio/gpio%d", pin);
    /* 文件存在时，卸载gpio*/
    if (access(path, F_OK) == 0)
    {
        memset(path, 0, 64);
        sprintf(&path[0], "/sys/class/gpio/unexport");
        open_gpio_file(path, O_WRONLY, fd);
        len = snprintf(buffer, sizeof(buffer), "%d", pin);
        if (write(fd, buffer, len) < 0)
        {
            err_out("write failed to unexport gpio!\n");
            return -1;
        }
        close(fd);
    }
    return 0;
}

/**
 * @brief : gpio 方向控制
 * @param : dir 方向(in/out)
 * @retval: 0 成功; -1失败
 */
int gpio_direction(const int pin, const char *dir)
{
    int fd;
    char path[64];
    int w_len = ((dir[0] == 'i') && (dir[1] == 'n')) ? 2 : 3;

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);
    open_gpio_file(path, O_WRONLY, fd);
    if (write(fd, dir, w_len) < 0)
    {
        err_out("Failed to set direction!\n");
        return -1;
    }

    close(fd);
    return 0;
}

/**
 * @brief : gpio 写
 * @param : 0 / 1
 * @retval: 0 成功; -1失败
 */
int gpio_write(const int pin, const int value)
{
    int fd;
    char path[64];
    const char *val[] = {"0", "1"};

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    open_gpio_file(path, O_WRONLY, fd);

    if (write(fd, val[value], 1) < 0)
    {
        err_out("Failed to write value!\n");
        return -1;
    }

    close(fd);
    return 0;
}

/**
 * @brief : gpio 读
 * @param : 读取的引脚值
 * @retval: 返回引脚的值 0 / 1
 */
int gpio_read(const int pin)
{
    int fd;
    char path[64];
    char value_str[3];

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    open_gpio_file(path, O_RDONLY, fd);
    if (read(fd, value_str, 3) < 0)
    {
        err_out("Failed to read value!\n");
        return -1;
    }

    close(fd);
    return (atoi(value_str));
}

/**
 * @brief : gpio 中断控制
 * @param : 0 none 表示引脚为输入，不是中断引脚
 *   @arg : 1 rising 表示引脚为中断输入，上升沿触发
 *   @arg : 2 falling 表示引脚为中断输入，下降沿触发
 *   @arg : 3 both 表示引脚为中断输入，边沿触发
 * @retval:
 */
int gpio_edge(const int pin, int edge)
{
    int fd;
    char path[64];
    const char *dir_str[] = {"none", "rising", "falling", "both"};

    if (edge > 3)
    {
        err_out("Failed edge parameter error\n");
        return -1;
    }

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/edge", pin);
    open_gpio_file(path, O_WRONLY, fd);

    if (write(fd, dir_str[edge], strlen(dir_str[edge])) < 0)
    {
        err_out("Failed to set edge!\n");
        return -1;
    }

    close(fd);
    return 0;
}

#endif