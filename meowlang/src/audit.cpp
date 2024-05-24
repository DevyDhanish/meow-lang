#include "../../include/audit.hpp"
#include "../../include/error.hpp"
#include "../../include/token.hpp"

enum meowAuditResult
{
    AUDIT_OK,   // 0
    AUDIT_BAD,  // 1
};

meowAuditResult audit_nameexpr(Auditor *a)
{
    if(a->tokens[a->counter]._TOKEN_TYPE == _TOKEN_VAR
        &&
        a->tokens[a->counter + 1]._TOKEN_TYPE == _TOKEN_EQU
    )
    {
        return meowAuditResult::AUDIT_OK;
    }
    else
    {
        Log(MEOW_ERROR_TYPES::SYNTAX_E, "Did you forgot to put '=' ??", a->tokens[a->counter]._TOKEN_LINE_NUMBER, a->tokens[a->counter]._TOKEN_LINE);
        return meowAuditResult::AUDIT_BAD;
    }
}

void Auditor::meowAudit()
{

    if(audit_nameexpr(this))
    {
        return;
    }

    move();
}