#include <fstream>
#include <iostream>

#include "aatree.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Not acceptable number of arguments" << std::endl;
        return -1;
    }
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        std::cerr << "Unable to open file: \"" << argv[1] << "\"" << std::endl;
        return -2;
    }
    std::ofstream outFile(argv[2]);
    if (!outFile) {
        std::cerr << "Unable to open file: \"" << argv[2] << "\"" << std::endl;
        inFile.close();
        return -2;
    }

    AATree tree;
    int n;
    inFile >> n;
    for (int i = 0; i < n; ++i) {
        char command;
        int val;
        inFile >> command >> val;
        switch (command) {
            case '+':
                if (abs(val) > 10e9) { break; }
                tree.insert(val);
                outFile << tree.getRootLevel() << '\n';
                break;
            case '-':
                tree.erase(val);
                outFile << tree.getRootLevel() << '\n';
                break;
            case '?':
                outFile << (tree.find(val) ? "true" : "false") << '\n';
                break;
            default:
                std::cout << "Undefined command: \"" << command << "\"\n";
                break;
        }
    }

    inFile.close();
    outFile.close();
    return 0;
}