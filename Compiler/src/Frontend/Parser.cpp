#include <Frontend/Parser.hh>

#include <Error.h>

#include <stdlib.h>

Parser::Parser(Scanner *scanner) {
    parse_toplevel();
}

void Parser::parse_toplevel() {
    parse_expression();
}

void Parser::parse_expression() {
    switch (peek_current().kind) {
        case TT_IDENT: {
            auto* expr = pools.get_expression();
            expr->kind = Expression::ExpressionKind::IDENT;
            expr->ident = eat_token();
        }
        case TT_HEX_LITERAL:
        case TT_OCTAL_LITERAL:
        case TT_BINARY_LITERAL:
        case TT_INT:
        case TT_FLOAT:
        case TT_STRING:
        case TT_CHAR:
        
        case TT_LPAREN:

        case TT_EXCL:
    }
}

void Parser::dispatch_typers() {
    for (uint64 i = 0; i < toplevel_count; i++) {
        const Declaration& decl = toplevel[i];
        if (decl.right.kind == Expression::ExpressionKind::IMPORT) {
            // Dispatch thread to import the target file
        } else {
            /* Dispatch thread to construct type
               information for the declaration
               and function body if applicable */
        }
    }
}

void Expression::print() {
    switch (kind) {
    case ExpressionKind::IDENT: {
        
    } break;
    default: return;
    }
}