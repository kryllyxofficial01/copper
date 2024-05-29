#ifndef __SCOPE_HPP
#define __SCOPE_HPP

#include <vector>
#include <tuple>
#include <string>
#include <any>

#define VARIABLE std::tuple<std::string, enum BuiltinTypes, std::any>

enum BuiltinTypes {
    INTEGER,
    FLOAT,
    STRING
};

typedef struct SCOPE {
    std::vector<VARIABLE> variables;
} scope_t;

#endif