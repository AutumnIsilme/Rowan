#include "Lexer.h"
#include "KeywordList.h"

TokenType get_token_type(const std::string& token) {
    return (TokenType)0;
}

u32 get_symbol_table_entry(const std::string& token, TokenType type) {
    return 0;
}

void Lexer::make_token(const std::string& token) {
    if (token.length() == 0 || comment_depth != 0) {
        return;
    }

    TokenType type = TT_IDENT;
    bool is_invalid = false;

    for (int i = 0; i < KEYWORD_LIST_LEN; i++)
	{
		if (token == KEYWORD_LIST[i])
		{
			type = (TokenType)i;
			break;
		}
	}
    if (type == TT_IDENT) { //If it is not a keyword...
        if (token[0] >= '0' && token[0] <= '9') {
            bool is_float = false;
            for (char c : token) {
                if (c == '.') {
                    if (is_float) {
                        is_invalid = true;
                        break;
                    }
                    is_float = true;
                }
                else if (c < '0' || c > '9') {
                    is_invalid = true;
                }
            }
            if (is_invalid) {
                if (is_float)
                    errors.push_back(Error{0, line_number, column_number});
                else
                    errors.push_back(Error{1, line_number, column_number});
                return;
            }
            if (is_float) {
                type = TT_FLOAT;
            } else {
                type = TT_INT;
            }
        } else if (token[0] < 'A' || (token[0] > 'Z' && token[0] < 'a' && token[0] != '_') || token[0] > 'z') {
            //Not a valid identifier, and not a number, and not a keyword, and not an operator! Lexical error!
            errors.push_back(Error{2, line_number, column_number});
        } else {
            type = TT_IDENT;
        }
    }

    if (!is_invalid)
        tokens->push_back(Token(type, line_number, column_number, token));
}

