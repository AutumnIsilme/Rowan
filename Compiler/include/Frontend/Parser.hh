#ifndef PARSER_H_GUARD
#define PARSER_H_GUARD

#include <Frontend/Scanner.hh>

struct Parser {
    Scanner *tokens;

    struct Declaration *toplevel;
    uint64 toplevel_count;

    struct Expression *temp_toplevel;

    struct Pools {
        struct {
            struct Expression expr;
            uint64 next;
        } *expressions;
        uint64 expression_count;
        uint64 expression_used;

        struct {
            struct Declaration decl;
            uint64 next;
        } *declarations;
        uint64 decl_count;
        uint64 decl_used;

        uint64 *generic_pool;
        uint64 generic_pool_size;
        uint64 generic_pool_used;

        Expression  *get_expression();
        Declaration *get_declaration();
        void        *get_mem_of_size(uint64 size);
    } pools;

    Parser(Scanner *scanner);

    void parse_toplevel();
    void parse_expression();
    void dispatch_typers();

    Token& peek_current();
    Token& peek_ahead(int ahead);
    Token& eat_token();
};

struct Declaration {
    Token& left; // Can only be an identifier token
    struct Expression& right;

    uint64 scope_depth;

    bool is_define_decl = false;
};

struct Block {
    Expression *expressions;
    uint64 expression_count;
};

struct Expression {
    enum class ExpressionKind {
        IMPORT,
        BINARY,
        UNARY,
        VALUE,
        IDENT,
        FUNCTION,
    };

    ExpressionKind kind;

    union {
        struct BinaryExpression bin_exp;
        struct UnaryExpression unary_exp;
        struct ValueNode value;
        Token& ident;
    };

    void print();
};

struct FunctionDefinition {
    Declaration *declarations;
    uint64 decl_count;

    Block& body;

    struct {
        bool is_macro: 1;
    } attrs;
};

struct UnaryExpression {
    Token& oper;
    Expression& right;
};

struct BinaryExpression {
    Expression& left;
    Token& oper;
    Expression& right;
};

struct ValueNode {
    enum class ValueKind {
        STRING,
        UINT,
        SINT,
        F32,
        F64,
        F128,
        BOOL
    };

    Token& token;

    ValueKind kind;

    union {
        const char *string_val;

        uint128 unsigned_int_val;
        int128 signed_int_val;

        float32 float32_val;
        float64 float64_val;
        float128 float128_val;
        
        bool bool_val;
    };
};

#endif /* PARSER_H_GUARD */