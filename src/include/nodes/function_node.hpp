#ifndef __FUNCTION_NODE_HPP
#define __FUNCTION_NODE_HPP

#include <string>
#include <vector>

#include "generic_node.hpp"
#include "argument_node.hpp"

class FunctionCallNode {
    public:
        std::string name;
        std::vector<GenericNode> arguments;
};

class FunctionDefinitionNode {
    public:
        std::string name;
        std::string return_type;
        std::vector<ArgumentNode> arguments;
        std::vector<NODE> body;
};

#endif