void Lexer::make_tokens(const std::string& input_string) {
    if (tokens)
        delete tokens;
    tokens = new std::vector<Token>();
    std::vector<Token>* token_backup = tokens;
    errors = std::vector<Error>();
    line_number = 1;
    column_number = 1;
    std::string intermediate;
    intermediate.reserve(127);
    //std::vector<char> splitChars = { ' ', '\n', '\t', '\f', '(', ')', '[', ']', '+', '-', '/', '*', '!', '=', '%', '^', '&', '|', '<', '>', ',', '"', '\'', '.', ':' };
    //std::vector<std::string> splitDuoStrings = { "/*", "*/", "//", "**", "&&", "==", "!=", "<=", ">=", "<<", ">>", "<-", "->", "||", "++", "--", "+=", "-=" };

    int i = 0;
    for (; i < input_string.length();) {
        char c = input_string[i];

        switch (c) {
            case '\n': case '\r': {
                make_token(intermediate);
                intermediate = "";
                line_number++;
                column_number = 1;
                i++;
                if (line_comment) {
                    comment_depth--;
                    if (comment_depth == 0) {
                        delete tokens;
                        tokens = token_backup;
                    }
                }
                break;
            }
            case ' ': case '\f': {
                make_token(intermediate);
                intermediate = "";
                column_number++;
                i++;
                break;
            }
            case '\t': {
                make_token(intermediate);
                intermediate = "";
                column_number += 4;
                i++;
                break;
            }
            case '(': {
                make_token(intermediate);
                intermediate = "";
                tokens->push_back(Token(TT_LPAREN, line_number, column_number, "("));
                column_number++;
                i++;
                break;
            }
            case ')': {
                make_token(intermediate);
                intermediate = "";
                tokens->push_back(Token(TT_RPAREN, line_number, column_number, ")"));
                column_number++;
                i++;
                break;
            }
            case '[': {
                make_token(intermediate);
                intermediate = "";
                tokens->push_back(Token(TT_LSQUARE, line_number, column_number, "["));
                column_number++;
                i++;
                break;
            }
            case ']': {
                make_token(intermediate);
                intermediate = "";
                tokens->push_back(Token(TT_RSQUARE, line_number, column_number, "]"));
                column_number++;
                i++;
                break;
            }
            case '{': {
                make_token(intermediate);
                intermediate = "";
                tokens->push_back(Token(TT_LCURLY, line_number, column_number, "{"));
                column_number++;
                i++;
                break;
            }
            case '}': {
                make_token(intermediate);
                intermediate = "";
                tokens->push_back(Token(TT_RCURLY, line_number, column_number, "}"));
                column_number++;
                i++;
                break;
            }
            case '+': {
                make_token(intermediate);
                intermediate = "";
                char c2 = input_string[i+1];
                if (c2 == '+') {
                    tokens->push_back(Token(TT_PLUS_PLUS, line_number, column_number, "++"));
                    column_number += 2;
                    i += 2;
                } else if (c2 == '=') {
                    tokens->push_back(Token(TT_PLUS_EQUALS, line_number, column_number, "+="));
                    column_number += 2;
                    i += 2;
                } else {
                    tokens->push_back(Token(TT_PLUS, line_number, column_number, "+"));
                    column_number++;
                    i++;
                }
                break;
            }
            case '-': {
                make_token(intermediate);
                intermediate = "";
                char c2 = input_string[i+1];
                if (c2 == '-') {
                    tokens->push_back(Token(TT_MINUS_MINUS, line_number, column_number, "--"));
                    column_number += 2;
                    i += 2;
                } else if (c2 == '=') {
                    tokens->push_back(Token(TT_MINUS_EQUALS, line_number, column_number, "-="));
                    column_number += 2;
                    i += 2;
                } else if (c2 == '>') {
                    tokens->push_back(Token(TT_MINUS_GT, line_number, column_number, "->"));
                    column_number += 2;
                    i += 2;
                }else {
                    tokens->push_back(Token(TT_MINUS, line_number, column_number, "-"));
                    column_number++;
                    i++;
                }
                break;
            }
            case '/': {
                make_token(intermediate);
                intermediate = "";
                char c2 = input_string[i+1];
                if (c2 == '*') {
                    if (comment_depth == 0)
                    {
                        tokens = new std::vector<Token>();
                    }
                    comment_depth++;
                    column_number += 2;
                    i += 2;
                } else if (c2 == '/') {
                    if (comment_depth == 0)
                    {
                        tokens = new std::vector<Token>();
                    }
                    comment_depth++;
                    line_comment = true;
                    i += 2;
                    column_number += 2;
                } else {
                    tokens->push_back(Token(TT_SLASH, line_number, column_number, "/"));
                    column_number++;
                    i++;
                }
                break;
            }
            case '*': {
                make_token(intermediate);
                intermediate = "";
                char c2 = input_string[i+1];
                if (c2 == '/') {
                    comment_depth--;
                    if (comment_depth == 0) {
                        delete tokens;
                        tokens = token_backup;
                    }
                    column_number += 2;
                    i += 2;
                } else if (c2 == '*') {
                    tokens->push_back(Token(TT_STAR_STAR, line_number, column_number, "**"));
                    column_number += 2;
                    i += 2;
                } else {
                    tokens->push_back(Token(TT_STAR, line_number, column_number, "*"));
                    column_number++;
                    i++;
                }
                break;
            }
            case '!': {
                make_token(intermediate);
                intermediate = "";
                if (input_string[i+1] == '=') {
                    tokens->push_back(Token(TT_EXCL_EQUAL, line_number, column_number, "!="));
                    column_number += 2;
                    i += 2;
                } else {
                    tokens->push_back(Token(TT_EXCL, line_number, column_number, "!"));
                    column_number++;
                    i++;
                }
                break;
            }
            case '=': {
                make_token(intermediate);
                intermediate = "";
                if (input_string[i+1] == '=') {
                    tokens->push_back(Token(TT_EQUAL_EQUAL, line_number, column_number, "=="));
                    column_number += 2;
                    i += 2;
                } else {
                    tokens->push_back(Token(TT_EQUAL, line_number, column_number, "="));
                    column_number++;
                    i++;
                }
                break;
            }
            case '%': {
                make_token(intermediate);
                intermediate = "";
                tokens->push_back(Token(TT_PERCENT, line_number, column_number, "%"));
                break;
            }
            case '^': {
                make_token(intermediate);
                intermediate = "";
                tokens->push_back(Token(TT_CARET, line_number, column_number, "^"));
                break;
            }
            case '&': {
                make_token(intermediate);
                intermediate = "";
                if (input_string[i+1] == '&') {
                    tokens->push_back(Token(TT_AMPERSAND_AMPERSAND, line_number, column_number, "&&"));
                    column_number += 2;
                    i += 2;
                } else {
                    tokens->push_back(Token(TT_AMPERSAND, line_number, column_number, "&"));
                    column_number++;
                    i++;
                }
                break;
            }
            case '|': {
                make_token(intermediate);
                intermediate = "";
                if (input_string[i+1] == '|') {
                    tokens->push_back(Token(TT_PIPE_PIPE, line_number, column_number, "||"));
                    column_number += 2;
                    i += 2;
                } else {
                    tokens->push_back(Token(TT_PIPE, line_number, column_number, "|"));
                    column_number++;
                    i++;
                }
                break;
            }
            case '<': {
                make_token(intermediate);
                intermediate = "";
                char c2 = input_string[i+1];
                if (c2 == '=') {
                    tokens->push_back(Token(TT_LT_EQUAL, line_number, column_number, "<="));
                    column_number += 2;
                    i += 2;
                } else if (c2 == '<') {
                    tokens->push_back(Token(TT_LT_LT, line_number, column_number, "<<"));
                    column_number += 2;
                    i += 2;
                } else {
                    tokens->push_back(Token(TT_LT, line_number, column_number, "<"));
                    column_number++;
                    i++;
                }
                break;
            }
            case '>': {
                make_token(intermediate);
                intermediate = "";
                char c2 = input_string[i+1];
                if (c2 == '=') {
                    tokens->push_back(Token(TT_GT_EQUAL, line_number, column_number, ">="));
                    column_number += 2;
                    i += 2;
                } else if (c2 == '>') {
                    tokens->push_back(Token(TT_GT_GT, line_number, column_number, ">>"));
                    column_number += 2;
                    i += 2;
                } else {
                    tokens->push_back(Token(TT_GT, line_number, column_number, ">"));
                    column_number++;
                    i++;
                }
                break;
            }
            case ',': {
                make_token(intermediate);
                intermediate = "";
                tokens->push_back(Token(TT_COMMA, line_number, column_number, ","));
                column_number++;
                i++;
                break;
            }
            case '"': {
                make_token(intermediate);
                intermediate = "";
                if (comment_depth == 0) {
                    i++;
                    while (input_string[i] != '"') {
                        while (input_string[i] != '\\' && input_string[i] != '"') {
                            intermediate += input_string[i];
                            i++;
                        }
                        if (input_string[i] == '\\') {
                            intermediate += input_string[i] + input_string[i+1];
                            i += 2;
                        }
                    }
                    i++;
                    tokens->push_back(Token(TT_STRING, line_number, column_number, intermediate));
                    intermediate = "";
                } else
                    i++;
                break;
            }
            case '\'': {
                make_token(intermediate);
                intermediate = "";
                if (input_string[i+1] == '\\') {
                    tokens->push_back(Token(TT_CHAR, line_number, column_number, "\\" + std::string(1, input_string[i+2])));
                    i += 3;
                } else {
                    tokens->push_back(Token(TT_CHAR, line_number, column_number, std::string(1, input_string[i+1])));
                    i += 2;
                }
                break;
            }
            case '.': {
                if (intermediate[0] >= '0' && intermediate[0] <= '9') {
                    intermediate += c;
                } else {
                    make_token(intermediate);
                    intermediate = "";
                    tokens->push_back(Token(TT_DOT, line_number, column_number, "."));
                }
                column_number++;
                i++;
                break;
            }
            case ':': {
                char c2 = input_string[i+1];
                if (c2 == '=') {
                    tokens->push_back(Token(TT_COLON_EQUALS, line_number, column_number, ":="));
                    column_number += 2;
                    i += 2;
                } else if (c2 == ':') {
                    tokens->push_back(Token(TT_COLON_COLON, line_number, column_number, "::"));
                    column_number += 2;
                    i += 2;
                } else {
                    tokens->push_back(Token(TT_COLON, line_number, column_number, ":"));
                    column_number++;
                    i++;
                }
                break;
            }
            default: {
                intermediate += c;
                column_number++;
                i++;
                break;
            }
        }
    }
    make_token(intermediate);
    tokens = token_backup;
}
