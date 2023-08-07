#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <string.h>

#define WHITESPACE " \n\t"

#define __IS_ALNUM(c) isalnum(c) || c == '_'
#define __IS_WHITESPACE(c) strchr(WHITESPACE, c)

#endif