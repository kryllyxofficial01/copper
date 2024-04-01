#ifndef __GENERIC_NODE_HPP
#define __GENERIC_NODE_HPP

#include <string>

#include "node.hpp"

class GenericNode: public Node {
    public:
        GenericNode() {
            this->type = GENERIC_NODE;
        }

        std::string value;
};

#endif