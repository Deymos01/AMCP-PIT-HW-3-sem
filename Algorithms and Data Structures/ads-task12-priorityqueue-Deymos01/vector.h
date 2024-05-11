#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <cstring>

template<typename T>
class vector {
private:
    T *data_;
    size_t sizeData_;
    size_t capacity_;
public:
    explicit vector(size_t n = 128) : data_(new T[n]), sizeData_(0), capacity_(n) {}

    explicit vector(int n) : vector(static_cast<size_t>(n)) {}

    explicit vector(long n) : vector(static_cast<size_t>(n)) {}

    explicit vector(long long n) : vector(static_cast<size_t>(n)) {}

    explicit vector(short n) : vector(static_cast<size_t>(n)) {}

    explicit vector(char n) : vector(static_cast<size_t>(n)) {}

    explicit vector(unsigned int n) : vector(static_cast<size_t>(n)) {}

    explicit vector(unsigned short n) : vector(static_cast<size_t>(n)) {}

    explicit vector(unsigned char n) : vector(static_cast<size_t>(n)) {}


    vector(size_t n, T value) : data_(new T[n]), sizeData_(n), capacity_(n) {
        for (size_t i = 0; i < n; ++i) {
            data_[i] = value;
        }
    }

    vector(int n, T value) : vector(static_cast<size_t>(n), value) {}

    vector(long n, T value) : vector(static_cast<size_t>(n), value) {}

    vector(long long n, T value) : vector(static_cast<size_t>(n), value) {}

    vector(short n, T value) : vector(static_cast<size_t>(n), value) {}

    vector(char n, T value) : vector(static_cast<size_t>(n), value) {}

    vector(unsigned int n, T value) : vector(static_cast<size_t>(n), value) {}

    vector(unsigned short n, T value) : vector(static_cast<size_t>(n), value) {}

    vector(unsigned char n, T value) : vector(static_cast<size_t>(n), value) {}

    vector(const vector<T> &v) : sizeData_(v.sizeData_), capacity_(v.capacity_) {
        data_ = new T[capacity_];
        memcpy(data_, v.data_, capacity_ * sizeof(T));
    }

    ~vector() {
        delete[] data_;
    }

    T &operator[](size_t index) {
        return data_[index];
    }

    const T &operator[](size_t index) const {
        return data_[index];
    }


    [[nodiscard]] size_t size() const {
        return sizeData_;
    }

    [[nodiscard]] size_t capacity() const {
        return capacity_;
    }

    [[nodiscard]] bool empty() const {
        return sizeData_ == 0;
    }

    void push_back(T value) {
        if (sizeData_ == capacity_) {
            if (capacity_ == 0) {
                capacity_ = 1;
            } else {
                capacity_ *= 2;
            }
            T *newData = new T[capacity_];
            memmove(newData, data_, sizeData_ * sizeof(T));
            delete[] data_;
            data_ = newData;
        }
        data_[sizeData_++] = value;
    }

    void pop_back() {
        if (sizeData_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        --sizeData_;
    }

    void resize(size_t newSize) {
        if (newSize > capacity_) {
            capacity_ = newSize;
            T *newData = new T[capacity_];
            memmove(newData, data_, sizeData_ * sizeof(T));
            delete[] data_;
            data_ = newData;
        }
        sizeData_ = newSize;
    }

    void print() const {
        for (size_t i = 0; i < sizeData_; ++i) {
            std::cout << data_[i] << " \n"[i == sizeData_ - 1];
        }
    }

    T *begin() {
        return data_;
    }

    T *end() {
        return data_ + sizeData_;
    }
};

#endif //VECTOR_H