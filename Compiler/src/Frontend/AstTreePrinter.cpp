#include <Frontend/AstTreePrinter.hh>

#include <Common.h>

#include <string>

#define STRAIGHT   "│   "
#define T_JUNCTION "├── "
#define L_JUNCTION "└── "
#define EMPTY      "    "

void ast_printer_print_expression_inner(Expression* expr, std::string prefix, std::string children_prefix) {
    switch (expr->kind) {
    case Expression::ExpressionKind::PREFIX: {
        printf("%sPrefix Expr\n", prefix.c_str());
        printf("%s%s%s: %.*s\n", children_prefix.c_str(), T_JUNCTION, token_type_names[(uint16)expr->unary_exp.oper->kind], (int)expr->unary_exp.oper->length, expr->unary_exp.oper->token);
        ast_printer_print_expression_inner(expr->unary_exp.expr, (children_prefix + L_JUNCTION).c_str(), (children_prefix + EMPTY).c_str());
    } break;
    case Expression::ExpressionKind::POSTFIX: {
        printf("%sPostfix Expr\n", prefix.c_str());
        ast_printer_print_expression_inner(expr->unary_exp.expr, (children_prefix + T_JUNCTION).c_str(), (children_prefix + STRAIGHT).c_str());
        printf("%s%s%s: %.*s\n", children_prefix.c_str(), L_JUNCTION, token_type_names[(uint16)expr->unary_exp.oper->kind], (int)expr->unary_exp.oper->length, expr->unary_exp.oper->token);
    } break;
    case Expression::ExpressionKind::BINARY: {
        printf("%sBinary Expr\n", prefix.c_str());
        ast_printer_print_expression_inner(expr->bin_exp.left, (children_prefix + T_JUNCTION).c_str(), (children_prefix + STRAIGHT).c_str());
        printf("%s%s%s: %.*s\n", children_prefix.c_str(), T_JUNCTION, token_type_names[(uint16)expr->bin_exp.oper->kind], (int)expr->bin_exp.oper->length, expr->bin_exp.oper->token);
        ast_printer_print_expression_inner(expr->bin_exp.right, (children_prefix + L_JUNCTION).c_str(), (children_prefix + EMPTY).c_str());
    } break;
    case Expression::ExpressionKind::VALUE: {
        printf("%sValue Node\n", prefix.c_str());
        printf("%s%s%s: %.*s\n", children_prefix.c_str(), L_JUNCTION, token_type_names[(uint16)expr->value.token->kind], (int)expr->value.token->length, expr->value.token->token);
    } break;
    default: printf("%sUnknown Node\n", prefix.c_str());
    }
}

void ast_printer_print_expression(Expression* expr) {
    ast_printer_print_expression_inner(expr, "", "");
}
