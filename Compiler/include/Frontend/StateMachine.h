#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

#include <Common.h>

enum equiv_class {
    C_WHITE,
    C_CR,
    C_LF,
    C_LETTER,
    C_LITERAL_BASE,
    C_ZERO,
    C_DIGIT,
    C_PLUS,
    C_HYPHEN,
    C_STAR,
    C_SLASH,
    C_LESS,
    C_GREATER,
    C_EQUAL,
    C_AMPERSAND,
    C_PIPE,
    C_COLON,
    C_SEMICOLON,
    C_EQUABLE,
    C_SINGLE_QUOTE,
    C_DOUBLE_QUOTE,
    C_PERIOD,
    C_MISC,
    C_UTF8_1,
    C_ERROR,
    C_EOF,
    LAST_EQUIV_CLASS
};

enum state {
    S_NEWLINE,
    S_CHAR,
    S_STRING,
    S_SINGLE_OP,
    S_DOUBLED_OP,
    S_EQUABLE,
    S_SAW_LETTER,
    S_SAW_NUMBER,
    S_SAW_NUMERIC_LITERAL,
    S_LONE_ZERO,
    S_ARROW,
    S_SINGLE_LINE_COMMENT,
    S_MULTI_LINE_COMMENT,
    S_SHIFT_EQUAL,
    S_ERROR,
    S_EOF,
    START,
    S_SEEN_ZERO,
    S_SEEN_PLUS,
    S_SEEN_HYPHEN,
    S_SEEN_STAR,
    S_SEEN_SLASH,
    S_SEEN_LESS,
    S_SEEN_GREATER,
    S_SEEN_EQUAL,
    S_SEEN_AMPERSAND,
    S_SEEN_PIPE,
    S_SEEN_COLON,
    S_SEEN_EQUABLE,
    S_SEEN_PERIOD,
    S_START_NEWLINE,
    S_LESS_LESS,
    S_GREATER_GREATER,
    LAST_STATE
};

#define LAST_FINAL_STATE S_EOF

const char in_token[LAST_STATE] = {
    /*[S_NEWLINE] =*/ 1, /*[S_CHAR] =*/ 1, /*[S_STRING] =*/ 1, /*[S_SINGLE_OP] =*/ 1, /*[S_DOUBLED_OP] =*/ 1, /*[S_EQUABLE] =*/ 1, /*[S_SAW_LETTER] =*/ 1,
    /*[S_SAW_NUMBER] =*/ 1, /*[S_SAW_NUMERIC_LITERAL] =*/ 1, /*[S_LONE_ZERO] =*/ 1, /*[S_ARROW] =*/ 1, /*[S_SINGLE_LINE_COMMENT] =*/ 1,
    /*[S_MULTI_LINE_COMMENT] =*/ 1, /*[S_SHIFT_EQUAL] =*/ 1, /*[S_ERROR] =*/ 1, /*[S_EOF] =*/ 1, /*[START] =*/ 0, /*[S_SEEN_ZERO] =*/ 1, /*[S_SEEN_PLUS] =*/ 1,
    /*[S_SEEN_HYPHEN] =*/ 1, /*[S_SEEN_STAR] =*/ 1, /*[S_SEEN_SLASH] =*/ 1, /*[S_SEEN_LESS] =*/ 1, /*[S_SEEN_GREATER] =*/ 1, /*[S_SEEN_EQUAL] =*/ 1,
    /*[S_SEEN_AMPERSAND] =*/ 1, /*[S_SEEN_PIPE] =*/ 1, /*[S_SEEN_COLON] =*/ 1, /*[S_SEEN_EQUABLE] =*/ 1, /*[S_SEEN_PERIOD] =*/ 1, /*[S_START_NEWLINE] =*/ 1, /*[S_LESS_LESS] =*/ 1, /*[S_GREATER_GREATER] =*/ 1
};

