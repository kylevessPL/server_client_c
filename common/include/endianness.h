#ifndef ENDIANNESS_H
#define ENDIANNESS_H

#include <stdint.h>

#define IS_BIG_ENDIAN (((union { unsigned x; unsigned char c; }){1}).c)

uint64_t htond(double hostdouble);
double ntohd(uint64_t netdouble);

#endif //ENDIANNESS_H
