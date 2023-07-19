#ifndef _INTERPRETER_HPP
#define _INTERPRETER_HPP

#include <vector>
#include <string>
#include <unordered_map>

#include "ast.hpp"
#include "builtins.hpp"

const static std::unordered_map<std::string, BUILTIN_TYPE> builtins = {
    {"println", &println}
};

class Interpreter {
    public:
        Interpreter(ast_t ast);
        Interpreter() = default;

        void interpret();

    private:
        void interpret_function_call(ast_t func_call_node);

        ast_t ast;
};

#endif