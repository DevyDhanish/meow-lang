#include "../../include/vm.hpp"
#include "../../include/code.hpp"
#include "../../include/internals/mewcore_constpool.hpp"

void Interpreter::pushFrame(MEOW_STACKFRAME *f)
{
    if(!f)
    {
        return;
    }

    frame.push_back(f);
    fp++;
    current_frame = frame.back();
}

MEOW_STACKFRAME *Interpreter::popFrame()
{
    if(frame.size() == 0)
    {
        return NULL;
    }

    fp--;
    MEOW_STACKFRAME *topop = frame.back();
    current_frame = frame[fp];
    frame.pop_back();

    return topop;
}

void handleByte(Interpreter *interpreter, bytecode byte)
{
    switch(byte.op)
    {
        case OP_CODES::LOAD_CONST:
        {
            std::cout << "LODED CONST TO STACK OF TYPE " << ((MeowObject *)byte.arg)->getKind() << "\n";
            interpreter->current_frame->pushToStack(byte.arg);
            break;
        }

        case OP_CODES::STORE :
        {
            put_const(interpreter->current_frame->pool, (MeowObject *)byte.arg, (MeowObject *)interpreter->current_frame->popFromStack());
            std::cout << "STORED VAL TO CONST POOL ID : " << ((Var *) byte.arg)->value << "\n";
            break;
        }

        case OP_CODES::LOAD_NAME :
        {
            MeowObject *valFromvar = get_const(interpreter->current_frame->pool, (MeowObject *)byte.arg);
            interpreter->current_frame->pushToStack((uint64_t)valFromvar);
            std::cout << "LOADED VALUE FROM CONST POOL TO STACK : ";
            valFromvar->onShow();
            std::cout << "\n";
            break;
        }

        case OP_CODES::ADD:
        {
                MeowObject *a = (MeowObject *)interpreter->current_frame->popFromStack();
                MeowObject *b = (MeowObject *)interpreter->current_frame->popFromStack();
                MeowObject *result = (MeowObject *) a->onAdd(b);
                if(result)
                {
                    interpreter->current_frame->pushToStack((uint64_t) result);
                }
                break;
        }

        case OP_CODES::SUB:
        {
            MeowObject *a = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *b = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *) a->onSub(b);
            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }   
            break;
        }

        case OP_CODES::MUL:
        {
            MeowObject *a = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *b = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *)a->onMul(b);
            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }
            break;
        }

        case OP_CODES::DIV:
        {
            MeowObject *a = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *b = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *) a->onDiv(b);
            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }
            break;
        }

        case OP_CODES::MOD:
        {
            MeowObject *a = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *b = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *) a->onMod(b);
            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }
            break;
        }

        case OP_CODES::CMP_EQU:
        {
            MeowObject *a = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *b = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *) a->onCmpE(b);
            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }
            break;
        }

        case OP_CODES::CMP_NOTEQU:
        {
            MeowObject *a = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *b = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *) a->onCmpNE(b);
            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }
            break;
        }

        case OP_CODES::CMP_LESS:
        {
            MeowObject *a = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *b = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *) a->onCmpL(b);
            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }
            break;
        }

        case OP_CODES::CMP_LESSEQU:
        {
            MeowObject *a = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *b = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *) a->onCmpLE(b);
            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }
            break;
        }

        case OP_CODES::CMP_GREAT:
        {
            MeowObject *a = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *b = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *) a->onCmpG(b);
            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }
            break;
        }

        case OP_CODES::CMP_GREATEQU:
        {
            MeowObject *a = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *b = (MeowObject *)interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *) a->onCmpGE(b);
            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }
            break;
        }

        case OP_CODES::NEGATE:
        {
            MeowObject *a = (MeowObject *) interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *) a->onNegate();
            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }
            break;
        }

        case OP_CODES::OUT:
        {
            MeowObject *valAtTop = (MeowObject *)interpreter->current_frame->getValFromStack(interpreter->current_frame->stack_pointer - 1);
            valAtTop->onShow();
            break;
        }

        default:
            break;
    }
}

void startexec(const std::vector<bytecode> &cooked_code)
{
    Interpreter *interpreter = new Interpreter();
    MEOW_STACKFRAME *main = new MEOW_STACKFRAME(); 

    // put the main frame into interpreter frame stack
    interpreter->pushFrame(main);

    std::cout << "Everything is working up to here\n";


    for(bytecode byte : cooked_code)
    {
        handleByte(interpreter, byte);
    }
}