#ifndef ERROR_H_GUARD
#define ERROR_H_GUARD

#include "Types.h"

struct Error {
    u32 error_code;
    u32 line_number;
    u32 column_number;
};

#endif /* ERROR_H_GUARD */