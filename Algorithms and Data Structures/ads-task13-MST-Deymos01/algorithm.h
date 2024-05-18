#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "mst.h"

template<typename T>
void swap(T &a, T &b);

template<typename T, typename Compare>
void sort(T *begin, T *end, Compare comp = [](const T &a, const T &b) -> bool { return a < b; });

int kruskal(int v, int e, Edge *edges);

template<typename T>
void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename T, typename Compare>
void sort(T *begin, T *end, Compare comp) {
    if (begin >= end) {
        return;
    }
    T pivot = *(begin + (end - begin) / 2);
    T *left = begin;
    T *right = end - 1;
    while (left <= right) {
        while (comp(*left, pivot)) { ++left; }
        while (comp(pivot, *right)) { --right; }
        if (left <= right) {
            swap(*left, *right);
            ++left;
            --right;
        }
    }
    sort(begin, right + 1, comp);
    sort(left, end, comp);
}

int kruskal(int v, int e, Edge *edges) {
    sort(edges, edges + e, [](const Edge &a, const Edge &b) -> bool { return a.w < b.w; });
    MST mst(v);
    int sum = 0;
    for (int i = 0; i < e; ++i) {
        if (mst.find(edges[i].v1) != mst.find(edges[i].v2)) {
            mst.unite(edges[i].v1, edges[i].v2);
            sum += edges[i].w;
        }
    }
    return sum;
}

#endif //ALGORITHM_H
