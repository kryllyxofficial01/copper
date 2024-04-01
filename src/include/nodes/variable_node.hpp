#ifndef __VARIABLE_NODE_HPP
#define __VARIABLE_NODE_HPP

#include <string>

#include "node.hpp"
#include "generic_node.hpp"

class VariableDefinitionNode: public Node {
    public:
        VariableDefinitionNode() {
            this->type = VARIABLE_DEFINITION_NODE;
        }

        std::string name;
        std::string value_type;
        GenericNode value;
};

#endif