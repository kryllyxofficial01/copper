#ifndef __SCOPE_HPP
#define __SCOPE_HPP

#include <vector>
#include <tuple>
#include <string>
#include <any>

#define VARIABLE std::tuple<std::string, enum BuiltinTypes, std::any>

#define VARIABLE_NAME 0
#define VARIABLE_TYPE 1
#define VARIABLE_VALUE 2

enum BuiltinTypes {
    INTEGER,
    FLOAT,
    STRING
};

typedef struct SCOPE {
    std::vector<VARIABLE> variables;
} scope_t;

std::pair<VARIABLE, int> get_variable_by_name(std::string name, scope_t* scope);

#endif