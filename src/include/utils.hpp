#ifndef __UTILS_HPP
#define __UTILS_HPP

#include <string>
#include <vector>
#include <memory>

#include "token.hpp"

#define __WHITESPACE__ " \n\t\r\v\f"

std::string trim(std::string string, std::string whitespace);

Token make_token(enum TokenTypes type, std::string value);

#endif