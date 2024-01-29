#include "include/parser.hpp"

Parser::Parser(std::vector<Token> tokens) {
    this->tokens = tokens;

    this->index = 0;

    this->next_token();
}

void Parser::next_token() {
    this->current_token = this->tokens.at(this->index++);
}