#ifndef _BUILTINS_HPP
#define _BUILTINS_HPP

#include <vector>
#include <functional>
#include <stdio.h>

#include "ast.hpp"

#define BUILTIN_FUNC_TYPE std::function<void(std::vector<ast_t>)>

void println(std::vector<ast_t> args);

#endif