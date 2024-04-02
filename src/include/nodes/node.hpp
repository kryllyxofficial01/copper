#ifndef __NODE_HPP
#define __NODE_HPP

enum NodeTypes {
    MASTER_NODE,
    VARIABLE_DEFINITION_NODE,
    FUNCTION_CALL_NODE,
    FUNCTION_DEFINITION_NODE,
    ARGUMENT_NODE,
    GENERIC_NODE
};

class Node {
    public:
        enum NodeTypes type;
};

#endif