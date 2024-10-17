#include <iostream>
#include <fstream>

#include "maxHeap.h"
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
    int x1, x2;
    inFile >> x1 >> x2;
    inFile.close();

    maxHeap<int> heap(right);
    heap.push(x1);
    if (right > 1) {
        heap.push(x2);
    } else if (x1 > x2) {
        heap.pop();
        heap.push(x1);
    }

    for (int i = 2; i < n; ++i) {
        int tmp = A * x1 + B * x2 + C;

        if (i < right) {
            heap.push(tmp);
        } else if (tmp < heap.top()) {
            heap.pop();
            heap.push(tmp);
        }
        x1 = x2;
        x2 = tmp;
    }

    vector<int> firstK2 = static_cast<vector<int>>(heap);
    sort(firstK2.begin(), firstK2.end(), [](const int &a, const int &b) -> bool { return a > b; });

    for (int i = right - left; i > 0; --i) {
        int tmp = firstK2[i];
        outFile << tmp << " ";
    }
    outFile << firstK2[0];
    outFile.close();
    return 0;
}