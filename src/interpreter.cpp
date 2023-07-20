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

            case VARIABLE_DEFINITION_NODE:
                this->interpret_variable_definition(node);
                break;
        }
    }
}

void Interpreter::interpret_variable_definition(ast_t var_def_node) {
    ast_t var_def_value = std::any_cast<struct AST>(
        var_def_node.var_def_value
    );

    this->variables.insert({
        var_def_node.var_def_name,
        std::make_pair(
            var_def_node.var_def_data_type,
            var_def_value
        )
    });
}

void Interpreter::interpret_function_call(ast_t func_call_node) {
    if (builtin_functions.count(func_call_node.func_call_name)) {
        BUILTIN_FUNC_TYPE builtin = builtin_functions.find(
            func_call_node.func_call_name
        )->second;
        builtin(func_call_node.func_call_args);
    }
}