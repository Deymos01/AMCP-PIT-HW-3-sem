#ifndef MEDIAN_ALGORITHM_H
#define MEDIAN_ALGORITHM_H

template<typename T>
void swap(T &a, T &b);

template<typename T, typename Compare>
void sort(T *begin, T *end, Compare comp = [](T a, T b) -> bool { return a < b; });

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

#endif //MEDIAN_ALGORITHM_H
