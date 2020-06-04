#include "Lexer.h"
#include "KeywordList.h"

TokenType get_token_type(const std::string& token) {
    return (TokenType)0;
}

u32 get_symbol_table_entry(const std::string& token, TokenType type) {
    return 0;
}

void Lexer::make_token(const std::string& token) {
    if (token.length() == 0) {
        return;
    }

    TokenType type = TT_IDENT;

    for (int i = 0; i < KEYWORD_LIST_LEN; i++)
	{
		if (token == KEYWORD_LIST[i])
		{
			type = (TokenType)i;
			break;
		}
	}
    if (type == TT_IDENT) {
        if (token[0] >= '0' && token[0] <= '9') {
            bool is_float = false;
            bool is_invalid = false;
            for (char c : token) {
                if (c == '.') {
                    if (is_float) {
                        is_invalid = true;
                        break;
                    }
                    is_float = true;
                }
            }
            if (is_invalid) {
                errors.push_back(Error{0, line_number, column_number});
                return;
            }
            if (is_float) {

            } else {
                
            }
        } else if (token[0] < 'A' || (token[0] > 'Z' && token[0] < 'a' && token[0] != '_') || token[0] > 'z') {
            //Not a valid identifier, and not a number, and not a keyword, and not an operator! Lexical error!
        }
    }

    tokens.push_back(Token(type, get_symbol_table_entry(token, type)));
}

void Lexer::make_tokens(const std::string& input_string) {
    tokens = std::vector<Token>();
    errors = std::vector<Error>();
    line_number = 1;
    column_number = 1;
    std::string intermediate;
    intermediate.reserve(127);
    //std::vector<char> splitChars = { ' ', '\n', '\t', '\f', '(', ')', '[', ']', '+', '-', '/', '*', '!', '=', '%', '^', '&', '|', '<', '>', ',', '"', '\'', '.', ':' };
    //std::vector<std::string> splitDuoStrings = { "/*", "*/", "//", "**", "&&", "==", "!=", "<=", ">=", "<<", ">>", "<-", "->", "||", "++", "--", "+=", "-=" };

    int i = 0;
    for (i; i < input_string.length();) {
        char c = input_string[i];

        switch (c) {
            case '\n': {
                line_number++;
                column_number = 0;
                break;
            }
            case ' ': case '\f': {
                column_number++;
                break;
            }
            case '\t': {
                column_number += 4;
                break;
            }
            case '(': {
                make_token(intermediate);
                intermediate = "";
                tokens.push_back(Token(TT_LPAREN));
                break;
            }
            case ')': {

                break;
            }
            case '[': {

                break;
            }
            case ']': {

                break;
            }
            case '+': {
                char c2 = input_string[i+1];
                if (c2 == '+') {

                } else if (c2 == '=') {
                    
                } else {

                }
                break;
            }
            case '-': {
                char c2 = input_string[i+1];
                if (c2 == '-') {

                } else if (c2 == '=') {
                    
                } else {

                }
                break;
            }
            case '/': {
                char c2 = input_string[i+1];
                if (c2 == '*') {

                } else if (c2 == '/') {

                } else {

                }
                break;
            }
            case '*': {
                char c2 = input_string[i+1];
                if (c2 == '/') {

                } else if (c2 == '*') {
                    
                } else {

                }
                break;
            }
            case '!': {
                if (input_string[i+1] == '=') {

                } else {
                    
                }
                break;
            }
            case '=': {
                if (input_string[i+1] == '=') {

                } else {
                    
                }
                break;
            }
            case '%': {

                break;
            }
            case '^': {

                break;
            }
            case '&': {
                if (input_string[i+1] == '&') {

                } else {
                    
                }
                break;
            }
            case '|': {
                if (input_string[i+1] == '|') {

                } else {
                    
                }
                break;
            }
            case '<': {
                char c2 = input_string[i+1];
                if (c2 == '=') {

                } else if (c2 == '<') {
                    
                } else if (c2 == '-') {
                    
                } else {

                }
                break;
            }
            case '>': {
                char c2 = input_string[i+1];
                if (c2 == '=') {

                } else if (c2 == '>') {
                    
                } else if (c2 == '-') {
                    
                } else {

                }
                break;
            }
            case ',': {

                break;
            }
            case '"': {

                break;
            }
            case '\'': {

                break;
            }
            case '.': {

                break;
            }
            case ':': {
                char c2 = input_string[i+1];
                if (c2 == '=') {

                } else if (c2 == ':') {
                    
                } else {

                }
                break;
            }
            default: {
                intermediate += c;
                break;
            }
        }
        i++;
    }
    make_token(intermediate);
}
