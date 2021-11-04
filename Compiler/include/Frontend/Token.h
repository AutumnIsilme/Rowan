#ifndef TOKEN_H_GUARD
#define TOKEN_H_GUARD

#include <Common.h>

//__attribute__((__packed__))
typedef enum _TokenKind : uint8 {
    /* Keywords */
    TT_BREAK = 0,
    TT_CASE,
    TT_CAST,
    TT_CONTINUE,
    TT_ELSE,
    TT_ENUM,
    TT_FOR,
    TT_IF,
    TT_IMPORT,
    TT_INCLUDE,
    TT_RETURN,
    TT_STRUCT,
    TT_SWITCH,
    TT_UNION,
    TT_USING,
    TT_WHILE,
    // TT_SOA,

    // I, F, E, L, S, O, R, W, H, T, U, N, B, K, C, A, M, P
    // G
    // abcdefghi klmnop rstu w
    // abcdefghijklmnopqrstuvwxyz

    // break
    // continue case cast
    // else enum
    // for
    // if include import
    // return
    // switch struct
    // using union
    // while

    // i, e, f, w, r, b, c, s, u, e
    // if, in, im, el, en, fo, wh, re, br, co, ca, sw, st,
    // us, un
    // inc, imp, els, enu

    //TT_TRUE,
    //TT_FALSE,

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

    TT_DOT_DOT,      /* .. */
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
} TokenKind;

static const char* token_type_names[TT_NONE + 1] = {
    "TT_BREAK",
    "TT_CASE",
    "TT_CAST",
    "TT_CONTINUE",
    "TT_ELSE",
    "TT_ENUM",
    "TT_FOR",
    "TT_IF",
    "TT_IMPORT",
    "TT_INCLUDE",
    "TT_RETURN",
    "TT_STRUCT",
    "TT_SWITCH",
    "TT_UNION",
    "TT_USING",
    "TT_WHILE",
    //"TT_SOA",

    //"TT_TRUE",
    //"TT_FALSE",

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

    "TT_DOT_DOT",
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