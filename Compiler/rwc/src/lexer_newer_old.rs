use super::{types, token::{Token, TokenType}, keyword_list};
use num_enum::TryFromPrimitive;
use std::convert::TryFrom;

pub struct Lexer<'a> {
    pub tokens: Vec<TokenType>,
    pub input_string: &'a str,

    pub current_token: TokenType,
    pub current_slice: String,
    pub current_line_number: usize,
    pub current_column_number: usize,
    
    peeked_current: bool,
    peeked_token: Option<TokenType>,
    peeked_slice: Option<String>,
    peeked_line_number: Option<usize>,
    peeked_column_number: Option<usize>,
    
    pub line_number: usize,
    pub column_number: usize,
    pub input_index: usize,
}

impl Lexer<'_> {
    pub fn create(input_string: &str) -> Lexer {
        return Lexer {
            tokens: Vec::new(),
            input_string: input_string,
            line_number: 1,
            column_number: 1,
            input_index: 0,
            current_token: TokenType::EOF,
            current_slice: String::new(),
            current_line_number: 0,
            current_column_number: 0,
            peeked_current: false,
            peeked_token: None,
            peeked_slice: None,
            peeked_line_number: None,
            peeked_column_number: None,
        }
    }

    pub fn peek(&mut self) -> TokenType {
        if self.peeked_current {
            return self.peeked_token.unwrap();
        }
        
        self.get_peek_data();

        return self.peeked_token.unwrap();
    }

    pub fn peek_slice(&mut self) -> String {
        if self.peeked_current {
            return self.peeked_slice.as_ref().unwrap().to_string();
        }

        self.get_peek_data();

        return self.peeked_slice.as_ref().unwrap().to_string();
    }

    pub fn peek_column_number(&mut self) -> usize {
        if self.peeked_current {
            return self.peeked_column_number.unwrap();
        }

        self.get_peek_data();

        return self.peeked_column_number.unwrap();
    }

    pub fn peek_line_number(&mut self) -> usize {
        if self.peeked_current {
            return self.peeked_line_number.unwrap();
        }

        self.get_peek_data();

        return self.peeked_line_number.unwrap();
    }

    fn get_peek_data(&mut self) {
        let (peeked_token, peeked_slice, peeked_line_number, peeked_column_number) = self.get_next_token();
        self.peeked_token = Some(peeked_token);
        self.peeked_slice = Some(peeked_slice);
        self.peeked_line_number = Some(peeked_line_number);
        self.peeked_column_number = Some(peeked_column_number);
        self.peeked_current = true;
    }

    pub fn next(&mut self) -> TokenType {
        if self.peeked_current {
            self.peeked_current = false;
            self.current_token = self.peeked_token.unwrap();
            self.current_slice = self.peeked_slice.as_ref().unwrap().to_string();
            self.current_line_number = self.peeked_line_number.unwrap();
            self.current_column_number = self.peeked_column_number.unwrap();
            return self.current_token;
        }

        let (current_token, current_slice, current_line_number, current_column_number) = self.get_next_token();
        self.current_token = current_token;
        self.current_slice = current_slice;
        self.current_line_number = current_line_number;
        self.current_column_number = current_column_number;
        return self.current_token;
    }

    pub fn get_next_token(&mut self) -> (TokenType, String, usize, usize) {
        let c = match self.input_string.chars().nth(self.input_index) {
            Some(c) => c,
            None => return (TokenType::EOF, String::new(), self.line_number, self.column_number),
        };
        let mut found_token = false;
        let mut token_type = TokenType::NONE;
        let mut slice = String::new();
        let mut stored_input_index = self.input_index;
        while !found_token {
            let c = match self.input_string.chars().nth(self.input_index) {
                Some(c) => c,
                None => return (TokenType::EOF, String::new(), self.line_number, self.column_number),
            };
        let (tslice, ttype) = match c {
            '\n' => {
                self.line_number += 1; self.column_number = 1;
                self.input_index += 1; stored_input_index = self.input_index;
                ("", TokenType::NONE)
            },
            '\r' | ' ' => {
                self.input_index += 1;
                ("", TokenType::NONE)
            }
            '\t' => {
                self.column_number += 4; //@TODO: Make this configurable
                self.input_index += 1; stored_input_index = self.input_index;
                ("", TokenType::NONE)
            },
            '(' => { found_token = true; self.input_index += 1; ("(", TokenType::LPAREN)},
            ')' => { found_token = true; self.input_index += 1; (")", TokenType::RPAREN)},
            '[' => { found_token = true; self.input_index += 1; ("[", TokenType::LSQUARE)},
            ']' => { found_token = true; self.input_index += 1; ("]", TokenType::RSQUARE)},
            '{' => { found_token = true; self.input_index += 1; ("{", TokenType::LCURLY)},
            '}' => { found_token = true; self.input_index += 1; ("}", TokenType::RCURLY)},
            '+' => { 
                found_token = true;
                self.input_index += 1;
                match self.input_string.chars().nth(self.input_index) {
                    Some(c) => match c {
                        '+' => {self.input_index += 1; ("++", TokenType::PLUS_PLUS)},
                        '=' => {self.input_index += 1; ("+=", TokenType::PLUS_EQUAL)},
                        _ => ("+", TokenType::PLUS),
                    },
                    None => ("+", TokenType::PLUS),
                }
            },
            '-' => {
                found_token = true;
                self.input_index += 1;
                match self.input_string.chars().nth(self.input_index) {
                    Some(c) => match c {
                        '-' => {self.input_index += 1; ("--", TokenType::MINUS_MINUS)},
                        '=' => {self.input_index += 1; ("-=", TokenType::MINUS_EQUAL)},
                        _ => ("-", TokenType::MINUS),
                    },
                    None => ("-", TokenType::MINUS),
                }
            },
            '/' => {
                found_token = true;
                self.input_index += 1;
                match self.input_string.chars().nth(self.input_index) {
                    Some(c) => match c {
                        '*' => {self.input_index += 1; ("/*", TokenType::SLASH_STAR)},
                        _ => ("/", TokenType::SLASH),
                    },
                    None => ("/", TokenType::SLASH),
                }
            },
            '*' => {
                found_token = true;
                self.input_index += 1;
                match self.input_string.chars().nth(self.input_index) {
                    Some(c) => match c {
                        '*' => {self.input_index += 1; ("**", TokenType::STAR_STAR)},
                        '/' => {self.input_index += 1; ("*/", TokenType::STAR_SLASH)},
                        _ => ("*", TokenType::STAR),
                    },
                    None => ("*", TokenType::STAR),
                }
            },
            '!' => {
                found_token = true;
                self.input_index += 1;
                match self.input_string.chars().nth(self.input_index) {
                    Some(c) => match c {
                        '=' => {self.input_index += 1; ("!=", TokenType::EXCL_EQUAL)},
                        _ => ("-", TokenType::EXCL),
                    },
                    None => ("-", TokenType::EXCL),
                }
            },
            '=' => {
                found_token = true;
                self.input_index += 1;
                match self.input_string.chars().nth(self.input_index) {
                    Some(c) => match c {
                        '=' => {self.input_index += 1; ("!=", TokenType::EQUAL_EQUAL)},
                        _ => ("=", TokenType::EQUAL),
                    },
                    None => ("=", TokenType::EQUAL),
                }
            },
            '%' => { found_token = true; self.input_index += 1; ("%", TokenType::PERCENT)},
            '^' => { found_token = true; self.input_index += 1; ("^", TokenType::CARET)},
            '&' => {
                found_token = true;
                self.input_index += 1;
                match self.input_string.chars().nth(self.input_index) {
                    Some(c) => match c {
                        '&' => {self.input_index += 1; ("&&", TokenType::AMPERSAND_AMPERSAND)},
                        _ => ("&", TokenType::AMPERSAND),
                    },
                    None => ("&", TokenType::AMPERSAND),
                }
            },
            '|' => {
                found_token = true;
                self.input_index += 1;
                match self.input_string.chars().nth(self.input_index) {
                    Some(c) => match c {
                        '|' => {self.input_index += 1; ("||", TokenType::PIPE_PIPE)},
                        _ => ("|", TokenType::PIPE),
                    },
                    None => ("|", TokenType::PIPE),
                }
            },
            '<' => {
                found_token = true;
                self.input_index += 1;
                match self.input_string.chars().nth(self.input_index) {
                    Some(c) => match c {
                        '<' => {self.input_index += 1; ("<<", TokenType::LT_LT)},
                        '=' => {self.input_index += 1; ("<=", TokenType::LT_EQUAL)},
                        _ => ("<", TokenType::LT),
                    },
                    None => ("<", TokenType::LT),
                }
            },
            '>' => {
                found_token = true;
                self.input_index += 1;
                match self.input_string.chars().nth(self.input_index) {
                    Some(c) => match c {
                        '>' => {self.input_index += 1; (">>", TokenType::GT_GT)},
                        '=' => {self.input_index += 1; (">=", TokenType::GT_EQUAL)},
                        _ => (">", TokenType::GT),
                    },
                    None => (">", TokenType::GT),
                }
            },
            ',' => { found_token = true; self.input_index += 1; (",", TokenType::COMMA)},
            '.' => { found_token = true; self.input_index += 1; (".", TokenType::DOT)},
            ':' => {
                found_token = true;
                self.input_index += 1;
                match self.input_string.chars().nth(self.input_index) {
                    Some(c) => match c {
                        ':' => {self.input_index += 1; ("::", TokenType::COLON_COLON)},
                        '=' => {self.input_index += 1; (":=", TokenType::COLON_EQUAL)},
                        _ => (":", TokenType::COLON),
                    },
                    None => (":", TokenType::COLON),
                }
            },
            ';' => { found_token = true; self.input_index += 1; (";", TokenType::SEMICOLON)},
            '"' => {
                found_token = true;
                self.input_index += 1;
                loop {
                    let c  = match self.input_string.chars().nth(self.input_index) { Some(c) => c, None => panic!("Error: EOF in string literal") };
                    match c {
                        '\\' => {self.input_index += 1; slice.push(match self.input_string.chars().nth(self.input_index) { Some(c) => c, None => panic!("Error: EOF in string literal") }); self.input_index += 1;},
                        '"' => {self.input_index += 1; break;},
                        _ => {self.input_index += 1; slice.push(c);}
                    };
                };

                (slice.as_str(), TokenType::STRING)
            },
            '\'' => {
                found_token = true;
                self.input_index += 1;
                let c  = match self.input_string.chars().nth(self.input_index) { Some(c) => c, None => panic!("Error: EOF in string literal") };
                (
                    match c {
                        '\\' => {self.input_index += 1; slice += "\\"; slice.push(match self.input_string.chars().nth(self.input_index) { Some(c) => c, None => panic!("Error: EOF in string literal") }); slice.as_str()}
                        _ => {slice.push(c); slice.as_str()}
                    },
                    TokenType::CHAR
                )
            },
            _ => {
                found_token = true;
                self.input_index += 1;
                let mut ttype = TokenType::NONE;
                
                if c >= '0' && c <= '9' { // Number
                    let mut is_float = false;
                    let mut done = false;
                    slice.push(c);
                    self.input_index += 1;
                    while !done {
                        let c  = match self.input_string.chars().nth(self.input_index) { Some(c) => c, None => {done = true; ' '} };
                        if c == '.' && is_float {
                            done = true;
                        } else if c == '.' {
                            is_float = true;
                        } else if c < '0' || c > '9' {
                            done = true;
                        } else {
                            slice.push(c);
                        }
                        if !done {
                            self.input_index += 1;
                        }
                    }
                    if is_float {
                        ttype = TokenType::FLOAT;
                    } else {
                        ttype = TokenType::INT;
                    }
                } else if c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_' { // Identifier or keyword.
                    let mut done = false;
                    let mut could_be_keyword = c != '_';
                    slice.push(c);
                    self.input_index += 1;
                    while !done {
                        let c  = match self.input_string.chars().nth(self.input_index) { Some(c) => c, None => panic!("Error: EOF in string literal") };
                        if c == '_' || c >= '0' && c <= '9' {
                            slice.push(c);
                            self.input_index += 1;
                            could_be_keyword = false;
                            break;
                        } else if c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' {
                            slice.push(c);
                            self.input_index += 1;
                        } else {
                            done = true;
                        }
                    }
                    while !done {
                        let c  = match self.input_string.chars().nth(self.input_index) { Some(c) => c, None => panic!("Error: EOF in string literal") };
                        if c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c >= '0' && c <= '9' || c == '_' {
                            slice.push(c);
                            self.input_index += 1;
                        } else {
                            done = true;
                        }
                    }
                    if could_be_keyword {
                        for i in 0..keyword_list::KEYWORD_LIST.len() {
                            if slice == keyword_list::KEYWORD_LIST[i] {
                                match TokenType::try_from(i) {
                                    Ok(out_token_type) => { ttype = out_token_type; break; },
                                    Err(_) => panic!("Error converting keyword list index to token type."),
                                }
                            }
                        }
                    } else {
                        ttype = TokenType::IDENT
                    }
                }
                
                (slice.as_str(), ttype)
            },
        };
        slice = String::from(tslice); token_type = ttype;
        };

        let column_number = self.column_number;
        self.column_number += self.input_index - stored_input_index;
        
        (token_type, slice, self.line_number, column_number)
    }
}