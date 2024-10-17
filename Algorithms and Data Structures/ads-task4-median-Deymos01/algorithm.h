#ifndef MEDIAN_ALGORITHM_H
#define MEDIAN_ALGORITHM_H

template<typename T>
void swap(T &a, T &b);

template<typename T, typename Compare>
void sort(T *begin, T *end, Compare comp = [](const T &a, const T &b) -> bool { return a < b; });

template<typename T, typename Compare>
T *find_kth_smallest(T *begin, T *end, int k, Compare comp = [](const T &a, const T &b) -> bool { return a < b; });

template<typename T, typename Compare>
size_t partition(T *begin, T *end, Compare comp = [](const T &a, const T &b) -> bool { return a < b; });

template<typename T, typename Compare>
T *find_min(T *begin, T *end, Compare comp = [](const T &a, const T &b) -> bool { return a < b; });

template<typename T, typename Compare>
T *find_max(T *begin, T *end, Compare comp = [](const T &a, const T &b) -> bool { return a < b; });

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

template<typename T, typename Compare>
size_t partition(T *begin, T *end, Compare comp) {
    T pivot = *(begin + (end - begin) / 2);

    T *equal = begin;
    T *greater = begin;

    for (auto now = begin; now < end; ++now) {
        if (comp(*now, pivot)) {
            if (now != greater) { swap(*now, *greater); }
            if (greater != equal) { swap(*greater, *equal); }
            ++greater;
            ++equal;
        } else if (*now == pivot) {
            if (now != greater) { swap(*now, *greater); }
            ++greater;
        }
    }
    return equal - begin;
}

template<typename T, typename Compare>
T *find_kth_smallest(T *begin, T *end, int k, Compare comp) {
    while (true) {
        int mid = partition(begin, end, comp);

        if (mid == k) {
            return begin + mid;
        } else if (mid < k) {
            begin += mid + 1;
            k -= mid + 1;
        } else {
            end = begin + mid;
        }
    }
}

template<typename T, typename Compare>
T *find_min(T *begin, T *end, Compare comp) {
    T *min = begin;
    for (auto now = begin + 1; now < end; ++now) {
        if (comp(*now, *min)) {
            min = now;
        }
    }
    return min;
}

template<typename T, typename Compare>
T *find_max(T *begin, T *end, Compare comp) {
    T *max = begin;
    for (auto now = begin + 1; now < end; ++now) {
        if (comp(*max, *now)) {
            max = now;
        }
    }
    return max;
}

#endif //MEDIAN_ALGORITHM_H
