#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        cout << "Syntax: " + string(argv[0]) + " <name of file>" << endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
