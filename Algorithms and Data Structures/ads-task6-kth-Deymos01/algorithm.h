#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstring>

//size_t nSwaps = 0;
//size_t nCallRecursion = 0;

template<typename T>
void swap(T &a, T &b);

template<typename T, typename Iter>
int partition(vector<T> &vec, Iter *begin, Iter *end);

template<typename T, typename Iter>
void quickSortRange(vector<T> &vec, Iter *begin, Iter *end, int left, int right);

template<typename T>
void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename T, typename Iter>
void quickSortRange(vector<T> &vec, Iter* begin, Iter* end, int left, int right) {
//    ++nCallRecursion;
    if (begin >= end || begin > vec.begin() + right || end < vec.begin() + left) {
        return;
    }

    int pivotIndex = partition(vec, begin, end);
    if (pivotIndex >= left) {
        quickSortRange(vec, begin, vec.begin() + pivotIndex, left, right);
    }
    if (pivotIndex < right) {
        quickSortRange(vec, vec.begin() + pivotIndex + 1, end, left, right);
    }
}

template<typename T, typename Iter>
int partition(vector<T> &vec, Iter *begin, Iter *end) {
    T pivot = *(begin + (end - begin) / 2);

    T *l = begin;
    T *r = end;
    while (l <= r) {
        while (*l < pivot) { ++l; }
        while (*r > pivot) { --r; }
        if (l >= r) { break; }
        swap(*l, *r);
        ++l;
        --r;
//        ++nSwaps;
    }
    return r - vec.begin();
}

#endif //ALGORITHM_H