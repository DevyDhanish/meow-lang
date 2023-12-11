#include "../../../include/internals/mewcore_ast.hpp"
#include "../../../include/internals/mewcore_obj.hpp"
#include <iostream>

void displayTargetexpr(expr_ty *target)
{
    std::cout << "expr kind : Name\n";
    switch (target->v.Name.id->kind)
    {
    case _const_kind::Char :
        std::cout << " id : Char : " << target->v.Name.id->data.Char.val << "\n";
        break;
    case _const_kind::Float :
        std::cout << " id : Float : " << target->v.Name.id->data.Float.val << "\n";
        break;

    case _const_kind::Int :
        std::cout << " id : Int : " << target->v.Name.id->data.Integer.val << "\n";
        break;
    
    default:
        break;
    }
}

void displayValueExpr(expr_ty *value)
{
    std::cout << "expr kind : Const\n";
    switch (value->v.Const.value->kind)
    {
    case _const_kind::Char :
        std::cout << " id : Char : " << value->v.Const.value->data.Char.val << "\n";
        break;
    case _const_kind::Float :
        std::cout << " id : Float : " << value->v.Const.value->data.Float.val << "\n";
        break;

    case _const_kind::Int :
        std::cout << " id : Int : " << value->v.Const.value->data.Integer.val << "\n";
        break;
    
    default:
        break;
    }
}

void displayBinopexpr(expr_ty *expr)
{
    std::cout << "left - >" << expr->v.BinOp.left->v.Const.value->data.Integer.val;
    std::cout << "Add\n";
    std::cout << "right -> " << expr->v.BinOp.right->v.Const.value->data.Integer.val;
}

void displayNameexpr(expr_ty *expr)
{
    std::cout << "expr kind : Name expr\n";
    std::cout << "target -> ";
    switch (expr->v.NameExpr.target->kind)
    {
    case _expr_kind::VarName :
        std::cout << expr->v.NameExpr.target->v.Name.id->data.Char.val << "\n";
        break;
    case _expr_kind::BinOp :
        displayBinopexpr(expr->v.NameExpr.target);
        break;

    default:
        break;
    }
    std::cout << "\n";
    std::cout << "value -> \n";
    switch (expr->v.NameExpr.value->kind)
    {
    case _expr_kind::BinOp :
        displayBinopexpr(expr->v.NameExpr.target);
        break;
    default:
        break;
    }
    std::cout << "\n";
}

void displayAssignStmt(stmt_ty *stmt)
{
    std::cout << "stmt kind : Assign\n";
    switch (stmt->v.Assign.body->kind)
    {
    case _expr_kind::NameExpr :
        displayNameexpr(stmt->v.Assign.body);
        break;
    case _expr_kind::BinOp :
        displayBinopexpr(stmt->v.Assign.body);
        break;
    default:
        break;
    }
}