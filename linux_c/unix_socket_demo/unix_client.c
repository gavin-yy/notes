#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/epoll.h>
#include <fcntl.h> /* Added for the nonblocking socket */

#include "demo_util.h"

/* do not create sockets in tmp directory
* To show a socket example – it is fine.
* creating sockets in tmp directory is a security
* vulnerability */

const char *path= "/tmp/unix_socket.sock";

struct sockaddr_un *servaddr = NULL;
int sockserver;

/* Interrupt_handler so that CTRL +C can be used
* to exit the program */
void interrupt_handler (int signum) {
        close(sockserver);
        free(servaddr);
        printf("socket connection closed\n");
        exit(0);
}

int main () {
        int length;
        char buffer[50];
        char *string = "Hello from client";

        /* signal handler to exit out of while 1 loop */
        signal (SIGINT, interrupt_handler);
        signal (SIGINT, interrupt_handler);

        /* Part 1 – create the socket */
        sockserver = socket(AF_UNIX, SOCK_SEQPACKET, 0);
        if (sockserver < 0) {
               printf("creating client socket failed\n");
               exit(0);
       }
        /* Part 2 – fill the structure and bind to the socket path
        * Remove/unlink any previous socket file creation
        */

        servaddr = (struct sockaddr_un *)malloc(sizeof(struct sockaddr_un));
        if(servaddr == NULL) {
                printf("unable to allocate memory\n");
                goto end;
        }
        servaddr->sun_family = AF_UNIX;

        if ((strlen(path)) > sizeof(servaddr->sun_path)) {
                printf("Path is too long\n");
                goto end1;
        }
        snprintf(servaddr->sun_path, (strlen(path)+1), "%s", path);

        if (0 != (connect(sockserver, (struct sockaddr *)servaddr, sizeof(struct sockaddr_un)))) {
                printf("unable to connect to the server\n");
                goto end1;
        }

        fcntl(sockserver, F_SETFL, O_NONBLOCK);

        demo_init_epoll();
        demo_epoll_add_fd(sockserver, EPOLLIN);
        while(1) {
            int rc = demo_epoll_wait();
            if( rc < 0 ) {
                break;
            }
        }

        #if 0
        /* read and write data from/to socket */
        while (1) {
                memset(buffer, 0, sizeof(buffer));
                snprintf(buffer, (strlen(string)+1), "%s", string);
                write(sockserver, buffer, sizeof(buffer));

                memset(buffer, 0, sizeof(buffer));
                read(sockserver, buffer, sizeof(buffer));
                printf("%s\n", buffer);
        }
        #endif
end1:
        free(servaddr);
end:
        close(sockserver);
        return 0;
}