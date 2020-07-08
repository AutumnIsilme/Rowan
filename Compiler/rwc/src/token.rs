use logos::Logos;

#[derive(Logos, Debug, PartialEq, Clone, Copy)]
#[allow(non_camel_case_types)]
#[derive(Debug, TryFromPrimitive)]
#[derive(PartialEq, Clone, Copy)]
#[repr(usize)]
pub enum TokenType {
    /* Keywords */
    #[token("if")]
    IF = 0,
    #[token("for")]
    FOR,
    #[token("while")]
    WHILE,
    #[token("return")]
    RETURN,
    #[token("break")]
    BREAK,
    #[token("continue")]
    CONTINUE,
    #[token("switch")]
    SWITCH,
    #[token("case")]
    CASE,
    #[token("include")]
    INCLUDE,
    #[token("usion")]
    USING,
    #[token("cast")]
    CAST,
    #[token("struct")]
    STRUCT,
    #[token("enum")]
    ENUM,
    #[token("union")]
    UNION,
    #[token("soa")]
    SOA,

    #[token("true")]
    TRUE,
    #[token("false")]
    FALSE,

    #[token("(")]
    LPAREN,
    #[token(")")]
    RPAREN,
    #[token("[")]
    LSQUARE,
    #[token("]")]
    RSQUARE,
    #[token("{")]
    LCURLY,
    #[token("}")]
    RCURLY,

    #[token("++")]
    PLUS_PLUS,
    PLUS_EQUAL,
    PLUS,

    #[token("--")]
    MINUS_MINUS,
    MINUS_EQUAL,
    MINUS_GT,
    #[token("-")]
    MINUS,

    SLASH_STAR,
    SLASH,

    #[token("**")]
    STAR_STAR,
    STAR_SLASH,
    STAR,

    #[token("!=")]
    EXCL_EQUAL,
    #[token("!")]
    EXCL,

    #[token("==")]
    EQUAL_EQUAL,
    #[token("=")]
    EQUAL,

    #[token("%")]
    PERCENT,
    #[token("^")]
    CARET,

    #[token("&&")]
    AMPERSAND_AMPERSAND,
    #[token("&")]
    AMPERSAND,

    #[token("||")]
    PIPE_PIPE,
    #[token("|")]
    PIPE,

    LT_LT,
    LT_EQUAL,
    LT,

    GT_GT,
    GT_EQUAL,
    GT,

    #[token(",")]
    COMMA,

    #[token(".")]
    DOT,

    COLON_COLON,
    COLON_EQUAL,
    COLON,
    #[token(";")]
    SEMICOLON,

    /* Other token types*/
    #[regex(r"[a-zA-Z_][a-zA-Z0-9_]*")]
    IDENT,
    #[regex(r"-?[0-9][0-9]?[0-9]?([0-9]+|(_[0-9][0-9][0-9])*)")]
    INT,
    #[regex(r"-?[0-9][0-9]?[0-9]?([0-9]+|(_[0-9][0-9][0-9])*)\\.[0-9]+")]
    FLOAT,
    #[regex("\"([^\"]|(\\\\\")|(\\n))*\"")]
    STRING,
    #[regex(r"'([^\\]|\\.)")]
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