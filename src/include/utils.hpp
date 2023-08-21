#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <set>
#include <string>
#include <string.h>

#define __WHITESPACE__ " \n\t"
const inline std::set<std::string> __BINARY_OPERATORS__{
    "+", "-", "*", "/"
};

#define __IS_ALNUM(c) isalnum(c) || c == '_'
#define __IS_DIGIT(c) isdigit(c) || c == '.'
#define __IS_WHITESPACE(c) strchr(__WHITESPACE__, c)
#define __IS_BINARY_OPERATOR(x) __BINARY_OPERATORS__.find(x) != __BINARY_OPERATORS__.end()

#endif