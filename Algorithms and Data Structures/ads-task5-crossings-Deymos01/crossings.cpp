#include <iostream>
#include <fstream>

#include "vector.h"
#include "algorithm.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Not acceptable number of arguments" << std::endl;
        return -1;
    }
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        std::cerr << "Unable to open file: \"" << argv[1] << "\"" << std::endl;
        return -2;
    }

    int n;
    inFile >> n;

    struct segment {
        int y0;
        int y1;
    };
    vector<segment> vec(n, {0, 0});
    for (int i = 0; i < n; ++i) {
        inFile >> vec[i].y0 >> vec[i].y1;
    }
    inFile.close();

    uint64_t inversionCount = 0;

    MergeSort(vec.begin(), vec.end(), inversionCount, [](const segment &a, const segment &b) {
        return a.y0 <= b.y0;
    });

    inversionCount = 0;
    MergeSort(vec.begin(), vec.end(), inversionCount, [](const segment &a, const segment &b) {
        return a.y1 <= b.y1;
    });

    inversionCount += countSegmentsInSamePoint(vec.begin(), vec.end(), [](const segment &a, const segment &b) {
        return a.y0 == b.y0;
    });
    inversionCount += countSegmentsInSamePoint(vec.begin(), vec.end(), [](const segment &a, const segment &b) {
        return a.y1 == b.y1;
    });

    std::cout << inversionCount << '\n';
    return 0;
}