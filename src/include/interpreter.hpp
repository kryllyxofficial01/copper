#ifndef _INTERPRETER_HPP
#define _INTERPRETER_HPP

#include <vector>
#include <string>
#include <unordered_map>

#include "ast.hpp"
#include "builtins.hpp"

// List of builtin functions.
const static std::unordered_map<std::string, BUILTIN_TYPE> builtins = {
    {"println", &println}
};

class Interpreter {
    public:
        Interpreter(ast_t ast);
        Interpreter() = default;

        /**
         * @brief Iterates through the AST and interpret each node.
        */
        void interpret();

    private:
        /**
         * @brief Interprets a function call.
         *
         * @param func_call_node The function call node.
        */
        void interpret_function_call(ast_t func_call_node);

        ast_t ast;
};

#endif