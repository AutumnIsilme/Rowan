#ifndef LEXER_H_GUARD
#define LEXER_H_GUARD

#include <vector>
#include <string>

#include "Types.h"
#include "Error.h"
#include "Token.h"

struct Lexer {
    static std::vector<Token> tokens;
    static std::vector<Error> errors;
    static u32 line_number;
    static u32 column_number;

    static void make_tokens(const std::string& input_string);
    static void make_token(const std::string& token);
};

#endif /* LEXER_H_GUARD */