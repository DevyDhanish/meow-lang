#include "../../include/compiler.hpp"
#include "../../include/token.hpp"
#include "../../include/internals/mewcore_ast.hpp"
#include "../../include/internals/mewcore_obj.hpp"
#include "../../include/code.hpp"
#include "../../include/byteblocks.hpp"
#include <iostream>
#include <unordered_map>

//std::vector<bytecode> bytevect;

void compileUnary(UnaryExpr *uExpr, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table);
void compileConstExpr(Const *constExpr, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table);
void compileBinopExpr(BinOpExpr *expr, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table);
void compileNameExpr(NameExpr *nameExpr, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table);
void compileAssignStmt(AssignmnetStmt *assstmt, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table);
void compileShowStmt(ShowStmt *showstmt, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table);
void compileIfStmt(IfStmt *ifstmt, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table);
void compileStmts(std::vector<Stmts *> stmts, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table);
void compileWhileStmt(WhileStmt *wstmt, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table);
void compileFuncCallStmt(FuncCallStmt *funcall, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table);
void compileFuncCallExpr(FuncCallExpr *funcallexpr, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table);
void compileReturnStmt(ReturnStmt *retstmt, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table);
void compileExpr(Expr *a, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table);
Block *compile(Module *mod);

void replaceJumpOpsWithOffset(std::vector<bytecode> &bcode, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    uint32_t c = 0;

    while(c < bcode.size())
    {
        if(offset_table.find(c) != offset_table.end())
        {
            bcode[c].arg = offset_table[c];
        }

        c++;
    }
}

void compileVarConst(Var *var, std::vector<bytecode> &bytevect, Block *block, OP_CODES type, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    switch (type)
    {
    case OP_CODES::STORE:
        bytevect.push_back(makeByteCode((uint8_t)OP_CODES::STORE, (uint64_t)var));
        break;

    case OP_CODES::LOAD_NAME:
        bytevect.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_NAME, (uint64_t)var));
        break;
    
    default:
        break;
    }
}

void compileConstExpr(Const *constExpr, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    // Check if the constExpr is null
    if (constExpr == nullptr) {
        std::cout << "Error: constExpr is null\n";
        return;
    }

    switch (((MeowObject *)constExpr->value)->getKind())
    {

    case MEOWOBJECTKIND::IntObj :
        //std::cout << "Integer value: " << ((Integer *) constExpr->value)->value << "\n";
        bytevect.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (uint64_t)((Integer *)constExpr->value)));
        break;

    case MEOWOBJECTKIND::FloatObj :
        //std::cout << "Float value: " << ((Float *) constExpr->value)->value << "\n";
        bytevect.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (uint64_t)((Float *)constExpr->value)));
        break;

    case MEOWOBJECTKIND::StringObj :
        //std::cout << "String value: " << ((String *) constExpr->value)->value << "\n";
        bytevect.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (uint64_t)((String *)constExpr->value)));
        break;

    case MEOWOBJECTKIND::VarObj :
        //std::cout << "Var : " << ((Var *)constExpr->value)->value << "\n";
        bytevect.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_NAME, (uint64_t)((Var *)constExpr->value)));
        break;

    default:
        std::cout << "Unknown constant expression kind\n";
        break;
    }
}

void compileExpr(Expr *a, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    switch (a->getKind())
    {
    case EXPR_TYPES::expr_const:
        compileConstExpr((Const *) a, bytevect, block, offset_table);
        break;

    case EXPR_TYPES::expr_binary:
        compileBinopExpr((BinOpExpr *) a, bytevect, block, offset_table);
        break;

    case EXPR_TYPES::expr_unary:
        compileUnary((UnaryExpr *) a, bytevect, block, offset_table);
        break;

    case EXPR_TYPES::expr_call:
        compileFuncCallExpr((FuncCallExpr *)a, bytevect, block, offset_table);
        break;

    case EXPR_TYPES::expr_nameexpr:
        compileNameExpr((NameExpr *)a, bytevect, block, offset_table);
        break;
    
    default:
        break;
    }
}

