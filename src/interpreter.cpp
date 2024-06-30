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

        case NodeTypes::VARIABLE_REDEFINITION_NODE:
            this->interpret_variable_redefinition(&this->global_scope);
            break;
    }
}

void Interpreter::interpret_variable_definition(scope_t* scope) {
    VariableDefinitionNode variable_node = std::any_cast<VariableDefinitionNode>(
        this->current_node.second
    );

    if (variable_node.value_type == "int") {
        scope->variables.push_back(
            make_variable(
                variable_node.name,
                BuiltinTypes::INTEGER,
                this->evaluate_expression(variable_node.value, BuiltinTypes::INTEGER, scope)
            )
        );
    }
    else if (variable_node.value_type == "float") {
        scope->variables.push_back(
            make_variable(
                variable_node.name,
                BuiltinTypes::FLOAT,
                this->evaluate_expression(variable_node.value, BuiltinTypes::FLOAT, scope)
            )
        );
    }
    else if (variable_node.value_type == "string") {
        scope->variables.push_back(
            make_variable(
                variable_node.name,
                BuiltinTypes::STRING,
                this->evaluate_expression(variable_node.value, BuiltinTypes::STRING, scope)
            )
        );
    }
}

void Interpreter::interpret_variable_redefinition(scope_t* scope) {
    VariableRedefinitionNode variable_node = std::any_cast<VariableRedefinitionNode>(
        this->current_node.second
    );

    for (int i = 0; i < scope->variables.size(); i++) {
        VARIABLE variable = scope->variables.at(i);

        if (std::get<VARIABLE_NAME>(variable) == variable_node.name) {
            std::get<VARIABLE_VALUE>(variable) = this->evaluate_expression(
                variable_node.value,
                std::get<VARIABLE_TYPE>(variable),
                scope
            );
        }
    }
}

std::any Interpreter::evaluate_expression(GenericNode node, enum BuiltinTypes value_type, scope_t* scope) {
    if (value_type == BuiltinTypes::INTEGER || value_type == BuiltinTypes::FLOAT) {
        std::stack<double> stack;

        for (auto item: node.expression) {
            if (item.first == RPN_BUFFER_NODE) {
                NODE item_node = std::any_cast<NODE>(item.second);

                if (item_node.first == NodeTypes::INTEGER_NODE) {
                    stack.push(
                        std::any_cast<IntegerNode>(item_node.second).value
                    );
                }
                else if (item_node.first == NodeTypes::FLOAT_NODE) {
                    stack.push(
                        std::any_cast<FloatNode>(item_node.second).value
                    );
                }
                else if (item_node.first == NodeTypes::STRING_NODE) {
                    printf(
                        "Interpreter: Error: Expected numeric value, got type string ('%s')\n",
                        std::any_cast<StringNode>(item_node.second).value.c_str()
                    );

                    exit(EXIT_FAILURE);
                }
                else if (item_node.first == NodeTypes::VARIABLE_CALL_NODE) {
                    VariableCallNode variable_node = std::any_cast<VariableCallNode>(item_node.second);

                    for (int i = 0; i < scope->variables.size(); i++) {
                        VARIABLE variable = scope->variables.at(i);

                        if (std::get<VARIABLE_NAME>(variable) == variable_node.name) {
                            if (std::get<VARIABLE_TYPE>(variable) == BuiltinTypes::INTEGER) {
                                stack.push(
                                    std::any_cast<int>(std::get<VARIABLE_VALUE>(variable))
                                );

                                break;
                            }
                            else if (std::get<VARIABLE_TYPE>(variable) == BuiltinTypes::FLOAT) {
                                stack.push(
                                    std::any_cast<double>(std::get<VARIABLE_VALUE>(variable))
                                );

                                break;
                            }
                            else if (std::get<VARIABLE_TYPE>(variable) == BuiltinTypes::STRING) {
                                printf(
                                    "Interpreter: Error: Expected numeric value, got type string ('%s')\n",
                                    std::any_cast<StringNode>(item_node.second).value.c_str()
                                );

                                exit(EXIT_FAILURE);
                            }
                        }
                    }
                }
            }
            else if (item.first == RPN_BUFFER_TOKEN) {
                double b = stack.top();
                stack.pop();

                double a = stack.top();
                stack.pop();

                stack.push(perform_numeric_operation(a, b, std::any_cast<Token>(item.second).type));
            }
        }

        if (value_type == BuiltinTypes::INTEGER) {
            return std::make_any<int>(trunc(stack.top()));
        }
        else if (value_type == BuiltinTypes::FLOAT) {
            return std::make_any<double>(stack.top());
        }
    }
    else if (value_type == BuiltinTypes::STRING) {
        std::stack<std::string> stack;

        for (auto item: node.expression) {
            if (item.first == RPN_BUFFER_NODE) {
                NODE item_node = std::any_cast<NODE>(item.second);

                if (item_node.first == NodeTypes::INTEGER_NODE) {
                    stack.push(
                        std::to_string(std::any_cast<IntegerNode>(item_node.second).value)
                    );
                }
                else if (item_node.first == NodeTypes::FLOAT_NODE) {
                    stack.push(
                        std::to_string(std::any_cast<FloatNode>(item_node.second).value)
                    );
                }
                else if (item_node.first == NodeTypes::STRING_NODE) {
                    stack.push(
                        std::any_cast<StringNode>(item_node.second).value
                    );
                }
                else if (item_node.first == NodeTypes::VARIABLE_CALL_NODE) {
                    VariableCallNode variable_node = std::any_cast<VariableCallNode>(item_node.second);

                    for (int i = 0; i < scope->variables.size(); i++) {
                        VARIABLE variable = scope->variables.at(i);

                        if (std::get<VARIABLE_NAME>(variable) == variable_node.name) {
                            if (std::get<VARIABLE_TYPE>(variable) == BuiltinTypes::INTEGER) {
                                stack.push(
                                    std::to_string(
                                        std::any_cast<int>(std::get<VARIABLE_VALUE>(variable))
                                    )
                                );

                                break;
                            }
                            else if (std::get<VARIABLE_TYPE>(variable) == BuiltinTypes::FLOAT) {
                                stack.push(
                                    std::to_string(
                                        std::any_cast<double>(std::get<VARIABLE_VALUE>(variable))
                                    )
                                );

                                break;
                            }
                            else if (std::get<VARIABLE_TYPE>(variable) == BuiltinTypes::STRING) {
                                stack.push(
                                    std::any_cast<std::string>(std::get<VARIABLE_VALUE>(variable))
                                );

                                break;
                            }
                        }
                    }
                }
            }
            else if (item.first == RPN_BUFFER_TOKEN) {
                std::string b = stack.top();
                stack.pop();

                std::string a = stack.top();
                stack.pop();

                stack.push(perform_string_operation(a, b, std::any_cast<Token>(item.second).type));
            }
        }

        return std::make_any<std::string>(stack.top());
    }
}

void Interpreter::next_node() {
    if (++index < this->ast.nodes.size()) {
        this->current_node = this->ast.nodes.at(this->index);
    }
}
