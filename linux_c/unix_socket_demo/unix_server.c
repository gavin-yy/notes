#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h> /* Added for the nonblocking socket */

#include "demo_util.h"

/* do not create sockets in tmp directory
* To show a socket example – it is fine.
* creating sockets in tmp directory is a security
* vulnerability */

const char *path = "/tmp/unix_socket.sock";

struct sockaddr_un *servaddr = NULL, *cliaddr = NULL;
int sockserver, sockclient;

/* Interrupt_handler so that CTRL +C can be used
* to exit the program */
void interrupt_handler(int signum)
{
    close(sockserver);
    close(sockclient);
    free(servaddr);
    free(cliaddr);
    printf("socket connection closed\n");
    exit(0);
}

int main()
{

    int length;
    char buffer[50];
    char *string = "Hello from server";

    /* signal handler to exit out of while 1 loop */
    signal(SIGINT, interrupt_handler);
    signal(SIGPIPE, interrupt_handler);

    /* Part 1 – create the socket */
    sockserver = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    if (sockserver < 0)
    {
        printf("creating server socket failed\n");
        exit(0);
    }
    /* Part 2 – fill the structure and bind to the socket path
        * Remove/unlink any previous socket file creation
        */
    remove(path);

    servaddr = (struct sockaddr_un *)malloc(sizeof(struct sockaddr_un));
    if (servaddr == NULL)
    {
        printf("Unable to allocate memory\n");
        goto end;
    }
    servaddr->sun_family = AF_UNIX;

    if ((strlen(path)) > sizeof(servaddr->sun_path))
    {
        printf("Path is too long\n");
        goto end1;
    }
    snprintf(servaddr->sun_path, (strlen(path) + 1), "%s", path);

    if (0 != (bind(sockserver, (struct sockaddr *)servaddr, sizeof(struct sockaddr_un))))
    {
        printf("Unable to bind to the socket path\n");
        goto end1;
    }

    /* Part 3 – make the server socket a passive socket and accept connections from client stations */

    if (-1 == listen(sockserver, 1))
    {
        printf("Listen Failed\n");
        goto end1;
    }
    cliaddr = (struct sockaddr_un *)malloc(sizeof(struct sockaddr_un));
    if (cliaddr == NULL)
    {
        printf("unable to allocate memory\n");
        goto end1;
    }

    printf("waiting for connection\n");
    sockclient = accept(sockserver, (struct sockaddr *)cliaddr, &length);
    if (sockclient < 0)
    {
        printf("unable to accept client connection\n");
        goto end2;
    }

    fcntl(sockclient, F_SETFL, O_NONBLOCK);

    //test code.
    printf("demo close client socket here\n");

    int cnt = 0;
    while (cnt < 3)
    {
        uint64_t ts_us = time_us();
        memcpy(buffer, &ts_us, sizeof(uint64_t));
        write(sockclient, buffer, sizeof(uint64_t));

        sleep(1);
        cnt++;
    }

    printf("send last data and close immediately\n");
    //test EPOLLIN & EPOLLERR
    {
        uint64_t ts_us = time_us();
        memcpy(buffer, &ts_us, sizeof(uint64_t));
        write(sockclient, buffer, sizeof(uint64_t));
    }

    close(sockclient);
    goto end2;

#if 0
    /* read and write data from/to socket */
    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        read(sockclient, buffer, sizeof(buffer));
        printf("%s\n", buffer);

        memset(buffer, 0, sizeof(buffer));
        snprintf(buffer, (strlen(string) + 1), "%s", string);
        write(sockclient, buffer, sizeof(buffer));

        //test:
        write(sockclient, buffer, sizeof(buffer));
        write(sockclient, buffer, sizeof(buffer));
    }
#endif

end3:
    if (sockclient >= 0)
        close(sockclient);
end2:
    free(cliaddr);
end1:
    free(servaddr);
end:
    close(sockserver);
    return 0;
}