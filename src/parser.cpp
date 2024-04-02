#include "include/parser.hpp"

Parser::Parser(std::vector<Token> tokens) {
    this->tokens = tokens;

    this->index = 0;

    this->next_token();
}

MasterNode Parser::parse() {
    MasterNode master_node;

    while (this->current_token.type != TT_EOF) {
        master_node.nodes.push_back(
            this->parse_next_token()
        );

        this->eat(TT_EOL);
    }

    return master_node;
}

Node Parser::parse_next_token() {
    if (this->current_token.type == TT_ID) {
        return this->parse_id();
    }
}

Node Parser::parse_id() {
    if (this->current_token.value == "var") {
        return this->parse_variable_definition();
    }
    else if (this->current_token.value == "func") {
        return this->parse_function_definition();
    }
    else if (this->peek(1).type == TT_LEFT_PAREN) {
        return this->parse_function_call();
    }
}

VariableDefinitionNode Parser::parse_variable_definition() {
    VariableDefinitionNode variable_node;

    this->eat(TT_ID); // var

    variable_node.name = this->current_token.value;
    this->eat(TT_ID); // variable name

    this->eat(TT_COLON);

    variable_node.value_type = this->current_token.value;
    this->eat(TT_ID); // variable type

    this->eat(TT_EQUALS_SIGN);

    std::vector<Token> value_tokens;
    while (this->current_token.type != TT_EOL) {
        value_tokens.push_back(this->current_token);
        this->next_token();
    }

    for (Token token: value_tokens) {
        variable_node.value.value.push_back(token);
    }

    return variable_node;
}

FunctionCallNode Parser::parse_function_call() {
    FunctionCallNode function_call_node;

    function_call_node.name = this->current_token.value;
    this->eat(TT_ID); // function name

    this->eat(TT_LEFT_PAREN);

    GenericNode argument;
    while (this->current_token.type != TT_RIGHT_PAREN) {
        argument.value.clear();

        while (this->current_token.type != TT_COMMA && this->current_token.type != TT_RIGHT_PAREN) {
            argument.value.push_back(this->current_token);
            this->next_token();
        }

        function_call_node.arguments.push_back(argument);

        if (this->current_token.type == TT_COMMA) this->eat(TT_COMMA);
    }

    this->eat(TT_RIGHT_PAREN);

    return function_call_node;
}

FunctionDefinitionNode Parser::parse_function_definition() {
    FunctionDefinitionNode function_definition_node;

    this->eat(TT_ID); // func

    function_definition_node.name = this->current_token.value;
    this->eat(TT_ID); // function name

    this->eat(TT_LEFT_PAREN);

    ArgumentNode argument;
    while (this->current_token.type != TT_RIGHT_PAREN) {
        argument.name = argument.value_type = "";

        while (this->current_token.type != TT_COMMA && this->current_token.type != TT_RIGHT_PAREN) {
            argument.name = this->current_token.value;
            this->eat(TT_ID); // argument name

            this->eat(TT_COLON);

            argument.value_type = this->current_token.value;
            this->eat(TT_ID); // argument type
        }

        function_definition_node.arguments.push_back(argument);

        if (this->current_token.type == TT_COMMA) this->eat(TT_COMMA);
    }

    this->eat(TT_RIGHT_PAREN);

    this->eat(TT_RIGHT_ARROW);

    function_definition_node.return_type = this->current_token.value;
    this->eat(TT_ID); // return type

    this->eat(TT_LEFT_BRACE);

    std::vector<Token> current_line_tokens;
    while (this->current_token.type != TT_RIGHT_BRACE) {
        current_line_tokens.clear();

        while (this->current_token.type != TT_EOL) {
            current_line_tokens.push_back(this->current_token);
            this->next_token();
        }
        current_line_tokens.push_back(this->current_token);

        // somehow parse each line
    }

    this->eat(TT_RIGHT_BRACE);
}

void Parser::eat(enum TokenTypes expected_type) {
    if (this->current_token.type != expected_type) {
        printf(
            "Unexpected token: '%s'\n", // verbose error reports? nahhhhh
            this->current_token.value.c_str()
        );

        exit(1);
    }

    this->next_token();
}

void Parser::next_token() {
    this->current_token = this->tokens.at(this->index++);
}

Token Parser::peek(int offset) {
    return this->tokens.at(
        (this->index + offset) - 1
    );
}