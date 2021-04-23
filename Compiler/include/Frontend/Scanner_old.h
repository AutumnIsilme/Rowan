#ifndef SCANNER_H_GUARD
#define SCANNER_H_GUARD

#ifdef __c_plus_plus
extern "C" {
#endif

#include <stdbool.h>

#include <Frontend/Common.h>
#include <Frontend/Error.h>
#include <Frontend/Token.h>

typedef struct Scanner {
    uint32 line_number;
    uint32 column_number;

    const char* start;
    const char* current;
    const char* end;
} Scanner;
Scanner* scanner_init(const char* src, size_t src_size);
Token scanner_next(Scanner* scanner);

TokenType check_keyword(Scanner* scanner, int start, int length, const char* rest, TokenType type);

#ifdef __c_plus_plus
}
#endif

#endif /* SCANNER_H_GUARD */