#ifndef TOKEN_H_GUARD
#define TOKEN_H_GUARD

#include <string>

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
    TT_RPAREN,
    TT_LSQUARE,
    TT_RSQUARE,
    TT_LCURLY,
    TT_RCURLY,

    TT_PLUS_PLUS,
    TT_PLUS_EQUALS,
    TT_PLUS,

    TT_MINUS_MINUS,
    TT_MINUS_EQUALS,
    TT_MINUS,

    TT_SLASH,

    TT_STAR_STAR,
    TT_STAR,

    TT_EXCL_EQUAL,
    TT_EXCL,

    TT_EQUAL_EQUAL,
    TT_EQUAL,

    TT_PERCENT,
    TT_CARET,

    TT_AMPERSAND_AMPERSAND,
    TT_AMPERSAND,

    TT_PIPE_PIPE,
    TT_PIPE,

    TT_LT_EQUAL,
    TT_LT_LT,
    TT_LT,

    TT_GT_EQUAL,
    TT_GT_GT,
    TT_GT,

    TT_COMMA,

    TT_DOT,

    TT_COLON_EQUALS,
    TT_COLON_COLON,
    TT_COLON,

    /* Other token types*/
    TT_IDENT,
    TT_INT,
    TT_FLOAT,
    TT_STRING,
    TT_CHAR,
};

struct Token {
    TokenType type;
    u32 line_number;
    u32 column_number;
    std::string contents;

    Token(TokenType type, u32 line_number, u32 column_number, const std::string& contents)
        : type(type), line_number(line_number), column_number(column_number), contents(contents) {}
};

#endif /* TOKEN_H_GUARD */