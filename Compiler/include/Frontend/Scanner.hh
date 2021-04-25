#ifndef _SCANNER_H
#define _SCANNER_H

#include <stdbool.h>

#include <Common.h>
#include <Frontend/Token.h>

struct Token {
    TokenType type;
    uint32 _unused;
    uint64 offset;
    char* token;
    uint64 length;
};

struct TokenView {
    Token *tokens;
    uint64 start;
    uint64 current;
    uint64 count;

    TokenView(Token *tokens, uint64 start_index, uint64 end_index)
        : tokens(tokens), start(start_index), current(start_index), count(end_index - start_index) {}
    
    Token peek_next_token();
    Token peek_token(int lookahead);
    void eat_token();
};

void init_keywords_table();
TokenView scan(const char *filename);


#endif /* _SCANNER_H */