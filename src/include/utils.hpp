#ifndef __UTILS_HPP
#define __UTILS_HPP

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "token.hpp"
#include "nodes/node.hpp"

#define __WHITESPACE__ " \n\t\r\v\f"

#define __make_token(t, v) (Token) { \
        .type = t, \
        .value = v \
    }
#define __make_node(nt, t, n) std::make_pair(nt, std::make_any<t>(n));

// #define __is_in_array(e, a) (std::find(std::begin(a), std::end(a), e) != std::end(a))

std::string trim(std::string string, std::string whitespace);

int get_operator_precedence(enum TokenTypes _operator);
bool get_operator_right_associativity(enum TokenTypes _operator);

#endif