#include <iostream>
#include <fstream>
#include <vector>

#include "include/lexer.hpp"
#include "include/token.hpp"
#include "include/utils.hpp"

using namespace std;

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        cout << "Syntax: " + string(argv[0]) + " <name of file>" << endl;
        exit(EXIT_FAILURE);
    }

    string filepath = argv[1];

    ifstream file(filepath);

    string line;
    vector<string> lines;
    while (getline(file, line)) {
        line = trim(line);

        if (line != "") {
            lines.push_back(line);
        }
    }

    for (string line: lines) {
        Lexer lexer(line);
        vector<token_t> tokens = lexer.lex();
    }

    return 0;
}
