#include <fstream>
#include <iostream>

#include "edge.h"
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

    int v, e;
    inFile >> v >> e;

    Edge *edges = new Edge[e];
    for (int i = 0; i < e; ++i) {
        inFile >> edges[i].v1 >> edges[i].v2 >> edges[i].w;
    }

    std::cout << kruskal(v, e, edges) << std::endl;

    inFile.close();
    delete[] edges;
    return 0;
}
