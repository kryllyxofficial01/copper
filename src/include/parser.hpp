#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <vector>
#include <string>
#include <any>
#include <queue>
#include <stack>

#include "token.hpp"
#include "utils.hpp"

#include "nodes/master_node.hpp"
#include "nodes/type_node.hpp"
#include "nodes/variable_node.hpp"
#include "nodes/if_statement_node.hpp"
#include "nodes/loop_node.hpp"
#include "nodes/function_node.hpp"
#include "nodes/node.hpp"

class Parser {
    public:
        Parser(std::vector<Token> tokens);

        MasterNode parse();

    private:
        NODE parse_next_token();
        NODE parse_id();
        std::vector<NODE> parse_block();
        GenericNode parse_expression(enum TokenTypes termination_token);
        GenericNode parse_expression(std::vector<enum TokenTypes> termination_tokens);

        NODE parse_variable_definition();
        NODE parse_variable_usage();
        NODE parse_if_statement();
        NODE parse_for_loop();
        NODE parse_function_call();
        NODE parse_function_definition();

        RPN to_rpn(std::deque<Token>& tokens);

        void eat(enum TokenTypes expected_type);
        void next_token();
        Token peek(int offset);

        std::vector<Token> tokens;

        size_t index;
        Token current_token;
};

#endif