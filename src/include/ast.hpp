#ifndef _AST_HPP
#define _AST_HPP

#include <string>
#include <vector>
#include <any>

#define ARG_NODE_TYPE std::pair<std::string, std::string>

enum NodeType {
    INTEGER_NODE,
    FLOAT_NODE,
    STRING_NODE,
    VARIABLE_DEFINITION_NODE,
    VARIABLE_REDEFINITION_NODE,
    VARIABLE_USAGE_NODE,
    FUNCTION_DEFINITION_NODE,
    FUNCTION_CALL_NODE,
    COMPOUND_NODE,
    NOP_NODE
};

typedef struct AST {
    enum NodeType type;

    int integer_value;

    double float_value;

    std::string string_value;

    std::string var_def_name;
    std::string var_def_type;
    std::any var_def_value;

    std::string var_redef_name;
    std::any var_redef_value;

    std::string var_use_name;

    std::string func_def_name;
    std::vector<ARG_NODE_TYPE> func_def_args;
    std::string func_def_return_type;
    std::vector<struct AST> func_def_body;

    std::string func_call_name;
    std::vector<struct AST> func_call_args;

    std::vector<struct AST> nodes;
} ast_t;

#endif