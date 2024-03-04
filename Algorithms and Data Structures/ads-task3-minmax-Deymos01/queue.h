#ifndef MINMAXQUEUE_QUEUE_H
#define MINMAXQUEUE_QUEUE_H

#include <stdexcept>

#include "stack.h"

template<typename T>
class Queue {
private:
    Stack<std::pair<T /*val*/, std::pair<T /*botMin*/, T /*botMax*/>>> leftStack;
    Stack<std::pair<T /*val*/, std::pair<T /*botMin*/, T /*botMax*/>>> rightStack;

    void moveToRight() {
        // Assume the left stack is not empty
        T currMin = leftStack.top().first;
        T currMax = leftStack.top().first;
        while (!leftStack.is_empty()) {
            currMin = std::min(currMin, leftStack.top().first);
            currMax = std::max(currMax, leftStack.top().first);
            rightStack.push({leftStack.pop().first, {currMin, currMax}});
        }
    }

public:
    Queue() = default;

    bool is_empty() {
        return leftStack.is_empty() && rightStack.is_empty();
    }

    void push(T elem) {
        T min = leftStack.is_empty() ? elem : std::min(elem, leftStack.top().second.first);
        T max = leftStack.is_empty() ? elem : std::max(elem, leftStack.top().second.second);
        leftStack.push({elem, {min, max}});
    }

    T top() {
        if (this->is_empty()) {
            throw std::runtime_error("Queue is empty");
        }
        if (rightStack.is_empty()) {
            this->moveToRight();
        }
        return rightStack.top().first;
    }

    T pop() {
        if (this->is_empty()) {
            throw std::runtime_error("Queue is empty");
        }
        if (rightStack.is_empty()) {
            this->moveToRight();
        }
        return rightStack.pop().first;
    }

    T getMin() {
        if (this->is_empty()) {
            throw std::runtime_error("Queue is empty");
        }
        if (leftStack.is_empty()) {
            return rightStack.top().second.first;
        }
        if (rightStack.is_empty()) {
            return leftStack.top().second.first;
        }
        return std::min(leftStack.top().second.first, rightStack.top().second.first);
    }

    T getMax() {
        if (this->is_empty()) {
            throw std::runtime_error("Queue is empty");
        }
        if (leftStack.is_empty()) {
            return rightStack.top().second.second;
        }
        if (rightStack.is_empty()) {
            return leftStack.top().second.second;
        }
        return std::max(leftStack.top().second.second, rightStack.top().second.second);
    }
};

#endif //MINMAXQUEUE_QUEUE_H
