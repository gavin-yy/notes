#ifndef COMMON_HDR_H
#define COMMON_HDR_H

#include <stdint.h>

int start_485_test();

int local_publish(char *topic, char *data, int len);

int send_data_by_485(uint8_t *data, int size);

int cmd_execl(const char * cmdstring);

#endif
