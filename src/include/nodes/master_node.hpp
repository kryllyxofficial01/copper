#ifndef __MASTER_NODE_HPP
#define __MASTER_NODE_HPP

#include <vector>
#include <any>

#include "node.hpp"

class MasterNode {
    public:
        std::vector<std::pair<enum NodeTypes, std::any>> nodes;
};

#endif