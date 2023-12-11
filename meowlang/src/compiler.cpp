#include "../../include/compiler.hpp"
#include "../../include/token.hpp"
#include "../../include/internals/mewcore_ast.hpp"
#include "../../include/internals/mewcore_obj.hpp"
#include "../../include/code.hpp"
#include <iostream>

std::vector<bytecode> bytes;

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
        bytes.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (int64_t)((Integer *)constExpr->value)));
        break;

    case MEOWOBJECTKIND::FloatObj :
        std::cout << "Float value: " << ((Float *) constExpr->value)->value << "\n";
        bytes.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (int64_t)((Float *)constExpr->value)));
        break;

    case MEOWOBJECTKIND::StringObj :
        std::cout << "String value: " << ((String *) constExpr->value)->value << "\n";
        bytes.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (int64_t)(String *)constExpr->value));
        break;

    default:
        std::cout << "Unknown constant expression kind\n";
        break;
    }
}

void compileBinopExpr(BinOpExpr *expr)
{
    switch (expr->left->getKind())
    {
    case EXPR_TYPES::ConstExpr:
        compileConstExpr((Const *) expr->left);
        break;

    case EXPR_TYPES::BinopExpr:
        compileBinopExpr((BinOpExpr *) expr->left); break;
    
    default:
        break;
    }

    switch (expr->right->getKind())
    {
    case EXPR_TYPES::ConstExpr:
        compileConstExpr((Const *) expr->right);
        break;
    
    case EXPR_TYPES::BinopExpr:
        compileBinopExpr((BinOpExpr *)expr->right); break;

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
    default : std::cout << "Bad opcode\n";   break;
    }

    bytes.push_back(makeByteCode((uint8_t)expr->op, (int64_t)0));
}

void compileNameExpr(NameExpr *nameExpr)
{
    switch (nameExpr->value->getKind())
    {
    case EXPR_TYPES::ConstExpr :
        compileConstExpr((Const *)nameExpr->value);
        break;
    case EXPR_TYPES::BinopExpr:
        compileBinopExpr((BinOpExpr *) nameExpr->value);
        break;
    
    default:
        break;
    }
    
    bytes.push_back(makeByteCode((uint8_t)OP_CODES::STORE, (int64_t)nameExpr->target));
}

void compileAssignStmt(AssignmnetStmt *assstmt)
{
    switch (assstmt->value->getKind())
    {
    case EXPR_TYPES::NameExprssion :
        compileNameExpr((NameExpr *)assstmt->value);
        break;
    
    default:
        break;
    }
}

std::vector<bytecode> compile(Module *mod)
{

    for(Stmts *a : mod->body)
    {
        switch (a->getKind())
        {
        case STMT_TYPES::AssignStmt:
            compileAssignStmt((AssignmnetStmt *)a);
            break;
        
        default:
            break;
        }
    }

    return bytes;
}