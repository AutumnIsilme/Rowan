#ifndef TOKEN_H_GUARD
#define TOKEN_H_GUARD

#include "types.h"

enum TokenType : u16 {
    /* Keywords */
    TT_IF = 0,
    TT_FOR,
    TT_WHILE,
    TT_RETURN,
    TT_BREAK,
    TT_CONTINUE,
    TT_SWITCH,
    TT_CASE,
    TT_INCLUDE,
    TT_USING,
    TT_CAST,
    TT_STRUCT,
    TT_ENUM,
    TT_UNION,
    TT_SOA,

    TT_TRUE,
    TT_FALSE,

    /* Operators and symbols*/
    TT_LPAREN,

    /* Other token types*/
    TT_IDENT,
    TT_INT,
    TT_FLOAT,
    TT_STRING
};

struct Token {
    TokenType type;
    u32 symbol_table_entry;
    u32 line_number;
    u32 column_number;

    Token(TokenType type, u32 symbol_table_entry = 0)
        : type(type), symbol_table_entry(symbol_table_entry) {}
};

#endif /* TOKEN_H_GUARD */