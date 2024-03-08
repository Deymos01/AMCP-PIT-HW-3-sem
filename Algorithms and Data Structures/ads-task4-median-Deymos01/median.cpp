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
    sort(v.begin(), v.end(), [](std::pair<int, double> a, std::pair<int, double> b) { return a.second < b.second; });
    std::cout << v[0].first + 1 << " " << v[n / 2].first + 1 << " " << v[n - 1].first + 1 << "\n";
    return 0;
}