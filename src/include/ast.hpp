#ifndef _AST_H
#define _AST_H

#include <string>
#include <vector>
#include <any>

enum NodeType {
    STRING_NODE,
    ARG_NODE,
    VARIABLE_DEFINITION_NODE,
    VARIABLE_USAGE_NODE,
    FUNCTION_DEFINITION_NODE,
    FUNCTION_CALL_NODE,
    COMPOUND_NODE,
    NOP_NODE
};

typedef struct AST {
    enum NodeType node_type;
    std::vector<struct AST> nodes;

    std::string string_value;

    std::string arg_data_type;
    std::string arg_name;

    std::string var_def_data_type;
    std::string var_def_name;
    std::any var_def_value;

    std::string var_use_name;

    std::string func_def_return_type;
    std::string func_def_name;
    std::vector<struct AST> func_def_args;
    std::any func_def_body;

    std::string func_call_name;
    std::vector<struct AST> func_call_args;
} ast_t;

#endif