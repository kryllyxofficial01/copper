#ifndef __FUNCTION_NODE_HPP
#define __FUNCTION_NODE_HPP

#include <string>
#include <vector>

#include "node.hpp"
#include "generic_node.hpp"

class FunctionCallNode: public Node {
    public:
        FunctionCallNode() {
            this->type = FUNCTION_CALL_NODE;
        }

        std::string name;
        std::vector<GenericNode> arguments;
};

#endif