void compileBinopExpr(BinOpExpr *expr, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    if(!expr->left) std::cout << "Left side is empty\n";
    compileExpr((Expr *)expr->left, bytevect, block, offset_table);

    if(!expr->right) std::cout << "Right side is empty\n";

    compileExpr(expr->right, bytevect, block, offset_table);

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

    bytevect.push_back(makeByteCode((uint8_t)op, (uint64_t)0));
}

void compileUnary(UnaryExpr *uExpr, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    compileExpr(uExpr->value, bytevect, block, offset_table);

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

    bytevect.push_back(makeByteCode((uint8_t)op, (uint64_t)0));
}

void compileNameExpr(NameExpr *nameExpr, std::vector<bytecode> &bytevect,  Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    compileExpr(nameExpr->value, bytevect, block, offset_table);
    
    bytevect.push_back(makeByteCode((uint8_t)OP_CODES::STORE, (uint64_t)(Var *)((Const *)nameExpr->target)->value));
}

void compileAssignStmt(AssignmnetStmt *assstmt, std::vector<bytecode> &bytevect,  Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    switch (assstmt->value->getKind())
    {
    case EXPR_TYPES::expr_nameexpr:
        compileNameExpr((NameExpr *)assstmt->value, bytevect, block, offset_table);
        break;
    
    default:
        break;
    }
}

void compileShowStmt(ShowStmt *showstmt, std::vector<bytecode> &bytevect,  Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    compileExpr(showstmt->value, bytevect, block, offset_table);

    bytevect.push_back(makeByteCode(OP_CODES::OUT, (uint64_t)0));
}

void compileIfStmt(IfStmt *ifstmt, std::vector<bytecode> &bytevect,  Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    if(!ifstmt->condition) std::cout << "Condition is empty\n";
    compileExpr(ifstmt->condition, bytevect, block, offset_table);

    bytevect.push_back(makeByteCode((uint8_t)OP_CODES::JUMP_IF_FALSE, (uint64_t)0));
    uint32_t jump_if_offset = bytevect.size() - 1;
    uint32_t pos = bytevect.size() - 1;

    //if(!ifstmt->tbody.size()) std::cout << "If statment does not have a true body\n";
    compileStmts(ifstmt->tbody, bytevect, block, offset_table);
    bytevect.push_back(makeByteCode((uint8_t)OP_CODES::JUMP, (uint64_t)0));

    jump_if_offset = (uint32_t) bytevect.size() - jump_if_offset; // the at the last there will be a jump byte
    offset_table[pos] = jump_if_offset;

    //std::cout << "JUMP OFFSET OVERTIME -> " << jump_if_offset << "\n";

    uint32_t jump_offset = bytevect.size() - 1;
    uint32_t pos2 = bytevect.size() - 1;
    //if(!ifstmt->fbody.size()) std::cout << "If statment does not have a false body\n";
    compileStmts(ifstmt->fbody, bytevect, block, offset_table);

    jump_offset = (uint32_t) bytevect.size() - jump_offset;
    offset_table[pos2] = jump_offset;
}

void compileWhileStmt(WhileStmt *wstmt, std::vector<bytecode> &bytevect,  Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    uint32_t whilestart = bytevect.size() - 1;
    if(!wstmt->condition) std::cout << "While does not have a condition\n";
    compileExpr(wstmt->condition, bytevect, block, offset_table);

    bytevect.push_back(makeByteCode((uint8_t)OP_CODES::JUMP_IF_FALSE, (uint64_t)0));
    uint32_t pos = bytevect.size() - 1;
    uint32_t jump_if_offset = bytevect.size() - 1;
    if(!wstmt->body.size()){ std::cout << "While does not have a body\n"; }
    compileStmts(wstmt->body, bytevect, block, offset_table);

    bytevect.push_back(makeByteCode((uint8_t)OP_CODES::JUMP_BACK, (bytevect.size() - (uint64_t)whilestart)));
    jump_if_offset = (uint32_t) bytevect.size() - jump_if_offset;

    offset_table[pos] = jump_if_offset;
}

