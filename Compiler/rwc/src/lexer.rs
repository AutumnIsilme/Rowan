use logos::Logos;

pub struct Lexer<'a> {
    lexer: logos::Lexer<'a, Token>,
    tokens: Vec<Token>,
    token_slices: Vec<String>,
    token_spans: Vec<core::ops::Range<usize>>,
    token_index: usize,
}

impl Lexer<'_> {
    pub fn create(file_string: &str) -> Lexer {
        let mut rv = Lexer {
            lexer: Token::lexer(file_string),
            tokens: Vec::new(),
            token_slices: Vec::new(),
            token_spans: Vec::new(),
            token_index: 0,
        };
        loop {
            let token = match rv.lexer.next() {
                Some(t) => t,
                None => Token::EOF,
            };
            rv.tokens.push(token);
            match token {
                Token::EOF => {rv.token_slices.push(String::new()); rv.token_spans.push(rv.lexer.span()); break},
                _ => {rv.token_slices.push(String::from(rv.lexer.slice())); rv.token_spans.push(rv.lexer.span())},
            }
        }

        rv
    }

    #[inline]
    pub fn next(&mut self) -> Token {
        self.token_index += 1;
        self.tokens[self.token_index - 1]
    }

    #[inline]
    pub fn slice(&mut self) -> String {
        self.token_slices[self.token_index - 1].clone()
    }

    #[inline]
    pub fn span(&mut self) -> core::ops::Range<usize> {
        self.token_spans[self.token_index - 1].clone()
    }

    #[inline]
    pub fn peek(&mut self) -> Token {
        self.tokens[self.token_index]
    }
}

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
    #[regex("\"([^\\\\\"]|(\\\\.))*\"")]
    STRING,
    #[regex(r"'([^\\]|\\.)")]
    CHAR,

    #[token("\n")]
    NEWLINE,

    #[error]
    #[regex(r"[ \t\r\f]+", logos::skip)]
    Error,

    EOF
}