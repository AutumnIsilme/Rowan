use num_enum::TryFromPrimitive;

pub struct Token {
    pub token_type: TokenType,
    pub line_number: u32,
    pub column_number: u32,
    pub contents: String,
}

impl Token {
    pub fn create(token_type: TokenType, line_number: u32, column_number: u32, contents: &str) -> Token {
        return Token {
            token_type: token_type,
            line_number: line_number,
            column_number: column_number,
            contents: String::from(contents),
        }
    }
}

#[allow(dead_code)]
#[allow(non_camel_case_types)]
#[derive(Debug, TryFromPrimitive)]
#[derive(PartialEq, Clone, Copy)]
#[repr(usize)]
pub enum TokenType {
    /* Keywords */
    IF = 0,
    FOR,
    WHILE,
    RETURN,
    BREAK,
    CONTINUE,
    SWITCH,
    CASE,
    INCLUDE,
    USING,
    CAST,
    STRUCT,
    ENUM,
    UNION,
    SOA,

    TRUE,
    FALSE,

    /* Operators and symbols*/
    LPAREN,
    RPAREN,
    LSQUARE,
    RSQUARE,
    LCURLY,
    RCURLY,

    PLUS_PLUS,
    PLUS_EQUAL,
    PLUS,

    MINUS_MINUS,
    MINUS_EQUAL,
    MINUS_GT,
    MINUS,

    SLASH_STAR,
    SLASH,

    STAR_STAR,
    STAR_SLASH,
    STAR,

    EXCL_EQUAL,
    EXCL,

    EQUAL_EQUAL,
    EQUAL,

    PERCENT,
    CARET,

    AMPERSAND_AMPERSAND,
    AMPERSAND,

    PIPE_PIPE,
    PIPE,

    LT_LT,
    LT_EQUAL,
    LT,

    GT_GT,
    GT_EQUAL,
    GT,

    COMMA,

    DOT,

    COLON_COLON,
    COLON_EQUAL,
    COLON,
    SEMICOLON,

    /* Other token types*/
    IDENT,
    INT,
    FLOAT,
    STRING,
    CHAR,

    EOF,
    NONE,
}

pub static TOKEN_TYPE_NAMES: [&str; 64] = [
    "IF",
    "FOR",
    "WHILE",
    "RETURN",
    "BREAK",
    "CONTINUE",
    "SWITCH",
    "CASE",
    "INCLUDE",
    "USING",
    "CAST",
    "STRUCT",
    "ENUM",
    "UNION",
    "SOA",
    "TRUE",
    "FALSE",
    "LPAREN",
    "RPAREN",
    "LSQUARE",
    "RSQUARE",
    "LCURLY",
    "RCURLY",
    "PLUS_PLUS",
    "PLUS_EQUAL",
    "PLUS",
    "MINUS_MINUS",
    "MINUS_EQUAL",
    "MINUS_GT",
    "MINUS",
    "SLASH_STAR",
    "SLASH",
    "STAR_STAR",
    "STAR_SLASH",
    "STAR",
    "EXCL_EQUAL",
    "EXCL",
    "EQUAL_EQUAL",
    "EQUAL",
    "PERCENT",
    "CARET",
    "AMPERSAND_AMPERSAND",
    "AMPERSAND",
    "PIPE_PIPE",
    "PIPE",
    "LT_LT",
    "LT_EQUAL",
    "LT",
    "GT_GT",
    "GT_EQUAL",
    "GT",
    "COMMA",
    "DOT",
    "COLON_COLON",
    "COLON_EQUALS",
    "COLON",
    "SEMICOLON",
    "IDENT",
    "INT",
    "FLOAT",
    "STRING",
    "CHAR",

    "EOF",
    "NONE",
];