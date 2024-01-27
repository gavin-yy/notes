#ifndef GPIO_H
#define GPIO_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

#define err_out(fmt, ...)                                                       \
    do                                                                          \
    {                                                                           \
        printf(fmt, ##__VA_ARGS__);                                             \
        printf("<%s>  \"%s()\" %d error\n", __FILE__, __FUNCTION__, __LINE__);  \
    } while (0)

#define open_gpio_file(path, flag, fd)                                          \
    do                                                                          \
    {                                                                           \
        fd = open(path, flag);                                                  \
        if (fd < 0)                                                             \
        {                                                                       \
            err_out("\"%s\" open failed \n", path);                             \
            return (-1);                                                        \
        }                                                                       \
    } while (0);

extern int gpio_export(const int pin);
extern int gpio_unexport(const int pin);
extern int gpio_direction(const int pin, const char *dir);
extern int gpio_write(const int pin, const int value);
extern int gpio_read(const int pin);
extern int gpio_edge(const int pin, int edge);

#endif