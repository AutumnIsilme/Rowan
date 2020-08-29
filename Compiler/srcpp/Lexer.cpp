#include "Lexer.h"

#include <string.h>

Lexer* Lexer::init(const char* src) {
    Lexer* lexer = new Lexer;
    lexer->start = src;
    lexer->current = src;
    return lexer;
}

bool is_alpha(char c) {
    return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || c == '_');
}

bool is_digit(char c) {
    return ('0' <= c && c <= '9');
}

TokenType Lexer::check_keyword(int check_start, int length, const char* rest, TokenType type) {
    if ((current - start) == check_start + length 
        && memcmp(start + check_start, rest, length) == 0) {
        return type;
    }
    return TT_IDENT;
}

Token Lexer::scanToken() {
    while (true) {
        switch (*current) {
        case '\0':
            return Token(TT_EOF, line_number, column_number, current, 1);
        case '\n': case '\r': {
            current++;
            line_number++;
            column_number = 0;
            break;
        }
        case ' ': case '\f': {
            current++;
            column_number++;
            break;
        }
        case '\t': {
            current++;
            column_number += 4 - (column_number % 4);
            break;
        }
        case '/': {
            bool line_comment = false;
            switch (*(current + 1))
            {
            case '/':
                line_comment = true;
            case '*': {
                current += 2;
                column_number += 2;
                u32 comment_depth = 1;
                while (comment_depth != 0) {
                    switch (*current) {
                        case '\0': { // @ERROR: EOF in comment
                            return Token(TT_EOF, line_number, column_number, current, 1);
                        }
                        case '\n': {
                            if (line_comment) {
                                line_comment = false;
                                comment_depth--;
                            }
                            current++;
                            line_number++;
                            column_number = 0;
                            break;
                        }
                        case '*': {
                            if (*(current+1) == '/') {
                                comment_depth--;
                                current += 2;
                                column_number += 2;
                            } else {
                                current++;
                                column_number++;
                            }
                            break;
                        }
                        case '/': {
                            if (*(current+1) == '*') {
                                comment_depth++;
                                current += 2;
                                column_number += 2;
                            } else if (*(current+1) == '/') {
                                comment_depth++;
                                line_comment = true;
                                current += 2;
                                column_number += 2;
                            } else {
                                current++;
                                column_number++;
                            }
                            break;
                        }
                        default: {
                            current++;
                            column_number++;
                        }
                    }
                }
                break;
            }
            default: {
                column_number++;
                start = current;
                current++;
                return Token(TT_SLASH, line_number, column_number, start, current - start);
                break;
            }
            }
            break;
        }
        default: goto whitespace_end;
        }
    }
    whitespace_end:
    start = current;
    switch (*current) {
        case '\0': {
            return Token(TT_EOF, line_number, column_number, current, 1);
        }
        case '(': {
            column_number++;
            current++;
            return Token(TT_LPAREN, line_number, column_number, start, current - start);
            break;
        }
        case ')': {
            column_number++;
            current++;
            return Token(TT_RPAREN, line_number, column_number, start, current - start);
            break;
        }
        case '[': {
            column_number++;
            current++;
            return Token(TT_LSQUARE, line_number, column_number, start, current - start);
            break;
        }
        case ']': {
            column_number++;
            current++;
            return Token(TT_RSQUARE, line_number, column_number, start, current - start);
            break;
        }
        case '{': {
            column_number++;
            current++;
            return Token(TT_LCURLY, line_number, column_number, start, current - start);
            break;
        }
        case '}': {
            column_number++;
            current++;
            return Token(TT_RCURLY, line_number, column_number, start, current - start);
            break;
        }
        case '+': {
            current++;
            if (*current == '+') {
                column_number += 2;
                current++;
                return Token(TT_PLUS_PLUS, line_number, column_number, start, current - start);
            } /*else if (*current == '=') {
                column_number += 2;
                current++;
                return Token(TT_PLUS_EQUALS, line_number, column_number, start, current - start);
            } */else {
                column_number++;
                current++;
                return Token(TT_PLUS, line_number, column_number, start, current - start);
            }
            break;
        }
        case '-': {
            current++;
            if (*current == '-') {
                column_number += 2;
                current++;
                return Token(TT_MINUS_MINUS, line_number, column_number, start, current - start);
            } /*else if (*current == '=') {
                column_number += 2;
                current++;
                return Token(TT_MINUS_EQUALS, line_number, column_number, start, current - start);
            } */else if (*current == '>') {
                column_number += 2;
                current++;
                return Token(TT_MINUS_GT, line_number, column_number, start, current - start);
            } else {
                column_number++;
                current++;
                return Token(TT_MINUS, line_number, column_number, start, current - start);
            }
            break;
        }
        case '*': {
            current++;
            if (*current == '*') {
                column_number += 2;
                current++;
                return Token(TT_STAR_STAR, line_number, column_number, start, current - start);
            } else {
                column_number++;
                return Token(TT_STAR, line_number, column_number, start, current - start);
            }
            break;
        }
        case '!': {
            current++;
            if (*current == '=') {
                column_number += 2;
                current++;
                return Token(TT_EXCL_EQUAL, line_number, column_number, start, current - start);
            } else {
                column_number++;
                return Token(TT_EXCL, line_number, column_number, start, current - start);
            }
            break;
        }
        case '=': {
            current++;
            if (*current == '=') {
                column_number += 2;
                current++;
                return Token(TT_EQUAL_EQUAL, line_number, column_number, start, current - start);
            } else {
                column_number++;
                return Token(TT_EQUAL, line_number, column_number, start, current - start);
            }
            break;
        }
        case '%': {
            column_number++;
            current++;
            return Token(TT_PERCENT, line_number, column_number, start, current - start);
            break;
        }
        case '^': {
            column_number++;
            current++;
            return Token(TT_CARET, line_number, column_number, start, current - start);
            break;
        }
        case '&': {
            current++;
            if (*current == '&') {
                column_number += 2;
                current++;
                return Token(TT_AMPERSAND_AMPERSAND, line_number, column_number, start, current - start);
            } else {
                column_number++;
                return Token(TT_AMPERSAND, line_number, column_number, start, current - start);
            }
            break;
        }
        case '|': {
            current++;
            if (*current == '|') {
                column_number += 2;
                current++;
                return Token(TT_PIPE_PIPE, line_number, column_number, start, current - start);
            } else {
                column_number++;
                return Token(TT_PIPE, line_number, column_number, start, current - start);
            }
            break;
        }
        case '<': {
            current++;
            if (*current == '=') {
                column_number += 2;
                current++;
                return Token(TT_LT_EQUAL, line_number, column_number, start, current - start);
            } else if (*current == '<') {
                column_number += 2;
                current++;
                return Token(TT_LT_LT, line_number, column_number, start, current - start);
            } else {
                column_number++;
                return Token(TT_LT, line_number, column_number, start, current - start);
            }
            break;
        }
        case '>': {
            current++;
            if (*current == '=') {
                column_number += 2;
                current++;
                return Token(TT_GT_EQUAL, line_number, column_number, start, current - start);
            } else if (*current == '>') {
                column_number += 2;
                current++;
                return Token(TT_GT_GT, line_number, column_number, start, current - start);
            } else {
                column_number++;
                return Token(TT_GT, line_number, column_number, start, current - start);
            }
            break;
        }
        case ',': {
            column_number++;
            current++;
            return Token(TT_COMMA, line_number, column_number, start, current - start);
            break;
        }
        case '"': {
            column_number++;
            current++;
            while (*current != '"') {
                if (*current == '\0') { // @ERROR: EOF in string literal
                    return Token(TT_EOF, line_number, column_number, current, 1);
                }
                if (*current == '\\' && *(current+1) == '"') {
                    column_number++;
                    current++;
                }
                column_number++;
                current++;
            }
            column_number++;
            current++;
            return Token(TT_STRING, line_number, column_number, start, current - start);
            break;
        }
        case '\'': {
            column_number++;
            current++;
            if (*current == '\\') {
                column_number++;
                current++;
            } else if (*current == '\0') { // @ERROR: EOF in character literal
                return Token(TT_EOF, line_number, column_number, current, 1);
            }
            column_number++;
            current++;
            return Token(TT_CHAR, line_number, column_number, start, current - start);
            break;
        }
        case '.': {
            column_number++;
            current++;
            return Token(TT_DOT, line_number, column_number, start, current - start);
            break;
        }
        case ':': {
            current++;
            if (*current == '=') {
                column_number += 2;
                current++;
                return Token(TT_COLON_EQUALS, line_number, column_number, start, current - start);
            } else if (*current == ':') {
                column_number += 2;
                current++;
                return Token(TT_COLON_COLON, line_number, column_number, start, current - start);
            } else {
                column_number++;
                return Token(TT_COLON, line_number, column_number, start, current - start);
            }
            break;
        }
        case ';': {
            column_number++;
            current++;
            return Token(TT_SEMICOLON, line_number, column_number, start, current - start);
            break;
        }
        default: { // Identifier or number or keyword
            if (is_alpha(*current)) {
                column_number++;
                current++;
                while (is_alpha(*current) || is_digit(*current)) {
                    column_number++;
                    current++;
                }
                TokenType ident_type = TT_IDENT;
                switch (*start) {
                    case 'b': ident_type = check_keyword(1, 4, "reak", TT_BREAK); break;
                    case 'c':
                        if (current - start > 3) {
                            switch (start[1]) {
                                case 'a':
                                    if (current - start == 4 && start[2] == 's') {
                                        if (start[3] == 'e') {
                                            ident_type = TT_CASE;
                                        } else if (start[3] == 't') {
                                            ident_type = TT_CAST;
                                        }
                                    } break;
                                case 'o': ident_type = check_keyword(2, 6, "ntinue", TT_CONTINUE); break;
                            }
                        } break;
                    case 'e': ident_type = check_keyword(1, 3, "num", TT_ENUM); break;
                    case 'f':
                        if (current - start > 2) {
                            switch (start[1]) {
                                case 'a': ident_type = check_keyword(2, 3, "lse", TT_FALSE); break;
                                case 'o': if (current - start == 3 && start[2] == 'r') { ident_type = TT_FOR; } break;
                            }
                        } break;
                    case 'i':
                        if (current - start > 1) {
                            switch (start[1]) {
                                case 'f': if (current - start == 2) { ident_type = TT_IF; } break;
                                case 'n': ident_type = check_keyword(2, 5, "clude", TT_INCLUDE); break;
                            }
                        } break;
                    case 'r': ident_type = check_keyword(1, 5, "eturn", TT_RETURN); break;
                    case 's':
                        if (current - start > 2) {
                            switch (start[1]) {
                                case 'o': if (current - start == 3 && start[2] == 'a') { ident_type = TT_SOA; } break;
                                case 't': ident_type = check_keyword(2, 4, "ruct", TT_STRUCT); break;
                                case 'w': ident_type = check_keyword(2, 4, "itch", TT_SWITCH); break;
                            }
                        } break;
                    case 't': ident_type = check_keyword(1, 3, "rue", TT_TRUE); break;
                    case 'u':
                        if (current - start == 5) {
                            switch (start[1]) {
                                case 'n': ident_type = check_keyword(2, 3, "ion", TT_UNION); break;
                                case 's': ident_type = check_keyword(2, 3, "ing", TT_USING); break;
                            }
                        } break;
                    case 'w': ident_type = check_keyword(1, 4, "hile", TT_WHILE); break;
                }
                return Token(ident_type, line_number, column_number, start, current - start);
            } else if (is_digit(*current)) {
                bool floating_point = false;
                column_number++;
                current++;
                while (is_digit(*current)) {
                    column_number++;
                    current++;
                }
                if (*current == '.' && is_digit(*(current + 1))) {
                    column_number += 2;
                    current += 2;
                    floating_point = true;
                    while (is_digit(*current)) {
                        column_number++;
                        current++;
                    }
                }
                return Token(floating_point ? TT_FLOAT : TT_INT, line_number, column_number, start, current - start);
            } else { // @ERROR: Unkown character
                return Token(TT_EOF, line_number, column_number, start, current - start);
            }
            break;
        }
    }
}