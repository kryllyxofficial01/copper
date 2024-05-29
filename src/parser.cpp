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

        if (this->peek(-1).type != TT_RIGHT_BRACE) this->eat(TT_SEMICOLON);
    }

    return master_node;
}

NODE Parser::parse_next_token() {
    if (this->current_token.type == TT_ID) {
        return this->parse_id();
    }
    else if (this->current_token.type == TT_DOLLAR_SIGN) {
        return this->parse_variable_usage();
    }
}

NODE Parser::parse_id() {
    if (this->current_token.value == "var") {
        return this->parse_variable_definition();
    }
    else if (this->current_token.value == "if") {
        return this->parse_if_statement();
    }
    else if (this->current_token.value == "for") {
        return this->parse_for_loop();
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

        this->eat(TT_SEMICOLON);
    }

    this->eat(TT_RIGHT_BRACE);

    return statements;
}

GenericNode Parser::parse_expression(enum TokenTypes termination_token) {
    GenericNode node;

    RPN_BUFFER buffer;
    while (this->current_token.type != termination_token) {
        buffer.push_back(this->get_next_node());

        this->next_token();
    }

    node.expression = this->to_rpn(buffer);

    return node;
}

GenericNode Parser::parse_expression(std::vector<enum TokenTypes> termination_tokens) {
    GenericNode node;

    RPN_BUFFER buffer;
    while (!__is_in_vector(this->current_token.type, termination_tokens)) {
        buffer.push_back(this->get_next_node());

        this->next_token();
    }

    node.expression = this->to_rpn(buffer);

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

    variable_definition_node.value = this->parse_expression(TT_SEMICOLON);

    return __make_node(
        VARIABLE_DEFINITION_NODE,
        VariableDefinitionNode,
        variable_definition_node
    );
}

NODE Parser::parse_variable_usage() {
    this->eat(TT_DOLLAR_SIGN);

    std::string variable_name = this->current_token.value;
    this->eat(TT_ID); // variable name

    if (this->current_token.type == TT_EQUALS_SIGN) {
        VariableRedefinitionNode variable_redefinition_node;

        variable_redefinition_node.name = variable_name;

        this->eat(TT_EQUALS_SIGN);

        variable_redefinition_node.value = this->parse_expression(TT_SEMICOLON);

        return __make_node(
            VARIABLE_REDEFINITION_NODE,
            VariableRedefinitionNode,
            variable_redefinition_node
        );
    }

    VariableCallNode variable_call_node;

    variable_call_node.name = variable_name;

    return __make_node(
        VARIABLE_CALL_NODE,
        VariableCallNode,
        variable_call_node
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

        return __make_node(
            IF_ELSE_STATEMENT_NODE,
            IfElseStatementNode,
            if_else_statement_node
        );
    }

    return __make_node(
        IF_STATEMENT_NODE,
        IfStatementNode,
        if_statement_node
    );
}

NODE Parser::parse_for_loop() {
    ForLoopNode for_loop_node;

    this->eat(TT_ID); // for

    this->eat(TT_LEFT_PAREN);

    for_loop_node.iteration_variable = std::any_cast<VariableDefinitionNode>(
        this->parse_variable_definition().second
    );

    this->eat(TT_SEMICOLON);

    for_loop_node.limit= this->parse_expression(TT_SEMICOLON);

    this->eat(TT_SEMICOLON);

    for_loop_node.iteration = this->parse_expression(TT_RIGHT_PAREN);

    this->eat(TT_RIGHT_PAREN);

    for_loop_node.body = this->parse_block();

    return __make_node(
        FOR_LOOP_NODE,
        ForLoopNode,
        for_loop_node
    );
}

NODE Parser::parse_function_call() {
    FunctionCallNode function_call_node;

    function_call_node.name = this->current_token.value;
    this->eat(TT_ID); // function name

    this->eat(TT_LEFT_PAREN);

    while (this->current_token.type != TT_RIGHT_PAREN) {
        GenericNode argument = parse_expression(
            std::vector<enum TokenTypes>{TT_COMMA, TT_RIGHT_PAREN}
        );

        function_call_node.arguments.push_back(argument);

        if (this->current_token.type == TT_COMMA) this->eat(TT_COMMA);
    }

    this->eat(TT_RIGHT_PAREN);

    return __make_node(
        FUNCTION_CALL_NODE,
        FunctionCallNode,
        function_call_node
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

        this->eat(TT_SEMICOLON);
    }

    this->eat(TT_RIGHT_BRACE);

    return __make_node(
        FUNCTION_DEFINITION_NODE,
        FunctionDefinitionNode,
        function_definition_node
    );
}

