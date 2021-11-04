#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

#include <Common.h>

enum equiv_class {
    C_WHITE,
    C_CR,
    C_LF,
    C_LETTER,
    C_LETTER_A,
    C_LETTER_B,
    C_LETTER_C,
    C_LETTER_D,
    C_LETTER_E,
    C_LETTER_F,
    C_LETTER_G,
    C_LETTER_H,
    C_LETTER_I,
    C_LETTER_K,
    C_LETTER_L,
    C_LETTER_M,
    C_LETTER_N,
    C_LETTER_O,
    C_LETTER_P,
    C_LETTER_R,
    C_LETTER_S,
    C_LETTER_T,
    C_LETTER_U,
    C_LETTER_W,
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
    S_KEYW_BREAK_COMP,
    S_KEYW_CASE_COMP,
    S_KEYW_CAST_COMP,
    S_KEYW_CONTINUE_COMP,
    S_KEYW_ELSE_COMP,
    S_KEYW_ENUM_COMP,
    S_KEYW_FOR_COMP,
    S_KEYW_IF_COMP,
    S_KEYW_IMPORT_COMP,
    S_KEYW_INCLUDE_COMP,
    S_KEYW_RETURN_COMP,
    S_KEYW_STRUCT_COMP,
    S_KEYW_SWITCH_COMP,
    S_KEYW_UNION_COMP,
    S_KEYW_USING_COMP,
    S_KEYW_WHILE_COMP,
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
    S_KEYW_B,
    S_KEYW_BR,
    S_KEYW_BRE,
    S_KEYW_BREA,
    S_KEYW_BREAK,
    S_KEYW_C,
    S_KEYW_CA,
    S_KEYW_CAS,
    S_KEYW_CASE,
    S_KEYW_CAST,
    S_KEYW_CO,
    S_KEYW_CON,
    S_KEYW_CONT,
    S_KEYW_CONTI,
    S_KEYW_CONTIN,
    S_KEYW_CONTINU,
    S_KEYW_CONTINUE,
    S_KEYW_E,
    S_KEYW_EL,
    S_KEYW_ELS,
    S_KEYW_ELSE,
    S_KEYW_EN,
    S_KEYW_ENU,
    S_KEYW_ENUM,
    S_KEYW_F,
    S_KEYW_FO,
    S_KEYW_FOR,
    S_KEYW_I,
    S_KEYW_IF,
    S_KEYW_IM,
    S_KEYW_IMP,
    S_KEYW_IMPO,
    S_KEYW_IMPOR,
    S_KEYW_IMPORT,
    S_KEYW_IN,
    S_KEYW_INC,
    S_KEYW_INCL,
    S_KEYW_INCLU,
    S_KEYW_INCLUD,
    S_KEYW_INCLUDE,
    S_KEYW_R,
    S_KEYW_RE,
    S_KEYW_RET,
    S_KEYW_RETU,
    S_KEYW_RETUR,
    S_KEYW_RETURN,
    S_KEYW_S,
    S_KEYW_ST,
    S_KEYW_STR,
    S_KEYW_STRU,
    S_KEYW_STRUC,
    S_KEYW_STRUCT,
    S_KEYW_SW,
    S_KEYW_SWI,
    S_KEYW_SWIT,
    S_KEYW_SWITC,
    S_KEYW_SWITCH,
    S_KEYW_U,
    S_KEYW_UN,
    S_KEYW_UNI,
    S_KEYW_UNIO,
    S_KEYW_UNION,
    S_KEYW_US,
    S_KEYW_USI,
    S_KEYW_USIN,
    S_KEYW_USING,
    S_KEYW_W,
    S_KEYW_WH,
    S_KEYW_WHI,
    S_KEYW_WHIL,
    S_KEYW_WHILE,
    LAST_STATE
};

#define LAST_FINAL_STATE S_EOF

