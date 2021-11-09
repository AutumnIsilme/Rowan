#ifndef KEYWORD_LIST_H_GUARD
#define KEYWORD_LIST_H_GUARD

#include <Common.h>
#include <Frontend/Token.h>

#define KEYWORD_LIST_LEN 15

struct KeywordData {
    const char *text;
    uint64 len;
    TokenKind kind;
};

KeywordData KEYWORD_LIST[KEYWORD_LIST_LEN] = {
    {"if", 2, TT_IF},
    {"else", 4, TT_ELSE},
    {"for", 3, TT_FOR},
    {"while", 5, TT_WHILE},
    {"break", 5, TT_BREAK},
    {"continue", 8, TT_CONTINUE},
    {"return", 6, TT_RETURN},
    {"switch", 6, TT_SWITCH},
    {"case", 4, TT_CASE},
    {"using", 5, TT_USING},
    {"cast", 4, TT_CAST},
    {"struct", 6, TT_STRUCT},
    {"enum", 4, TT_ENUM},
    {"union", 5, TT_UNION},
    //{"soa", 3, TT_SOA},

    //{"true", 4, TT_TRUE},
    //{"false", 5, TT_FALSE},

    /*{"int8", 4, TT_TYPE},
    {"int16", 5, TT_TYPE},
    {"int32", 5, TT_TYPE},
    {"int64", 5, TT_TYPE},
    {"int128", 6, TT_TYPE},

    {"uint8", 5, TT_TYPE},
    {"uint16", 6, TT_TYPE},
    {"uint32", 6, TT_TYPE},
    {"uint64", 6, TT_TYPE},
    {"uint128", 7, TT_TYPE},

    {"float32", 7, TT_TYPE},
    {"float64", 7, TT_TYPE},
    {"float128", 8, TT_TYPE},
    
    {"bool", 4, TT_TYPE},
    {"string", 6, TT_TYPE},
    {"char8", 5, TT_TYPE},
    {"char16", 6, TT_TYPE},
    {"char32", 6, TT_TYPE},*/
};

const uint8 KEYWORD_LEN[KEYWORD_LIST_LEN] = {
    2, 3, 5, 6, 5, 8, 6, 4, 7, 5, 4, 6, 4, 5, 3, //4, 5,
};

#endif /* KEYWORD_LIST_H_GUARD */
