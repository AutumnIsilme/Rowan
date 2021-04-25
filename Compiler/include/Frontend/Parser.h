#ifndef PARSER_H_GUARD
#define PARSER_H_GUARD

#include <Frontend/Scanner.h>

typedef struct _Parser {

} Parser;

Parser *parser_create(TokenView *tokens);

#endif /* PARSER_H_GUARD */