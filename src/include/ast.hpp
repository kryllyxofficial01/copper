#ifndef _AST_H
#define _AST_H

#include <string>
#include <vector>

enum NodeType {
    STRING_NODE,
    FUNCTION_CALL_NODE,
    COMPOUND_NODE,
    NOP_NODE
};

typedef struct AST {
    enum NodeType node_type;

    std::string string_value;

    std::string func_call_name;
    std::vector<struct AST> func_call_args;

    std::vector<struct AST> compound_nodes;
} ast_t;

#endif