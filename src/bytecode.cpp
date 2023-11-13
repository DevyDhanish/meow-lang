#include "../include/bytecode.hpp"


bytecode makebytecode(bytecode_type _mne, Token _op)
{
    bytecode bc;
    bc.mnemonic = _mne;
    bc.operand = _op;

    return bc;
}