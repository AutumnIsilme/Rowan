#include <Frontend/HashTable.hh>
#include <Frontend/Token.h>
#include <Frontend/Scanner.hh>
#include <Frontend/StateMachine.h>
#include <Frontend/KeywordList.hh>
#include <Error.h>
#include <Files.hh>
#include <Instrumentor.hh>

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

//static HashTable<KeywordData> *keywords_table;

void extend_tokens_array(Token **tokens, uint64 *token_array_capacity_bytes, uint64 *token_array_capacity) {
    *token_array_capacity_bytes += *token_array_capacity_bytes;
    *tokens = (Token*)realloc(*tokens, *token_array_capacity_bytes);
    if (*tokens == NULL) {
        printf("ERROR: Realloc failed to return a valid pointer?!\n");
        exit(1);
    }
    *token_array_capacity += *token_array_capacity;
}

void init_symbol_table() {
    PROFILE_FUNC();
    /*keywords_table = new HashTable<KeywordData>(7);
    for (uint i = 0; i < KEYWORD_LIST_LEN; i++) {
        auto table_entry = TableEntry<KeywordData>(
            fnv_1(KEYWORD_LIST[i].text, KEYWORD_LIST[i].len),
            &KEYWORD_LIST[i],
            true,
            0
        );
        if (keywords_table->add(table_entry)) {
            printf("Failed to add keyword to table: %s\n", KEYWORD_LIST[i].text);
        }
    }*/
}

