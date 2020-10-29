#ifndef TOKEN_H_GUARD
#define TOKEN_H_GUARD

#include <malloc/_malloc.h>

#include "Types.h"

typedef enum _TokenType {
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
    //TT_PLUS_EQUALS,
    TT_PLUS,

    TT_MINUS_MINUS,
    //TT_MINUS_EQUALS,
    TT_MINUS_GT,
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
    TT_SEMICOLON,

    /* Other token types*/
    TT_IDENT,
    TT_INT,
    TT_FLOAT,
    TT_STRING,
    TT_CHAR,

    TT_EOF
} TokenType;

typedef struct Token {
    TokenType type;
    u32 line_number;
    u32 column_number;
    const char* token;
    u64 length;
} Token;

Token *token_create(TokenType type, u32 line_number, u32 column_number, const char *token, u64 length);

/*
Token(TokenType type, u32 line_number, u32 column_number, const char* token, u32 length)
   : type(type), line_number(line_number), column_number(column_number), token(token), length(length) {}*/

static const char* token_type_names[59] = {
    "TT_IF",
    "TT_FOR",
    "TT_WHILE",
    "TT_RETURN",
    "TT_BREAK",
    "TT_CONTINUE",
    "TT_SWITCH",
    "TT_CASE",
    "TT_INCLUDE",
    "TT_USING",
    "TT_CAST",
    "TT_STRUCT",
    "TT_ENUM",
    "TT_UNION",
    "TT_SOA",
    "TT_TRUE",
    "TT_FALSE",
    "TT_LPAREN",
    "TT_RPAREN",
    "TT_LSQUARE",
    "TT_RSQUARE",
    "TT_LCURLY",
    "TT_RCURLY",
    "TT_PLUS_PLUS",
    //"TT_PLUS_EQUALS",
    "TT_PLUS",
    "TT_MINUS_MINUS",
    //"TT_MINUS_EQUALS",
    "TT_MINUS_GT",
    "TT_MINUS",
    "TT_SLASH",
    "TT_STAR_STAR",
    "TT_STAR",
    "TT_EXCL_EQUAL",
    "TT_EXCL",
    "TT_EQUAL_EQUAL",
    "TT_EQUAL",
    "TT_PERCENT",
    "TT_CARET",
    "TT_AMPERSAND_AMPERSAND",
    "TT_AMPERSAND",
    "TT_PIPE_PIPE",
    "TT_PIPE",
    "TT_LT_EQUAL",
    "TT_LT_LT",
    "TT_LT",
    "TT_GT_EQUAL",
    "TT_GT_GT",
    "TT_GT",
    "TT_COMMA",
    "TT_DOT",
    "TT_COLON_EQUALS",
    "TT_COLON_COLON",
    "TT_COLON",
    "TT_SEMICOLON",
    "TT_IDENT",
    "TT_INT",
    "TT_FLOAT",
    "TT_STRING",
    "TT_CHAR",

    "TT_EOF"
};

#endif /* TOKEN_H_GUARD */