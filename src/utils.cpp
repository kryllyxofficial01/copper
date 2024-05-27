#include "include/utils.hpp"

std::string trim(std::string string, std::string whitespace) {
    string.erase(0, string.find_first_not_of(whitespace));
    string.erase(string.find_last_not_of(whitespace) + 1);

    return string;
}

int get_operator_precedence(enum TokenTypes _operator) {
    if (_operator == TokenTypes::TT_PLUS_SIGN || _operator == TokenTypes::TT_HYPHEN) return 1;
    if (_operator == TokenTypes::TT_ASTERICK || _operator == TokenTypes::TT_FORWARD_SLASH) return 2;

    return 0;
}

bool get_operator_right_associativity(enum TokenTypes _operator) {
    return _operator == TokenTypes::TT_CARET;
}