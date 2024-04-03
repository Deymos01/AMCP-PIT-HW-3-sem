#include <iostream>
#include <fstream>

#include "vector.h"
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

    int n;
    int left;
    int right;
    int A;
    int B;
    int C;
    inFile >> n >> left >> right >> A >> B >> C;
    left -= 1;
    right -= 1;
    vector<int> vec(n);
    inFile >> vec[0] >> vec[1];
    inFile.close();
    for (int i = 2; i < n; ++i) {
        int tmp = A * vec[i - 2] + B * vec[i - 1] + C;
        vec[i] = tmp;
    }

    clock_t start = clock();
    quickSortRange(vec, vec.begin(), vec.end() - 1, left, right);
    std::cout << "Time: " << (double)(clock() - start) / CLOCKS_PER_SEC << " s." << std::endl;

    for (int i = left; i < right; ++i) {
        outFile << vec[i] << " ";
    }
    outFile << vec[right];

    outFile.close();
    return 0;
}