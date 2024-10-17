#include <fstream>
#include <iostream>
#include <cstring>
#include <ctime>

#include "algorithm.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Not acceptable number of arguments" << std::endl;
        return -1;
    }
    std::ifstream inFile(argv[2]);
    if (!inFile) {
        std::cerr << "Unable to open file: \"" << argv[1] << "\"" << std::endl;
        return -2;
    }

    char *pattern = argv[1];
    size_t patternLength = std::strlen(pattern);
    int *suffix = new int[patternLength];

//    clock_t start = clock();

    fillSuffix(pattern, suffix, patternLength);

    char line[1028];
    std::memset(line, '\0', sizeof(line));
    size_t counter = 0;
    while (inFile.getline(line, sizeof(line), '\n')) {
        counter += countOccurrenceKMP(line, pattern, suffix, patternLength);
        std::memset(line, '\0', sizeof(line));
    }
//    clock_t end = clock();
    std::cout << counter << '\n';
//    std::cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << '\n';

    inFile.close();
    delete[] suffix;
    return 0;
}
