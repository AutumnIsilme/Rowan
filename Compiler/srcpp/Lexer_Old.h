#ifndef LEXER_OLD_H_GUARD
#define LEXER_OLD_H_GUARD

#include <vector>
#include <string>

#include "Types.h"
#include "Error.h"
#include "Token.h"

struct Lexer_Old {
    std::vector<Token>* tokens;
    std::vector<Error> errors;
    u32 line_number;
    u32 column_number;

    u32 comment_depth = 0;
    bool line_comment = false;

    void make_tokens(const std::string& input_string);
    void make_token(const std::string& token);

    ~Lexer_Old() {
        if (tokens)
            delete tokens;
    }
};

#endif /* LEXER_OLD_H_GUARD */