#include "Frontend/Token.h"

Token *token_create(TokenType type, u32 line_number, u32 column_number, const char *token, u64 length) {
    Token *t = malloc(sizeof(*t));
    t->type = type;
    t->line_number = line_number;
    t->column_number = column_number;
    t->token = token;
    t->length = length;
    return t;
}