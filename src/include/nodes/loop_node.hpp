#ifndef __LOOP_NODE
#define __LOOP_NODE

#include "variable_node.hpp"
#include "generic_node.hpp"
#include "node.hpp"

class ForLoopNode {
    public:
        VariableDefinitionNode iteration_variable;
        GenericNode limit;
        GenericNode iteration;
        std::vector<NODE> body;
};

#endif