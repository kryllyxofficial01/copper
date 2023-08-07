#ifndef _AST_HPP
#define _AST_HPP

#include <string>
#include <vector>
#include <any>

enum NodeType {
    STRING_NODE,
    VARIABLE_DEFINITION_NODE,
    VARIABLE_USAGE_NODE,
    FUNCTION_CALL_NODE,
    COMPOUND_NODE,
    NOP_NODE
};

typedef struct AST {
    enum NodeType type;

    std::string string_value;

    std::string var_def_name;
    std::string var_def_type;
    std::any var_def_value;

    std::string var_use_name;

    std::string func_call_name;
    std::vector<struct AST> func_call_args;

    std::vector<struct AST> nodes;
} ast_t;

#endif