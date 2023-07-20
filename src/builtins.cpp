#include "include/builtins.hpp"

void println(std::vector<ast_t> args, VARS_TYPE variables) {
    for (ast_t arg: args) {
        switch (arg.node_type) {
            case STRING_NODE:
                printf(
                    "%s\n",
                    arg.string_value.c_str()
                );
                break;

            case VARIABLE_USAGE_NODE:
                ast_t var = __GET_VAR(
                    variables,
                    arg.var_use_name
                );

                if (variables.find(
                    arg.var_use_name
                )->second.first == "string"
                ) {
                    printf(
                        "%s\n",
                        var.string_value.c_str()
                    );
                }

                break;
        }
    }
}