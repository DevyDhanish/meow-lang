#include "../../include/vm.hpp"
#include "../../include/code.hpp"
#include "../../include/internals/mewcore_constpool.hpp"
#include "../../include/internals/mewcore_stackframe.hpp"
#include "../../include/bltins/bltins.hpp"
#include <stack>

void Interpreter::Execute()
{
    MEOW_STACKFRAME *main_frame = new MEOW_STACKFRAME(code->getBlockById("$main"));
    frame.push(main_frame);

    FRAME_EXIT_CODE frame_exit_code = frame.top()->executeFrame();

again:
    switch (frame_exit_code)
    {
    case FRAME_EXIT_CODE::FRAME_CALL:
    {
        std::stack<uint64_t> args;
        uint32_t amount = frame.top()->getByteByIp().arg;
        // store the args
        while (amount)
        {
            args.push(frame.top()->popFromStack());
            amount--;
        }

        MeowObject *func_name = (MeowObject *) frame.top()->popFromStack();
        //func_name->onShow();
        std::string func_name_str = ((Var *)func_name)->value;

        BLTIN_METHODS id = getBltinMethodId( func_name_str );

        if(id != BUILDINT_NULL)
        {
            MeowObject *r_val = execBltMethod(id, args);
            
            if(r_val) frame.top()->pushToStack((uint64_t) r_val);
            
            frame_exit_code = frame.top()->resumeFrame();
            goto again;
            break;
        }

        std::string name = "$" + ((Var *)func_name)->value;

        MEOW_STACKFRAME *func_frame = new MEOW_STACKFRAME(code->getBlockById(name));
        put_const(func_frame->pool, func_name, func_name);

        // this is soo stupid
        std::stack<uint64_t> r_args;

        while(!args.empty())
        {
            r_args.push(args.top());
            args.pop();
        }

        // unload the r_args
        while (!r_args.empty())
        {
            func_frame->pushToStack(r_args.top());
            r_args.pop();
        }
    
        // push & call the frame
        frame.push(func_frame);
        frame_exit_code = frame.top()->executeFrame();
        goto again;
        break;
    }

    case FRAME_EXIT_CODE::FRAME_RETURN:
    {
        MeowObject *return_val = (MeowObject *) frame.top()->popFromStack();
        frame.pop();
        if(frame.empty()) return;
        frame.top()->pushToStack((uint64_t) return_val);
        frame_exit_code = frame.top()->resumeFrame();
        goto again;
        break;
    }

    case FRAME_EXIT_CODE::FRAME_EXIT_NORMAL:
    {
        frame.pop();
        if(frame.empty()) return;
        frame_exit_code = frame.top()->resumeFrame();
        goto again;
        break;
    }

    default:
        break;
    
    }
}