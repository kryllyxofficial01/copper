#include <iostream>
#include <fstream>
#include <vector>

#include "include/lexer.hpp"
#include "include/parser.hpp"
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

        if (line != "" && line.substr(0, 2) != "//") {
            lines.push_back(line);
        }
    }

    vector<Token> all_tokens;

    for (string line: lines) {
        Lexer lexer(line);
        vector<Token> tokens = lexer.lex();

        all_tokens.insert(all_tokens.end(), tokens.begin(), tokens.end());
    }

    Parser parser(all_tokens);

    return 0;
}