void compileFuncStmt(FuncStmt *fstmt, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    bytevect.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (uint64_t)(((Var *)(Const *)fstmt->name))));
    bytevect.push_back(makeByteCode((uint8_t)OP_CODES::STORE, (uint64_t)(((Var *)(Const *)fstmt->name))));

    std::string funcname = "$" + ((Var *)((Const *)fstmt->name))->value;
    Block *fblock = new Block(funcname);

    std::unordered_map<uint32_t, uint32_t> offset_table_nblock;

    for(Expr *p : fstmt->parameters)
    {
        //std::cout << ((Var *)((Const *)p))->value << "\n";
        compileVarConst( ((Var *)((Const *)p)->value), fblock->bytes, fblock, OP_CODES::STORE, offset_table_nblock);
    }

    if(fstmt->body.size())
        compileStmts(fstmt->body, fblock->bytes, fblock, offset_table_nblock);

    // Integer *retVal = new Integer(0, MEOWOBJECTKIND::IntObj);
    // fblock->bytes.push_back(makeByteCode((uint8_t)OP_CODES::LOAD_CONST, (uint64_t)retVal));
    // fblock->bytes.push_back(makeByteCode((uint8_t)OP_CODES::RETURN, (uint64_t)0));

    replaceJumpOpsWithOffset(fblock->bytes, offset_table_nblock);

    block->block.push_back(fblock);
}

void compileFuncCallExpr(FuncCallExpr *funcall, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    if(!funcall->name) std::cout << "Func has no name\n";
    compileExpr(funcall->name, bytevect, block, offset_table);

    for(Expr *a : funcall->args)
    {
        compileExpr(a, bytevect, block, offset_table);
    }

    bytevect.push_back(makeByteCode((uint8_t )OP_CODES::CALL, (uint64_t)funcall->args.size()));
}

void compileFuncCallStmt(FuncCallStmt *funcall, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    compileFuncCallExpr((FuncCallExpr *) funcall->value, bytevect, block, offset_table);
}

void compileReturnStmt(ReturnStmt *retstmt, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    if(retstmt->value)
    {
        compileExpr((Expr *)retstmt->value, bytevect, block, offset_table);
    }

    bytevect.push_back(makeByteCode((uint8_t)OP_CODES::RETURN, (uint64_t)0));
}

void compileStmts(std::vector<Stmts *> stmts, std::vector<bytecode> &bytevect, Block *block, std::unordered_map<uint32_t, uint32_t> &offset_table)
{
    for(Stmts *a : stmts)
    {
        switch (a->getKind())
        {

        case STMT_TYPES::stmt_assign:
            compileAssignStmt((AssignmnetStmt *)a, bytevect, block, offset_table);
            break;
        
        case STMT_TYPES ::stmt_show:
            compileShowStmt((ShowStmt *)a, bytevect, block, offset_table);
            break; 

        case STMT_TYPES::stmt_if:
            compileIfStmt((IfStmt *)a, bytevect, block, offset_table);
            break;

        case STMT_TYPES::stmt_while:
            compileWhileStmt((WhileStmt *)a, bytevect, block, offset_table);
            break;

        case STMT_TYPES::stmt_func:
            compileFuncStmt((FuncStmt *)a, bytevect, block, offset_table);
            break;

        case STMT_TYPES::stmt_funcall:
            compileFuncCallStmt((FuncCallStmt *)a, bytevect, block, offset_table);
            break;

        case STMT_TYPES::stmt_return:
            compileReturnStmt((ReturnStmt *)a, bytevect, block, offset_table);
            break;

        default:
            break;
        }
    }
}

Block *compile(Module *mod)
{

    Block *main = new Block("$main");
    std::unordered_map<uint32_t, uint32_t> offset_table_main;

    compileStmts(mod->body, main->bytes, main, offset_table_main);

    replaceJumpOpsWithOffset(main->bytes, offset_table_main);

    return main;
}