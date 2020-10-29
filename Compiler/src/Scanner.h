#ifndef LEXER_H_GUARD
#define LEXER_H_GUARD

#ifdef __c_plus_plus
extern "C" {
#endif

#include <stdbool.h>

#include "Types.h"
#include "Error.h"
#include "Token.h"

typedef struct Scanner {
    u32 line_number;
    u32 column_number;

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

#endif /* LEXER_H_GUARD */