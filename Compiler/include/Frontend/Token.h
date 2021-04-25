#ifndef TOKEN_H_GUARD
#define TOKEN_H_GUARD

#include <Common.h>

typedef enum __attribute__((__packed__)) _TokenType {
    /* Keywords */
    TT_IF = 0,
    TT_ELSE,
    TT_FOR,
    TT_WHILE,
    TT_RETURN,
    TT_BREAK,
    TT_CONTINUE,
    TT_SWITCH,
    TT_CASE,
    TT_INCLUDE,
    TT_IMPORT,
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

    TT_PLUS_PLUS,    /* ++ */
    TT_PLUS_EQUAL,  /* += */
    TT_PLUS,         /* + */

    TT_MINUS_MINUS,  /* -- */
    TT_MINUS_EQUAL, /* -= */
    TT_ARROW,        /* -> */
    TT_MINUS,        /* - */

    TT_SLASH_EQUAL,  /* /= */
    TT_SLASH,        /* / */

    // TT_STAR_STAR,    /* ** */
    TT_STAR_EQUAL,   /* *= */
    TT_STAR,         /* * */

    TT_EXCL_EQUAL,   /* != */
    TT_EXCL,         /* ! */

    TT_EQUAL_EQUAL,  /* == */
    TT_EQUAL,        /* = */

    TT_PERCENT_EQUAL,/* %= */
    TT_PERCENT,      /* % */

    TT_CARET_EQUAL,  /* ^= */
    TT_CARET,        /* ^ */

    TT_AMPERSAND_AMPERSAND, /* && */
    TT_AMPERSAND_EQUAL,     /* &= */
    TT_AMPERSAND,           /* & */

    TT_PIPE_PIPE,    /* || */
    TT_PIPE_EQUAL,   /* |= */
    TT_PIPE,         /* | */

    TT_LESS_LESS,        /* << */
    TT_LESS_LESS_EQUAL,  /* <<= */
    TT_LESS_EQUAL,     /* <= */
    TT_LESS,           /* < */

    TT_GREATER_GREATER,        /* >> */
    TT_GREATER_GREATER_EQUAL,  /* >>= */
    TT_GREATER_EQUAL,     /* >= */
    TT_GREATER,           /* > */

    TT_COMMA,        /* , */

    TT_DOT,          /* . */

    TT_COLON_EQUAL, /* := */
    TT_COLON_COLON, /* :: */
    TT_COLON,       /* : */
    TT_SEMICOLON,   /* ; */

    TT_TILDE,     /* ~ */
    TT_HASH,      /* # */
    TT_DOLLAR,    /* $ */
    TT_AT,        /* @ */
    TT_QUESTION,  /* ? */
    TT_BACKSLASH, /* \ */

    /* Other token types*/
    TT_IDENT,
    TT_INT,
    TT_HEX_LITERAL,
    TT_OCTAL_LITERAL,
    TT_BINARY_LITERAL,
    TT_FLOAT,
    TT_STRING,
    TT_CHAR,

    TT_NEWLINE,
    TT_EOF,

    TT_NONE
} TokenType;

static const char* token_type_names[TT_NONE + 1] = {
    "TT_IF",
    "TT_ELSE",
    "TT_FOR",
    "TT_WHILE",
    "TT_RETURN",
    "TT_BREAK",
    "TT_CONTINUE",
    "TT_SWITCH",
    "TT_CASE",
    "TT_INCLUDE",
    "TT_IMPORT",
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
    "TT_PLUS_EQUALS",
    "TT_PLUS",

    "TT_MINUS_MINUS",
    "TT_MINUS_EQUALS",
    "TT_ARROW",
    "TT_MINUS",

    "TT_SLASH_EQUAL",
    "TT_SLASH",

    "TT_STAR_EQUAL",
    "TT_STAR",

    "TT_EXCL_EQUAL",
    "TT_EXCL",

    "TT_EQUAL_EQUAL",
    "TT_EQUAL",

    "TT_PERCENT_EQUAL",
    "TT_PERCENT",

    "TT_CARET_EQUAL",
    "TT_CARET",

    "TT_AMPERSAND_AMPERSAND",
    "TT_AMPERSAND_EQUAL",
    "TT_AMPERSAND",

    "TT_PIPE_PIPE",
    "TT_PIPE_EQUAL",
    "TT_PIPE",

    "TT_LESS_LESS",
    "TT_LESS_LESS_EQUAL",
    "TT_LESS_EQUAL",
    "TT_LESS",

    "TT_GREATER_GREATER",
    "TT_GREATER_GREATER_EQUAL",
    "TT_GREATER_EQUAL",
    "TT_GREATER",

    "TT_COMMA",

    "TT_DOT",

    "TT_COLON_EQUALS",
    "TT_COLON_COLON",
    "TT_COLON",
    "TT_SEMICOLON",

    "TT_TILDE",
    "TT_HASH",
    "TT_DOLLAR",
    "TT_AT",
    "TT_QUESTION",
    "TT_BACKSLASH",

    "TT_IDENT",
    "TT_INT",
    "TT_HEX_LITERAL",
    "TT_OCTAL_LITERAL",
    "TT_BINARY_LITERAL",
    "TT_FLOAT",
    "TT_STRING",
    "TT_CHAR",

    "TT_NEWLINE",
    "TT_EOF",

    "TT_NONE"
};

#endif /* TOKEN_H_GUARD */