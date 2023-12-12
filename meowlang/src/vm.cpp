#include "../../include/vm.hpp"
#include "../../include/internals/mewcore_stackframe.hpp"
#include "../../include/code.hpp"

void PROG_FRAME::push_frame(MEOW_STACKFRAME *f)
{
    ++frame_pointer;
    frame.push_back(f);
}

void PROG_FRAME::pop_frame()
{
    --frame_pointer;
    delete(frame[frame_pointer]);
    frame.pop_back();
}

void startexec(const std::vector<bytecode> cooked_code)
{
    PROG_FRAME current_frame;
    MEOW_STACKFRAME m_stackframe;
    current_frame.push_frame(&m_stackframe);

    for(bytecode byte : cooked_code)
    {
        switch (byte.op)
        {
        case OP_CODES::LOAD_CONST :
            current_frame.frame[current_frame.frame_pointer]->push_stack((int64_t *) byte.arg);
            break;

        case OP_CODES::ADD :
        {
            Integer *a = (Integer *)current_frame.frame[current_frame.frame_pointer]->pop_stack();
            Integer *b = (Integer *)current_frame.frame[current_frame.frame_pointer]->pop_stack();
            Integer *newVal = new Integer(((int64_t)a->value + (int64_t)b->value), MEOWOBJECTKIND::IntObj);
            current_frame.frame[current_frame.frame_pointer]->push_stack((int64_t *) newVal);
            break;
        }
        case OP_CODES::SUB :
        {
            Integer *a = (Integer *)current_frame.frame[current_frame.frame_pointer]->pop_stack();
            Integer *b = (Integer *)current_frame.frame[current_frame.frame_pointer]->pop_stack();
            Integer *newVal = new Integer(((int64_t)a->value - (int64_t)b->value), MEOWOBJECTKIND::IntObj);
            current_frame.frame[current_frame.frame_pointer]->push_stack((int64_t *) newVal);
            break;
        }
        case OP_CODES::MUL :
        {
            Integer *a = (Integer *)current_frame.frame[current_frame.frame_pointer]->pop_stack();
            Integer *b = (Integer *)current_frame.frame[current_frame.frame_pointer]->pop_stack();
            Integer *newVal = new Integer(((int64_t)a->value * (int64_t)b->value), MEOWOBJECTKIND::IntObj);
            current_frame.frame[current_frame.frame_pointer]->push_stack((int64_t *) newVal);
            break;
        }
        case OP_CODES::DIV :
        {  
            Integer *a = (Integer *)current_frame.frame[current_frame.frame_pointer]->pop_stack();
            Integer *b = (Integer *)current_frame.frame[current_frame.frame_pointer]->pop_stack();
            Integer *newVal = new Integer(((int64_t)a->value / (int64_t)b->value), MEOWOBJECTKIND::IntObj);
            current_frame.frame[current_frame.frame_pointer]->push_stack((int64_t *) newVal);
            break;
        }
        case OP_CODES::MOD :
        {
            Integer *a = (Integer *)current_frame.frame[current_frame.frame_pointer]->pop_stack();
            Integer *b = (Integer *)current_frame.frame[current_frame.frame_pointer]->pop_stack();
            Integer *newVal = new Integer(((int64_t)a->value % (int64_t)b->value), MEOWOBJECTKIND::IntObj);
            current_frame.frame[current_frame.frame_pointer]->push_stack((int64_t *) newVal);
            break;
        }
        case OP_CODES::STORE :
        {
            MeowObject *var = (MeowObject *)byte.arg;
            MeowObject *val = (MeowObject *)current_frame.frame[current_frame.frame_pointer]->pop_stack();
            current_frame.frame[current_frame.frame_pointer]->store_const(var, val);
            break;
        }
        
        case OP_CODES::OUT :
        {
            MeowObject *top = (MeowObject *) current_frame.frame[current_frame.frame_pointer]->pop_stack();
            top->onShow();
            break;
        }

        default:
            break;
        }
    }
}