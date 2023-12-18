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
    current_frame = frame.back();
}

void Interpreter::popFrame()
{
    if(frame.size() == 0)
    {
        return;
    }

    frame.pop_back();
    current_frame = frame.back();
}

void Interpreter::jumpIpForward(uint32_t offset)
{
    ip = ip + offset;
}

void Interpreter::jumpIpBackward(uint32_t offset)
{
    ip = ip - offset;
    //std::cout << "IP pointing to " << opcodes_string[cooked_code[ip].op];
    if(ip < 0)
    {
        std::cout << "Ip was offseted to negative\n";
        exit(0);
    }
}

void Interpreter::saveip()
{
    ip_state = ip;
}

void Interpreter::loadip()
{
    ip = ip_state;
}

void Interpreter::saveblock()
{
    block_state = currExecBlock;
}

void Interpreter::loadblock()
{
    currExecBlock = block_state;
}

void handleByte(Interpreter *interpreter, bytecode byte)
{
    switch(byte.op)
    {
        case OP_CODES::LOAD_CONST:
        {
            //std::cout << "LODED CONST TO STACK OF TYPE " << ((MeowObject *)byte.arg)->getKind() << "\n";
            interpreter->current_frame->pushToStack(byte.arg);
            break;
        }

        case OP_CODES::STORE :
        {
            //((Var *)((MeowObject *)byte.arg))->value;
            put_const(interpreter->current_frame->pool, (MeowObject *)byte.arg, (MeowObject *)interpreter->current_frame->popFromStack());
            //std::cout << "STORED VAL TO CONST POOL ID : " << ((Var *) byte.arg)->value << "\n";
            break;
        }

        case OP_CODES::LOAD_NAME :
        {
            //std::cout << "Trying to load name -> " << ((Var *)((MeowObject *)byte.arg))->value << "\n";
            MeowObject *valFromvar = get_const(interpreter->current_frame->pool, (MeowObject *)byte.arg);
            if(!valFromvar)
            {
                std::cout << "Undefined Variable " << ((Var *)byte.arg)->value << "\n";
                exit(0);
            }
            interpreter->current_frame->pushToStack((uint64_t)valFromvar);
            // std::cout << "LOADED VALUE FROM CONST POOL TO STACK : ";
            // valFromvar->onShow();
            // std::cout << "\n";
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

        case OP_CODES::AND:
        {
            MeowObject *a = (MeowObject *) interpreter->current_frame->popFromStack();
            MeowObject *b = (MeowObject *) interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *) a->onAnd(b);
            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }
            break;
        }

        case OP_CODES::OR:
        {
            MeowObject *a = (MeowObject *) interpreter->current_frame->popFromStack();
            MeowObject *b = (MeowObject *) interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *) a->onOr(b);

            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }

            break;
        }

        case OP_CODES::NOT:
        {
            MeowObject *a = (MeowObject *) interpreter->current_frame->popFromStack();
            MeowObject *result = (MeowObject *) a->onNot();

            if(result)
            {
                interpreter->current_frame->pushToStack((uint64_t) result);
            }

            break;
        }

        case OP_CODES::JUMP:
        {
            interpreter->jumpIpForward((uint32_t) byte.arg - 1);
            break;
        }

        case OP_CODES::JUMP_BACK:
        {
            interpreter->jumpIpBackward((uint32_t) byte.arg);
            break;
        }

        case OP_CODES::JUMP_IF_FALSE:
        {
            MeowObject *a = (MeowObject *) interpreter->current_frame->popFromStack();
            if(!((Integer *)a)->value)
            {
                interpreter->jumpIpForward((uint32_t) byte.arg - 1);
            }
            break;
        }

        case OP_CODES::CALL:
        {
            MEOW_STACKFRAME *nframe = new MEOW_STACKFRAME();
            uint32_t arg_cout = byte.arg;

            interpreter->saveip();
            interpreter->saveblock();
            
            while(arg_cout)
            {
                nframe->pushToStack(interpreter->current_frame->popFromStack());
                arg_cout--;
            }

            MeowObject *fname = (MeowObject *) interpreter->current_frame->popFromStack();
            interpreter->Execute( ("$" + ((Var *)fname)->value), nframe);
            break;
        }

        case OP_CODES::RETURN:
        {
            MeowObject *top = (MeowObject * )interpreter->current_frame->popFromStack();
            interpreter->popFrame();
            interpreter->current_frame->pushToStack((uint64_t) top);
            interpreter->loadblock();
            interpreter->loadip();
            break;
        }

        case OP_CODES::OUT:
        {
            MeowObject *valAtTop = (MeowObject *)interpreter->current_frame->popFromStack();
            valAtTop->onShow();
            std::cout << "\n";
            break;
        }

        default:
            break;
    }
}

void Interpreter::Execute(std::string _id, MEOW_STACKFRAME *frame)
{
    pushFrame(frame);
    currExecBlock = cooked_code->getBlockById(_id);
    ip = 0;

    while(ip < currExecBlock->bytes.size())
    {
        handleByte(this, currExecBlock->bytes[ip]);

        ip++;
    }
}