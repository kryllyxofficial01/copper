#ifndef __IF_STATEMENT_NODE_HPP
#define __IF_STATEMENT_NODE_HPP

#include <vector>

#include "generic_node.hpp"
#include "node.hpp"

class IfStatementNode {
    public:
        GenericNode conditional;
        std::vector<NODE> body;
};

class IfElseStatementNode {
    public:
        GenericNode conditional;
        std::vector<NODE> if_body;
        std::vector<NODE> else_body;
};

#endif