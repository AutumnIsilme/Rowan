#include "Frontend/Scanner.h"

#include <string.h>
#include <stdint.h>

Scanner* scanner_init(const char* src, size_t src_size) {
    Scanner* scanner = malloc(sizeof(*scanner));
    scanner->column_number = 0;
    scanner->line_number = 1;
    scanner->start = src;
    scanner->current = src;
    scanner->end = src + src_size;
    return scanner;
}

bool is_alpha(char c) {
    return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || c == '_');
}

bool is_digit(char c) {
    return ('0' <= c && c <= '9');
}

TokenType check_keyword(Scanner *scanner, int start, int length, const char* rest, TokenType type) {
    if ((scanner->current - scanner->start) == start + length 
        && memcmp(scanner->start + start, rest, length) == 0) {
        return type; 
    }
    return TT_IDENT;
}

#ifdef FASTBUILD
#define INC_COLUMN(scanner, n)
#else
#define INC_COLUMN(scanner, n) scanner->column_number += n
#endif

Token scanner_next(Scanner *scanner) {
    static uint64_t token_index = 0;
    token_index++;
    while (true) {
        if (scanner->current == scanner->end) {
            return (Token){TT_EOF, scanner->line_number, scanner->column_number, scanner->current, 1};
        }
        switch (*scanner->current) {
        case '\n': case '\r': {
            static uint64_t prev = 0;
            if (prev + 1 != token_index) {
                scanner->current++;
                scanner->line_number++;
                INC_COLUMN(scanner, -scanner->column_number);
                prev = token_index;
                return (Token){TT_NEWLINE, scanner->line_number, scanner->column_number, scanner->current - 1, 1};
            }
            scanner->current++;
            scanner->line_number++;
            INC_COLUMN(scanner, -scanner->column_number);
            prev = token_index;
            break;
        }
        case ' ': case '\f': {
            scanner->current++;
            INC_COLUMN(scanner,1);
            break;
        }
        case '\t': {
            scanner->current++;
            INC_COLUMN(scanner, 4 - (scanner->column_number % 4));
            break;
        }
        case '/': {
            bool line_comment = false;
            switch (*(scanner->current + 1))
            {
            case '/': {
                line_comment = true;
                while (line_comment) {
                    if (scanner->current == scanner->end) {
                        return (Token){TT_EOF, scanner->line_number, scanner->column_number, scanner->current, 1};
                    }
                    if (*(scanner->current+1) == '\n') {
                        line_comment = false;
                        scanner->current++;
                        scanner->line_number++;
                        INC_COLUMN(scanner, -scanner->column_number);
                    } else {
                        scanner->current++;
                        INC_COLUMN(scanner,1);
                    }
                }
                break;
            }
            case '*': {
                scanner->current += 2;
                INC_COLUMN(scanner, 2);
                u32 comment_depth = 1;
                while (comment_depth != 0) {
                    if (scanner->current == scanner->end) {
                        return (Token){TT_EOF, scanner->line_number, scanner->column_number, scanner->current, 1};
                    }
                    switch (*scanner->current) {
                        case '\n': {
                            scanner->current++;
                            scanner->line_number++;
                            INC_COLUMN(scanner, -scanner->column_number);
                            break;
                        }
                        case '*': {
                            if (*(scanner->current+1) == '/') {
                                comment_depth--;
                                scanner->current += 2;
                                INC_COLUMN(scanner,2);
                            } else {
                                scanner->current++;
                                INC_COLUMN(scanner,1);
                            }
                            break;
                        }
                        case '/': {
                            if (*(scanner->current+1) == '*') {
                                comment_depth++;
                                scanner->current += 2;
                                INC_COLUMN(scanner,2);
                            } else {
                                scanner->current++;
                                INC_COLUMN(scanner,1);
                            }
                            break;
                        }
                        default: {
                            scanner->current++;
                            INC_COLUMN(scanner,1);
                        }
                    }
                }
                break;
            }
            default: {
                INC_COLUMN(scanner,1);
                scanner->start = scanner->current;
                scanner->current++;
                return (Token){TT_SLASH, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
                break;
            }
            }
            break;
        }
        default: goto whitespace_end;
        }
    }
    whitespace_end:
    scanner->start = scanner->current;
    switch (*scanner->current) {
        case '(': {
            INC_COLUMN(scanner,1);
            scanner->current++;
            return (Token){TT_LPAREN, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            break;
        }
        case ')': {
            INC_COLUMN(scanner,1);
            scanner->current++;
            return (Token){TT_RPAREN, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            break;
        }
        case '[': {
            INC_COLUMN(scanner,1);
            scanner->current++;
            return (Token){TT_LSQUARE, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            break;
        }
        case ']': {
            INC_COLUMN(scanner,1);
            scanner->current++;
            return (Token){TT_RSQUARE, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            break;
        }
        case '{': {
            INC_COLUMN(scanner,1);
            scanner->current++;
            return (Token){TT_LCURLY, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            break;
        }
        case '}': {
            INC_COLUMN(scanner,1);
            scanner->current++;
            return (Token){TT_RCURLY, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            break;
        }
        case '+': {
            scanner->current++;
            if (*scanner->current == '+') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_PLUS_PLUS, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } /*else if (*scanner->current == '=') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_PLUS_EQUALS, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } */else {
                INC_COLUMN(scanner,1);
                scanner->current++;
                return (Token){TT_PLUS, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            }
            break;
        }
        case '-': {
            scanner->current++;
            if (*scanner->current == '-') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_MINUS_MINUS, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } /*else if (*scanner->current == '=') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_MINUS_EQUALS, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } */else if (*scanner->current == '>') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_MINUS_GT, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else {
                INC_COLUMN(scanner,1);
                scanner->current++;
                return (Token){TT_MINUS, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            }
            break;
        }
        case '*': {
            scanner->current++;
            if (*scanner->current == '*') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_STAR_STAR, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else {
                INC_COLUMN(scanner,1);
                return (Token){TT_STAR, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            }
            break;
        }
        case '!': {
            scanner->current++;
            if (*scanner->current == '=') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_EXCL_EQUAL, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else {
                INC_COLUMN(scanner,1);
                return (Token){TT_EXCL, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            }
            break;
        }
        case '=': {
            scanner->current++;
            if (*scanner->current == '=') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_EQUAL_EQUAL, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else {
                INC_COLUMN(scanner,1);
                return (Token){TT_EQUAL, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            }
            break;
        }
        case '%': {
            INC_COLUMN(scanner,1);
            scanner->current++;
            return (Token){TT_PERCENT, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            break;
        }
        case '^': {
            INC_COLUMN(scanner,1);
            scanner->current++;
            return (Token){TT_CARET, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            break;
        }
        case '&': {
            scanner->current++;
            if (*scanner->current == '&') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_AMPERSAND_AMPERSAND, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else {
                INC_COLUMN(scanner,1);
                return (Token){TT_AMPERSAND, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            }
            break;
        }
        case '|': {
            scanner->current++;
            if (*scanner->current == '|') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_PIPE_PIPE, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else {
                INC_COLUMN(scanner,1);
                return (Token){TT_PIPE, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            }
            break;
        }
        case '<': {
            scanner->current++;
            if (*scanner->current == '=') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_LT_EQUAL, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else if (*scanner->current == '<') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_LT_LT, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else {
                INC_COLUMN(scanner,1);
                return (Token){TT_LT, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            }
            break;
        }
        case '>': {
            scanner->current++;
            if (*scanner->current == '=') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_GT_EQUAL, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else if (*scanner->current == '>') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_GT_GT, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else {
                INC_COLUMN(scanner,1);
                return (Token){TT_GT, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            }
            break;
        }
        case ',': {
            INC_COLUMN(scanner,1);
            scanner->current++;
            return (Token){TT_COMMA, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            break;
        }
        case '"': {
            INC_COLUMN(scanner,1);
            scanner->current++;
            while (*scanner->current != '"') {
                if (scanner->current == scanner->end) { // @ERROR: EOF in string literal
                    return (Token){TT_EOF, scanner->line_number, scanner->column_number, scanner->current, 1};
                }
                if (*scanner->current == '\\' && *(scanner->current+1) == '"') {
                    INC_COLUMN(scanner,1);
                    scanner->current++;
                }
                INC_COLUMN(scanner,1);
                scanner->current++;
            }
            INC_COLUMN(scanner,1);
            scanner->current++;
            return (Token){TT_STRING, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            break;
        }
        case '\'': {
            INC_COLUMN(scanner,1);
            scanner->current++;
            if (*scanner->current == '\\') {
                INC_COLUMN(scanner,1);
                scanner->current++;
            } else if (scanner->current == scanner->end) { // @ERROR: EOF in character literal
                return (Token){TT_EOF, scanner->line_number, scanner->column_number, scanner->current, 1};
            }
            INC_COLUMN(scanner,1);
            scanner->current++;
            return (Token){TT_CHAR, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            break;
        }
        case '.': {
            INC_COLUMN(scanner,1);
            scanner->current++;
            return (Token){TT_DOT, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            break;
        }
        case ':': {
            scanner->current++;
            if (*scanner->current == '=') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_COLON_EQUALS, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else if (*scanner->current == ':') {
                INC_COLUMN(scanner,2);
                scanner->current++;
                return (Token){TT_COLON_COLON, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else {
                INC_COLUMN(scanner,1);
                return (Token){TT_COLON, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            }
            break;
        }
        case ';': {
            INC_COLUMN(scanner,1);
            scanner->current++;
            return (Token){TT_SEMICOLON, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            break;
        }
        default: { // Identifier or number or keyword
            if (is_alpha(*scanner->current)) {
                INC_COLUMN(scanner,1);
                scanner->current++;
                while (is_alpha(*scanner->current) || is_digit(*scanner->current)) {
                    INC_COLUMN(scanner,1);
                    scanner->current++;
                }
                TokenType ident_type = TT_IDENT;
                switch (*scanner->start) {
                    case 'b': ident_type = check_keyword(scanner, 1, 4, "reak", TT_BREAK); break;
                    case 'c':
                        if (scanner->current - scanner->start > 3) {
                            switch (scanner->start[1]) {
                                case 'a':
                                    if (scanner->current - scanner->start == 4 && scanner->start[2] == 's') {
                                        if (scanner->start[3] == 'e') {
                                            ident_type = TT_CASE;
                                        } else if (scanner->start[3] == 't') {
                                            ident_type = TT_CAST;
                                        }
                                    } break;
                                case 'o': ident_type = check_keyword(scanner, 2, 6, "ntinue", TT_CONTINUE); break;
                            }
                        } break;
                    case 'e': ident_type = check_keyword(scanner, 1, 3, "num", TT_ENUM); break;
                    case 'f':
                        if (scanner->current - scanner->start > 2) {
                            switch (scanner->start[1]) {
                                case 'a': ident_type = check_keyword(scanner, 2, 3, "lse", TT_FALSE); break;
                                case 'o': if (scanner->current - scanner->start == 3 && scanner->start[2] == 'r') { ident_type = TT_FOR; } break;
                            }
                        } break;
                    case 'i':
                        if (scanner->current - scanner->start > 1) {
                            switch (scanner->start[1]) {
                                case 'f': if (scanner->current - scanner->start == 2) { ident_type = TT_IF; } break;
                                case 'n': ident_type = check_keyword(scanner, 2, 5, "clude", TT_INCLUDE); break;
                            }
                        } break;
                    case 'r': ident_type = check_keyword(scanner, 1, 5, "eturn", TT_RETURN); break;
                    case 's':
                        if (scanner->current - scanner->start > 2) {
                            switch (scanner->start[1]) {
                                case 'o': if (scanner->current - scanner->start == 3 && scanner->start[2] == 'a') { ident_type = TT_SOA; } break;
                                case 't': ident_type = check_keyword(scanner, 2, 4, "ruct", TT_STRUCT); break;
                                case 'w': ident_type = check_keyword(scanner, 2, 4, "itch", TT_SWITCH); break;
                            }
                        } break;
                    case 't': ident_type = check_keyword(scanner, 1, 3, "rue", TT_TRUE); break;
                    case 'u':
                        if (scanner->current - scanner->start == 5) {
                            switch (scanner->start[1]) {
                                case 'n': ident_type = check_keyword(scanner, 2, 3, "ion", TT_UNION); break;
                                case 's': ident_type = check_keyword(scanner, 2, 3, "ing", TT_USING); break;
                            }
                        } break;
                    case 'w': ident_type = check_keyword(scanner, 1, 4, "hile", TT_WHILE); break;
                }
                return (Token){ident_type, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else if (is_digit(*scanner->current)) {
                bool floating_point = false;
                INC_COLUMN(scanner,1);
                scanner->current++;
                while (is_digit(*scanner->current)) {
                    INC_COLUMN(scanner,1);
                    scanner->current++;
                }
                if (*scanner->current == '.' && is_digit(*(scanner->current + 1))) {
                    INC_COLUMN(scanner,2);
                    scanner->current += 2;
                    floating_point = true;
                    while (is_digit(*scanner->current)) {
                        INC_COLUMN(scanner,1);
                        scanner->current++;
                    }
                }
                return (Token){floating_point ? TT_FLOAT : TT_INT, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            } else { // @ERROR: Unkown character
                return (Token){TT_EOF, scanner->line_number, scanner->column_number, scanner->start, scanner->current - scanner->start};
            }
            break;
        }
    }
}
