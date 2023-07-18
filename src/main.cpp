#include <iostream>
#include <fstream>

#include "include/lexer.hpp"
#include "include/token.hpp"

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

    token_t token;
    while ((token = lexer.get_next_token()).type != TOKEN_EOF) {
        printf("TOKEN(%d, '%s')\n", token.type, token.value.c_str());
    }

    return 0;
}
