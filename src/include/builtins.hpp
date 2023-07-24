#ifndef _BUILTINS_HPP
#define _BUILTINS_HPP

#include <vector>
#include <stdio.h>
#include <map>

#include "ast.hpp"
#include "utils.hpp"

void println(std::vector<ast_t> args, VARS_TYPE variables);

const static std::unordered_map<std::string, BUILTIN_FUNC_TYPE> builtin_functions = {
    {"println", &println}
};

#endif