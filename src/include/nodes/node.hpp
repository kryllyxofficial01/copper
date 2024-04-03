#ifndef __NODE_HPP
#define __NODE_HPP

#include <any>

enum NodeTypes {
    MASTER_NODE,

    VARIABLE_DEFINITION_NODE,
    VARIABLE_MODIFICATION_NODE,

    IF_STATEMENT_NODE,
    IF_ELSE_STATEMENT_NODE,

    FUNCTION_CALL_NODE,
    FUNCTION_DEFINITION_NODE,

    ARGUMENT_NODE,

    GENERIC_NODE
};

#define NODE std::pair<enum NodeTypes, std::any>

#endif