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
    u32 line_number;
    u32 column_number;

    u32 comment_depth = 0;
    bool line_comment = false;

    void make_tokens(const std::string& input_string);
    void make_token(const std::string& token);

    ~Lexer() {
        if (tokens)
            delete tokens;
    }
};

#endif /* LEXER_H_GUARD */