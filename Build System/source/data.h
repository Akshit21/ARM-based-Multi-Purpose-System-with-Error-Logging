#ifndef _DATA_H
#define _DATA_H
#include<stdint.h>

int8_t *my_itoa(int8_t * str, int32_t data, int32_t base);
int32_t my_atoi(uint8_t * str);
void dump_memory(uint8_t * start, uint32_t length);
int32_t big_to_little(int32_t data);
int32_t little_to_big(int32_t data);

#endif