/*
white:         space, \t
cr:            \r
lf:            \n
first_letter:  #$`
letter:        a-zA-Z_
literal_base:  b B o O x X
zero:          0
digit:         1-9

plus:          +  // ++ +=
hyphen:        -  // -> -- -=
star:          *
slash:         /  // // */ /* /=
less:          <  // << <= <<=
greater:       >  // >> >= >>= ->
equal:         =
ampersand:     &  // && &=
pipe:          |  // || |=
colon:         :  // :: :=
semicolon:     ;
equable:
               ^  // ^=
               !  // !=
               %  // %=

single_quote:  '
double_quote:  "
period:        .
misc:          ~ , ? @ ( ) { } [ ] \

eof:           \0
*/
/*
START:
    whitespace -> START
    letter, literal_base -> S_SAW_LETTER (final)
    zero      -> S_SEEN_ZERO
    digit     -> S_SAW_NUMBER (final)
    plus      -> S_SEEN_PLUS
    hyphen    -> S_SEEN_HYPHEN
    star      -> S_SEEN_STAR
    slash     -> S_SEEN_SLASH
    less      -> S_SEEN_LESS
    greater   -> S_SEEN_GREATER
    equal     -> S_SEEN_EQUAL
    ampersand -> S_SEEN_AMPERSAND
    pipe      -> S_SEEN_PIPE
    equable   -> S_SEEN_EQUABLE
    single_quote -> S_CHAR (final)
    double_quote -> S_STRING (final)
    period    -> S_SEEN_PERIOD
    misc      -> S_SINGLE_OP (final)
    cr        -> S_START_NEWLINE
    lf, semicolon -> S_NEWLINE (final)
    error, utf8_1 -> S_ERROR (final)
    eof       -> S_EOF (final)

S_SEEN_ZERO:
    literal_base -> S_SAW_NUMERIC_LITERAL (final)
    zero, digit, period -> S_SAW_NUMBER (final)
    default -> S_LONE_ZERO (final)

S_SEEN_PLUS:
    plus    -> S_DOUBLED_OP (final)
    equal   -> S_EQUABLE (final)
    default -> S_SINGLE_OP (final)

S_SEEN_HYPHEN:
    hyphen  -> S_DOUBLED_OP (final)
    equal   -> S_EQUABLE (final)
    greater -> S_ARROW (final)
    default -> S_SINGLE_OP (final)

S_SEEN_STAR:
    equal -> S_EQUABLE (final)
    default -> S_SINGLE_OP (final)

S_SEEN_SLASH:
    slash -> S_SINGLE_LINE_COMMENT (final)
    star  -> S_MULTI_LINE_COMMENT (final)
    equal -> S_EQUABLE (final)
    default -> S_SINGLE_OP (final)

S_SEEN_LESS:
    less -> S_LESS_LESS
    equal -> S_EQUABLE (final)
    default -> S_SINGLE_OP (final)

S_LESS_LESS:
    equal -> S_SHIFT_EQUAL (final)
    default -> S_DOUBLED_OP (final)

S_SEEN_GREATER:
    greater -> S_GREATER_GREATER
    equal -> S_EQUABLE (final)
    default -> S_SINGLE_OP (final)

S_GREATER_GREATER:
    equal -> S_SHIFT_EQUAL (final)
    default -> S_DOUBLED_OP (final)

S_SEEN_EQUAL:
    equal -> S_DOUBLED_OP (final)
    default -> S_SINGLE_OP (final)

S_SEEN_AMPERSAND:
    ampersand -> S_DOUBLED_OP (final)
    equal -> S_EQUABLE (final)
    default -> S_SINGLE_OP (final)

S_SEEN_PIPE:
    pipe -> S_DOUBLED_OP (final)
    equal -> S_EQUABLE (final)
    default -> S_SINGLE_OP (final)

S_SEEN_COLON:
    colon -> S_DOUBLED_OP (final)
    equal -> S_EQUABLE (final)
    default -> S_SINGLE_OP (final)

S_SEEN_EQUABLE:
    equal -> S_EQUABLE (final)
    default -> S_SINGLE_OP (final)

S_SEEN_PERIOD:
    period -> S_DOUBLED_OP (final)
    default -> S_SINGLE_OP (final)

S_START_NEWLINE:
    lf -> S_NEWLINE (final)
    default -> S_ERROR (final)
*/

const unsigned char transition[(uint64)LAST_STATE * (uint64)LAST_EQUIV_CLASS] = {
                           /* Final states */                    /* START */         /* S_SEEN_ZERO */       /* S_SEEN_PLUS */   /* S_SEEN_HYPHEN */ /* S_SEEN_STAR */   /* S_SEEN_SLASH */      /* S_SEEN_LESS */   /* S_SEEN_GREATER */    /* S_SEEN_EQUAL */  /* S_SEEN_AMPERSAND */  /* S_SEEN_PIPE */   /* S_SEEN_COLON */    /* S_SEEN_EQUABLE */   /* S_SEEN_PERIOD */    /* S_START_NEWLINE */   /* S_LESS_LESS */   /* S_GREATER_GREATER */
    /* C_WHITE        */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    START,              S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_CR           */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_START_NEWLINE,    S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_LF           */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_NEWLINE,          S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_NEWLINE,              S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_LETTER       */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_LITERAL_BASE */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_SAW_NUMERIC_LITERAL,  S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_ZERO         */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_ZERO,        S_SAW_NUMBER,           S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_DIGIT        */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_NUMBER,       S_SAW_NUMBER,           S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_PLUS         */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_PLUS,        S_LONE_ZERO,            S_DOUBLED_OP,       S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_HYPHEN       */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_HYPHEN,      S_LONE_ZERO,            S_SINGLE_OP,        S_DOUBLED_OP,       S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_STAR         */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_STAR,        S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_MULTI_LINE_COMMENT,   S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_SLASH        */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_SLASH,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_LINE_COMMENT,  S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_LESS         */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_LESS,        S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_LESS_LESS,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_GREATER      */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_GREATER,     S_LONE_ZERO,            S_SINGLE_OP,        S_ARROW,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_GREATER_GREATER,      S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_EQUAL        */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_EQUAL,       S_LONE_ZERO,            S_EQUABLE,          S_EQUABLE,          S_EQUABLE,          S_EQUABLE,              S_EQUABLE,          S_EQUABLE,              S_DOUBLED_OP,       S_EQUABLE,              S_EQUABLE,          S_EQUABLE,            S_EQUABLE,             S_SINGLE_OP,           S_ERROR,                S_SHIFT_EQUAL,      S_SHIFT_EQUAL,
    /* C_AMPERSAND    */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_AMPERSAND,   S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_DOUBLED_OP,           S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_PIPE         */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_PIPE,        S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_DOUBLED_OP,       S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_COLON        */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_COLON,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_DOUBLED_OP,         S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_SEMICOLON    */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_NEWLINE,          S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_EQUABLE      */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_EQUABLE,     S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_SINGLE_QUOTE */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_CHAR,             S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_DOUBLE_QUOTE */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_STRING,           S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_PERIOD       */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SINGLE_OP,        S_SAW_NUMBER,           S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_DOUBLED_OP,          S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_MISC         */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SINGLE_OP,        S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_UTF8_1       */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_ERROR,            S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_ERROR        */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_ERROR,            S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
    /* C_EOF          */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_EOF,              S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,
};

