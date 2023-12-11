#pragma once
#include "token.hpp"
#include <vector>
#include "code.hpp"
#include "internals/mewcore_ast.hpp"

std::vector<bytecode> compile(Module *mod);
