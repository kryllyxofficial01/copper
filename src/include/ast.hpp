#ifndef _AST_HPP
#define _AST_HPP

#include <string>
#include <vector>

enum NodeType {
    STRING_NODE,
    FUNCTION_CALL_NODE,
    COMPOUND_NODE,
    NOP_NODE
};

typedef struct AST {
    enum NodeType type;

    std::string string_value;

    std::string func_call_name;
    std::vector<struct AST> func_call_args;

    std::vector<struct AST> nodes;
} ast_t;

#endif