#ifndef __MASTER_NODE_HPP
#define __MASTER_NODE_HPP

#include <vector>

#include "node.hpp"

class MasterNode: public Node {
    public:
        MasterNode() {
            this->type = MASTER_NODE;
        }

        std::vector<Node> nodes;
};

#endif