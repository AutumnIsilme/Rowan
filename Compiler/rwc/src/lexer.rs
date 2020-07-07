use crate::{token::{Token, TokenType}, keyword_list, error::Error};
use std::convert::TryFrom;

pub struct Lexer {
    pub line_number: u32,
    pub column_number: u32,

    pub comment_depth: u32,
    pub line_comment: bool,
}

impl Lexer {
    pub fn create() -> Lexer {
        return Lexer {
            line_number: 0,
            column_number: 0,
            comment_depth: 0,
            line_comment: false,
        }
    }

    pub fn make_tokens(&mut self, input_string: &str) -> (Vec<Token>, Vec<Error>) {
        let mut tokens_master: Vec<Token> = Vec::new();
        let mut tokens_discard: Vec<Token> = Vec::new();
        let mut tokens: &mut Vec<Token> = &mut tokens_master;
        let mut errors: Vec<Error> = Vec::new();
        
        self.line_number = 1;
        self.column_number = 1;
        let mut intermediate = String::with_capacity(127);

        println!("Input length: {}", input_string.len());

        let mut i: usize = 0;
        loop {
            let c = match input_string.chars().nth(i) {
                Some(k) => k,
                None => break,
            };

            match c {
                '\n' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    self.line_number += 1;
                    self.column_number = 1;
                    i += 1;
                    if self.line_comment {
                        self.comment_depth -= 1;
                        if self.comment_depth == 0 {
                            tokens = &mut tokens_master;
                        }
                    }
                },
                '\r' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    self.column_number += 1;
                    i += 1;
                    if self.line_comment {
                        self.comment_depth -= 1;
                        if self.comment_depth == 0 {
                            tokens = &mut tokens_master;
                        }
                    }
                }
                ' ' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    self.column_number += 1;
                    i += 1;
                },
                '\t' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    self.column_number += 4;
                    i += 1;
                },
                '(' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    tokens.push(Token::create(TokenType::LPAREN, self.line_number, self.column_number, "("));
                    self.column_number += 1;
                    i += 1;
                },
                ')' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    tokens.push(Token::create(TokenType::RPAREN, self.line_number, self.column_number, ")"));
                    self.column_number += 1;
                    i += 1;
                },
                '[' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    tokens.push(Token::create(TokenType::LSQUARE, self.line_number, self.column_number, "["));
                    self.column_number += 1;
                    i += 1;
                },
                ']' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    tokens.push(Token::create(TokenType::RSQUARE, self.line_number, self.column_number, "]"));
                    self.column_number += 1;
                    i += 1;
                },
                '{' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    tokens.push(Token::create(TokenType::LCURLY, self.line_number, self.column_number, "{"));
                    self.column_number += 1;
                    i += 1;
                },
                '}' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    tokens.push(Token::create(TokenType::RCURLY, self.line_number, self.column_number, "}"));
                    self.column_number += 1;
                    i += 1;
                },
                '+' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    let c2 = match input_string.chars().nth(i+1) {
                        Some(k) => k,
                        None => ' ',
                    };
                    if c2 == '+' {
                        tokens.push(Token::create(TokenType::PLUS_PLUS, self.line_number, self.column_number, "++"));
                        self.column_number += 2;
                        i += 2;
                    } else if c2 == '=' {
                        tokens.push(Token::create(TokenType::PLUS_EQUALS, self.line_number, self.column_number, "+="));
                        self.column_number += 2;
                        i += 2;
                    } else {
                        tokens.push(Token::create(TokenType::PLUS, self.line_number, self.column_number, "+"));
                        self.column_number += 1;
                        i += 1;
                    }
                },
                '-' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    let c2 = match input_string.chars().nth(i+1) {
                        Some(k) => k,
                        None => ' ',
                    };
                    if c2 == '-' {
                        tokens.push(Token::create(TokenType::MINUS_MINUS, self.line_number, self.column_number, "--"));
                        self.column_number += 2;
                        i += 2;
                    } else if c2 == '=' {
                        tokens.push(Token::create(TokenType::MINUS_EQUALS, self.line_number, self.column_number, "-="));
                        self.column_number += 2;
                        i += 2;
                    } else if c2 == '>' {
                        tokens.push(Token::create(TokenType::MINUS_GT, self.line_number, self.column_number, "->"));
                        self.column_number += 2;
                        i += 2;
                    }else {
                        tokens.push(Token::create(TokenType::MINUS, self.line_number, self.column_number, "-"));
                        self.column_number += 1;
                        i += 1;
                    }
                },
                '/' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    let c2 = match input_string.chars().nth(i+1) {
                        Some(k) => k,
                        None => ' ',
                    };
                    if c2 == '*' {
                        //tokens = &mut tokens_discard;
                        self.comment_depth += 1;
                        self.column_number += 2;
                        i += 2;
                        self.consume_comments(&mut errors, input_string, &mut i);
                    } else if c2 == '/' {
                        if self.comment_depth == 0
                        {
                            tokens = &mut tokens_discard;
                        }
                        self.comment_depth += 1;
                        self.line_comment = true;
                        i += 2;
                        self.column_number += 2;
                        self.consume_comments(&mut errors, input_string, &mut i);
                    } else {
                        tokens.push(Token::create(TokenType::SLASH, self.line_number, self.column_number, "/"));
                        self.column_number += 1;
                        i += 1;
                    }
                },
                '*' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    let c2 = match input_string.chars().nth(i+1) {
                        Some(k) => k,
                        None => ' ',
                    };
                    if c2 == '/' {
                        if self.comment_depth != 0 {
                            self.comment_depth -= 1;
                            if self.comment_depth == 0 {
                                tokens = &mut tokens_master;
                            }
                        } else {
                            tokens.push(Token::create(TokenType::STAR, self.line_number, self.column_number, "*"));
                            tokens.push(Token::create(TokenType::SLASH, self.line_number, self.column_number, "/"));
                        }
                        self.column_number += 2;
                        i += 2;
                    } else if c2 == '*' {
                        tokens.push(Token::create(TokenType::STAR_STAR, self.line_number, self.column_number, "**"));
                        self.column_number += 2;
                        i += 2;
                    } else {
                        tokens.push(Token::create(TokenType::STAR, self.line_number, self.column_number, "*"));
                        self.column_number += 1;
                        i += 1;
                    }
                },
                '!' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    if match input_string.chars().nth(i+1) { Some(k) => k, None => ' ' } == '=' {
                        tokens.push(Token::create(TokenType::EXCL_EQUAL, self.line_number, self.column_number, "!="));
                        self.column_number += 2;
                        i += 2;
                    } else {
                        tokens.push(Token::create(TokenType::EXCL, self.line_number, self.column_number, "!"));
                        self.column_number += 1;
                        i += 1;
                    }
                },
                '=' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    if match input_string.chars().nth(i+1) { Some(k) => k, None => ' ' } == '=' {
                        tokens.push(Token::create(TokenType::EQUAL_EQUAL, self.line_number, self.column_number, "=="));
                        self.column_number += 2;
                        i += 2;
                    } else {
                        tokens.push(Token::create(TokenType::EQUAL, self.line_number, self.column_number, "="));
                        self.column_number += 1;
                        i += 1;
                    }
                },
                '%' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    tokens.push(Token::create(TokenType::PERCENT, self.line_number, self.column_number, "%"));
                },
                '^' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    tokens.push(Token::create(TokenType::CARET, self.line_number, self.column_number, "^"));
                },
                '&' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    if match input_string.chars().nth(i+1) { Some(k) => k, None => ' ' } == '&' {
                        tokens.push(Token::create(TokenType::AMPERSAND_AMPERSAND, self.line_number, self.column_number, "&&"));
                        self.column_number += 2;
                        i += 2;
                    } else {
                        tokens.push(Token::create(TokenType::AMPERSAND, self.line_number, self.column_number, "&"));
                        self.column_number += 1;
                        i += 1;
                    }
                },
                '|' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    if match input_string.chars().nth(i+1) { Some(k) => k, None => ' ' } == '|' {
                        tokens.push(Token::create(TokenType::PIPE_PIPE, self.line_number, self.column_number, "||"));
                        self.column_number += 2;
                        i += 2;
                    } else {
                        tokens.push(Token::create(TokenType::PIPE, self.line_number, self.column_number, "|"));
                        self.column_number += 1;
                        i += 1;
                    }
                },
                '<' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    let c2 = match input_string.chars().nth(i+1) {
                        Some(k) => k,
                        None => ' ',
                    };
                    if c2 == '=' {
                        tokens.push(Token::create(TokenType::LT_EQUAL, self.line_number, self.column_number, "<="));
                        self.column_number += 2;
                        i += 2;
                    } else if c2 == '<' {
                        tokens.push(Token::create(TokenType::LT_LT, self.line_number, self.column_number, "<<"));
                        self.column_number += 2;
                        i += 2;
                    } else {
                        tokens.push(Token::create(TokenType::LT, self.line_number, self.column_number, "<"));
                        self.column_number += 1;
                        i += 1;
                    }
                },
                '>' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    let c2 = match input_string.chars().nth(i+1) {
                        Some(k) => k,
                        None => ' ',
                    };
                    if c2 == '=' {
                        tokens.push(Token::create(TokenType::GT_EQUAL, self.line_number, self.column_number, ">="));
                        self.column_number += 2;
                        i += 2;
                    } else if c2 == '>' {
                        tokens.push(Token::create(TokenType::GT_GT, self.line_number, self.column_number, ">>"));
                        self.column_number += 2;
                        i += 2;
                    } else {
                        tokens.push(Token::create(TokenType::GT, self.line_number, self.column_number, ">"));
                        self.column_number += 1;
                        i += 1;
                    }
                },
                ',' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    tokens.push(Token::create(TokenType::COMMA, self.line_number, self.column_number, ","));
                    self.column_number += 1;
                    i += 1;
                },
                '"' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    if self.comment_depth == 0 {
                        i += 1;
                        let mut c2 = match input_string.chars().nth(i) { Some(k) => k, None => ' ' };
                        while c2 != '"' {
                            c2 = match input_string.chars().nth(i) { Some(k) => k, None => ' ' };
                            while c2 != '\\' && c2 != '"' {
                                intermediate.push(c2);
                                i += 1;
                                c2 = match input_string.chars().nth(i) { Some(k) => k, None => ' ' };
                            }
                            if c2 == '\\' {
                                intermediate.push(c2);
                                intermediate.push(match input_string.chars().nth(i+1) { Some(k) => k, None => ' ' });
                                i += 2;
                            }
                        }
                        i += 1;
                        tokens.push(Token::create(TokenType::STRING, self.line_number, self.column_number, intermediate.as_str()));
                        intermediate.clear();
                    } else {
                        i += 1;
                    }
                },
                '\'' => {
                    self.make_token(tokens, &mut errors,  intermediate.as_str());
                    intermediate.clear();
                    if match input_string.chars().nth(i+1) { Some(k) => k, None => ' ' } == '\\' {
                        tokens.push(Token::create(TokenType::CHAR, self.line_number, self.column_number, format!("\\{}", match input_string.chars().nth(i+2) { Some(k) => k, None => ' ' }).as_str()));
                        i += 3;
                    } else {
                        tokens.push(Token::create(TokenType::CHAR, self.line_number, self.column_number, format!("{}", match input_string.chars().nth(i+1) { Some(k) => k, None => ' ' }).as_str()));
                        i += 2;
                    }
                },
                '.' => {
                    if intermediate.chars().nth(0).unwrap() >= '0' && intermediate.chars().nth(0).unwrap() <= '9' {
                        intermediate.push(c);
                    } else {
                        self.make_token(tokens, &mut errors,  intermediate.as_str());
                        intermediate.clear();
                        tokens.push(Token::create(TokenType::DOT, self.line_number, self.column_number, "."));
                    }
                    self.column_number += 1;
                    i += 1;
                },
                ':' => {
                    let c2 = match input_string.chars().nth(i+1) {
                        Some(k) => k,
                        None => ' ',
                    };
                    if c2 == '=' {
                        tokens.push(Token::create(TokenType::COLON_EQUALS, self.line_number, self.column_number, ":="));
                        self.column_number += 2;
                        i += 2;
                    } else if c2 == ':' {
                        tokens.push(Token::create(TokenType::COLON_COLON, self.line_number, self.column_number, "::"));
                        self.column_number += 2;
                        i += 2;
                    } else {
                        tokens.push(Token::create(TokenType::COLON, self.line_number, self.column_number, ":"));
                        self.column_number += 1;
                        i += 1;
                    }
                },
                ';' => {
                    self.make_token(tokens, &mut errors, intermediate.as_str());
                    intermediate.clear();
                    tokens.push(Token::create(TokenType::SEMICOLON, self.line_number, self.column_number, ";"));
                    self.column_number += 1;
                    i += 1;
                }
                _ => {
                    intermediate.push(c);
                    self.column_number += 1;
                    i += 1;
                }
            }
        }

        return (tokens_master, errors);
    }

    fn consume_comments(&mut self, errors: &mut Vec<Error>, input_string: &str, i: &mut usize) {
        loop {
            if self.comment_depth == 0 {
                break;
            }
            
            let c = match input_string.chars().nth(*i) { Some(c) => c, None => {
                errors.push(Error::create(3, self.line_number, self.column_number));
                break;
            }};
            match c {
                '\n' => {
                    if self.line_comment {
                        self.line_comment = false;
                        self.comment_depth -= 1;
                    }
                    self.line_number += 1;
                    self.column_number = 1;
                    *i += 1;
                },
                '/' => {
                    let c2 = match input_string.chars().nth(*i+1) { Some(c) => c, None => {
                        errors.push(Error::create(3, self.line_number, self.column_number));
                        break;
                    }};
                    if c2 == '/' {
                        if !self.line_comment {
                            self.line_comment = true;
                            self.comment_depth += 1;
                        }
                        self.column_number += 2;
                        *i += 2;
                    } else if c2 == '*' {
                        self.comment_depth += 1;
                        self.column_number += 2;
                        *i += 2;
                    } else {
                        self.column_number += 1;
                        *i += 1;
                    }
                },
                '*' => {
                    let c2 = match input_string.chars().nth(*i+1) { Some(c) => c, None => {
                        errors.push(Error::create(3, self.line_number, self.column_number));
                        break;
                    }};
                    if c2 == '/' {
                        if (self.comment_depth > 0 &&! self.line_comment) || self.comment_depth > 1 {
                            self.comment_depth -= 1;
                        }
                        self.column_number += 2;
                        *i += 2;
                    } else {
                        self.column_number += 1;
                        *i += 1;
                    }
                },
                '\t' => {
                    self.column_number += 4;
                    *i += 1;
                },
                _ => {
                    self.column_number += 1;
                    *i += 1;
                },
            }
        }
    }

    fn make_token(&self, tokens: &mut Vec<Token>, errors: &mut Vec<Error>, token: &str) {
        if token.len() == 0 || self.comment_depth != 0 {
            return;
        }

        let mut token_type: TokenType = TokenType::IDENT;
        let mut is_invalid = false;
        
        for i in 0..keyword_list::KEYWORD_LIST.len() {
            if token == keyword_list::KEYWORD_LIST[i] {
                match TokenType::try_from(i) {
                    Ok(out_token_type) => { token_type = out_token_type; break; },
                    Err(_) => println!("This shouldn't happen!"),
                }
            }
        }
        if token_type == TokenType::IDENT {
            let c = token.chars().nth(0).expect("0 out of range.");
            if c >= '0' && c <= '9' {
                let mut is_float = false;
                for c in token.chars(){
                    if c == '.' {
                        if is_float {
                            is_invalid = true;
                            break;
                        }
                        is_float = true;
                    }
                    else if c < '0' || c > '9' {
                        is_invalid = true;
                    }
                }
                if is_invalid {
                    if is_float { 
                        errors.push(Error::create(0, self.line_number, self.column_number)); 
                    } else { 
                        errors.push(Error::create(1, self.line_number, self.column_number)); 
                        println!("{}", token);
                    }
                    return;
                }
                if is_float {
                    token_type = TokenType::FLOAT;
                } else {
                    token_type = TokenType::INT;
                }
            } else if c < 'A' || (c > 'Z' && c < 'a' && c != '_') || c > 'z' {
                errors.push(Error::create(2, self.line_number, self.column_number));
            } else {
                token_type = TokenType::IDENT;
            }
        }

        if !is_invalid {
            tokens.push(Token::create(token_type, self.line_number, self.column_number - token.len() as u32, token));
        }
    }
}