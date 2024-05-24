#include "../../../include/internals/mewcore_stackframe.hpp"
#include "../../../include/bltins/bltins.hpp"

void MEOW_STACKFRAME::pushToStack(uint64_t val)
{
    if(!val)
    {
        return;
    }

    //stack_pointer++;
    //std::cout << "STACK SIZE -> " << stack->size() << "\n";
    stack.push_back(val);
}

uint64_t MEOW_STACKFRAME::popFromStack()
{
    if(stack.size() == 0)
    {
        return 0;
    }

    int64_t toPop = stack.back();
    //stack_pointer--;
    stack.pop_back();
    return toPop;
}

uint64_t MEOW_STACKFRAME::topOfStack()
{
    if(stack.size() == 0)
    {
        return 0;
    }

    return stack.back();
}

bytecode MEOW_STACKFRAME::getByteByIp()
{
    return code->bytes[ip];
}

// void MEOW_STACKFRAME::replaceValInStack(uint16_t idx, uint64_t val)
// {
//     //stack[idx] = val;
//     //return NULL;
// }

// uint64_t MEOW_STACKFRAME::getValFromStack(uint16_t idx)
// {
//     //return stack[idx];
//     return NULL;
// }

FRAME_EXIT_CODE MEOW_STACKFRAME::executeFrame()
{
    while (ip < code->bytes.size())
    {
        bytecode byte = code->bytes[ip];
        switch(byte.op)
        {
            case OP_CODES::LOAD_CONST:
            {
                //std::cout << "LODED CONST TO STACK OF TYPE " << ((MeowObject *)byte.arg)->getKind() << "\n";
                pushToStack(byte.arg);
                break;
            }
            case OP_CODES::STORE :
            {
                MeowObject *val = (MeowObject *) popFromStack();
                //std::cout << "kind -> " << val->getKind() << "\n";
                put_const(pool, (MeowObject *)byte.arg, val);
                break;
            }
            case OP_CODES::LOAD_NAME :
            {
                BLTIN_METHODS id = getBltinMethodId( ((Var *)byte.arg)->value );
                if(id)
                {
                    //std::cout << "PUSHED -> " << ((Var *)byte.arg)->value << "\n";
                    pushToStack(byte.arg);
                }
                else
                {
                    MeowObject *valFromvar = get_const(pool, (MeowObject *)byte.arg);
                    if(!valFromvar)
                    {
                        std::cout << "Undefined Variable " << ((Var *)byte.arg)->value << "\n";
                        exit(0);
                    }
                    
                    pushToStack((uint64_t)valFromvar);
                }
                break;
            }
            case OP_CODES::ADD:
            {
                MeowObject *a = (MeowObject *)popFromStack();
                MeowObject *b = (MeowObject *)popFromStack();
                MeowObject *result = (MeowObject *) a->onAdd(b);
                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                break;
            }
            case OP_CODES::SUB:
            {
                MeowObject *a = (MeowObject *)popFromStack();
                MeowObject *b = (MeowObject *)popFromStack();
                MeowObject *result = (MeowObject *) a->onSub(b);
                if(result)
                {
                    pushToStack((uint64_t) result);
                }   
                break;
            }
            case OP_CODES::MUL:
            {
                MeowObject *a = (MeowObject *)popFromStack();
                MeowObject *b = (MeowObject *)popFromStack();
                MeowObject *result = (MeowObject *)a->onMul(b);
                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                break;
            }
            case OP_CODES::DIV:
            {
                MeowObject *a = (MeowObject *)popFromStack();
                MeowObject *b = (MeowObject *)popFromStack();
                MeowObject *result = (MeowObject *) a->onDiv(b);
                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                break;
            }
            case OP_CODES::MOD:
            {
                MeowObject *a = (MeowObject *)popFromStack();
                MeowObject *b = (MeowObject *)popFromStack();
                MeowObject *result = (MeowObject *) a->onMod(b);
                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                break;
            }
            case OP_CODES::IDX:
            {
                MeowObject *a = (MeowObject *) popFromStack(); // idx
                MeowObject *b = (MeowObject *) popFromStack();  // val

                MeowObject *result = (MeowObject *)b->getAtIndex( ((Integer *)a)->value );

                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                break;
            }
            case OP_CODES::SET_IDX:
            {
                MeowObject *a = (MeowObject *) popFromStack(); // idx
                MeowObject *b = (MeowObject *) popFromStack(); // value
                MeowObject *c = (MeowObject *) popFromStack(); // target

                c->setAtIndex((uint64_t)((Integer *)a)->value, b);
                
                break;
            }
            case OP_CODES::FOR_ITER:
            {
                MeowObject *a = (MeowObject *) popFromStack(); // iterable value

                if(!a->isIterable())
                {
                    std::cout << a->printInfo() << " cannot be iterated\n";
                    exit(0);
                }
                
                Iter *iter_obj = new Iter(a);
                pushToStack((uint64_t)((MeowObject *)iter_obj));

                break;
            }
            case OP_CODES::GET_NEXT:
            {
                MeowObject *iter_obj = (MeowObject *) popFromStack();

                if(iter_obj->getKind() != MEOWOBJECTKIND::Meow_iterObj)
                {
                    std::cout << "Value at the top of the stack was not a iterator\n";
                }

                if(((Iter *)iter_obj)->isExhausted)
                {
                    ip = ip + ((uint32_t) byte.arg - 1);
                }

                pushToStack( (uint64_t)((Iter *)iter_obj)->next());

                break;
            }
            case OP_CODES::CMP_EQU:
            {
                MeowObject *a = (MeowObject *)popFromStack();
                MeowObject *b = (MeowObject *)popFromStack();
                MeowObject *result = (MeowObject *) a->onCmpE(b);
                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                break;
            }
            case OP_CODES::CMP_NOTEQU:
            {
                MeowObject *a = (MeowObject *)popFromStack();
                MeowObject *b = (MeowObject *)popFromStack();
                MeowObject *result = (MeowObject *) a->onCmpNE(b);
                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                break;
            }

            case OP_CODES::CMP_LESS:
            {
                MeowObject *a = (MeowObject *)popFromStack();
                MeowObject *b = (MeowObject *)popFromStack();
                MeowObject *result = (MeowObject *) a->onCmpL(b);
                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                break;
            }
            case OP_CODES::CMP_LESSEQU:
            {
                MeowObject *a = (MeowObject *)popFromStack();
                MeowObject *b = (MeowObject *)popFromStack();
                MeowObject *result = (MeowObject *) a->onCmpLE(b);
                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                break;
            }
            case OP_CODES::CMP_GREAT:
            {
                MeowObject *a = (MeowObject *)popFromStack();
                MeowObject *b = (MeowObject *)popFromStack();
                MeowObject *result = (MeowObject *) a->onCmpG(b);
                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                break;
            }
            case OP_CODES::CMP_GREATEQU:
            {
                MeowObject *a = (MeowObject *)popFromStack();
                MeowObject *b = (MeowObject *)popFromStack();
                MeowObject *result = (MeowObject *) a->onCmpGE(b);
                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                break;
            }
            case OP_CODES::NEGATE:
            {
                MeowObject *a = (MeowObject *) popFromStack();
                MeowObject *result = (MeowObject *) a->onNegate();
                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                break;
            }
            case OP_CODES::AND:
            {
                MeowObject *a = (MeowObject *) popFromStack();
                MeowObject *b = (MeowObject *) popFromStack();
                MeowObject *result = (MeowObject *) a->onAnd(b);
                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                break;
            }
            case OP_CODES::OR:
            {
                MeowObject *a = (MeowObject *) popFromStack();
                MeowObject *b = (MeowObject *) popFromStack();
                MeowObject *result = (MeowObject *) a->onOr(b);

                if(result)
                {
                    pushToStack((uint64_t) result);
                }

                break;
            }
            case OP_CODES::NOT:
            {
                MeowObject *a = (MeowObject *) popFromStack();
                MeowObject *result = (MeowObject *) a->onNot();

                if(result)
                {
                    pushToStack((uint64_t) result);
                }
                
                break;
            }
            case OP_CODES::JUMP:
            {

                ip = ip + ((uint32_t) byte.arg - 1);
                
                break;
            }
            case OP_CODES::JUMP_BACK:
            {
                ip = ip - ((uint32_t) byte.arg);
                
                break;   
            }
            case OP_CODES::JUMP_IF_FALSE:
            {
                MeowObject *a = (MeowObject *) popFromStack();
                if(!((Integer *)a)->value)
                {
                    ip = ip + ((uint32_t) byte.arg - 1);
                }
                break;
            }
            case OP_CODES::CALL:
            {
                ip_savepoint = ip + 1;
                return FRAME_EXIT_CODE::FRAME_CALL;
            }
            case OP_CODES::RETURN:
            {
                return FRAME_EXIT_CODE::FRAME_RETURN; 
            }
            case OP_CODES::OUT:
            {
                MeowObject *valAtTop = (MeowObject *) popFromStack();
                valAtTop->onShow();
                std::cout << "\n";
                break;
            }

            default:
                break;
        }

        ip++;
    }

    return FRAME_EXIT_CODE::FRAME_EXIT_NORMAL;
}

FRAME_EXIT_CODE MEOW_STACKFRAME::resumeFrame()
{
    //std::cout << "Resuming frame -> " << code->id << "\n";
    //std::cout << "Starting from -> " << ip_savepoint << "\n";
    ip = ip_savepoint;
    return executeFrame();
}