#ifndef __FUNCTION_NODE_HPP
#define __FUNCTION_NODE_HPP

#include <string>
#include <vector>

#include "node.hpp"
#include "generic_node.hpp"
#include "argument_node.hpp"

class FunctionCallNode: public Node {
    public:
        FunctionCallNode() {
            this->type = FUNCTION_CALL_NODE;
        }

        std::string name;
        std::vector<GenericNode> arguments;
};

class FunctionDefinitionNode: public Node {
    public:
        FunctionDefinitionNode() {
            this->type = FUNCTION_DEFINITION_NODE;
        }

        std::string name;
        std::string return_type;
        std::vector<ArgumentNode> arguments;
        std::vector<MasterNode> lines;
};

#endif