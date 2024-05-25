#ifndef __UTILS_HPP
#define __UTILS_HPP

#include <string>
#include <vector>
#include <memory>

#include "token.hpp"
#include "nodes/node.hpp"

#define __WHITESPACE__ " \n\t\r\v\f"

#define __make_token(t, v) (Token) { \
        .type = t, \
        .value = v \
    }
#define __make_node(nt, t, n) std::make_pair(nt, std::make_any<t>(n));

std::string trim(std::string string, std::string whitespace);

#endif