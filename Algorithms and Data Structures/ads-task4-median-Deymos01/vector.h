#ifndef MEDIAN_VECTOR_H
#define MEDIAN_VECTOR_H

#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <cstring>

template<typename T>
class vector {
private:
    T *data;
    size_t sizeData;
    size_t capacity;
public:
    vector() : data(nullptr), sizeData(0), capacity(0) {}

    explicit vector(size_t n) : data(new T[n]), sizeData(n), capacity(n) {}

    vector(size_t n, T value) : data(new T[n]), sizeData(n), capacity(n) {
        memset(data, value, n * sizeof(T));
    }

    ~vector() {
        delete[] data;
    }

    T &operator[](size_t index) {
        if (index >= sizeData) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T &operator[](size_t index) const {
        if (index >= sizeData) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t size() const {
        return sizeData;
    }

    bool empty() const {
        return sizeData == 0;
    }

    void push_back(T value) {
        if (sizeData == capacity) {
            if (capacity == 0) {
                capacity = 1;
            } else {
                capacity *= 2;
            }
            T *newData = new T[capacity];
            memmove(newData, data, sizeData * sizeof(T));
            delete[] data;
            data = newData;
        }
        data[sizeData++] = value;
    }

    void pop_back() {
        if (sizeData == 0) {
            throw std::out_of_range("Vector is empty");
        }
        --sizeData;
    }

    void print() const {
        for (size_t i = 0; i < sizeData; ++i) {
            std::cout << data[i] << " \n"[i == sizeData - 1];
        }
    }

    T *begin() {
        return data;
    }

    T *end() {
        return data + sizeData;
    }
};

#endif //MEDIAN_VECTOR_H
