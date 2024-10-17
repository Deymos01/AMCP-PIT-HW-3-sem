#include <fstream>
#include <iostream>
#include <cstring>

#include "algorithm.h"

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

    size_t n, m, k;
    inFile >> n >> m >> k;
    char **table = new char *[n];

    for (size_t i = 0; i < n; ++i) {
        table[i] = new char[m + 1];
        memset(table[i], '\0', sizeof(char) * (m + 1));
    }
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            inFile >> table[j][i];
        }
    }

    radixSortString(table, n, m, k);

    for (int i = 0; i < n; ++i) {
        outFile << table[i][0];
    }

    for (size_t i = 0; i < n; ++i) {
        delete[] table[i];
    }
    delete[] table;
    inFile.close();
    outFile.close();
    return 0;
}