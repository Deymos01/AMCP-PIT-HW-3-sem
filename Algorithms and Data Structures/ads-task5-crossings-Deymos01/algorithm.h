#ifndef CROSSINGS_ALGORITHM_H
#define CROSSINGS_ALGORITHM_H

#include "vector.h"

template<typename T, typename Compare>
void MergeSort(T *begin, T *end, uint64_t &inversionCounter, Compare comp = [](const T &a, const T &b) -> bool { return a < b; });

template<typename T, typename Compare>
void merge(T *begin, T *mid, T *end, uint64_t &inversionCounter, Compare comp);

template<typename T, typename Compare>
uint64_t countSegmentsInSamePoint(T *begin, T *end, Compare comp);

template<typename T, typename Compare>
void MergeSort(T *begin, T *end, uint64_t &inversionCounter, Compare comp) {
    // Sort an array using merge sort algorithm. Stable sort.
    if (end - begin <= 1) { return; }
    T *mid = begin + (end - begin) / 2;
    MergeSort(begin, mid, inversionCounter, comp);
    MergeSort(mid, end, inversionCounter, comp);
    merge(begin, mid, end, inversionCounter, comp);
}

template<typename T, typename Compare>
void merge(T *begin, T *mid, T *end, uint64_t &inversionCounter, Compare comp) {
    vector<T> tmp(end - begin);
    T *start1 = begin;
    T *end1 = mid;
    T *start2 = mid;
    T *end2 = end;
    int i = 0;
    while (start1 < end1 && start2 < end2) {
        if (comp(*start1, *start2)) {
            tmp[i++] = *start1++;
        } else {
            tmp[i++] = *start2++;
            inversionCounter += end1 - start1;
        }
    }
    while (start1 < end1) { tmp[i++] = *start1++; }
    while (start2 < end2) { tmp[i++] = *start2++; }
    i = 0;
    while (begin < end) {
        *begin = tmp[i++];
        ++begin;
    }
}

template<typename T, typename Compare>
uint64_t countSegmentsInSamePoint(T *begin, T *end, Compare comp) {
    uint64_t inSamePoint = 1;
    uint64_t res = 0;
    for (auto it = begin + 1; it < end; ++it) {
        if (comp(*it, *(it - 1))) {
            ++inSamePoint;
        } else {
            res += inSamePoint * (inSamePoint - 1) / 2;
            inSamePoint = 1;
        }
    }
    res += inSamePoint * (inSamePoint - 1) / 2;
    return res;
}

#endif //CROSSINGS_ALGORITHM_H
