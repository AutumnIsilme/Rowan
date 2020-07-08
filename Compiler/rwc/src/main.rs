use std::{fs::File, io::prelude::*, path::Path, time::{SystemTime}};

mod types;
mod keyword_list;
mod error;
mod lexer;
mod token;


fn main() {
    let timer = SystemTime::now();
    let path = Path::new("../test.rw");
    
    let mut file = File::open(&path).expect("Unable to open file!");
    let mut file_string = String::new();
    file.read_to_string(&mut file_string).expect("Unable to read file!");
    println!("Read file to string!");
    
    let read_file_time = match timer.elapsed() { Ok(val) => val, Err(_) => panic!("timer.elapsed failed at read file time")};
    let timer = SystemTime::now();

    let mut lex = lexer::Lexer::create(file_string.as_str());
    println!("Made tokens!");

    let make_tokens_time = match timer.elapsed() { Ok(val) => val, Err(_) => panic!("timer.elapsed failed at make tokens time")};

    println!("logos: {}, read file: {}", make_tokens_time.as_secs_f64(), read_file_time.as_secs_f64());
    return;
}

