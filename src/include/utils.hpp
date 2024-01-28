#ifndef __UTILS_HPP
#define __UTILS_HPP

#include <string>

#define __WHITESPACE__ " \n\t\r\v\f"

std::string trim(std::string string, std::string whitespace = __WHITESPACE__);

#endif