// credit: https://gist.github.com/t-mat/b9f681b7591cdae712f6
RPN_BUFFER Parser::to_rpn(RPN_BUFFER buffer) {
    RPN_BUFFER queue;
    std::vector<Token> stack;

    for (auto item: buffer) {
        if (item.first) {
            queue.push_back(item);
        }
        else {
            Token token = std::any_cast<Token>(item.second);

            switch (token.type) {
                case TokenTypes::TT_LEFT_PAREN:
                    stack.push_back(token);
                    break;

                case TokenTypes::TT_RIGHT_PAREN: {
                    bool match = RPN_TOKEN;

                    while (!stack.empty() && stack.back().type != TokenTypes::TT_LEFT_PAREN) {
                        queue.push_back(
                            std::make_pair(RPN_TOKEN, std::make_any<Token>(stack.back()))
                        );
                        stack.pop_back();

                        match = true;
                    }

                    if (!match && stack.empty()) {
                        printf("Parser: Error: Mismatched parentheses\n");
                        exit(EXIT_FAILURE);
                    }

                    stack.pop_back();

                    break;
                }

                default: {
                    Token operator1 = token;
                    bool operator1_associativity = get_operator_right_associativity(operator1.type);
                    int operator1_precedence = get_operator_precedence(operator1.type);

                    while (!stack.empty()) {
                        Token operator2 = stack.back();
                        int operator2_precedence = get_operator_precedence(operator2.type);

                        if (
                            (!operator1_associativity && operator1_precedence <= operator2_precedence) ||
                            (operator1_associativity && operator1_precedence < operator2_precedence)
                        ) {
                            queue.push_back(
                                std::make_pair(RPN_TOKEN, std::make_any<Token>(operator2))
                            );
                            stack.pop_back();

                            continue;
                        }

                        break;
                    }

                    stack.push_back(operator1);

                    break;
                }
            }
        }
    }

    while (!stack.empty()) {
        if (stack.back().type == TokenTypes::TT_LEFT_PAREN) {
            printf("Parser: Error: Mismatched parentheses\n");
            exit(EXIT_FAILURE);
        }

        queue.push_back(std::move(
            std::make_pair(RPN_TOKEN, std::make_any<Token>(stack.back()))
        ));
        stack.pop_back();
    }

    return queue;
}

std::pair<bool, std::any> Parser::get_next_node() {
    switch (this->current_token.type) {
        case TokenTypes::TT_ID: {
            if (this->peek(1).type == TT_LEFT_PAREN) {
                return this->update_index_with(std::make_pair(
                    RPN_NODE,
                    std::make_any<NODE>(this->parse_function_call())
                ));
            }

            break;
        }

        case TokenTypes::TT_INTEGER: {
            IntegerNode integer_node(atoi(this->current_token.value.c_str()));

            NODE node = __make_node(INTEGER_NODE, IntegerNode, integer_node);

            return std::make_pair(RPN_NODE, std::make_any<NODE>(node));
        }

        case TokenTypes::TT_FLOAT: {
            FloatNode float_node(atof(this->current_token.value.c_str()));

            NODE node = __make_node(FLOAT_NODE, FloatNode, float_node);

            return std::make_pair(RPN_NODE, std::make_any<NODE>(node));
        }

        case TokenTypes::TT_STRING: {
            StringNode string_node(this->current_token.value);

            NODE node = __make_node(STRING_NODE, StringNode, string_node);

            return std::make_pair(RPN_NODE, std::make_any<NODE>(node));
        }

        case TokenTypes::TT_DOLLAR_SIGN: {
            return this->update_index_with(std::make_pair(
                RPN_NODE,
                std::make_any<NODE>(this->parse_variable_usage())
            ));
        }

        default: return std::make_pair(RPN_TOKEN, std::make_any<Token>(this->current_token));
    }
}

void Parser::eat(enum TokenTypes expected_type) {
    if (this->current_token.type != expected_type) {
        printf(
            "Parser: Error: Unexpected token: '%s'\n",
            this->current_token.value.c_str()
        );

        exit(EXIT_FAILURE);
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

std::pair<bool, std::any> Parser::update_index_with(std::pair<bool, std::any> item) {
    this->index--;

    return item;
}