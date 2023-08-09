#include <iostream>
#include <fstream>
#include <vector>

#include "include/lexer.hpp"
#include "include/parser.hpp"
#include "include/token.hpp"
#include "include/ast.hpp"

using namespace std;

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("Syntax: ./build/main <filepath>\n");
        exit(1);
    }

    string filepath = argv[1];

    ifstream reader(filepath);

    string contents;
    string line;
    while (getline(reader, line)) {
        contents += line;
    }

    Lexer lexer(contents);
    vector<token_t> tokens = lexer.lex();

    Parser parser(tokens);
    ast_t AST = parser.parse();

    for (ast_t node: AST.nodes) {
        printf("%i\n", node.type);
    }
}