#ifndef LEXER_H_GUARD
#define LEXER_H_GUARD

#include <vector>
#include <string>

#include "Types.h"
#include "Error.h"
#include "Token.h"

struct Lexer {
    std::vector<Token>* tokens;
    std::vector<Error> errors;
    u32 line_number = 0;
    u32 column_number = 0;

    const char* start;
    const char* current;

    static Lexer* init(const char* src);
    Token scanToken();

    TokenType check_keyword(int start, int length, const char* rest, TokenType type);

    ~Lexer() {
        if (tokens)
            delete tokens;
    }
};

#endif /* LEXER_H_GUARD */