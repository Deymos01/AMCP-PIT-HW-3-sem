#include <fstream>
#include <iostream>

#include "BTreeNode.h"
#include "parser.h"
#include "algorithm.h"
#include "validator.h"

// TODO: Написать норм парсер

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

    uint32_t N;
    uint32_t t;
    uint32_t rootIndex;
    inFile >> N >> t >> rootIndex;
    auto **nodes = new BTreeNode *[N];
    for (int i = 0; i < N; ++i) {
        nodes[i] = parseNode(inFile);
        if (nodes[i] == nullptr) {
            std::cout << "no";
            inFile.close();
            for (int j = 0; j < i; ++j) {
                delete nodes[j];
            }
            delete[] nodes;
            return 0;
        }
    }

    sort(nodes, nodes + N, [](BTreeNode *a, BTreeNode *b) {
        return *a < *b;
    });

    BTreeValidator validator(nodes, N, t, rootIndex);

//    for (int i = 0; i < N; ++i) {
//        std::cout << *nodes[i] << "\n%%%%%%%%%%%%%%%%%%%%%%%%%\n";
//    }

    if (validator.isValidBTree()) {
        std::cout << "yes";
    } else {
        std::cout << "no";
    }

    inFile.close();
    for (int i = 0; i < N; ++i) {
        delete nodes[i];
    }
    delete[] nodes;
    return 0;
}