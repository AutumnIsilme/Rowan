#include <Frontend/HashTable.hh>
#include <Frontend/Token.h>
#include <Frontend/Scanner.hh>
#include <Frontend/StateMachine.h>
#include <Frontend/KeywordList.hh>
#include <Error.h>
#include <Instrumentor.hh>

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

static HashTable *keywords_table;

void extend_tokens_array(Token **tokens, uint64 *token_array_capacity_bytes, uint64 *token_array_capacity) {
    *token_array_capacity_bytes += *token_array_capacity_bytes;
    *tokens = (Token*)realloc(*tokens, *token_array_capacity_bytes);
    if (*tokens == NULL) exit(1);
    *token_array_capacity += *token_array_capacity;
}

void init_keywords_table() {
    PROFILE_FUNC();
    keywords_table = hash_table_create(7);
    for (uint i = 0; i < KEYWORD_LIST_LEN; i++) {
        if (hash_table_add(keywords_table, (TableEntry){
            .hash=fnv_1(KEYWORD_LIST[i].text, KEYWORD_LIST[i].len),
            .data=&KEYWORD_LIST[i],
            .present=true,
            .probe_count=0,
        })) {
            printf("Failed to add keyword to table: %s\n", KEYWORD_LIST[i].text);
        }
    }
}

Token TokenView::peek_next_token() {
    
}

Token TokenView::peek_token(int lookahead) {

}

void TokenView::eat_token() {

}

