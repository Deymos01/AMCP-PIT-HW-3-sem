#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "vector.h"

template<typename T>
class maxHeap {
private:
    vector<T> data;
    size_t sizeData;
    size_t capacity;

    void upSifting(int startIndex) {
        int currIndex = startIndex;
        while (currIndex > 0) {
            int tmpInd = (currIndex - 1) / 2;
            if (data[currIndex] < data[tmpInd]) {
                return;
            }
            std::swap(data[currIndex], data[tmpInd]);
            currIndex = tmpInd;
        }
    }

    void downSifting(int startIndex = 0) {
        int currIndex = startIndex;
        while (true) {
            if (currIndex * 2 + 1 > sizeData - 1) {
                return;
            }
            int indMax = currIndex * 2 + 1;
            if (currIndex * 2 + 2 < sizeData && data[indMax] < data[currIndex * 2 + 2]) {
                indMax = currIndex * 2 + 2;
            }
            if (data[currIndex] >= data[indMax]) {
                return;
            }
            std::swap(data[currIndex], data[indMax]);
            currIndex = indMax;
        }
    }

public:
    maxHeap() : sizeData(0), capacity(0) {}
    maxHeap(size_t n) : sizeData(0), capacity(n), data(vector<T>(n)) {}
    maxHeap(size_t n, T val) : sizeData(n), capacity(n), data(vector<T>(n, val)) {}

    size_t size() const {
        return sizeData;
    }

    size_t max_size() const {
        return capacity;
    }

    T top() {
        if (data.empty()) {
            throw std::out_of_range("The heap size is zero");
        }
        return data[0];
    }

    void pop() {
        if (data.empty()) {
            throw std::out_of_range("The heap size is zero");
        }
        data[0] = data[sizeData - 1];
        --sizeData;
        downSifting();
    }

    void push(T value) {
        if (sizeData == data.size()) {
            data.push_back(value);
            ++sizeData;
            capacity = data.max_size();
        } else {
            data[sizeData++] = value;
        }
        upSifting(sizeData - 1);
    }

    // allow casting to vector<T>
    explicit operator vector<T>() {
        vector<T> tmp(data);
        return tmp;
    }
};

#endif //MAXHEAP_H
