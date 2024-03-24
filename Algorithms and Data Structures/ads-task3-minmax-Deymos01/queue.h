#ifndef MINMAXQUEUE_QUEUE_H
#define MINMAXQUEUE_QUEUE_H

#include <stdexcept>
#include "stack.h"

template<typename T>
class Queue {
protected:
    Stack<T> leftStack;
    Stack<T> rightStack;

    void moveToRight() {
        // Assume the left stack is not empty
        while (!leftStack.is_empty()) {
            rightStack.push(leftStack.pop());
        }
    }
public:
    Queue() = default;

    bool is_empty() {
        return leftStack.is_empty() && rightStack.is_empty();
    }

    void push(const T& elem) {
        leftStack.push(elem);
    }

    T top() {
        if (this->is_empty()) {
            throw std::runtime_error("Queue is empty");
        }
        if (rightStack.is_empty()) {
            this->moveToRight();
        }
        return rightStack.top();
    }

    T pop() {
        if (this->is_empty()) {
            throw std::runtime_error("Queue is empty");
        }
        if (rightStack.is_empty()) {
            this->moveToRight();
        }
        return rightStack.pop();
    }
};

#endif  // MINMAXQUEUE_QUEUE_H