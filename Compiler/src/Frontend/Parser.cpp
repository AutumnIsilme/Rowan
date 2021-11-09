#include <Frontend/Parser.hh>

#include <Error.h>
#include <Instrumentor.hh>

#include <stdlib.h>

Parser::Parser(Scanner *scanner) {
    pools.expressions = static_cast<Parser::Pools::ExpressionPoolNode*>(malloc(128 * sizeof(*pools.expressions)));
    tokens = scanner;
    tokens->current = 0;
    parse_toplevel();
}

void Parser::parse_toplevel() {
    temp_toplevel = parse_expression(0);
}

Expression* Parser::parse_expression(int precedence) {
    PROFILE_FUNC();
    auto* expr = pools.get_expression();
    auto* current = peek_current();
    switch (current->kind) {
        case TT_IDENT: {
            //fprintf(stderr, "Parser::parse_expression case TT_IDENT\n");
            expr->kind = Expression::ExpressionKind::IDENT;
            expr->ident = eat_token();
        }
        case TT_HEX_LITERAL:
        case TT_OCTAL_LITERAL:
        case TT_BINARY_LITERAL: {

        }
        case TT_INT: {
            expr->kind = Expression::ExpressionKind::VALUE;
            expr->value.unsigned_int_val = 0;
            expr->value.kind = ValueNode::ValueKind::UINT;
            expr->value.token = eat_token();
        }
        case TT_FLOAT:
        case TT_STRING:
        case TT_CHAR:
        
        case TT_LPAREN:

        case TT_EXCL: {

        }
        default: {

        }
    }

    current = peek_current();
    switch (current->kind) {
        case TT_PLUS: {
            if (precedence > 5) {
                return expr;
            }
            auto* center_expr = pools.get_expression();
            center_expr->kind = Expression::ExpressionKind::BINARY;
            center_expr->bin_exp.left = expr;
            center_expr->bin_exp.oper = eat_token();
            center_expr->bin_exp.right = parse_expression(5);
            expr = center_expr;
        }
        default: {

        }
    }
    return expr;
}

void Parser::dispatch_typers() {
    /*for (uint64 i = 0; i < toplevel_count; i++) {
        const Declaration& decl = toplevel[i];
        if (decl.right.kind == Expression::ExpressionKind::IMPORT) {
            // Dispatch thread to import the target file
        } else {
            /* Dispatch thread to construct type
               information for the declaration
               and function body if applicable */
        /*}
    }*/
}

Expression *Parser::Pools::get_expression() {
    return static_cast<Expression*>(&expressions[expression_used++].expr);
}

void Expression::print() {
    switch (kind) {
    case ExpressionKind::IDENT: {
        
    } break;
    default: return;
    }
}