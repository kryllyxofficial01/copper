#include <iostream>
#include <fstream>

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
}