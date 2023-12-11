#include "../../include/compiler.hpp"
#include "../../include/token.hpp"
#include "../../include/internals/mewcore_ast.hpp"
#include "../../include/internals/mewcore_obj.hpp"
#include "../../include/code.hpp"

std::vector<bytecode> bytes;

void compileConstExpr(Const *constExpr)
{
    switch (constExpr->value->getKind())
    {
    case MEOWOBJECTKIND::IntObj :
        std::cout << "Const : " << ((Integer *) constExpr->value)->value << "\n";
        bytes.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (int64_t)constExpr->value));
        break;

    case MEOWOBJECTKIND::FloatObj :
        std::cout << "Const : " << ((Float *) constExpr->value)->value << "\n";
        bytes.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (int64_t)constExpr->value));
        break;

    case MEOWOBJECTKIND::StringObj :
        std::cout << "Const : " << ((String *) constExpr->value)->value << "\n";
        bytes.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (int64_t)constExpr->value));
        break;
    
    default:
        break;
    }
}

void compileNameExpr(NameExpr *nameExpr)
{
    switch (nameExpr->value->getKind())
    {
    case EXPR_TYPES::ConstExpr :
        compileConstExpr((Const *)nameExpr->value);
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