#ifndef __INTERPRETER_HPP
#define __INTERPRETER_HPP

#include <stdio.h>
#include <any>
#include <stack>
#include <string>

#include "scope.hpp"
#include "token.hpp"
#include "utils.hpp"

#include "nodes/master_node.hpp"
#include "nodes/variable_node.hpp"
#include "nodes/type_node.hpp"
#include "nodes/generic_node.hpp"
#include "nodes/node.hpp"

class Interpreter {
    public:
        Interpreter(MasterNode ast);

        void interpret();

    private:
        void interpret_next_node();
        void interpret_variable_definition(scope_t* scope);
        void interpret_variable_redefinition(scope_t* scope);

        std::any evaluate_expression(GenericNode node, enum BuiltinTypes value_type, scope_t* scope);

        void next_node();

        MasterNode ast;

        scope_t global_scope;

        size_t index;
        NODE current_node;
};

#endif
