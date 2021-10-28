#ifndef PARSER_H_GUARD
#define PARSER_H_GUARD

#include <Frontend/Scanner.hh>

struct Expression;

struct Declaration {
    Token* left; // Can only be an identifier token
    struct Expression* right;

    uint64 scope_depth;

    bool is_define_decl = false;
};

struct Block {
    Expression *expressions;
    uint64 expression_count;
};

struct UnaryExpression {
    Token* oper;
    Expression* right;
};

struct BinaryExpression {
    Expression* left;
    Token* oper;
    Expression* right;
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

    Token* token;

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
        BinaryExpression bin_exp;
        UnaryExpression unary_exp;
        ValueNode value;
        Token* ident;
    };

    void print();
};

struct FunctionDefinition {
    Declaration *declarations;
    uint64 decl_count;

    Block* body;

    struct {
        bool is_macro: 1;
    } attrs;
};

struct Parser {
    Scanner *tokens;

    Expression *temp_toplevel;

    /*struct Declaration *toplevel;
    uint64 toplevel_count;*/


    struct Pools {
        struct ExpressionPoolNode {
            struct Expression expr;
            uint64 next;
        };
        ExpressionPoolNode *expressions;
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
    };
    Pools pools;

    Parser(Scanner *scanner);

    void parse_toplevel();
    Expression* parse_expression(int precedence);
    void dispatch_typers();

    inline Token* peek_current() {
        return tokens->peek_next_token();
    }
    inline Token* peek_ahead(int ahead) {
        return tokens->peek_token(ahead);
    }
    inline Token* eat_token() {
        tokens->eat_token();
        return tokens->peek_token(-1);
    }
};

#endif /* PARSER_H_GUARD */