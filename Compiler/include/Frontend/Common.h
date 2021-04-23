#ifndef _COMMON_H
#define _COMMON_H

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

typedef signed char        int8;
typedef signed short       int16;
typedef signed int         int32;
typedef signed long long   int64;

typedef unsigned int uint;

#define _COMBINE(x, y) x##y
#define COMBINE(x, y) _COMBINE(x, y)

#define ROL(t, x) ((t << x) | (t >> (sizeof(t) * 8 - x)))

#define alignof(type) ((size_t)&((struct { char c; type d; } *)0)->d)

uint8 log2_64 (uint64 value);

#endif /* _COMMON_H */
