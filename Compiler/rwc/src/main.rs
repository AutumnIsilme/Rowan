use std::{fs::File, io::prelude::*, path::Path, time::{SystemTime}};
use logos::Logos;

fn main() {
    let timer3 = SystemTime::now();
    let timer = SystemTime::now();
    let path = Path::new("../test.rw");
    
    let mut file = File::open(&path).expect("Unable to open file!");
    let mut file_string = String::new();
    file.read_to_string(&mut file_string).expect("Unable to read file!");
    
    let read_file_time = match timer.elapsed() { Ok(val) => val, Err(_) => panic!("timer.elapsed failed at read file time")};
    let timer = SystemTime::now();
    
    let mut lex = Token::lexer(file_string.as_str());

    let make_tokens_time = match timer.elapsed() { Ok(val) => val, Err(_) => panic!("timer.elapsed failed at make tokens time")};
    //let timer = SystemTime::now();

    let mut times: Vec<f64> = Vec::new();
    let mut count: u64 = 0;
    let mut error_count: u64 = 0;
    loop {
        let timer2 = SystemTime::now();
        let token = match lex.next() {
            Some(t) => match t {
                Token::Error => { error_count += 1; t },
                _ => t,
            },
            None => break,
        };
        times.push(timer2.elapsed().unwrap().as_secs_f64());
        println!("[{:?}, {}]", token, lex.slice());
        count += 1;
    }

    let mut total = 0.0;
    let mut largest = 0.0;
    let mut smallest = 10000000.0;
    for time in times {
        total += time;
        if time < smallest { smallest = time; }
        if time > largest {largest = time; }
    }
    let av = total / (count as f64);

    println!("average time: {}, largest time: {}, smallest time: {}, total time: {}, count: {}, error count: {}", av, largest, smallest, total, count, error_count);

    let output_time = match timer3.elapsed() { Ok(val) => val, Err(_) => panic!("timer.elapsed failed at output time")};
    
    println!("{}, {}, {}", read_file_time.as_secs_f64(), make_tokens_time.as_secs_f64(), output_time.as_secs_f64());
}


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
}