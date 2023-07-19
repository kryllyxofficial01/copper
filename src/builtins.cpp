#include "include/builtins.hpp"

void println(std::vector<ast_t> args) {
    for (ast_t arg: args) {
        switch (arg.node_type) {
            case STRING_NODE:
                printf(
                    "%s\n",
                    arg.string_value.c_str()
                );
                break;
        }
    }
}