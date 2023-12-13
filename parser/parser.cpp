#include "parser.hpp"
#include "../include/internals/mewcore_ast.hpp"
#include "../include/internals/mewcore_obj.hpp"

struct Parser gen_parser(const std::vector<Token> &toks, size_t c, size_t l)
{
    struct Parser p;
    p.counter = 0;
    p.level = 0;
    p.tokens = toks;

    return p;
}

bool consume_token(Parser &p, TOKEN_T type)
{
    if(p.tokens[p.counter]._TOKEN_TYPE == type)
    {
        ++p.counter;
        return true;
    }
    else
    {
        return false;
    }
}

bool expect_token(Parser &p, TOKEN_T type)
{
    if(p.tokens[p.counter]._TOKEN_TYPE == type)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int getPrecedence(TOKEN_T optype)
{
    switch(optype)
    {
        case _TOKEN_PLUS: case _TOKEN_MINUS: return 1; break;
        case _TOKEN_MUL: case _TOKEN_DIV: case _TOKEN_MOD: return 2; break;
        default: return 0; break;
    }
}

void *var_rule(Parser &p)
{
    if(expect_token(p, _TOKEN_VAR))
    {
        Var *varname = nullptr;
        varname = new Var(p.tokens[p.counter]._TOKEN_VALUE, MEOWOBJECTKIND::VarObj); // get the var name
        ++p.counter;
        return varname;
    }
    else
    {
        return NULL;
    }
}

void *const_rule(Parser &p)
{
    std::string curr_token_value = p.tokens[p.counter]._TOKEN_VALUE;
    MeowObject *const_obj = nullptr;
    switch(p.tokens[p.counter]._TOKEN_TYPE)
    {
        case _TOKEN_INT:
        {
            long long val = std::stoll(curr_token_value);
            Integer *mewint = new Integer(val, MEOWOBJECTKIND::IntObj);
            const_obj = mewint;
            break;
        }
        case _TOKEN_STRING:
        {
            String *mewstr = new String(curr_token_value, MEOWOBJECTKIND::StringObj);
            const_obj = mewstr;
            break;
        }
        case _TOKEN_FLOAT:
        {
            long double val = std::stold(curr_token_value);
            Float *mewfloat = new Float(val, MEOWOBJECTKIND::FloatObj);
            const_obj = mewfloat;
            break;
        }
        case _TOKEN_VAR:
        {
            return var_rule(p);
            break;
        }
        default:
            std::cout << "Unknow token encountered\n";
            return NULL;
            break;
    }
    ++p.counter;
    return const_obj;
}

void *expression_rule(Parser &p, int prec)
{
    if(expect_token(p, _TOKEN_BRAOPEN))
    {
        ++p.counter;
        void *val = expression_rule(p, 1);

        if(!consume_token(p, _TOKEN_BRACLOSE))
            std::cout << "Expected `)` after expression\n";

        return val;
    }

    void *a = const_rule(p); // lhs

    void *lhs = new Const((MeowObject *)a, EXPR_TYPES::expr_const);

    while(1)
    {
        if(getPrecedence(p.tokens[p.counter]._TOKEN_TYPE) < prec) break;

        OP_TYPES op;

        switch (p.tokens[p.counter]._TOKEN_TYPE)
        {
            case _TOKEN_PLUS: op = OP_TYPES::Add; break;
            case _TOKEN_MUL: op = OP_TYPES::Mul; break;
            case _TOKEN_DIV: op = OP_TYPES::Div; break;
            case _TOKEN_MINUS: op = OP_TYPES::Sub; break;
            case _TOKEN_MOD: op = OP_TYPES::Mod; break;
            default: std::cout << "Unsuported operator encoutered\n"; break;
        }

        int nextPrec = getPrecedence(p.tokens[p.counter]._TOKEN_TYPE);
        ++p.counter;
        void *rhs = expression_rule(p, nextPrec);
        //std::cout << ((Expr *)rhs)->getKind() << "\n";
        lhs = new BinOpExpr((Expr *)lhs, op, (Expr *)rhs, EXPR_TYPES::expr_binary);
    }

    return lhs;
}

void *assign_stmt_rule(Parser &p)
{
    void *var_name = nullptr;
    void *value = nullptr;
    if(
        (var_name = var_rule(p))
        &&
        (consume_token(p, _TOKEN_EQU)) // consume `=`
        &&
        (value = expression_rule(p, 1))
    )
    {
        Const *var_name_const_node = new Const((MeowObject *)var_name, EXPR_TYPES::expr_const);
        NameExpr *name_expr_node = new NameExpr((Expr *)var_name_const_node, (Expr *)value, EXPR_TYPES::expr_nameexpr);
        return name_expr_node;
    }
    else
    {
        return NULL;
    }
}

void *show_stmt_rule(Parser &p)
{
    void *a = nullptr;

    if(
        consume_token(p, _TOKEN_SHOW)
        &&
        (
            a = expression_rule(p, 1)
        )
    )
    {
        // since expression_rule will return Binop expr, const expr or other expr
        // i gonna just return that and compiler will handle the type and all
        return a;
    }
    else
    {
        return NULL;
    }
}

void *statment_rule(Parser &p)
{
    void *a = nullptr;

    if(a = assign_stmt_rule(p))
    {
        AssignmnetStmt *assignstmt = new AssignmnetStmt((Expr *)a, STMT_TYPES::stmt_assign);
        return assignstmt;
    }
    else if(a = show_stmt_rule(p))
    {
        ShowStmt *showStmt = new ShowStmt((Expr *)a, STMT_TYPES::stmt_show);
        return showStmt;
    }
    else
    {
        return NULL;
    }
}

void *parse(const std::vector<Token> &tok_list, _rule rule)
{
    if(tok_list.size() == 1 && tok_list.back()._TOKEN_TYPE == _TOKEN_EOT) return NULL;

    Parser p = gen_parser(tok_list, 0, 0);

    Module *mod = new Module();
    void *a = nullptr;

again:
    if(a = statment_rule(p))
    {
        mod->addStmt((Stmts *) a);
    }
    else 
    {
        mod = NULL;
    }

    if(!expect_token(p, _TOKEN_EOT)) goto again;

    return mod;
}