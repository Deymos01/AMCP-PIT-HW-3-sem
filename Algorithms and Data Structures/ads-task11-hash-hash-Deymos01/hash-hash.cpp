#include <fstream>
#include <iostream>

#include "hash_table.h"

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

    int n;
    inFile >> n;

    hash_table<long long> hashTable;
    while (n-- > 0) {
        char command;
        int number;
        inFile >> command >> number;
        switch (command) {
            case '+':
                hashTable.add(number);
                break;
            case '-':
                hashTable.erase(number);
                break;
            case '?':
                outFile << (hashTable.find(number) ? "true" : "false") << '\n';
                break;
            default:
                std::cerr << "Undefined command: '" << command << "'\n";
        }
    }

    inFile.close();
    outFile.close();
    return 0;
}