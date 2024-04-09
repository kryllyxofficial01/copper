#include "include/utils.hpp"

std::string trim(std::string string, std::string whitespace) {
    string.erase(0, string.find_first_not_of(whitespace));
    string.erase(string.find_last_not_of(whitespace) + 1);

    return string;
}

Token make_token(enum TokenTypes type, std::string value) {
    return (Token) {
        .type = type,
        .value = value
    };
}