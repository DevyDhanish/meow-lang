/*

This Parser.cpp files assumes that the tokens given to is are correct as in syntax wise
syntax checks and error display happens in audit.cpp

*/

#include "parser.hpp"
#include "../include/internals/mewcore_ast.hpp"
#include "../include/internals/mewcore_obj.hpp"

void *statment_rule(Parser &p);
void *expression_rule(Parser &p, int prec);

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
        case _TOKEN_COMMA:
        case _TOKEN_SQRBRACLOSE:
            return 0;
            break;

        // case _TOKEN_EQU:
        //     return 2;
        //     break;

        case _TOKEN_AND:
        case _TOKEN_OR:
            return 3;

        case _TOKEN_EQUALSTO: 
        case _TOKEN_NOTEQUALS: 
            return 4;
            break;

        case _TOKEN_LESSTHAN: 
        case _TOKEN_LESSEQU: 
        case _TOKEN_GREATERTHAN:
        case _TOKEN_GREATEREQU:
            return 5;

        case _TOKEN_PLUS: 
        case _TOKEN_MINUS: 
            return 6; 
            break;

        case _TOKEN_MUL: 
        case _TOKEN_DIV: 
        case _TOKEN_MOD: 
            return 7; 
            break;

        case _TOKEN_NEGATE:
        case _TOKEN_NOT:
            return 8;

        case _TOKEN_BRAOPEN:
        case _TOKEN_SQRBRAOPEN:
            return 9;

        default:
            return -1;
            break;
    }
}

