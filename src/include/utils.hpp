#ifndef __UTILS_HPP
#define __UTILS_HPP

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>
#include <any>
#include <tuple>
#include <math.h>

#include "token.hpp"
#include "nodes/node.hpp"

#define RPN_BUFFER std::deque<std::pair<bool, std::any>>

#define RPN_BUFFER_TOKEN false
#define RPN_BUFFER_NODE true

#define __WHITESPACE__ " \n\t\r\v\f"

#define make_token(t, v) (Token) { \
        .type = t, \
        .value = v \
    }
#define make_node(nt, t, n) std::make_pair(nt, std::make_any<t>(n));
#define make_variable(n, t, v) std::make_tuple(n, t, v)

#define is_in_vector(e, v) (std::find(v.begin(), v.end(), e) != v.end())

std::string trim(std::string string, std::string whitespace);

int get_operator_precedence(enum TokenTypes _operator);
bool get_operator_right_associativity(enum TokenTypes _operator);

template<typename T> T perform_numeric_operation(T a, T b, enum TokenTypes _operator) {
    switch (_operator) {
        case TokenTypes::TT_PLUS_SIGN: return a + b;
        case TokenTypes::TT_HYPHEN: return a - b;
        case TokenTypes::TT_ASTERICK: return a * b;
        case TokenTypes::TT_FORWARD_SLASH: return a / b;
        case TokenTypes::TT_CARET: return pow(a, b);
    }
}

std::string perform_string_operation(std::string a, std::string b, enum TokenTypes _operator);

#endif