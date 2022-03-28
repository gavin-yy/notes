#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t time_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    uint64_t ts = tv.tv_sec*1000*1000;
    ts += tv.tv_usec;

    return ts;
    // printf("gettimeofday UTC:%lu\n", tv.tv_sec);
}