int getAssociativity(TOKEN_T type)
{
    // 1 -> left associtive
    // 0 -> right associtive

    switch (type)
    {
    case _TOKEN_PLUS:
    case _TOKEN_MINUS:
    case _TOKEN_MUL:
    case _TOKEN_DIV:
    case _TOKEN_MOD:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

void *var_rule(Parser &p)
{
    if(expect_token(p, _TOKEN_VAR))
    {
        //std::cout << "Variable\n";
        Var *varname = nullptr;
        varname = new Var(p.tokens[p.counter]._TOKEN_VALUE, MEOWOBJECTKIND::Meow_VarObj); // get the var name
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
            Integer *mewint = new Integer(val, MEOWOBJECTKIND::Meow_IntObj);
            const_obj = mewint;
            break;
        }
        case _TOKEN_STRING:
        {
            String *mewstr = new String(curr_token_value, MEOWOBJECTKIND::Meow_StringObj);
            const_obj = mewstr;
            break;
        }
        case _TOKEN_FLOAT:
        {
            long double val = std::stold(curr_token_value);
            Float *mewfloat = new Float(val, MEOWOBJECTKIND::Meow_FloatObj);
            const_obj = mewfloat;
            break;
        }
        case _TOKEN_VAR:
        {
            return var_rule(p);
            break;
        }
        case _TOKEN_NULL:
        {
            Integer *nullint = new Integer (0, MEOWOBJECTKIND::Meow_IntObj);
            const_obj = nullint;
            break;
        }
        case _TOKEN_TRUE:
        {
            Integer *trueint = new Integer(1, MEOWOBJECTKIND::Meow_IntObj);
            const_obj = trueint;
            break;
        }
        case _TOKEN_FALSE:
        {
            Integer *falseint = new Integer(0, MEOWOBJECTKIND::Meow_IntObj);
            const_obj = falseint;
            break;
        }
        case _TOKEN_CURLOPEN:
        {
            consume_token(p, _TOKEN_CURLOPEN);
            ArrayObj *arr = new ArrayObj(MEOWOBJECTKIND::Meow_ArrayObj);

            vals:
                MeowObject *ele = (MeowObject *) const_rule(p);
                consume_token(p, _TOKEN_COMMA);
                if(ele) arr->addElements(ele);
                if(!consume_token(p, _TOKEN_CURLCLOSE)) goto vals;

            return arr;
        }
        default:
            //std::cout << "Unknow token encountered\n";
            return NULL;
            break;
    }
    ++p.counter;
    return const_obj;
}

void *expression_rule(Parser &p, int prec)
{
    void *a = nullptr;
    void *lhs = nullptr;

    a = const_rule(p);
    //std::cout << "a -> " << ((MeowObject *)a)->getKind() << "\n";
    if(a != NULL)
    {
        lhs = new Const((MeowObject *)a, EXPR_TYPES::expr_const);
    }

    if(expect_token(p, _TOKEN_NEGATE))
    {
        ++p.counter;
        a = expression_rule(p, getPrecedence(_TOKEN_NEGATE));
        lhs = new UnaryExpr((Expr *)a, OP_TYPES::negate, EXPR_TYPES::expr_unary);
    }

    if(expect_token(p, _TOKEN_NOT))
    {
        ++p.counter;
        a = expression_rule(p, getPrecedence(_TOKEN_NOT));
        lhs = new UnaryExpr((Expr *)a, OP_TYPES::logical_not, EXPR_TYPES::expr_unary);
    }

    // if(expect_token(p, _TOKEN_SQRBRAOPEN))
    // {
    //     if(p.tokens[p.counter - 1]._TOKEN_TYPE == _TOKEN_VAR)
    //     {
    //         ++p.counter;

    //         Expr *val = (Expr *)expression_rule(p, 1);
    //         consume_token(p, _TOKEN_SQRBRACLOSE);

    //         IndexExpr *indexexpr = new IndexExpr(val, (Expr *) lhs, EXPR_TYPES::expr_index);

    //         lhs = indexexpr;
    //     }

    //     else
    //     {
    //         std::cout << "bad use of `[]`\n";
    //         exit(0);
    //     }
    // }

    if(expect_token(p, _TOKEN_BRAOPEN))
    {
        if(p.tokens[p.counter - 1]._TOKEN_TYPE == _TOKEN_VAR)
        {
            ++p.counter;
            //std::cout << "LHS -> " << ((Const *)lhs)->getKind() << "\n";
            FuncCallExpr *funcallexpr = new FuncCallExpr((Expr *) lhs, EXPR_TYPES::expr_call);

            if(!consume_token(p, _TOKEN_BRACLOSE))
            {
                args:
                    funcallexpr->addArgs((Expr *) expression_rule(p, 1));
                    consume_token(p, _TOKEN_COMMA);
                    if(!consume_token(p, _TOKEN_BRACLOSE)) goto args;

                    //std::cout << "Func args -> " << funcallexpr->args.size() << "\n";

                    lhs = funcallexpr;
            }
            else
            {
                lhs = funcallexpr;
            }

        }
        else{
            ++p.counter;
            lhs = expression_rule(p, 1);
            consume_token(p, _TOKEN_BRACLOSE);
        }
    }

    while(1)
    {
        // std::cout << p.tokens[p.counter]._TOKEN_VALUE << "\n";
        // std::cout << "Current prec -> " << prec << "\n";
        // std::cout << "Next prev -> " << getPrecedence(p.tokens[p.counter]._TOKEN_TYPE) << "\n"; 

        if(getPrecedence(p.tokens[p.counter]._TOKEN_TYPE) < prec) break;

        OP_TYPES op;

        switch (p.tokens[p.counter]._TOKEN_TYPE)
        {
            // arthimetic
            case _TOKEN_PLUS: op = OP_TYPES::Add; break;
            case _TOKEN_MUL: op = OP_TYPES::Mul; break;
            case _TOKEN_DIV: op = OP_TYPES::Div; break;
            case _TOKEN_MINUS: op = OP_TYPES::Sub; break;
            case _TOKEN_MOD: op = OP_TYPES::Mod; break;
            // comparission
            case _TOKEN_EQUALSTO: op = OP_TYPES::Cmp_equ; break;
            case _TOKEN_LESSTHAN: op = OP_TYPES::Cmp_less; break;
            case _TOKEN_LESSEQU: op = OP_TYPES::Cmp_lessequ; break;
            case _TOKEN_GREATERTHAN: op = OP_TYPES::Cmp_great; break;
            case _TOKEN_GREATEREQU: op = OP_TYPES::Cmp_greatequ; break;
            case _TOKEN_NOTEQUALS: op = OP_TYPES::Cmp_notequ; break;
            case _TOKEN_AND: op = OP_TYPES::logical_and; break;
            case _TOKEN_OR: op = OP_TYPES::logical_or; break;
            // indexing
            case _TOKEN_SQRBRAOPEN: op = OP_TYPES::indexing; break;
            default: break;
        }

        int nextPrec = getPrecedence(p.tokens[p.counter]._TOKEN_TYPE);

        if(getAssociativity(p.tokens[p.counter]._TOKEN_TYPE))
        {
            nextPrec++;
        }

        ++p.counter;

        void *rhs = nullptr;
        rhs = expression_rule(p, nextPrec);
        
        //std::cout << ((Expr *)rhs)->getKind() << "\n";
        lhs = new BinOpExpr((Expr *)lhs, op, (Expr *)rhs, EXPR_TYPES::expr_binary);
    }

    consume_token(p, _TOKEN_SQRBRACLOSE); // if there is sqr_bracket left out it will be consumed here
    return lhs;
}

void *name_expr_rule(Parser &p)
{
    if(expect_token(p, _TOKEN_VAR) && p.tokens[p.counter + 1]._TOKEN_TYPE == _TOKEN_EQU)
    {
        void *var_name = nullptr;
        void *value = nullptr;
        var_name = var_rule(p);
        consume_token(p, _TOKEN_EQU);
        value = expression_rule(p, 1);
        Const *var_name_const_node = new Const((MeowObject *)var_name, EXPR_TYPES::expr_const);
        NameExpr *name_expr_node = new NameExpr((Expr *)var_name_const_node, (Expr *)value, EXPR_TYPES::expr_nameexpr);
        return name_expr_node;
    }
    else
    {
        return NULL;
    }
}

void *idxass_expr_rule(Parser &p)
{
    
    if(expect_token(p, _TOKEN_VAR) && p.tokens[p.counter + 1]._TOKEN_TYPE == _TOKEN_SQRBRAOPEN)
    {
        BinOpExpr *var = (BinOpExpr *) expression_rule(p, 1);
        void *idx = var->right;
        var = (BinOpExpr *) var->left;

        //std::cout << ((Var *)var)->value;
        // while(expect_token(p, _TOKEN_SQRBRAOPEN))
        // {
        //     consume_token(p, _TOKEN_SQRBRAOPEN);

        //     void *idx = expression_rule(p, 1);

        //     consume_token(p, _TOKEN_SQRBRACLOSE);

        //     var = new BinOpExpr((Expr *)var, OP_TYPES::indexing, (Expr *)idx, EXPR_TYPES::expr_binary);
        // }

        consume_token(p, _TOKEN_EQU);

        void *value = expression_rule(p, 1);

        IndexAssignExpr *idxAss = new IndexAssignExpr((Expr *)var, (Expr *)idx, (Expr *)value, EXPR_TYPES::expr_indexAssign);

        return idxAss;
    }
    // {
    //     //std::cout << "Parsing herer\n";
    //     void *var = nullptr;
    //     void *idx = nullptr;
    //     void *value = nullptr;

    //     var = var_rule(p);
    //     Const *var_const = new Const((MeowObject *)var, EXPR_TYPES::expr_const);

    //     //std::cout << "TOok val -> " << ((Var *)var)->value << "\n";
    //     consume_token(p, _TOKEN_SQRBRAOPEN);
    //     idx = expression_rule(p, 1);

    //     //std::cout << ((Expr *)idx)->getKind() << "\n";
    //     consume_token(p, _TOKEN_SQRBRACLOSE);

    //     consume_token(p, _TOKEN_EQU);

    //     //std::cout << p.tokens[p.counter]._TOKEN_VALUE << "\n";
    //     value = expression_rule(p, 1);
    //     //std::cout << ((Expr *)value)->getKind() << "\n";

    //     IndexAssignExpr *idxAss = new IndexAssignExpr((Expr *)var_const, (Expr *)idx, (Expr *)value, EXPR_TYPES::expr_indexAssign);
    //     return idxAss;
    // }

    else
    {
        return NULL;
    }
}

void *assign_stmt_rule(Parser &p)
{
    void *a = nullptr;

    if(a = name_expr_rule(p))
    {
        return a;
    }
    else
    {
        return NULL;
    }
}

void *show_stmt_rule(Parser &p)
{
    void *a = nullptr;

    if(!consume_token(p, _TOKEN_SHOW)) { return NULL; }

    a = expression_rule(p, 1);

    return a;
}

void *elif_stmt_rule(Parser &p)
{
    void *a = nullptr;  // hold condition
    void *b = nullptr;  // hold true block
    void *c = nullptr;  // hold false block if provided

    if(consume_token(p, _TOKEN_ELIF))
    {
        //p.counter++;
    }
    else
    {
        return NULL;
    }

    a = expression_rule(p, 1);  // parse condition

    IfStmt *ifstmt = new IfStmt((Expr *)a, STMT_TYPES::stmt_if);

    consume_token(p, _TOKEN_CURLOPEN);

true_condition:
    b = statment_rule(p);
    ifstmt->addTbody((Stmts *)b);
    if(!consume_token(p, _TOKEN_CURLCLOSE)) goto true_condition;

    if(expect_token(p, _TOKEN_ELIF))
    {
        ifstmt->addFbody((Stmts *) elif_stmt_rule(p));
        return ifstmt;
    }

    if(!consume_token(p, _TOKEN_ELSE))
    {
        return ifstmt;
    }

    consume_token(p, _TOKEN_CURLOPEN);

false_condition:
    c = statment_rule(p);
    ifstmt->addFbody((Stmts *)c);   
    if(!consume_token(p, _TOKEN_CURLCLOSE)) goto false_condition;

    return ifstmt;
}

void *if_stmt_rule(Parser &p)
{
    void *a = nullptr;  // hold condition
    void *b = nullptr;  // hold true block
    void *c = nullptr;  // hold false block if provided

    if(consume_token(p, _TOKEN_IF))
    {
        //p.counter++;
    }
    else
    {
        return NULL;
    }

    a = expression_rule(p, 1);  // parse condition

    IfStmt *ifstmt = new IfStmt((Expr *)a, STMT_TYPES::stmt_if);

    consume_token(p, _TOKEN_CURLOPEN);

true_condition:
    b = statment_rule(p);
    ifstmt->addTbody((Stmts *)b);
    if(!consume_token(p, _TOKEN_CURLCLOSE)) goto true_condition;

    if(expect_token(p, _TOKEN_ELIF))
    {
        ifstmt->addFbody((Stmts *) elif_stmt_rule(p));
        return ifstmt;
    }

    if(!consume_token(p, _TOKEN_ELSE))
    {
        return ifstmt;
    }

    consume_token(p, _TOKEN_CURLOPEN);

false_condition:
    c = statment_rule(p);
    ifstmt->addFbody((Stmts *)c);   
    if(!consume_token(p, _TOKEN_CURLCLOSE)) goto false_condition;

    return ifstmt;
}

void *while_stmt_rule(Parser &p)
{
    void *a = nullptr;
    void *b = nullptr;
    
    if(!consume_token(p, _TOKEN_WHILE))
    {
        return NULL;
    }

    a = expression_rule(p, 1);

    WhileStmt *whilestmt = new WhileStmt((Expr *)a, STMT_TYPES::stmt_while);

    consume_token(p, _TOKEN_CURLOPEN);

body:
    b = statment_rule(p);
    whilestmt->addBody((Stmts *)b);
    if(!consume_token(p, _TOKEN_CURLCLOSE)) goto body;

    return whilestmt;
}

void *func_stmt_rule(Parser &p)
{
    void *a = nullptr;
    void *b = nullptr;
    void *c = nullptr;

    if(!consume_token(p, _TOKEN_FUNC))
    {
        return NULL;
    }

    a = const_rule(p); // parse the function name
    FuncStmt *funcstmt = new FuncStmt((Expr *)a, STMT_TYPES::stmt_func);
    
    consume_token(p, _TOKEN_BRAOPEN);

    if(!consume_token(p, _TOKEN_BRACLOSE))
    {
        params:
            b = expression_rule(p, 1);
            //std::cout << ((Var *)((Const *)b)->value)->value << "\n";
            consume_token(p, _TOKEN_COMMA);
            funcstmt->addPrams((Expr *)b);
            if(!consume_token(p, _TOKEN_BRACLOSE)) goto params;
    }

    consume_token(p, _TOKEN_CURLOPEN);
    
    if(consume_token(p, _TOKEN_CURLCLOSE))
    {
        return funcstmt;
    }

body:
    c = statment_rule(p);
    funcstmt->addBody((Stmts *)c);
    if(!consume_token(p, _TOKEN_CURLCLOSE)) goto body;

    return funcstmt;
}

void *return_stmt_rule(Parser &p)
{
    void *a = nullptr;

    if(!consume_token(p, _TOKEN_RETURN)) return NULL;

    a = expression_rule(p, 1);

    ReturnStmt *retstmt = new ReturnStmt((Expr *)a, STMT_TYPES::stmt_return);

    return retstmt;
}

void *funcall_stmt_rule(Parser &p)
{
    void *a = nullptr;

    //std::cout << "func call" << "\n";
    a = expression_rule(p, 1);
    FuncCallStmt *funcCstmt = new FuncCallStmt((Expr *) a, STMT_TYPES::stmt_funcall);

    return funcCstmt;
}

void *for_stmt_rule(Parser &p)
{
    if(!consume_token(p, _TOKEN_FOR))
    {
        return NULL;
    }

    void *val = expression_rule(p, 1); // get the left variable;
    consume_token(p, _TOKEN_IN);       
    void *r_val = expression_rule(p, 1); // get the right variable;

    ForStmt *for_stmt = new ForStmt((Expr *)val, (Expr *)r_val, STMT_TYPES::stmt_for);

    consume_token(p, _TOKEN_CURLOPEN);

    if(expect_token(p, _TOKEN_CURLCLOSE))
    {
        return for_stmt;
    }

    void *c = nullptr;

body:
    c = statment_rule(p);
    for_stmt->addBody((Stmts *)c);
    if(!consume_token(p, _TOKEN_CURLCLOSE)) goto body;

    return for_stmt;
}

void *simple_stmt_rule(Parser &p)
{
    void *a = nullptr;
    if(a = idxass_expr_rule(p))
    {
        SimpleStmt *s_stmt = new SimpleStmt((Expr *)a, STMT_TYPES::stmt_simple);
        return s_stmt;
    }
    else if (a = funcall_stmt_rule(p))
    {
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
    else if(a = if_stmt_rule(p))
    {
        return a;
    }
    else if(a = while_stmt_rule(p))
    {
        return a;
    }
    else if(a = return_stmt_rule(p))
    {
        return a;
    }
    else if(a = func_stmt_rule(p))
    {
        return a;
    }
    else if(a = for_stmt_rule(p))
    {
        return a;
    }
    else if(a = simple_stmt_rule(p))
    {
        return a;
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