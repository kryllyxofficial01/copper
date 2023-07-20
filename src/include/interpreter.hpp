#ifndef _INTERPRETER_HPP
#define _INTERPRETER_HPP

#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <any>

#include "ast.hpp"
#include "builtins.hpp"

#define __GET_VAR(v, x) std::any_cast<ast_t>(v.find(x)->second.second)

const static std::unordered_map<std::string, BUILTIN_FUNC_TYPE> builtin_functions = {
    {"println", &println}
};

class Interpreter {
    public:
        Interpreter(ast_t ast);
        Interpreter() = default;

        void interpret();

    private:
        void interpret_variable_definition(ast_t var_def_node);
        void interpret_function_call(ast_t func_call_node);

        ast_t ast;

        std::map<std::string, std::pair<std::string, std::any>> variables;
};

#endif