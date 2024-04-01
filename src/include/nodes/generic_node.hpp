#ifndef __GENERIC_NODE_HPP
#define __GENERIC_NODE_HPP

#include <vector>

#include "node.hpp"

class GenericNode: public Node {
    public:
        GenericNode() {
            this->type = GENERIC_NODE;
        }

        std::vector<Token> value;
};

#endif