TokenView scan(const char *filename) {
    PROFILE_FUNC();
    uint64 token_array_capacity_bytes = 4096;
    uint64 token_array_capacity = 128;
    uint64 token_array_length = 0;
    Token *tokens = (Token*)malloc(token_array_capacity_bytes);
    if (tokens == NULL) {
        exit(1);
    }
    Token *next_token = tokens;

    char *source;
    size_t file_size;

    {
        PROFILE_SCOPE("Scanner::read_file");
        int file = open(filename, O_RDONLY);
        struct stat s;
        int status = fstat(file, &s);
        if (status == -1) {
            exit(1); // show errno
        }
        file_size = s.st_size;

        source = (char*)mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, file, 0);
        if (source == NULL) {
            exit(1);
        }
        if (madvise(source, file_size, MADV_SEQUENTIAL | MADV_WILLNEED)) {
            exit(1);
        }
        close(file);
    }

    char *current = source;
    char *end = source + file_size;
    while (current < end) {
        PROFILE_SCOPE("Scanner::token_loop");
        int state = START;
        uint64 token_len = 0;
        //printf("Starting token %llu, %s\n", token_array_length, current);
        do {
            int ch = *current++;
            int equiv_class = equivalence_class[ch];
            state = transition[state + equiv_class];
            token_len += in_token[state];
        } while (state > LAST_FINAL_STATE);

        //printf("Final state %d\n", state);
        switch (state) {
            case S_NEWLINE: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 1 + (*(current - token_len) == '\r');
                next_token->type = (TokenType)(TT_SEMICOLON + (TT_NEWLINE - TT_SEMICOLON) * (*(current - token_len) < ';'));
                current = next_token->token + next_token->length;
            } break;
            case S_CHAR: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                while (*current != '\'') {
                    token_len++;
                    if (*current == '\\') {
                        current++;
                        token_len++;
                    }
                    if (*current == 0) {
                        report_error(__FILE__, __LINE__, filename, source, next_token->offset, 1, "Scanner: End Of File in character literal");
                        return TokenView(tokens, 0, token_array_length);
                    }
                    current++;
                }
                if ((token_len > 2 && next_token->token[1] != '\\') || (next_token->token[1] == '\\' && token_len > 3)) {
                    report_error(__FILE__, __LINE__, filename, source, next_token->offset, 1, "Scanner: More than one character in character literal");
                }
                next_token->length = token_len + 1;
                next_token->type = TT_CHAR;
                current = next_token->token + next_token->length;
            } break;
            case S_STRING: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                while (*current != '"') {
                    token_len++;
                    if (*current == '\\') {
                        current++;
                        token_len++;
                    } else if (*current == 0) {
                        report_error(__FILE__, __LINE__, filename, source, next_token->offset, 1, "Scanner: End Of File in string literal");
                        return TokenView(tokens, 0, token_array_length);
                    }
                    current++;
                }
                next_token->length = token_len + 1;
                next_token->type = TT_STRING;
                current = next_token->token + next_token->length;
            } break;
            case S_SINGLE_OP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 1;
                switch (*next_token->token) {
                    case '.': next_token->type = TT_DOT;        break;
                    case '~': next_token->type = TT_TILDE;      break;
                    case '#': next_token->type = TT_HASH;       break;
                    case '$': next_token->type = TT_DOLLAR;     break;
                    case ',': next_token->type = TT_COMMA;      break;
                    case '?': next_token->type = TT_QUESTION;   break;
                    case '@': next_token->type = TT_AT;         break;
                    case '(': next_token->type = TT_LPAREN;     break;
                    case ')': next_token->type = TT_RPAREN;     break;
                    case '{': next_token->type = TT_LCURLY;     break;
                    case '}': next_token->type = TT_RCURLY;     break;
                    case '[': next_token->type = TT_LSQUARE;    break;
                    case ']': next_token->type = TT_RSQUARE;    break;
                    case '\\': next_token->type = TT_BACKSLASH; break;
                    case '+': next_token->type = TT_PLUS;       break;
                    case '-': next_token->type = TT_MINUS;      break;
                    case '*': next_token->type = TT_STAR;       break;
                    case '/': next_token->type = TT_SLASH;      break;
                    case '<': next_token->type = TT_LESS;       break;
                    case '>': next_token->type = TT_GREATER;    break;
                    case '=': next_token->type = TT_EQUAL;      break;
                    case '&': next_token->type = TT_AMPERSAND;  break;
                    case '|': next_token->type = TT_PIPE;       break;
                    case '^': next_token->type = TT_CARET;      break;
                    case '!': next_token->type = TT_EXCL;       break;
                    case '%': next_token->type = TT_PERCENT;    break;
                    case ':': next_token->type = TT_COLON;      break;
                    default: {
                        report_error(__FILE__, __LINE__, filename, source, next_token->offset, 1, "Scanner: Encountered unrecognised character for S_SINGLE_OP: %c", *next_token->token);
                        //printf("%s %d: Error - Encountered unrecognised character for S_SINGLE_OP: %d\n", __FILE__, __LINE__, *next_token->token);
                    }
                }
                current = next_token->token + next_token->length;
            } break;
            case S_DOUBLED_OP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 2;
                switch (*next_token->token) {
                    case '+': next_token->type = TT_PLUS_PLUS;           break;
                    case '-': next_token->type = TT_MINUS_MINUS;         break;
                    case '<': next_token->type = TT_LESS_LESS;           break;
                    case '>': next_token->type = TT_GREATER_GREATER;     break;
                    case '&': next_token->type = TT_AMPERSAND_AMPERSAND; break;
                    case '|': next_token->type = TT_PIPE_PIPE;           break;
                    case '=': next_token->type = TT_EQUAL_EQUAL;         break;
                    case ':': next_token->type = TT_COLON_COLON;         break;
                    default: {
                        report_error(__FILE__, __LINE__, filename, source, next_token->offset, 2, "Scanner: Encountered unrecognised character for S_DOUBLED_OP: %c", *next_token->token);
                        //printf("%s %s: Error - Encountered unrecognised character for S_DOUBLED_OP: %c", __FILE__, __LINE__, *next_token->token);
                    }
                }
                current = next_token->token + next_token->length;
            } break;
            case S_EQUABLE: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 2;
                switch (*next_token->token) {
                    case '+': next_token->type = TT_PLUS_EQUAL;       break;
                    case '-': next_token->type = TT_MINUS_EQUAL;      break;
                    case '*': next_token->type = TT_STAR_EQUAL;       break;
                    case '/': next_token->type = TT_SLASH_EQUAL;      break;
                    case '<': next_token->type = TT_LESS_EQUAL;       break;
                    case '>': next_token->type = TT_GREATER_EQUAL;    break;
                    case '=': next_token->type = TT_EQUAL_EQUAL;      break;
                    case '&': next_token->type = TT_AMPERSAND_EQUAL;  break;
                    case '|': next_token->type = TT_PIPE_EQUAL;       break;
                    case '^': next_token->type = TT_CARET_EQUAL;      break;
                    case '!': next_token->type = TT_EXCL_EQUAL;       break;
                    case '%': next_token->type = TT_PERCENT_EQUAL;    break;
                    case ':': next_token->type = TT_COLON_EQUAL;      break;
                    default: {
                        report_error(__FILE__, __LINE__, filename, source, next_token->offset, 2, "Scanner: Encountered unrecognised character for S_EQUABLE: %c", *next_token->token);
                        //printf("%s %s: Error - Encountered unrecognised character for S_DOUBLED_OP: %c", __FILE__, __LINE__, *next_token->token);
                    }
                }
                current = next_token->token + next_token->length;
            } break;
            case S_SAW_LETTER: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                //uint64 hash = next_token->token[0];
                uint64 hash = 0xcbf29ce484222325UL;
                hash ^= next_token->token[0];
                hash *= 0x100000001b3UL;
                while (1) {
                    char c = *current++;
                    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9') || c == '_' || c == '$') {
                        //hash = ROL(hash, 2) + c;
                        hash ^= c;
                        hash *= 0x100000001b3UL;
                        token_len++;
                    } else {
                        break;
                    }
                }
                next_token->length = token_len;
                next_token->type = TT_IDENT;
                TableEntry *e = hash_table_get(keywords_table, hash);
                if (e) {
                    const struct KeywordData *data = (struct KeywordData*)e->data;
                    if (data->len == next_token->length && !memcmp(data->text, next_token->token, data->len)) {
                        next_token->type = data->type;
                    }
                }
                current = next_token->token + next_token->length;
            } break;
            case S_SAW_NUMBER: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                bool is_float = false;
                if (*(current - 1) == '.') {
                    while (1) {
                        char c = *current++;
                        if (('0' <= c && c <= '9') || c == '_') {
                            token_len++;
                        } else if (c == '.') {
                            is_float = true;
                            token_len++;
                        } else {
                            break;
                        }
                    }
                    is_float = true;
                } else {
                    while (1) {
                        char c = *current++;
                        if (('0' <= c && c <= '9') || c == '_') {
                            token_len++;
                        } else if (c == '.') {
                            is_float = true;
                            token_len++;
                        } else {
                            break;
                        }
                    }
                }
                next_token->length = token_len;
                next_token->type = is_float ? TT_FLOAT : TT_INT;
                current = next_token->token + next_token->length;
            } break;
            case S_SAW_NUMERIC_LITERAL: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                char base = *(current - 1);
                switch (base) {
                    case 'b': {
                        while (1) {
                            char c = *current++;
                            if (('0' <= c && c <= '1') || c == '_') {
                                token_len++;
                            } else {
                                break;
                            }
                        }
                        next_token->type = TT_BINARY_LITERAL;
                    } break;
                    case 'o': {
                        while (1) {
                            char c = *current++;
                            if (('0' <= c && c <= '7') || c == '_') {
                                token_len++;
                            } else {
                                break;
                            }
                        }
                        next_token->type = TT_OCTAL_LITERAL;
                    } break;
                    case 'x': {
                        while (1) {
                            char c = *current++;
                            if (('a' <= c && c <= 'f') || ('A' <= c && c <= 'F') || ('0' <= c && c <= '9') || c == '_') {
                                token_len++;
                            } else {
                                break;
                            }
                        }
                        next_token->type = TT_HEX_LITERAL;
                    } break;
                    default: {
                        next_token->type = TT_NONE;
                    }
                }
                next_token->length = token_len;
                current = next_token->token + next_token->length;
            } break;
            case S_LONE_ZERO: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 1;
                next_token->type = TT_INT;
                current = next_token->token + next_token->length;
            } break;
            case S_ARROW: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 2;
                next_token->type = TT_ARROW;
                current = next_token->token + next_token->length;
            } break;
            case S_SINGLE_LINE_COMMENT: {
                while (current < end && *current != '\n') current++;
                next_token--;
                token_array_length--;
            } break;
            case S_MULTI_LINE_COMMENT: {
                while (current < (end - 1) && !(*current == '*' && *(current + 1) == '/')) current++;
                if (current >= end - 1) {
                    report_error(__FILE__, __LINE__, filename, source, current - source, 1, "Scanner: EOF in multi-line comment");
                }
                current += 2;
                next_token--;
                token_array_length--;
            } break;
            case S_SHIFT_EQUAL: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 3;
                next_token->type = *next_token->token == '<' ? TT_LESS_LESS_EQUAL : TT_GREATER_GREATER_EQUAL;
                current = next_token->token + next_token->length;
            } break;
            case S_ERROR: {
                report_error(__FILE__, __LINE__, filename, source, current - source, 1, "Scanner: Encountered unexpected character (%d)", *current);
                return TokenView(tokens, 0, token_array_length);
            } break;
            case S_EOF: {
            } break;
        }
        next_token++;
        token_array_length++;
        //printf("length: %llu, capacity: %llu\n", token_array_length, token_array_capacity);
        if (token_array_length == token_array_capacity) {
            extend_tokens_array(&tokens, &token_array_capacity_bytes, &token_array_capacity);
            next_token = tokens + token_array_length;
        }
    }

    next_token->offset = file_size;
    next_token->token = end;
    next_token->length = 0;
    next_token->type = TT_EOF;
    token_array_length++;

    // @TODO: Probably don't leak this memory
    //munmap(source, file_size);

    return TokenView(tokens, 0, token_array_length);
}
