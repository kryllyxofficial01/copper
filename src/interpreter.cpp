#include "include/interpreter.hpp"

Interpreter::Interpreter(ast_t ast) {
    this->ast = ast;
}

void Interpreter::interpret() {
    for (ast_t node: this->ast.nodes) {
        switch (node.node_type) {
            case FUNCTION_CALL_NODE:
                this->interpret_function_call(node);
                break;
        }
    }
}

void Interpreter::interpret_function_call(ast_t func_call_node) {
    if (builtins.count(func_call_node.func_call_name)) {
        BUILTIN_TYPE builtin = builtins.find(
            func_call_node.func_call_name
        )->second;
        builtin(func_call_node.func_call_args);
    }
}