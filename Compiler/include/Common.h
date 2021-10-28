#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>
#include <assert.h>

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;
typedef __uint128_t        uint128;

typedef signed char        int8;
typedef signed short       int16;
typedef signed int         int32;
typedef signed long long   int64;
typedef __int128_t         int128;

typedef unsigned int uint;

typedef float float32;
typedef double float64;
typedef long double float128;

static_assert(sizeof(float128) == 16, "'long double' size is not 128 bits!");

#define _COMBINE(x, y) x##y
#define COMBINE(x, y) _COMBINE(x, y)

#define BIT(x) (1<<(x))
#define ROL(x, n) (((x) << (n)) | ((x) >> sizeof(x) - (n)))
#define ROR(x, n) (((x) >> (n)) | ((x) << sizeof(x) - (n)))

uint8 log2_64 (uint64 value);
uint64 fnv_1(const char *data, uint64 length);

#endif /* _COMMON_H */