Scanner::Scanner(const char *filename) {
    PROFILE_FUNC();
    start = 0;
    current = 0;

    uint64 token_array_capacity_bytes = 4096;
    uint64 token_array_capacity = 128;
    uint64 token_array_length = 0;
    tokens = (Token*)malloc(token_array_capacity_bytes);
    if (tokens == NULL) {
        printf("ERROR: Malloc failed to return a valid pointer?!\n");
        exit(1);
    }
    Token *next_token = tokens;

    char *source;

    {
        PROFILE_SCOPE("Scanner::read_file");
        auto file_read_result = read_file(filename);
        source = file_read_result.buffer;
        file_size = file_read_result.size;
    }

    // NOTE: This memory probably sticks around for the rest of the
    // program, because we need to be able to report errors and
    // see the text of tokens sometimes.
    file_data = source;

    char *current = source;
    char *end = source + file_size;
    while (current < end) {
        uint8 state = START;
        uint64 token_len = 0;
        do {
            char ch = *current++;
            uint16 equiv_class = equivalence_class[static_cast<uint8>(ch)];
            state = transition[state + equiv_class];
            token_len += in_token[state];
            //printf("STATE: %d\n", state);
        } while (state > LAST_FINAL_STATE);

        //printf("Final state %d\n", state);
        switch (state) {
            case S_NEWLINE: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 1 + (*(current - token_len) == '\r');
                next_token->kind = (TokenKind)(TT_SEMICOLON + (TT_NEWLINE - TT_SEMICOLON) * (*(current - token_len) < ';'));
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
                        return;
                    }
                    current++;
                }
                if ((token_len > 2 && next_token->token[1] != '\\') || (next_token->token[1] == '\\' && token_len > 3)) {
                    report_error(__FILE__, __LINE__, filename, source, next_token->offset, 1, "Scanner: More than one character in character literal");
                }
                next_token->length = token_len + 1;
                next_token->kind = TT_CHAR;
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
                        return;
                    }
                    current++;
                }
                next_token->length = token_len + 1;
                next_token->kind = TT_STRING;
                current = next_token->token + next_token->length;
            } break;
            case S_SINGLE_OP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 1;
                switch (*next_token->token) {
                    case '.': next_token->kind = TT_DOT;        break;
                    case '~': next_token->kind = TT_TILDE;      break;
                    //case '#': next_token->kind = TT_HASH;       break;
                    case '$': next_token->kind = TT_DOLLAR;     break;
                    case ',': next_token->kind = TT_COMMA;      break;
                    case '?': next_token->kind = TT_QUESTION;   break;
                    case '@': next_token->kind = TT_AT;         break;
                    case '(': next_token->kind = TT_LPAREN;     break;
                    case ')': next_token->kind = TT_RPAREN;     break;
                    case '{': next_token->kind = TT_LCURLY;     break;
                    case '}': next_token->kind = TT_RCURLY;     break;
                    case '[': next_token->kind = TT_LSQUARE;    break;
                    case ']': next_token->kind = TT_RSQUARE;    break;
                    case '\\': next_token->kind = TT_BACKSLASH; break;
                    case '+': next_token->kind = TT_PLUS;       break;
                    case '-': next_token->kind = TT_MINUS;      break;
                    case '*': next_token->kind = TT_STAR;       break;
                    case '/': next_token->kind = TT_SLASH;      break;
                    case '<': next_token->kind = TT_LESS;       break;
                    case '>': next_token->kind = TT_GREATER;    break;
                    case '=': next_token->kind = TT_EQUAL;      break;
                    case '&': next_token->kind = TT_AMPERSAND;  break;
                    case '|': next_token->kind = TT_PIPE;       break;
                    case '^': next_token->kind = TT_CARET;      break;
                    case '!': next_token->kind = TT_EXCL;       break;
                    case '%': next_token->kind = TT_PERCENT;    break;
                    case ':': next_token->kind = TT_COLON;      break;
                    default: {
                        report_error(__FILE__, __LINE__, filename, source, next_token->offset, 1, "Scanner: Encountered unrecognised character for S_SINGLE_OP: %c", *next_token->token);
                    }
                }
                current = next_token->token + next_token->length;
            } break;
            case S_DOUBLED_OP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 2;
                switch (*next_token->token) {
                    case '.': next_token->kind = TT_DOT_DOT;             break;
                    case '+': next_token->kind = TT_PLUS_PLUS;           break;
                    case '-': next_token->kind = TT_MINUS_MINUS;         break;
                    case '<': next_token->kind = TT_LESS_LESS;           break;
                    case '>': next_token->kind = TT_GREATER_GREATER;     break;
                    case '&': next_token->kind = TT_AMPERSAND_AMPERSAND; break;
                    case '|': next_token->kind = TT_PIPE_PIPE;           break;
                    case '=': next_token->kind = TT_EQUAL_EQUAL;         break;
                    case ':': next_token->kind = TT_COLON_COLON;         break;
                    default: {
                        report_error(__FILE__, __LINE__, filename, source, next_token->offset, 2, "Scanner: Encountered unrecognised character for S_DOUBLED_OP: %c", *next_token->token);
                    }
                }
                current = next_token->token + next_token->length;
            } break;
            case S_EQUABLE: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 2;
                switch (*next_token->token) {
                    case '+': next_token->kind = TT_PLUS_EQUAL;       break;
                    case '-': next_token->kind = TT_MINUS_EQUAL;      break;
                    case '*': next_token->kind = TT_STAR_EQUAL;       break;
                    case '/': next_token->kind = TT_SLASH_EQUAL;      break;
                    case '<': next_token->kind = TT_LESS_EQUAL;       break;
                    case '>': next_token->kind = TT_GREATER_EQUAL;    break;
                    case '=': next_token->kind = TT_EQUAL_EQUAL;      break;
                    case '&': next_token->kind = TT_AMPERSAND_EQUAL;  break;
                    case '|': next_token->kind = TT_PIPE_EQUAL;       break;
                    case '^': next_token->kind = TT_CARET_EQUAL;      break;
                    case '!': next_token->kind = TT_EXCL_EQUAL;       break;
                    case '%': next_token->kind = TT_PERCENT_EQUAL;    break;
                    case ':': next_token->kind = TT_COLON_EQUAL;      break;
                    default: {
                        report_error(__FILE__, __LINE__, filename, source, next_token->offset, 2, "Scanner: Encountered unrecognised character for S_EQUABLE: %c", *next_token->token);
                    }
                }
                current = next_token->token + next_token->length;
            } break;
            case S_SAW_LETTER: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                current--;
                token_len--;
                {
                    char c = *current;
                    if (c == '#' || c == '`' || c == '$') {
                        token_len++;
                        current++;
                    }
                }
                //printf("We are here: '%.10s'\n", current);
                while (1) {
                    char c = *current++;
                    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9') || c == '_') {
                        token_len++;
                    } else break;
                }
                next_token->length = token_len;
                next_token->kind = TT_IDENT;
                current = next_token->token + next_token->length;
                /*
                current = next_token->token;
                token_len = 0;
                uint64 hash = 0xcbf29ce484222325UL;
                hash ^= next_token->token[0];
                hash *= 0x100000001b3UL;
                while (1) {
                    char c = *current++;
                    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9') || c == '_') {
                        hash ^= c;
                        hash *= 0x100000001b3UL;
                        token_len++;
                    } else {
                        break;
                    }
                }*/
                /*
                @OPTIMISATION:
                We shouldn't be looking up the ident hash here, as we need to compare strings if we do that, and
                that is slow. Instead this should probably be deferred to parsing, or keywords expanded into the
                main state machine.
                */
                /*TableEntry<KeywordData> *e = keywords_table->get(hash);
                if (e) {
                    const struct KeywordData *data = e->data;
                    if (data->len == next_token->length && !memcmp(data->text, next_token->token, data->len)) {
                        next_token->kind = data->kind;
                    } else goto not_keyword;
                } else {*/
                //not_keyword:
                    /*const char first = *next_token->token;
                    if (first == '`')
                        next_token->flags |= (uint8)IdentTokenFlags::IS_BACKTICKED;
                    else if (first == '#') {
                        next_token->kind = TT_HASH;
                        next_token->flags |= (uint8)IdentTokenFlags::IS_HASHED;
                    } else if (first == '$') {
                        next_token->flags |= (uint8)IdentTokenFlags::IS_DOLLARED;
                    }*/
                //}
                //printf("We are here: '%.10s' (with length %llu)\n", current, token_len);
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
                next_token->kind = is_float ? TT_FLOAT : TT_INT;
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
                        next_token->kind = TT_BINARY_LITERAL;
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
                        next_token->kind = TT_OCTAL_LITERAL;
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
                        next_token->kind = TT_HEX_LITERAL;
                    } break;
                    default: {
                        next_token->kind = TT_NONE;
                    }
                }
                next_token->length = token_len;
                current = next_token->token + next_token->length;
            } break;
            case S_LONE_ZERO: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 1;
                next_token->kind = TT_INT;
                current = next_token->token + next_token->length;
            } break;
            case S_ARROW: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 2;
                next_token->kind = TT_ARROW;
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
                next_token->kind = *next_token->token == '<' ? TT_LESS_LESS_EQUAL : TT_GREATER_GREATER_EQUAL;
                current = next_token->token + next_token->length;
            } break;
            case S_ERROR: {
                report_error(__FILE__, __LINE__, filename, source, current - source, 1, "Scanner: Encountered unexpected character (%d)", *current);
                return;
            } break;
            case S_EOF: {
            } break;
            case S_KEYW_BREAK_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 5;
                next_token->kind = TT_BREAK;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_CASE_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 4;
                next_token->kind = TT_CASE;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_CAST_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 4;
                next_token->kind = TT_CAST;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_CONTINUE_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 8;
                next_token->kind = TT_CONTINUE;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_ELSE_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 4;
                next_token->kind = TT_ELSE;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_ENUM_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 4;
                next_token->kind = TT_ENUM;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_FOR_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 3;
                next_token->kind = TT_FOR;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_IF_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 2;
                next_token->kind = TT_IF;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_IMPORT_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 6;
                next_token->kind = TT_IMPORT;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_INCLUDE_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 7;
                next_token->kind = TT_INCLUDE;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_RETURN_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 6;
                next_token->kind = TT_RETURN;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_STRUCT_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 6;
                next_token->kind = TT_STRUCT;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_SWITCH_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 6;
                next_token->kind = TT_SWITCH;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_UNION_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 5;
                next_token->kind = TT_UNION;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_USING_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 5;
                next_token->kind = TT_USING;
                current = next_token->token + next_token->length;
            } break;
            case S_KEYW_WHILE_COMP: {
                next_token->offset = current - token_len - source;
                next_token->token = current - token_len;
                next_token->length = 5;
                next_token->kind = TT_WHILE;
                current = next_token->token + next_token->length;
            } break;
        }
        next_token++;
        token_array_length++;
        if (token_array_length == token_array_capacity) {
            extend_tokens_array(&tokens, &token_array_capacity_bytes, &token_array_capacity);
            next_token = tokens + token_array_length;
        }
    }

    count = token_array_length;

    next_token->offset = file_size;
    next_token->token = end;
    next_token->length = 0;
    next_token->kind = TT_EOF;
    this->end = token_array_length;
    token_array_length++;


    return;
}
