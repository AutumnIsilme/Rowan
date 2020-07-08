use std::{fs::File, io::prelude::*, path::Path, time::{SystemTime}};
use logos::{Logos, Lexer};

mod token;
mod parser;

use token::Token;
use parser::ASTNode;

fn print_ast(ast: &Box<ASTNode>) {
    match ast.as_ref() {
        ASTNode::ATOM(_atom, string) => {
            print!("{}", string);
        },
        ASTNode::INFIX_OP_NODE{lhs, op, rhs} => {
            let op_char = match op {
                Token::PLUS => '+',
                Token::MINUS => '-',
                Token::STAR => '*',
                Token::SLASH => '/',
                _ => panic!("Invalid op!")
            };
            print!("( {} ", op_char);
            print_ast(lhs);
            print!(" ");
            print_ast(rhs);
            print!(" )");
        }
    }
}

fn main() {
    let path = Path::new("../test.rw");
    let mut file = File::open(&path).expect("Unable to open file!");
    let mut file_string = String::new();
    file.read_to_string(&mut file_string).expect("Unable to read file!");
    
    let mut lex = Token::lexer(file_string.as_str());

    println!("{:?}", lex.next().unwrap_or(Token::EOF));

    let mut lex_test = Token::lexer("1+2+3");
    let ast = parser::expr(&mut lex_test);
    
    print_ast(&ast);
    
    /*
    let timer3 = SystemTime::now();
    let timer = SystemTime::now();
    
    let read_file_time = match timer.elapsed() { Ok(val) => val, Err(_) => panic!("timer.elapsed failed at read file time")};
    let timer = SystemTime::now();
    

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
    
    println!("{}, {}, {}", read_file_time.as_secs_f64(), make_tokens_time.as_secs_f64(), output_time.as_secs_f64());*/
}
