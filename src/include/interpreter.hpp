#ifndef _INTERPRETER_HPP
#define _INTERPRETER_HPP

#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <any>

#include "ast.hpp"
#include "builtins.hpp"
#include "utils.hpp"

class Interpreter {
    public:
        Interpreter(ast_t ast);
        Interpreter() = default;

        void interpret();

    private:
        void interpret(ast_t ast);

        void interpret_variable_definition(ast_t var_def_node);
        void interpret_function_definition(ast_t func_def_node);
        void interpret_function_call(ast_t func_call_node);

        ast_t ast;

        VARS_TYPE variables;
        FUNCS_TYPE functions;
};

#endif