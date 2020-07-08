use logos::Logos;

#[derive(Logos, Debug, PartialEq, Clone, Copy)]
#[allow(non_camel_case_types)]
pub enum Token {
    #[token("if")]
    IF,
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
    #[token("+=")]
    PLUS_EQUALS,
    #[token("+")]
    PLUS,

    #[token("--")]
    MINUS_MINUS,
    #[token("-=")]
    MINUS_EQUALS,
    #[token("->")]
    MINUS_GT,
    #[token("-")]
    MINUS,

    #[token("//")]
    SLASH_SLASH,
    #[token("/*")]
    SLASH_STAR,
    #[token("/")]
    SLASH,

    #[token("**")]
    STAR_STAR,
    #[token("*/")]
    STAR_SLASH,
    #[token("*")]
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

    #[token("<=")]
    LT_EQUAL,
    #[token("<<")]
    LT_LT,
    #[token("<")]
    LT,

    #[token(">=")]
    GT_EQUAL,
    #[token(">>")]
    GT_GT,
    #[token(">")]
    GT,

    #[token(",")]
    COMMA,

    #[token(".")]
    DOT,

    #[token(":=")]
    COLON_EQUALS,
    #[token("::")]
    COLON_COLON,
    #[token(":")]
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

    #[token("\n")]
    NEWLINE,

    #[error]
    #[regex(r"[ \t\r\f]+", logos::skip)]
    Error,

    EOF,
}