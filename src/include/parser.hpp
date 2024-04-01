#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <vector>
#include <string>

#include "token.hpp"

#include "nodes/master_node.hpp"
#include "nodes/variable_node.hpp"

class Parser {
    public:
        Parser(std::vector<Token> tokens);

        Node parse();

    private:
        Node parse_next_token();
        Node parse_id();

        Node parse_variable_definition();

        Token peek(int offset);
        void eat(enum TokenTypes expected_type);
        void next_token();

        std::vector<Token> tokens;

        size_t index;
        Token current_token;
};

#endif