#ifndef _BUILTINS_HPP
#define _BUILTINS_HPP

#include <vector>
#include <functional>
#include <stdio.h>

#include "ast.hpp"

#define BUILTIN_TYPE std::function<void(std::vector<ast_t>)>

/**
 * @brief Prints to stdout, and attaches a newline to the end.
 *
 * @param args The list of arguments passed to the function.
*/
void println(std::vector<ast_t> args);

#endif