#include "../../include/compiler.hpp"
#include "../../include/token.hpp"
#include "../../include/internals/mewcore_ast.hpp"
#include "../../include/internals/mewcore_obj.hpp"
#include "../../include/code.hpp"
#include <iostream>

std::vector<bytecode> bytes;

void compileUnaryNegate(UnaryExpr *uExpr);
void compileConstExpr(Const *constExpr);
void compileBinopExpr(BinOpExpr *expr);
void compileNameExpr(NameExpr *nameExpr);
void compileAssignStmt(AssignmnetStmt *assstmt);
void compileShowStmt(ShowStmt *showstmt);
std::vector<bytecode> compile(Module *mod);

void compileConstExpr(Const *constExpr)
{
    // Check if the constExpr is null
    if (constExpr == nullptr) {
        std::cout << "Error: constExpr is null\n";
        return;
    }

    switch (((MeowObject *)constExpr->value)->getKind())
    {

    case MEOWOBJECTKIND::IntObj :
        std::cout << "Integer value: " << ((Integer *) constExpr->value)->value << "\n";
        bytes.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (uint64_t)((Integer *)constExpr->value)));
        break;

    case MEOWOBJECTKIND::FloatObj :
        std::cout << "Float value: " << ((Float *) constExpr->value)->value << "\n";
        bytes.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (uint64_t)((Float *)constExpr->value)));
        break;

    case MEOWOBJECTKIND::StringObj :
        std::cout << "String value: " << ((String *) constExpr->value)->value << "\n";
        bytes.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (uint64_t)((String *)constExpr->value)));
        break;

    case MEOWOBJECTKIND::VarObj :
        std::cout << "Var : " << ((Var *)constExpr->value)->value << "\n";
        bytes.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_NAME, (uint64_t)((Var *)constExpr->value)));
        break;

    default:
        std::cout << "Unknown constant expression kind\n";
        break;
    }
}

void compileBinopExpr(BinOpExpr *expr)
{
    if(!expr->left) std::cout << "Left side is empty\n";
    switch (expr->left->getKind())
    {
    case EXPR_TYPES::expr_const:
        compileConstExpr((Const *) expr->left);
        break;

    case EXPR_TYPES::expr_binary:
        compileBinopExpr((BinOpExpr *) expr->left);
        break;

    case EXPR_TYPES::expr_unary:
        compileUnaryNegate((UnaryExpr *) expr->left);
        break;
    
    default:
        break;
    }

    if(!expr->right) std::cout << "Right side is empty\n";
    switch (expr->right->getKind())
    {
    case EXPR_TYPES::expr_const:
        compileConstExpr((Const *) expr->right);
        break;
    
    case EXPR_TYPES::expr_binary:
        compileBinopExpr((BinOpExpr *)expr->right);
        break;

    case EXPR_TYPES::expr_unary:
        compileUnaryNegate((UnaryExpr *)expr->right);
        break;

    default:
        break;
    }

    OP_CODES op;

    switch (expr->op)
    {
    case OP_TYPES::Add : op = OP_CODES::ADD; break;
    case OP_TYPES::Sub : op = OP_CODES::SUB; break;
    case OP_TYPES::Mul : op = OP_CODES::MUL; break;
    case OP_TYPES::Div : op = OP_CODES::DIV; break;
    case OP_TYPES::Mod : op = OP_CODES::MOD; break;

    case OP_TYPES::Cmp_equ: op = OP_CODES::CMP_EQU; break;
    case OP_TYPES::Cmp_notequ: op = OP_CODES::CMP_NOTEQU; break;
    case OP_TYPES::Cmp_less: op = OP_CODES::CMP_LESS; break;
    case OP_TYPES::Cmp_lessequ: op = OP_CODES::CMP_LESSEQU; break;
    case OP_TYPES::Cmp_great: op = OP_CODES::CMP_GREAT; break;
    case OP_TYPES::Cmp_greatequ: op = OP_CODES::CMP_GREATEQU; break;
    case OP_TYPES::logical_and: op = OP_CODES::AND; break;
    case OP_TYPES::logical_or: op = OP_CODES::OR; break;
    default : std::cout << "Bad opcode\n";   break;
    }

    bytes.push_back(makeByteCode((uint8_t)op, (int64_t)0));
}

void compileUnaryNegate(UnaryExpr *uExpr)
{
    switch (uExpr->value->getKind())
    {
    case EXPR_TYPES::expr_const :
        compileConstExpr((Const *) uExpr->value);
        break;

    case EXPR_TYPES::expr_binary :
        compileBinopExpr((BinOpExpr *)uExpr->value);
        break;

    case EXPR_TYPES::expr_unary:
        compileUnaryNegate((UnaryExpr *)uExpr->value);
        break;
    
    default:
        break;
    }

    OP_CODES op;

    switch (uExpr->op)
    {
    case OP_TYPES::negate :
        op = OP_CODES::NEGATE;
        break;
    case OP_TYPES::logical_not:
        op = OP_CODES::NOT;
        break;
    
    default:
        break;
    }

    bytes.push_back(makeByteCode((uint8_t)op, (int64_t)0));
}

void compileNameExpr(NameExpr *nameExpr)
{
    switch (nameExpr->value->getKind())
    {
    case EXPR_TYPES::expr_const:
        compileConstExpr((Const *)nameExpr->value);
        break;
    case EXPR_TYPES::expr_binary:
        compileBinopExpr((BinOpExpr *) nameExpr->value);
        break;

    case EXPR_TYPES::expr_unary:
        compileUnaryNegate((UnaryExpr *)nameExpr->value);
        break;
    
    default:
        break;
    }
    
    bytes.push_back(makeByteCode((uint8_t)OP_CODES::STORE, (uint64_t)(Var *)((Const *)nameExpr->target)->value));
}

void compileAssignStmt(AssignmnetStmt *assstmt)
{
    switch (assstmt->value->getKind())
    {
    case EXPR_TYPES::expr_nameexpr:
        compileNameExpr((NameExpr *)assstmt->value);
        break;
    
    default:
        break;
    }
}

void compileShowStmt(ShowStmt *showstmt)
{
    switch (showstmt->value->getKind())
    {
    case EXPR_TYPES::expr_const :
        compileConstExpr((Const *)showstmt->value);
        break;

    case EXPR_TYPES::expr_binary :
        compileBinopExpr((BinOpExpr *)showstmt->value);
        break;

    case EXPR_TYPES::expr_unary:
        compileUnaryNegate((UnaryExpr *)showstmt->value);
        break;
    
    default:
        break;
    }

    bytes.push_back(makeByteCode(OP_CODES::OUT, (int64_t)0));
}

std::vector<bytecode> compile(Module *mod)
{

    for(Stmts *a : mod->body)
    {
        switch (a->getKind())
        {

        case STMT_TYPES::stmt_assign:
            compileAssignStmt((AssignmnetStmt *)a);
            break;
        
        case STMT_TYPES ::stmt_show:
            compileShowStmt((ShowStmt *)a);
            break; 

        default:
            break;
        }
    }

    return bytes;
}