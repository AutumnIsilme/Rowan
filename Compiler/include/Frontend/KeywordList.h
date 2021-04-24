#ifndef KEYWORD_LIST_H_GUARD
#define KEYWORD_LIST_H_GUARD

#include <Frontend/Common.h>
#include <Frontend/Token.h>

#define KEYWORD_LIST_LEN 19

const char *KEYWORD_LIST[KEYWORD_LIST_LEN] = {
    "if",
    "else",
    "for",
    "while",
    "break",
    "continue",
    "return",
    "switch",
    "case",
    "include",
    "import",
    "using",
    "cast",
    "struct",
    "enum",
    "union",
    "soa",
    "true",
    "false",
};

const uint8 KEYWORD_LEN[KEYWORD_LIST_LEN] = {
    2, 3, 5, 6, 5, 8, 6, 4, 7, 5, 4, 6, 4, 5, 3, 4, 5,
};

const TokenType KEYWORD_TYPE[128] = {
    TT_IDENT, TT_CASE,  TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT,    TT_RETURN, TT_IDENT, TT_IDENT,  TT_IDENT,   TT_IF,    TT_IDENT,
    TT_IDENT, TT_IDENT, TT_FOR,   TT_IDENT, TT_CAST,  TT_IDENT,    TT_IDENT,  TT_IDENT, TT_IDENT,  TT_IDENT,   TT_IDENT, TT_IDENT,
    TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT,    TT_IDENT,  TT_IDENT, TT_IDENT,  TT_IDENT,   TT_IDENT, TT_IDENT,
    TT_IDENT, TT_WHILE, TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT,    TT_IDENT,  TT_IDENT, TT_IDENT,  TT_IDENT,   TT_IDENT, TT_IDENT,
    TT_IDENT, TT_FALSE, TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT,    TT_IDENT,  TT_IDENT, TT_IDENT,  TT_IDENT,   TT_UNION, TT_IDENT,
    TT_IDENT, TT_IDENT, TT_IDENT, TT_BREAK, TT_IDENT, TT_IDENT,    TT_IDENT,  TT_IDENT, TT_IDENT,  TT_INCLUDE, TT_IDENT, TT_IDENT,
    TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT, TT_SOA,      TT_IDENT,  TT_IDENT, TT_STRUCT, TT_IDENT,   TT_IDENT, TT_IDENT,
    TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT, TT_CONTINUE, TT_TRUE,   TT_IDENT, TT_IDENT,  TT_IDENT,   TT_IDENT, TT_IDENT,
    TT_IDENT, TT_ENUM,  TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT,    TT_IDENT,  TT_IDENT, TT_IDENT,  TT_IDENT,   TT_IDENT, TT_IDENT,
    TT_IDENT, TT_IDENT, TT_IDENT, TT_USING, TT_IDENT, TT_IDENT,    TT_IDENT,  TT_IDENT, TT_SWITCH, TT_IDENT,   TT_IDENT, TT_IDENT,
    TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT, TT_IDENT,    TT_IDENT,  TT_IDENT
};

const uint64 KEYWORD_HASHES[128] = {
    0, 8449, 0, 0, 0, 0, 152454, 0, 0, 0, 552, 0, 0, 0, 2190, 0, 8464, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 39333, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 34609, 0, 0, 0, 0, 0, 0, 0, 0, 39226, 0, 0, 0, 0, 34495, 0, 0, 0, 0, 0, 577349,
    0, 0, 0, 0, 0, 0, 0, 2381, 0, 0, 157136, 0, 0, 0, 0, 0, 0, 0, 0, 2228057, 9817, 0, 0, 0, 0, 0, 0, 8801, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 39535, 0, 0, 0, 0, 157300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#endif /* KEYWORD_LIST_H_GUARD */
