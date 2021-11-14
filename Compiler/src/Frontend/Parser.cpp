#include <Frontend/Parser.hh>

#include <Error.h>
#include <Instrumentor.hh>

#include <stdlib.h>

/* @TODO: Clean these up */
#define BASE_PRECEDENCE 0
#define PLUS_PRECEDENCE 10
#define MULTIPLY_PRECEDENCE 50
#define UNARY_PRECEDENCE 100

Parser::Parser(Scanner *scanner) {
    pools.expressions = static_cast<Parser::Pools::ExpressionPoolNode*>(malloc(128 * sizeof(*pools.expressions)));
    pools.expression_used = 0;
    pools.expression_count = 128;
    tokens = scanner;
    tokens->current = 0;
    parse_toplevel();
}

void Parser::parse_toplevel() {
    temp_toplevel = parse_expression(BASE_PRECEDENCE);
}

Expression* Parser::parse_expression(int precedence) {
    PROFILE_FUNC();
    auto* current = peek_current();
    Expression* expr;
    if (current->kind == TT_LPAREN) {
        auto* start_paren = eat_token();
        expr = parse_expression(BASE_PRECEDENCE);
        current = peek_current();
        if (current->kind != TT_RPAREN) {
            report_error(__FILE__, __LINE__, "aaa", tokens->file_data, current->offset, current->length, "Parser: Syntax Error: A set of parentheses has not been closed correctly.");
            report_error(__FILE__, __LINE__, "aaa", tokens->file_data, start_paren->offset, start_paren->length, "Parser: Info: The parentheses were opened here:");
            exit(1); // @FIXME I should do something better here.
        }
        // Eat the close parentheses
        eat_token();
    } else {
        expr = pools.get_expression();
        switch (current->kind) {
        case TT_IDENT: {
            //fprintf(stderr, "Parser::parse_expression case TT_IDENT\n");
            expr->kind = Expression::ExpressionKind::IDENT;
            expr->ident = eat_token();
        } break;
        case TT_HEX_LITERAL:
        case TT_OCTAL_LITERAL:
        case TT_BINARY_LITERAL: {

        } break;
        case TT_INT: {
            expr->kind = Expression::ExpressionKind::VALUE;
            expr->value.unsigned_int_val = 0;
            expr->value.kind = ValueNode::ValueKind::UINT;
            expr->value.token = eat_token();
        } break;
        case TT_FLOAT:
        case TT_STRING:
        case TT_CHAR: {

        } break;

        /* @TODO: Put prefix operators into an iterative structure, and maybe sometimes collapse them 
           inside the parser rather than waiting for later. */
        case TT_PLUS_PLUS:
        case TT_MINUS_MINUS:
        case TT_TILDE:
        case TT_EXCL:
        case TT_PLUS:
        case TT_MINUS: {
            expr->kind = Expression::ExpressionKind::PREFIX;
            expr->unary_exp.oper = eat_token();
            expr->unary_exp.expr = parse_expression(UNARY_PRECEDENCE);
        } break;

        default: {
            // @TODO: Say the name of the token I have a problem with?
            report_error(__FILE__, __LINE__, "aaa", tokens->file_data, current->offset, current->length, "Parser: Syntax Error: I expected a value or expression here, not a '%s'!", token_type_names[current->kind]);
            exit(1);
        } break;
        }
    }

    // Handle postfix operators. These operators bind tighter than anything else.
    // In general, I think you can only have a single postfix on an expression, but 
    // they will still be parsed tightly then rejected in the type checker.
    // @TODO: more than one postfix is never allowed, remove this loop :Postfix_binding
    while (true) {
        current = peek_current();
        switch (current->kind) {
        case TT_MINUS_MINUS:
        case TT_PLUS_PLUS: {
            /* In terms of ordering, something like a++.b is allowed. C also allows this, so its probably fine. */
            auto* new_expr = pools.get_expression();
            new_expr->kind = Expression::ExpressionKind::POSTFIX;
            new_expr->unary_exp.expr = expr;
            new_expr->unary_exp.oper = eat_token();
            expr = new_expr;
        } break;
        default: {
            goto parser__parse_expression__postfix_expr_loop_end;
        } break;
        }
    }

parser__parse_expression__postfix_expr_loop_end:
    while (true) {
        current = peek_current();
        switch (current->kind) {
            case TT_PLUS: {
                if (precedence > PLUS_PRECEDENCE) {
                    return expr;
                }
                auto* center_expr = pools.get_expression();
                center_expr->kind = Expression::ExpressionKind::BINARY;
                center_expr->bin_exp.left = expr;
                center_expr->bin_exp.oper = eat_token();
                center_expr->bin_exp.right = parse_expression(PLUS_PRECEDENCE);
                expr = center_expr;
            } break;
            case TT_STAR: {
                if (precedence > MULTIPLY_PRECEDENCE) {
                    return expr;
                }
                auto* center_expr = pools.get_expression();
                center_expr->kind = Expression::ExpressionKind::BINARY;
                center_expr->bin_exp.left = expr;
                center_expr->bin_exp.oper = eat_token();
                center_expr->bin_exp.right = parse_expression(MULTIPLY_PRECEDENCE);
                expr = center_expr;
            } break;
            default: {
                /* Double break! */
                goto parser__parse_expression__bin_expr_loop_end;
            }
        }
    }
    
parser__parse_expression__bin_expr_loop_end:
    return expr;
}

void Parser::dispatch_typers() {
    /*for (uint64 i = 0; i < toplevel_count; i++) {
        const Declaration& decl = toplevel[i];
        if (decl.right.kind == Expression::ExpressionKind::IMPORT) {
            // Dispatch thread to import the target file
        } else {
            / Dispatch thread to construct type
               information for the declaration
               and function body if applicable /
        /*}
    }*/
}

Expression *Parser::Pools::get_expression() {
    return static_cast<Expression*>(&(expressions[expression_used++].expr));
}

void Expression::print() {
    switch (kind) {
    /*case ExpressionKind::UNARY: {
        printf("{Unary Expr: ");
        printf("[%s: %.*s] ", token_type_names[(uint16)unary_exp.oper->kind], (int)unary_exp.oper->length, unary_exp.oper->token);
        unary_exp.right->print();
        printf("}");
    } break;*/
    case ExpressionKind::BINARY: {
        printf("{Binary Expr: ");
        bin_exp.left->print();
        printf(" [%s: %.*s] ", token_type_names[(uint16)bin_exp.oper->kind], (int)bin_exp.oper->length, bin_exp.oper->token);
        bin_exp.right->print();
        printf("}");
    } break;
    case ExpressionKind::VALUE: {
        printf("{Value Node: [%s: %.*s]}", token_type_names[(uint16)value.token->kind], (int)value.token->length, value.token->token);
    } break;
    default: printf("{Unknown Node}");
    }
}