const unsigned short equivalence_class[256] = {
    (uint8)LAST_STATE * (uint8)C_EOF,   // 0
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR, // 2
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_EOF,   // 4
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR, // 8
    (uint8)LAST_STATE * (uint8)C_WHITE,
    (uint8)LAST_STATE * (uint8)C_LF,
    (uint8)LAST_STATE * (uint8)C_WHITE,
    (uint8)LAST_STATE * (uint8)C_WHITE, // C
    (uint8)LAST_STATE * (uint8)C_CR,
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR, // 10
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR, // 14
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR, // 18
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR, // 1C
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_WHITE, // 20
    (uint8)LAST_STATE * (uint8)C_EQUABLE,
    (uint8)LAST_STATE * (uint8)C_DOUBLE_QUOTE,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER, // 24
    (uint8)LAST_STATE * (uint8)C_EQUABLE,
    (uint8)LAST_STATE * (uint8)C_AMPERSAND,
    (uint8)LAST_STATE * (uint8)C_SINGLE_QUOTE,
    (uint8)LAST_STATE * (uint8)C_MISC, // 28
    (uint8)LAST_STATE * (uint8)C_MISC,
    (uint8)LAST_STATE * (uint8)C_STAR,
    (uint8)LAST_STATE * (uint8)C_PLUS,
    (uint8)LAST_STATE * (uint8)C_MISC, // 2C
    (uint8)LAST_STATE * (uint8)C_HYPHEN,
    (uint8)LAST_STATE * (uint8)C_PERIOD,
    (uint8)LAST_STATE * (uint8)C_SLASH,
    (uint8)LAST_STATE * (uint8)C_ZERO, // 30
    (uint8)LAST_STATE * (uint8)C_DIGIT,
    (uint8)LAST_STATE * (uint8)C_DIGIT,
    (uint8)LAST_STATE * (uint8)C_DIGIT,
    (uint8)LAST_STATE * (uint8)C_DIGIT, // 34
    (uint8)LAST_STATE * (uint8)C_DIGIT,
    (uint8)LAST_STATE * (uint8)C_DIGIT,
    (uint8)LAST_STATE * (uint8)C_DIGIT,
    (uint8)LAST_STATE * (uint8)C_DIGIT, // 38
    (uint8)LAST_STATE * (uint8)C_DIGIT,
    (uint8)LAST_STATE * (uint8)C_COLON,
    (uint8)LAST_STATE * (uint8)C_SEMICOLON,
    (uint8)LAST_STATE * (uint8)C_LESS, // 3C
    (uint8)LAST_STATE * (uint8)C_EQUAL,
    (uint8)LAST_STATE * (uint8)C_GREATER,
    (uint8)LAST_STATE * (uint8)C_MISC,
    (uint8)LAST_STATE * (uint8)C_MISC, // 40
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LITERAL_BASE,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LITERAL_BASE,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LITERAL_BASE,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_MISC,
    (uint8)LAST_STATE * (uint8)C_MISC,
    (uint8)LAST_STATE * (uint8)C_MISC,
    (uint8)LAST_STATE * (uint8)C_EQUABLE,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LITERAL_BASE,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LITERAL_BASE,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LITERAL_BASE,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_MISC,
    (uint8)LAST_STATE * (uint8)C_PIPE,
    (uint8)LAST_STATE * (uint8)C_MISC,
    (uint8)LAST_STATE * (uint8)C_MISC,
    (uint8)LAST_STATE * (uint8)C_ERROR,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
    (uint8)LAST_STATE * (uint8)C_UTF8_1,
};

#endif /* _STATE_MACHINE_H */