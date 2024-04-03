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

        if (this->peek(-1).type != TT_RIGHT_BRACE) this->eat(TT_EOL);
    }

    return master_node;
}

NODE Parser::parse_next_token() {
    if (this->current_token.type == TT_ID) {
        return this->parse_id();
    }
}

NODE Parser::parse_id() {
    if (this->current_token.value == "var") {
        return this->parse_variable_definition();
    }
    else if (this->current_token.value == "modify") { // not the greatest word choice, but idk
        return this->parse_variable_modification();
    }
    else if (this->current_token.value == "if") {
        return this->parse_if_statement();
    }
    else if (this->current_token.value == "func") {
        return this->parse_function_definition();
    }
    else if (this->peek(1).type == TT_LEFT_PAREN) {
        return this->parse_function_call();
    }
}

std::vector<NODE> Parser::parse_block() {
    std::vector<NODE> statements;

    this->eat(TT_LEFT_BRACE);

    while (this->current_token.type != TT_RIGHT_BRACE) {
        NODE statement = this->parse_next_token();

        statements.push_back(statement);

        this->eat(TT_EOL);
    }

    this->eat(TT_RIGHT_BRACE);

    return statements;
}

GenericNode Parser::parse_expression(enum TokenTypes termination_token) {
    GenericNode node;

    while (this->current_token.type != termination_token) {
        node.value.push_back(this->current_token);

        this->next_token();
    }

    return node;
}

NODE Parser::parse_variable_definition() {
    VariableDefinitionNode variable_definition_node;

    this->eat(TT_ID); // var

    variable_definition_node.name = this->current_token.value;
    this->eat(TT_ID); // variable name

    this->eat(TT_COLON);

    variable_definition_node.value_type = this->current_token.value;
    this->eat(TT_ID); // variable type

    this->eat(TT_EQUALS_SIGN);

    variable_definition_node.value = this->parse_expression(TT_EOL);

    return std::make_pair(
        VARIABLE_DEFINITION_NODE,
        std::make_any<VariableDefinitionNode>(variable_definition_node)
    );
}

NODE Parser::parse_variable_modification() {
    VariableModificationNode variable_modification_node;

    this->eat(TT_ID); // modify

    variable_modification_node.name = this->current_token.value;
    this->eat(TT_ID); // variable name

    this->eat(TT_EQUALS_SIGN);

    variable_modification_node.new_value = this->parse_expression(TT_EOL);

    return std::make_pair(
        VARIABLE_MODIFICATION_NODE,
        std::make_any<VariableModificationNode>(variable_modification_node)
    );
}

NODE Parser::parse_if_statement() {
    IfStatementNode if_statement_node;

    this->eat(TT_ID); // if

    this->eat(TT_LEFT_PAREN);

    if_statement_node.conditional = this->parse_expression(TT_RIGHT_PAREN);

    this->eat(TT_RIGHT_PAREN);

    if_statement_node.body = this->parse_block();

    if (this->current_token.value == "else") {
        IfElseStatementNode if_else_statement_node;

        if_else_statement_node.conditional = if_statement_node.conditional;
        if_else_statement_node.if_body = if_statement_node.body;

        this->eat(TT_ID); // else

        if_else_statement_node.else_body = this->parse_block();

        return std::make_pair(
            IF_ELSE_STATEMENT_NODE,
            std::make_any<IfElseStatementNode>(if_else_statement_node)
        );
    }

    return std::make_pair(
        IF_STATEMENT_NODE,
        std::make_any<IfStatementNode>(if_statement_node)
    );
}

NODE Parser::parse_function_call() {
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

    return std::make_pair(
        FUNCTION_CALL_NODE,
        std::make_any<FunctionCallNode>(function_call_node)
    );
}

NODE Parser::parse_function_definition() {
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

    while (this->current_token.type != TT_RIGHT_BRACE) {
        NODE statement = this->parse_next_token();

        function_definition_node.body.push_back(statement);

        this->eat(TT_EOL);
    }

    this->eat(TT_RIGHT_BRACE);

    return std::make_pair(
        FUNCTION_DEFINITION_NODE,
        std::make_any<FunctionDefinitionNode>(function_definition_node)
    );
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