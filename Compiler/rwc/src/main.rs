use std::{fs::File, io::prelude::*, path::Path, time::{SystemTime}};
mod types;
mod keyword_list;
mod error;
mod lexer;
mod parser;
//mod token;

use lexer::Token;
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
    let mut lex = lexer::Lexer::create("1+2+3");
    let ast = parser::expr(&mut lex);
    print_ast(&ast);
    /*
    let timer = SystemTime::now();
    let path = Path::new("../test.rw");
    let mut file = File::open(&path).expect("Unable to open file!");
    let mut file_string = String::new();
    file.read_to_string(&mut file_string).expect("Unable to read file!");
    println!("Read file to string!");
    
    let mut lex = Token::lexer(file_string.as_str());

    println!("{:?}", lex.next().unwrap_or(Token::EOF));

    let mut lex_test = Token::lexer("1+2+3");
    let ast = parser::expr(&mut lex_test);
    
    print_ast(&ast);

    println!("logos: {}, read file: {}", make_tokens_time.as_secs_f64(), read_file_time.as_secs_f64());*/
    return;
}
