#include <iostream>
#include <fstream>
#include <vector>

#include "include/lexer.hpp"
#include "include/parser.hpp"
#include "include/interpreter.hpp"
#include "include/token.hpp"
#include "include/ast.hpp"

using namespace std;

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("Syntax: make file=<filepath>\n");
        exit(1);
    }

    string filepath = argv[1];

    ifstream reader(filepath);

    if (reader.fail()) {
        printf("Unable to retrieve the file '%s'\n", filepath);
        exit(1);
    }

    string contents;
    string line;
    while (getline(reader, line)) {
        contents += line;
    }

    Lexer lexer(contents);
    vector<token_t> tokens = lexer.lex();

    Parser parser(tokens);
    ast_t ast = parser.parse();

    Interpreter interpreter(ast);
    interpreter.interpret();

    return 0;
}
