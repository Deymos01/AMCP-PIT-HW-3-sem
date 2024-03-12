#include <fstream>
#include <iostream>

#include "monotonic_queue.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Not enough arguments" << std::endl;
        return -1;
    }
    std::ifstream inFile(argv[1]);
    std::ofstream outFile(argv[2]);
    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "An error occurred when attempting to open the files." << std::endl;
        inFile.close();
        outFile.close();
        return -2;
    }

    int n;
    inFile >> n;
    monotonic_queue<int> q;
    for (int i = 0; i < n; ++i) {
        char command;
        inFile >> command;
        switch (command) {
            case '+':
                int number;
                inFile >> number;
                q.push(number);
                break;
            case '?':
                outFile << q.getMax() - q.getMin() << '\n';
                break;
            case '-':
                q.pop();
                break;
            default:
                continue;
        }
    }

    inFile.close();
    outFile.close();
    return 0;
}