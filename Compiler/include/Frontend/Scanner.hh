#ifndef _SCANNER_H
#define _SCANNER_H

#include <stdbool.h>
#include <stdio.h>

#include <Common.h>
#include <Frontend/Token.h>

enum class IdentTokenFlags : uint8 {
    NONE = 0,
    IS_BACKTICKED = BIT(1),
    IS_HASHED = BIT(2),
    IS_DOLLARED = BIT(3),
};

struct Token {
    TokenKind kind;
    uint32 flags;
    uint64 offset;
    char* token;
    uint64 length;
};

struct Scanner {
    Token *tokens;
    uint64 start;
    uint64 current;
    uint64 count;
    uint64 end;
    char *file_data;
    uint64 file_size;

    //Scanner(Token *tokens, uint64 start_index, uint64 end_index)
    //    : tokens(tokens), start(start_index), current(start_index), count(end_index - start_index), end(end_index) {}
    Scanner(const char *filename);

    inline Token* peek_next_token() {
        if (current < end)
            return &tokens[current];
        else
            // This should be an EOF token
            return &tokens[end];
    }

    inline Token* peek_token(int lookahead) {
        if (current + lookahead > start && current + lookahead < end)
            return &tokens[current + lookahead];
        else
            // This should be an EOF token
            return &tokens[end];
    }

    inline void eat_token() {
        current++;
    }
};

void init_keywords_table();
Scanner scan(const char *filename);


#endif /* _SCANNER_H */