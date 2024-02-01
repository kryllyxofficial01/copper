#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <vector>
#include <string>

#include "token.hpp"

class Parser {
    public:
        Parser(std::vector<Token> tokens);

        void parse();

    private:
        void next_token();

        std::vector<Token> tokens;

        size_t index;
        Token current_token;
};

#endif