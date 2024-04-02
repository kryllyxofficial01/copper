#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <vector>
#include <string>

#include "token.hpp"

#include "nodes/master_node.hpp"
#include "nodes/variable_node.hpp"
#include "nodes/function_node.hpp"

class Parser {
    public:
        Parser(std::vector<Token> tokens);

        MasterNode parse();

    private:
        Node parse_next_token();
        Node parse_id();

        VariableDefinitionNode parse_variable_definition();
        FunctionCallNode parse_function_call();
        FunctionDefinitionNode parse_function_definition();

        void eat(enum TokenTypes expected_type);
        void next_token();
        Token peek(int offset);

        std::vector<Token> tokens;

        size_t index;
        Token current_token;
};

#endif