use std::{fs::File, io::prelude::*, path::Path, time::{Duration, SystemTime}};

mod token;
mod keyword_list;
mod error;
mod lexer;

fn main() {
    let timer = SystemTime::now();
    let path = Path::new("../test.rw");

    let mut file = File::open(&path).expect("Unable to open file!");
    let mut file_string = String::new();
    file.read_to_string(&mut file_string).expect("Unable to read file!");

    let read_file_time = match timer.elapsed() { Ok(val) => val, Err(_) => panic!("timer.elapsed failed at read file time")};
    let timer = SystemTime::now();
    let mut lexer: lexer::Lexer = lexer::Lexer::create();
    let (tokens, errors) = lexer.make_tokens(file_string.as_str());

    let make_tokens_time = match timer.elapsed() { Ok(val) => val, Err(_) => panic!("timer.elapsed failed at make tokens time")};
    let timer = SystemTime::now();
    for token in tokens {
        println!("[{}, {}, {{{},{}}}]", token::TOKEN_TYPE_NAMES[token.token_type as usize], token.contents, token.line_number, token.column_number);
    }

    for error in errors {
        println!("Error code {}, line {} column {}", error.error_code, error.line_number, error.column_number);
    }
    let output_time = match timer.elapsed() { Ok(val) => val, Err(_) => panic!("timer.elapsed failed at output time")};

    println!("{}, {}, {}", read_file_time.as_secs_f64(), make_tokens_time.as_secs_f64(), output_time.as_secs_f64());
}

/*
fn main() {
    println!("Guess the number!");

    let mut play_again = true;
    while play_again {
        let secret_number = rand::thread_rng().gen_range(1, 101);
        println!("I have generated a secret number between 1 and 100. You must guess it within ten guesses.");
        let mut i = 0;
        let mut win = false;
        while i < 10 && !win {
            print!("Please input your guess: ");
            io::stdout().flush().unwrap();

            let mut guess = String::new();

            io::stdin()
                .read_line(&mut guess).expect("Failed to read line!");

            let guess: u32 = match guess.trim().parse() {
                Ok(num) => num,
                Err(_) => { println!("Please type a number."); continue },
            };

            i += 1;
            match guess.cmp(&secret_number) {
                Ordering::Less => println!("Too small!"),
                Ordering::Greater => println!("Too big!"),
                Ordering::Equal => {
                    println!("You win! Guesses remaining: {}", 10 - i);
                    win = true;
                },
            }
        }
        if !win {
            println!("You lose. The correct answer was: {}", secret_number);
        }

        print!("Do you want to play again? (Y/N) ");
        io::stdout().flush().unwrap();

        let mut play_again_in = String::new();
        io::stdin()
            .read_line(&mut play_again_in)
            .expect("Failed to read line!");
        
        let play_again_in = play_again_in.trim();

        if !(play_again_in == "Y" || play_again_in == "y" || play_again_in == "Yes" || play_again_in == "YES" || play_again_in == "yes") {
            play_again = false;
            println!("Goodbye.");
        }
    }
}
*/