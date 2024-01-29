#ifndef __NODE_HPP
#define __NODE_HPP

#include <string>
#include <vector>

enum NodeTypes {
    NT_FUNC_CALL,
    NT_VAR_DEF
};

struct Node {
    enum NodeTypes type;

    std::string func_call_name;
    std::vector<std::string> func_call_params;

    std::string var_def_name;
    std::string var_def_type;
    std::string var_def_value;
};

#endif