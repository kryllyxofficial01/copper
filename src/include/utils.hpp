#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <string>
#include <algorithm>
#include <functional>
#include <tuple>
#include <any>

#define VARS_TYPE std::map<std::string, std::pair<std::string, std::any>>
#define FUNCS_TYPE std::map<std::string, std::tuple<std::string, std::vector<ast_t>, ast_t>>
#define BUILTIN_FUNC_TYPE std::function<void(std::vector<ast_t>, VARS_TYPE variables)>

#define __VECTOR_FIND(v, x) std::find(v.begin(), v.end(), x)
#define __GET_VAR(v, x) std::any_cast<ast_t>(v.find(x)->second.second)

#endif