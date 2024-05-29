#include <iostream>
#include <fstream>
#include <vector>

#include "include/lexer.hpp"
#include "include/parser.hpp"
#include "include/interpreter.hpp"

#include "include/token.hpp"
#include "include/utils.hpp"

#include "include/nodes/master_node.hpp"
#include "include/nodes/node.hpp"

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cout << "Syntax: " + std::string(argv[0]) + " <name of file>" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string filepath = argv[1];

    std::ifstream file(filepath);

    std::string line;
    std::string lines;
    while (getline(file, line)) {
        line = trim(line, __WHITESPACE__);

        if (line != "" && line.substr(0, 2) != "//") {
            lines += line;
        }
    }

    Lexer lexer(lines);
    std::vector<Token> tokens = lexer.lex();

    Parser parser(tokens);
    MasterNode ast = parser.parse();

    Interpreter interpreter(ast);
    interpreter.interpret();

    return 0;
}