const char in_token[LAST_STATE] = {
    1 /* S_NEWLINE */,
    1 /* S_CHAR */,
    1 /* S_STRING */,
    1 /* S_SINGLE_OP */,
    1 /* S_DOUBLED_OP */,
    1 /* S_EQUABLE */,
    1 /* S_SAW_LETTER */,
    1 /* S_SAW_NUMBER */,
    1 /* S_SAW_NUMERIC_LITERAL */,
    1 /* S_LONE_ZERO */,
    1 /* S_ARROW */,
    1 /* S_SINGLE_LINE_COMMENT */,
    1 /* S_MULTI_LINE_COMMENT */,
    1 /* S_SHIFT_EQUAL */,
    1 /* S_ERROR */,
    1 /* S_KEYW_BREAK_COMP */,
    1 /* S_KEYW_CASE_COMP */,
    1 /* S_KEYW_CAST_COMP */,
    1 /* S_KEYW_CONTINUE_COMP */,
    1 /* S_KEYW_ELSE_COMP */,
    1 /* S_KEYW_ENUM_COMP */,
    1 /* S_KEYW_FOR_COMP */,
    1 /* S_KEYW_IF_COMP */,
    1 /* S_KEYW_IMPORT_COMP */,
    1 /* S_KEYW_INCLUDE_COMP */,
    1 /* S_KEYW_RETURN_COMP */,
    1 /* S_KEYW_STRUCT_COMP */,
    1 /* S_KEYW_SWITCH_COMP */,
    1 /* S_KEYW_UNION_COMP */,
    1 /* S_KEYW_USING_COMP */,
    1 /* S_KEYW_WHILE_COMP */,
    1 /* S_EOF */,
    0 /* START */,
    1 /* S_SEEN_ZERO */,
    1 /* S_SEEN_PLUS */,
    1 /* S_SEEN_HYPHEN */,
    1 /* S_SEEN_STAR */,
    1 /* S_SEEN_SLASH */,
    1 /* S_SEEN_LESS */,
    1 /* S_SEEN_GREATER */,
    1 /* S_SEEN_EQUAL */,
    1 /* S_SEEN_AMPERSAND */,
    1 /* S_SEEN_PIPE */,
    1 /* S_SEEN_COLON */,
    1 /* S_SEEN_EQUABLE */,
    1 /* S_SEEN_PERIOD */,
    1 /* S_START_NEWLINE */,
    1 /* S_LESS_LESS */,
    1 /* S_GREATER_GREATER */,
    1 /* S_KEYW_B */,
    1 /* S_KEYW_BR */,
    1 /* S_KEYW_BRE */,
    1 /* S_KEYW_BREA */,
    1 /* S_KEYW_BREAK */,
    1 /* S_KEYW_C */,
    1 /* S_KEYW_CA */,
    1 /* S_KEYW_CAS */,
    1 /* S_KEYW_CASE */,
    1 /* S_KEYW_CAST */,
    1 /* S_KEYW_CO */,
    1 /* S_KEYW_CON */,
    1 /* S_KEYW_CONT */,
    1 /* S_KEYW_CONTI */,
    1 /* S_KEYW_CONTIN */,
    1 /* S_KEYW_CONTINU */,
    1 /* S_KEYW_CONTINUE */,
    1 /* S_KEYW_E */,
    1 /* S_KEYW_EL */,
    1 /* S_KEYW_ELS */,
    1 /* S_KEYW_ELSE */,
    1 /* S_KEYW_EN */,
    1 /* S_KEYW_ENU */,
    1 /* S_KEYW_ENUM */,
    1 /* S_KEYW_F */,
    1 /* S_KEYW_FO */,
    1 /* S_KEYW_FOR */,
    1 /* S_KEYW_I */,
    1 /* S_KEYW_IF */,
    1 /* S_KEYW_IM */,
    1 /* S_KEYW_IMP */,
    1 /* S_KEYW_IMPO */,
    1 /* S_KEYW_IMPOR */,
    1 /* S_KEYW_IMPORT */,
    1 /* S_KEYW_IN */,
    1 /* S_KEYW_INC */,
    1 /* S_KEYW_INCL */,
    1 /* S_KEYW_INCLU */,
    1 /* S_KEYW_INCLUD */,
    1 /* S_KEYW_INCLUDE */,
    1 /* S_KEYW_R */,
    1 /* S_KEYW_RE */,
    1 /* S_KEYW_RET */,
    1 /* S_KEYW_RETU */,
    1 /* S_KEYW_RETUR */,
    1 /* S_KEYW_RETURN */,
    1 /* S_KEYW_S */,
    1 /* S_KEYW_ST */,
    1 /* S_KEYW_STR */,
    1 /* S_KEYW_STRU */,
    1 /* S_KEYW_STRUC */,
    1 /* S_KEYW_STRUCT */,
    1 /* S_KEYW_SW */,
    1 /* S_KEYW_SWI */,
    1 /* S_KEYW_SWIT */,
    1 /* S_KEYW_SWITC */,
    1 /* S_KEYW_SWITCH */,
    1 /* S_KEYW_U */,
    1 /* S_KEYW_UN */,
    1 /* S_KEYW_UNI */,
    1 /* S_KEYW_UNIO */,
    1 /* S_KEYW_UNION */,
    1 /* S_KEYW_US */,
    1 /* S_KEYW_USI */,
    1 /* S_KEYW_USIN */,
    1 /* S_KEYW_USING */,
    1 /* S_KEYW_W */,
    1 /* S_KEYW_WH */,
    1 /* S_KEYW_WHI */,
    1 /* S_KEYW_WHIL */,
    1 /* S_KEYW_WHILE */,
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
                           /* Final states */                                                  /* START */         /* S_SEEN_ZERO */       /* S_SEEN_PLUS */   /* S_SEEN_HYPHEN */ /* S_SEEN_STAR */   /* S_SEEN_SLASH */      /* S_SEEN_LESS */   /* S_SEEN_GREATER */    /* S_SEEN_EQUAL */  /* S_SEEN_AMPERSAND */  /* S_SEEN_PIPE */   /* S_SEEN_COLON */    /* S_SEEN_EQUABLE */   /* S_SEEN_PERIOD */    /* S_START_NEWLINE */   /* S_LESS_LESS */   /* S_GREATER_GREATER */  /* S_KEYW_B   */   /* S_KEYW_BR   */   /* S_KEYW_BRE   */   /* S_KEYW_BREA   */   /* S_KEYW_BREAK   */   /* S_KEYW_C   */   /* S_KEYW_CA   */   /* S_KEYW_CAS   */   /* S_KEYW_CASE   */   /* S_KEYW_CAST   */   /* S_KEYW_CO   */   /* S_KEYW_CON   */   /* S_KEYW_CONT   */   /* S_KEYW_CONTI   */   /* S_KEYW_CONTIN   */   /* S_KEYW_CONTINU   */   /* S_KEYW_CONTINUE   */   /* S_KEYW_E   */   /* S_KEYW_EL   */   /* S_KEYW_ELS   */   /* S_KEYW_ELSE   */   /* S_KEYW_EN   */   /* S_KEYW_ENU   */   /* S_KEYW_ENUM   */   /* S_KEYW_F   */   /* S_KEYW_FO   */   /* S_KEYW_FOR   */   /* S_KEYW_I   */   /* S_KEYW_IF   */   /* S_KEYW_IM   */   /* S_KEYW_IMP   */   /* S_KEYW_IMPO   */   /* S_KEYW_IMPOR   */   /* S_KEYW_IMPORT   */   /* S_KEYW_IN   */   /* S_KEYW_INC   */   /* S_KEYW_INCL   */   /* S_KEYW_INCLU   */   /* S_KEYW_INCLUD   */   /* S_KEYW_INCLUDE   */   /* S_KEYW_R   */   /* S_KEYW_RE   */   /* S_KEYW_RET   */   /* S_KEYW_RETU   */   /* S_KEYW_RETUR   */   /* S_KEYW_RETURN   */   /* S_KEYW_S   */   /* S_KEYW_ST   */   /* S_KEYW_STR   */   /* S_KEYW_STRU   */   /* S_KEYW_STRUC   */   /* S_KEYW_STRUCT   */   /* S_KEYW_SW   */   /* S_KEYW_SWI   */   /* S_KEYW_SWIT   */   /* S_KEYW_SWITC   */   /* S_KEYW_SWITCH   */   /* S_KEYW_U   */   /* S_KEYW_UN   */   /* S_KEYW_UNI   */   /* S_KEYW_UNIO   */   /* S_KEYW_UNION   */   /* S_KEYW_US   */   /* S_KEYW_USI   */   /* S_KEYW_USIN   */   /* S_KEYW_USING   */   /* S_KEYW_W   */   /* S_KEYW_WH   */   /* S_KEYW_WHI   */   /* S_KEYW_WHIL   */   /* S_KEYW_WHILE   */
    /* C_WHITE        */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    START,              S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_CR           */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_START_NEWLINE,    S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_LF           */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_NEWLINE,          S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_NEWLINE,              S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_LETTER       */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_A     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_KEYW_BREA,          S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_CA,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_B     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_KEYW_B,           S_SAW_NUMERIC_LITERAL,  S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_C     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_KEYW_C,           S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INC,         S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_STRUC,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_SWITC,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_D     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_INCLUD,         S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_E     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_KEYW_E,           S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_KEYW_BRE,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_CASE,         S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_CONTINUE,         S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_ELSE,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_INCLUDE,         S_SAW_LETTER,            S_KEYW_RE,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_WHILE,         S_SAW_LETTER,
    /* C_LETTER_F     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_KEYW_F,           S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_IF,         S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_G     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_USING,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_H     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_SWITCH,         S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_WH,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_I     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_KEYW_I,           S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CONTI,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_SWI,         S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_KEYW_UNI,         S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_USI,         S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_KEYW_WHI,         S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_K     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_KEYW_BREAK,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_L     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_KEYW_EL,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_KEYW_INCL,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_WHIL,         S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_M     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_KEYW_ENUM,         S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_IM,         S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_N     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_CON,         S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_CONTIN,         S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_KEYW_EN,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_IN,         S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_RETURN,         S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_UN,         S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_UNION,         S_SAW_LETTER,          S_SAW_LETTER,       S_KEYW_USIN,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_O     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_SAW_NUMERIC_LITERAL,  S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_CO,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_FO,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_KEYW_IMPO,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_UNIO,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_P     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_IMP,         S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_R     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_KEYW_R,           S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_KEYW_BR,         S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_KEYW_FOR,         S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_IMPOR,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_RETUR,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_KEYW_STR,         S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_S     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_KEYW_S,           S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_KEYW_CAS,         S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_KEYW_ELS,         S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_US,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_T     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_CAST,         S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_KEYW_CONT,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_IMPORT,         S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_KEYW_RET,         S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_ST,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_STRUCT,         S_SAW_LETTER,           S_SAW_LETTER,       S_KEYW_SWIT,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_U     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_KEYW_U,           S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_CONTINU,         S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_ENU,         S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_INCLU,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_RETU,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_STRU,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LETTER_W     */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_KEYW_W,           S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_SW,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_LITERAL_BASE */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_LETTER,       S_SAW_NUMERIC_LITERAL,  S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_ZERO         */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_ZERO,        S_SAW_NUMBER,           S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_DIGIT        */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SAW_NUMBER,       S_SAW_NUMBER,           S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,             S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,
    /* C_PLUS         */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_PLUS,        S_LONE_ZERO,            S_DOUBLED_OP,       S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_HYPHEN       */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_HYPHEN,      S_LONE_ZERO,            S_SINGLE_OP,        S_DOUBLED_OP,       S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_STAR         */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_STAR,        S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_MULTI_LINE_COMMENT,   S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_SLASH        */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_SLASH,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_LINE_COMMENT,  S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_LESS         */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_LESS,        S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_LESS_LESS,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_GREATER      */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_GREATER,     S_LONE_ZERO,            S_SINGLE_OP,        S_ARROW,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_GREATER_GREATER,      S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_EQUAL        */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_EQUAL,       S_LONE_ZERO,            S_EQUABLE,          S_EQUABLE,          S_EQUABLE,          S_EQUABLE,              S_EQUABLE,          S_EQUABLE,              S_DOUBLED_OP,       S_EQUABLE,              S_EQUABLE,          S_EQUABLE,            S_EQUABLE,             S_SINGLE_OP,           S_ERROR,                S_SHIFT_EQUAL,      S_SHIFT_EQUAL,           S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_AMPERSAND    */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_AMPERSAND,   S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_DOUBLED_OP,           S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_PIPE         */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_PIPE,        S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_DOUBLED_OP,       S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_COLON        */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_COLON,       S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_DOUBLED_OP,         S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_SEMICOLON    */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_NEWLINE,          S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_EQUABLE      */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SEEN_EQUABLE,     S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_SINGLE_QUOTE */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_CHAR,             S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_DOUBLE_QUOTE */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_STRING,           S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_PERIOD       */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SINGLE_OP,        S_SAW_NUMBER,           S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_DOUBLED_OP,          S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_MISC         */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_SINGLE_OP,        S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_UTF8_1       */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_ERROR,            S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_ERROR        */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_ERROR,            S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
    /* C_EOF          */      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    S_EOF,              S_LONE_ZERO,            S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,            S_SINGLE_OP,        S_SINGLE_OP,          S_SINGLE_OP,           S_SINGLE_OP,           S_ERROR,                S_DOUBLED_OP,       S_DOUBLED_OP,            S_SAW_LETTER,      S_SAW_LETTER,      S_SAW_LETTER,         S_SAW_LETTER,         S_KEYW_BREAK_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_CASE_COMP,     S_KEYW_CAST_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_SAW_LETTER,            S_KEYW_CONTINUE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ELSE_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_KEYW_ENUM_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_KEYW_FOR_COMP,     S_SAW_LETTER,      S_KEYW_IF_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_IMPORT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_SAW_LETTER,           S_KEYW_INCLUDE_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_RETURN_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_STRUCT_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_SAW_LETTER,          S_KEYW_SWITCH_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_UNION_COMP,     S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_USING_COMP,     S_SAW_LETTER,      S_SAW_LETTER,       S_SAW_LETTER,        S_SAW_LETTER,         S_KEYW_WHILE_COMP,
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
    (uint8)LAST_STATE * (uint8)C_LETTER_A,
    (uint8)LAST_STATE * (uint8)C_LETTER_B,
    (uint8)LAST_STATE * (uint8)C_LETTER_C,
    (uint8)LAST_STATE * (uint8)C_LETTER_D,
    (uint8)LAST_STATE * (uint8)C_LETTER_E,
    (uint8)LAST_STATE * (uint8)C_LETTER_F,
    (uint8)LAST_STATE * (uint8)C_LETTER_G,
    (uint8)LAST_STATE * (uint8)C_LETTER_H,
    (uint8)LAST_STATE * (uint8)C_LETTER_I,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER_K,
    (uint8)LAST_STATE * (uint8)C_LETTER_L,
    (uint8)LAST_STATE * (uint8)C_LETTER_M,
    (uint8)LAST_STATE * (uint8)C_LETTER_N,
    (uint8)LAST_STATE * (uint8)C_LETTER_O,
    (uint8)LAST_STATE * (uint8)C_LETTER_P,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER_R,
    (uint8)LAST_STATE * (uint8)C_LETTER_S,
    (uint8)LAST_STATE * (uint8)C_LETTER_T,
    (uint8)LAST_STATE * (uint8)C_LETTER_U,
    (uint8)LAST_STATE * (uint8)C_LETTER,
    (uint8)LAST_STATE * (uint8)C_LETTER_W,
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