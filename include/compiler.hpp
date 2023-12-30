#pragma once
#include "token.hpp"
#include <vector>
#include "code.hpp"
#include "internals/mewcore_ast.hpp"
#include "byteblocks.hpp"

Block *compile(Module *mod);
