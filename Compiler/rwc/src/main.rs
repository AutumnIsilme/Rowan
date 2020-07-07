use std::{fs::File, io::prelude::*, path::Path, time::{SystemTime}};
use logos::Logos;

#[derive(Logos, Debug, PartialEq)]
#[allow(non_camel_case_types)]
enum Token {
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

    #[token("/")]
    SLASH,

    #[token("**")]
    STAR_STAR,
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
    #[regex(r"[a-zA-Z_][a-zA-Z0-9_]+")]
    IDENT,
    #[regex(r"-?[0-9][0-9]?[0-9]?([0-9]+|(_[0-9][0-9][0-9])*)")]
    INT,
    #[regex(r"-?[0-9][0-9]?[0-9]?([0-9]+|(_[0-9][0-9][0-9])*)\\.[0-9]+")]
    FLOAT,
    #[regex("\"([^\"]|(\\\\\")|(\\n))*\"")]
    STRING,
    #[regex(r"'.")]
    CHAR,

    #[error]
    #[regex(r"[ \t\n\f]+", logos::skip)]
    Error,
}

fn main() {
    let timer = SystemTime::now();
    let path = Path::new("../test.rw");
    
    let mut file = File::open(&path).expect("Unable to open file!");
    let mut file_string = String::new();
    file.read_to_string(&mut file_string).expect("Unable to read file!");
    
    let read_file_time = match timer.elapsed() { Ok(val) => val, Err(_) => panic!("timer.elapsed failed at read file time")};
    let timer = SystemTime::now();
    
    let mut lex = Token::lexer(file_string.as_str());

    let make_tokens_time = match timer.elapsed() { Ok(val) => val, Err(_) => panic!("timer.elapsed failed at make tokens time")};
    let timer = SystemTime::now();

    let mut times: [f64; 189] = [0.0; 189];
    let mut count = 0;
    loop {
        let timer2 = SystemTime::now();
        let token = match lex.next() {
            Some(t) => match t {
                Token::Error => continue,
                _ => t,
            },
            None => break,
        };
        times[count] = timer2.elapsed().unwrap().as_secs_f64();
        println!("[{:?}, {}]", token, lex.slice());
        count += 1;
    }

    let mut total = 0.0;
    for time in times.iter() {
        total += time;
    }
    let av = total / 189.0;

    println!("average time: {}", av);

    let output_time = match timer.elapsed() { Ok(val) => val, Err(_) => panic!("timer.elapsed failed at output time")};
    
    println!("{}, {}, {}", read_file_time.as_secs_f64(), make_tokens_time.as_secs_f64(), output_time.as_secs_f64());
}
