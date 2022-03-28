#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/epoll.h>
#include <errno.h>
#include "demo_util.h"

#define FDSIZE  512

static int epoll_fds;

int demo_init_epoll()
{
    epoll_fds = epoll_create(FDSIZE);
}

void demo_epoll_add_fd(int fd, int event_type)
{
    struct epoll_event ev;
    ev.events = event_type;
    ev.data.fd = fd;

    if (epoll_ctl(epoll_fds, EPOLL_CTL_ADD, fd, &ev) < 0) {
        printf("Add event failed!\n");
    }
}

void demo_delete_event(int fd, int state) {
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    if (epoll_ctl(epoll_fds, EPOLL_CTL_DEL, fd, &ev) < 0) {
        printf("Delete event failed!\n");
    }
}

#define MAX_EVENT_CNT 10
int demo_epoll_wait()
{
    struct epoll_event events[MAX_EVENT_CNT];

    int ready_cnt = epoll_wait(epoll_fds, events, MAX_EVENT_CNT, 5);
    for(int i=0; i<ready_cnt; i++) {
        printf("Get event [%d]: fd=%d ", i, events[i].data.fd);

        if( events[i].events & EPOLLIN) {
            printf(" EPOLLIN\n");
            unsigned char buf[100];
            int rc = read(events[i].data.fd, buf, 100);
            if( rc > 0 ) {
                uint64_t tick_us = *(uint64_t *)buf;
                uint64_t now = time_us();

                printf("\tread %d cnt, schedule delay:%llu us \n", rc, now - tick_us);
            } else {
                printf("\t read rc=%d error:%s ", rc, strerror(errno));
                demo_delete_event(events[i].data.fd, EPOLLIN | EPOLLOUT);

                close(events[i].data.fd);
                return -1;
            }
        }

        if( events[i].events & EPOLLERR) {
            printf("get EPOLLERR\n");
        }

        if( events[i].events & EPOLLHUP) {
            printf("get EPOLLHUP\n");
        }

        if( events[i].events & EPOLLOUT) {
            printf(" EPOLLOUT\n");
        }
    }
}

