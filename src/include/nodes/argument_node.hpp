#ifndef __ARGUMENT_NODE_HPP
#define __ARGUMENT_NODE_HPP

#include <string>

#include "node.hpp"

class ArgumentNode: public Node {
    public:
        ArgumentNode() {
            this->type = ARGUMENT_NODE;
        }

        std::string name;
        std::string value_type;
};

#endif