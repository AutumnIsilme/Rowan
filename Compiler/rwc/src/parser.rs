use super::lexer::{Lexer, Token};

pub enum ASTNode {
    INFIX_OP_NODE { lhs: Box<ASTNode>, op: Token, rhs: Box<ASTNode> },
    ATOM(Token, String),
}

pub fn expr(input: &mut Lexer) -> Box<ASTNode> {
    expr_bp(input, 0)
}

fn expr_bp(input: &mut Lexer, min_bp: i16) -> Box<ASTNode> {
    let mut lhs = atom(input);

    loop {
        println!("Starting next operator");
        let op = input.peek();match op {
            Token::EOF => break,
            Token::PLUS | Token::MINUS | Token::STAR | Token::SLASH => (),
            _ => panic!(format!("Error: invalid operator in expr_bp: {:?}", op)),
        };
        
        let (l_bp, r_bp) = infix_bp(&op);
        println!("l_bp: {}, r_bp: {}, min_bp: {}", l_bp, r_bp, min_bp);
        if l_bp < min_bp {
            println!("Breaking!");
            break;
        }
        //println!("next!(input): {:?}", next!(input));
        input.next();
        let rhs = expr_bp(input, r_bp);

        lhs = Box::from(ASTNode::INFIX_OP_NODE {lhs: lhs, op: op, rhs: rhs});
    }

    lhs
}

/* 1 + 2 + 3

atom(1) next
op(+) next
expr_bp(2)
atom(2) next
op(+) next
return


*/

fn atom(input: &mut Lexer) -> Box<ASTNode> {
    /*IDENT,
    INT,
    FLOAT,
    STRING,
    CHAR,*/
    let t = input.next();
    let t = match t {
        Token::IDENT | Token::INT | Token::FLOAT | Token::STRING | Token::CHAR => t,
        _ => panic!("Error: bad token in atom!"),
    };

    return Box::from(ASTNode::ATOM(t, input.slice().to_string()));
}

fn infix_bp(op: &Token) -> (i16, i16) {
    match op {
        Token::PLUS | Token::MINUS => (1, 2),
        Token::STAR | Token::SLASH => (3, 4),
        _ => panic!("Bad operator!"),
    }
}