#include <fstream>
#include <iostream>
#include <cstring>

#include "priority_queue.h"

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

    priority_queue pq;
    char command[16];
    int commandNumber = 1;
    int val;
    while (inFile >> command) {
        if (strcmp(command, "push") == 0) {
            inFile >> val;
            pq.push(val, commandNumber);
        } else if (strcmp(command, "extract-min") == 0) {
            pq.extract_min(outFile);
        } else if (strcmp(command, "decrease-key") == 0) {
            int x;
            int y;
            inFile >> x >> y;
            pq.decrease_key(x, y);
        }
        ++commandNumber;
    }

    inFile.close();
    outFile.close();
    return 0;
}