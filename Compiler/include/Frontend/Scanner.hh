#ifndef _SCANNER_HH
#define _SCANNER_HH

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

    /*
    @TODO: Profile some of these options properly.
extern int start;
extern int end;
extern int current;
extern int* data;
void increment() {
    if (current < end)
        current++;
}

void base_eat_token() {
    current++;
}

void base_eat_token_2() {
    if (current < end)
        current++;
}

int* base_peek() {
    if (current < end) {
        return &data[current];
    }
    return &data[end];
}

int* base_peek_2() {
    return &data[current];
}

int* base_peek_ahead(int lookahead) {
    if (current + lookahead >= start && current + lookahead < end) {
        return &data[current];
    }
    return &data[end];
}

int* eat_token() {
    base_eat_token();
    return base_peek_ahead(-1);
}

int* eat_token_3() {
    int* current = base_peek();
    base_eat_token();
    return current;
}

int* eat_token_2() {
    auto* current = base_peek_2();
    base_eat_token_2();
    return current;
}
    */
    
    inline Token* peek_next_token() {
        /* Current is kept between start and end so unless I do something stupid,
           this should always be valid. */
        return &tokens[current];
    }

    inline Token* peek_token(int lookahead) {
        if (current + lookahead >= start && current + lookahead < end)
            return &tokens[current + lookahead];
        // This should be an EOF token
        return &tokens[end];
    }

    inline void eat_token() {
        if (current < end)
            current++;
    }
};

void init_symbol_table();
Scanner scan(const char *filename);


#endif /* _SCANNER_HH */