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
        cout << "Syntax: make file=<filepath>" << endl;
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

    return 0;
}
