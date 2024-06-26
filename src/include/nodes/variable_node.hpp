#ifndef __VARIABLE_NODE_HPP
#define __VARIABLE_NODE_HPP

#include <string>

#include "generic_node.hpp"

class VariableDefinitionNode {
    public:
        std::string name;
        std::string value_type;
        GenericNode value;
};

class VariableRedefinitionNode {
    public:
        std::string name;
        GenericNode value;
};

class VariableCallNode {
    public:
        std::string name;
};

#endif