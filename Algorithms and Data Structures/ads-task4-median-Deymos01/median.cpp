#include <fstream>
#include <iostream>

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
    vector<std::pair<int /*index*/, double /*value*/>> v(n);
    for (int i = 0; i < n; ++i) {
        v[i].first = i;
        inFile >> v[i].second;
    }
    inFile.close();
    int medianIndex = n / 2;
    int median = find_kth_smallest(v.begin(), v.end(), medianIndex,
                                   [](const std::pair<int, double> &a, const std::pair<int, double> &b) -> bool {
                                       return a.second < b.second;
                                   })->first + 1;
    int min = find_min(v.begin(), v.end(),
                       [](const std::pair<int, double> &a, const std::pair<int, double> &b) -> bool {
                           return a.second < b.second;
                       })->first + 1;
    int max = find_max(v.begin(), v.end(),
                       [](const std::pair<int, double> &a, const std::pair<int, double> &b) -> bool {
                           return a.second < b.second;
                       })->first + 1;
    std::cout << min << ' ' << median << ' ' << max << '\n';
    return 0;
}