#ifndef MST_EDGE_H
#define MST_EDGE_H

#include <iostream>

struct Edge {
    int w;
    int v1;
    int v2;
};

std::ostream &operator<<(std::ostream &out, const Edge &edge) {
    out << "[" << edge.v1 << ", " << edge.v2 << "], weight: " << edge.w;
    return out;
}

#endif //MST_EDGE_H
