#include "include/scope.hpp"

std::pair<VARIABLE, int> get_variable_by_name(std::string name, scope_t* scope) {
    for (int i = 0; i < scope->variables.size(); i++) {
        VARIABLE variable = scope->variables.at(i);

        if (std::get<VARIABLE_NAME>(variable) == name) {
            return std::make_pair(variable, i);
        }
    }

    return std::make_pair(VARIABLE(), -1); // i hate this
}