#include "../../include/compiler.hpp"
#include "../../include/token.hpp"
#include "../../include/internals/mewcore_ast.hpp"
#include "../../include/internals/mewcore_obj.hpp"
#include "../../include/code.hpp"
#include <iostream>

std::vector<bytecode> bytes;
std::vector<uint32_t> jump_if_false_offset_table;
std::vector<uint32_t> jump_offset_table;

void compileUnary(UnaryExpr *uExpr);
void compileConstExpr(Const *constExpr);
void compileBinopExpr(BinOpExpr *expr);
void compileNameExpr(NameExpr *nameExpr);
void compileAssignStmt(AssignmnetStmt *assstmt);
void compileShowStmt(ShowStmt *showstmt);
void compileIfStmt(IfStmt *ifstmt);
void compileStmts(std::vector<Stmts *> stmts);
void compileWhileStmt(WhileStmt *wstmt);
std::vector<bytecode> compile(Module *mod);

void replaceJumpOpsWithOffset(std::vector<bytecode> &bcode, std::vector<uint32_t> offset_table, OP_CODES type)
{
    uint32_t counter = offset_table.size() - 1;

    for(bytecode &bc : bcode)
    {
        if(bc.op == type)
        {
            bc.arg = offset_table[counter];
            counter--;                          // from back because the offset table is calculated using recursion so the first value is at last
        }
    }
}

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
        compileUnary((UnaryExpr *) expr->left);
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
        compileUnary((UnaryExpr *)expr->right);
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

    bytes.push_back(makeByteCode((uint8_t)op, (uint64_t)0));
}

void compileUnary(UnaryExpr *uExpr)
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
        compileUnary((UnaryExpr *)uExpr->value);
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

    bytes.push_back(makeByteCode((uint8_t)op, (uint64_t)0));
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
        compileUnary((UnaryExpr *)nameExpr->value);
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
        compileUnary((UnaryExpr *)showstmt->value);
        break;
    
    default:
        break;
    }

    bytes.push_back(makeByteCode(OP_CODES::OUT, (uint64_t)0));
}

void compileIfStmt(IfStmt *ifstmt)
{
    if(!ifstmt->condition) std::cout << "Condition is empty\n";
    switch(ifstmt->condition->getKind())
    {
        case EXPR_TYPES::expr_binary:
            compileBinopExpr((BinOpExpr *)ifstmt->condition);
            break;
        case EXPR_TYPES::expr_const:
            compileConstExpr((Const *)ifstmt->condition);
            break;
        case EXPR_TYPES::expr_nameexpr:
            compileNameExpr((NameExpr *)ifstmt->condition);
            break;
        case EXPR_TYPES::expr_unary:
            compileUnary((UnaryExpr *)ifstmt->condition);
            break;
        default:
            break;
    }

    bytes.push_back(makeByteCode((uint8_t)OP_CODES::JUMP_IF_FALSE, (uint64_t)0));
    
    uint32_t jump_if_offset = bytes.size() - 1;
    if(!ifstmt->tbody.size()) std::cout << "If statment does not have a true body\n";
    compileStmts(ifstmt->tbody);
    bytes.push_back(makeByteCode((uint8_t)OP_CODES::JUMP, (uint64_t)0));
    jump_if_offset = (uint32_t) bytes.size() - jump_if_offset; // the at the last there will be a jump byte

    std::cout << "JUMP OFFSET OVERTIME -> " << jump_if_offset << "\n";

    uint32_t jump_offset = bytes.size() - 1;
    if(!ifstmt->fbody.size()) std::cout << "If statment does not have a false body\n";
    compileStmts(ifstmt->fbody);
    jump_offset = (uint32_t) bytes.size() - jump_offset;

    jump_if_false_offset_table.push_back(jump_if_offset);
    jump_offset_table.push_back(jump_offset);
}

void compileWhileStmt(WhileStmt *wstmt)
{
    uint32_t whilestart = bytes.size() - 1;
    if(!wstmt->condition) std::cout << "While does not have a condition\n";
    switch(wstmt->condition->getKind())
    {
        case EXPR_TYPES::expr_binary:
            compileBinopExpr((BinOpExpr *)wstmt->condition);
            break;
        case EXPR_TYPES::expr_const:
            compileConstExpr((Const *)wstmt->condition);
            break;
        case EXPR_TYPES::expr_nameexpr:
            compileNameExpr((NameExpr *)wstmt->condition);
            break;
        case EXPR_TYPES::expr_unary:
            compileUnary((UnaryExpr *)wstmt->condition);
            break;
        default:
            break;
    }
    bytes.push_back(makeByteCode((uint8_t)OP_CODES::JUMP_IF_FALSE, (uint64_t)0));

    uint32_t jump_if_offset = bytes.size() - 1;
    if(!wstmt->body.size()){ std::cout << "While does not have a body\n"; }
    compileStmts(wstmt->body);
    bytes.push_back(makeByteCode((uint8_t)OP_CODES::JUMP_BACK, (bytes.size() - (uint64_t)whilestart)));
    jump_if_offset = (uint32_t) bytes.size() - jump_if_offset;

    jump_if_false_offset_table.push_back(jump_if_offset);
}

void compileStmts(std::vector<Stmts *> stmts)
{
    for(Stmts *a : stmts)
    {
        switch (a->getKind())
        {

        case STMT_TYPES::stmt_assign:
            compileAssignStmt((AssignmnetStmt *)a);
            break;
        
        case STMT_TYPES ::stmt_show:
            compileShowStmt((ShowStmt *)a);
            break; 

        case STMT_TYPES::stmt_if:
            compileIfStmt((IfStmt *)a);
            break;

        case STMT_TYPES::stmt_while:
            compileWhileStmt((WhileStmt *)a);
            break;

        default:
            break;
        }
    }
}

std::vector<bytecode> compile(Module *mod)
{

    compileStmts(mod->body);

    replaceJumpOpsWithOffset(bytes, jump_if_false_offset_table, OP_CODES::JUMP_IF_FALSE);   // replace all the jump_if_false op codes with correct offset
    replaceJumpOpsWithOffset(bytes, jump_offset_table, OP_CODES::JUMP);                     // replace all the jump op codes with correct offset

    return bytes;
}