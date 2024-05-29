#include "include/interpreter.hpp"

Interpreter::Interpreter(MasterNode ast) {
    this->ast = ast;

    this->index = -1;
    this->next_node();

    this->global_scope.variables.clear();
}

void Interpreter::interpret() {
    while (this->index < this->ast.nodes.size()) {
        this->interpret_next_node();

        this->next_node();
    }
}

void Interpreter::interpret_next_node() {
    switch (this->current_node.first) {
        case NodeTypes::VARIABLE_DEFINITION_NODE:
            this->interpret_variable_definition(&this->global_scope);
            break;
    }
}

void Interpreter::interpret_variable_definition(scope_t* scope) {
    VariableDefinitionNode variable_node = std::any_cast<VariableDefinitionNode>(
        this->current_node.second
    );

    if (variable_node.value_type == "int") {
        scope->variables.push_back(
            __make_variable(
                variable_node.name,
                Types::INTEGER,
                this->evaluate_expression(variable_node.value, Types::INTEGER)
            )
        );
    }
    else if (variable_node.value_type == "float") {
        scope->variables.push_back(
            __make_variable(
                variable_node.name,
                Types::FLOAT,
                this->evaluate_expression(variable_node.value, Types::FLOAT)
            )
        );
    }
    else if (variable_node.value_type == "string") {
        scope->variables.push_back(
            __make_variable(
                variable_node.name,
                Types::STRING,
                this->evaluate_expression(variable_node.value, Types::STRING)
            )
        );
    }
}

std::any Interpreter::evaluate_expression(GenericNode node, enum Types value_type) {
    switch (value_type) {
        case Types::INTEGER:
        case Types::FLOAT: {
            std::stack<double> stack;

            for (auto token: node.expression) {
                if (token.first == RPN_NODE) {
                    NODE _node = std::any_cast<NODE>(token.second);

                    switch (_node.first) {
                        case NodeTypes::INTEGER_NODE: {
                            stack.push(
                                std::any_cast<IntegerNode>(_node.second).value
                            );

                            break;
                        }

                        case NodeTypes::FLOAT_NODE: {
                            stack.push(
                                std::any_cast<FloatNode>(_node.second).value
                            );

                            break;
                        }

                        case NodeTypes::STRING_NODE: {
                            printf(
                                "Interpreter: Error: Cannot evaluate string ('%s') to integer type\n",
                                std::any_cast<StringNode>(_node.second).value.c_str()
                            );

                            exit(EXIT_FAILURE);
                        }
                    }
                }
                else if (token.first == RPN_TOKEN) {
                    double b = stack.top();
                    stack.pop();

                    double a = stack.top();
                    stack.pop();

                    stack.push(perform_operation(a, b, std::any_cast<Token>(token.second).type));
                }
            }

            if (value_type == Types::INTEGER) {
                return std::make_any<int>(trunc(stack.top()));
            }
            else if (value_type == Types::FLOAT) {
                return std::make_any<double>(stack.top());
            }
        }

        case Types::STRING: {
            std::stack<std::string> stack;

            for (auto token: node.expression) {
                if (token.first == RPN_NODE) {
                    NODE _node = std::any_cast<NODE>(token.second);

                    switch (_node.first) {
                        case NodeTypes::INTEGER_NODE: {
                            stack.push(
                                std::to_string(std::any_cast<IntegerNode>(_node.second).value)
                            );

                            break;
                        }

                        case NodeTypes::FLOAT_NODE: {
                            stack.push(
                                std::to_string(std::any_cast<FloatNode>(_node.second).value)
                            );

                            break;
                        }

                        case NodeTypes::STRING_NODE: {
                            stack.push(
                                std::any_cast<StringNode>(_node.second).value
                            );

                            break;
                        }
                    }
                }
                else if (token.first == RPN_TOKEN) {
                    std::string b = stack.top();
                    stack.pop();

                    std::string a = stack.top();
                    stack.pop();

                    stack.push(perform_string_operation(a, b, std::any_cast<Token>(token.second).type));
                }
            }

            return std::make_any<std::string>(stack.top());
        }
    }
}

void Interpreter::next_node() {
    if (++index < this->ast.nodes.size()) {
        this->current_node = this->ast.nodes.at(this->index);
    }
}