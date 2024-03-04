#ifndef MINMAXQUEUE_STACK_H
#define MINMAXQUEUE_STACK_H

#include <cstdint>
#include <stdexcept>
#include <cstring>

template <typename T>
class Stack {
private:
    uint32_t sizeDataArray;
    uint32_t sizeData;
    T* data;
public:
    Stack() : sizeData(0), sizeDataArray(1) {
        data = new T[1];
    }

    ~Stack() {
        delete[] data;
    }

    bool is_empty() {
        return sizeData == 0;
    }

    void push(T elem) {
        if (sizeData == sizeDataArray) {
            T* tmp = new T[sizeDataArray * 2];
            sizeDataArray *= 2;
            memmove(tmp, data, sizeData * sizeof(T));
            delete[] data;
            data = tmp;
        }
        data[sizeData] = elem;
        ++sizeData;
    }

    T pop() {
        if (this->is_empty()) {
            throw std::runtime_error("stack is empty");
        }
        return data[sizeData-- - 1];
    }

    T top() {
        if (this->is_empty()) {
            throw std::runtime_error("stack is empty");
        }
        return data[sizeData - 1];
    }
};

#endif  // MINMAXQUEUE_STACK_H
