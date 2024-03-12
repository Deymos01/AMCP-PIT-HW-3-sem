#ifndef MINMAXQUEUE_MONOTONIC_QUEUE_H
#define MINMAXQUEUE_MONOTONIC_QUEUE_H

#include <stdexcept>
#include "queue.h"

template<typename T>
class monotonic_queue : public Queue<std::pair<T /*val*/, std::pair<T /*botMin*/, T /*botMax*/>>> {
protected:
    void moveToRight() {
        // Assume the left stack is not empty
        T currMin = Queue<std::pair<T, std::pair<T, T>>>::leftStack.top().first;
        T currMax = Queue<std::pair<T, std::pair<T, T>>>::leftStack.top().first;
        while (!Queue<std::pair<T, std::pair<T, T>>>::leftStack.is_empty()) {
            currMin = std::min(currMin, Queue<std::pair<T, std::pair<T, T>>>::leftStack.top().first);
            currMax = std::max(currMax, Queue<std::pair<T, std::pair<T, T>>>::leftStack.top().first);
            Queue<std::pair<T, std::pair<T, T>>>::rightStack.push({Queue<std::pair<T, std::pair<T, T>>>::leftStack.pop().first,
                                                                   {currMin, currMax}
                                                                  });
        }
    }
public:
    monotonic_queue() = default;

    void push(T elem) {
        T min = Queue<std::pair<T, std::pair<T, T>>>::leftStack.is_empty() ? elem :
                std::min(elem, Queue<std::pair<T, std::pair<T, T>>>::leftStack.top().second.first);

        T max = Queue<std::pair<T, std::pair<T, T>>>::leftStack.is_empty() ? elem :
                std::max(elem, Queue<std::pair<T, std::pair<T, T>>>::leftStack.top().second.second);

        Queue<std::pair<T, std::pair<T, T>>>::leftStack.push({elem, {min, max}});
    }

    T top() {
        if (this->is_empty()) {
            throw std::runtime_error("Monotonic queue is empty");
        }
        if (Queue<std::pair<T, std::pair<T, T>>>::rightStack.is_empty()) {
            this->moveToRight();
        }
        return Queue<std::pair<T, std::pair<T, T>>>::rightStack.top().first;
    }

    T pop() {
        if (this->is_empty()) {
            throw std::runtime_error("Monotonic queue is empty");
        }
        if (Queue<std::pair<T, std::pair<T, T>>>::rightStack.is_empty()) {
            this->moveToRight();
        }
        return Queue<std::pair<T, std::pair<T, T>>>::pop().first;
    }

    T getMin() {
        if (this->is_empty()) {
            throw std::runtime_error("Monotonic queue is empty");
        }
        if (Queue<std::pair<T, std::pair<T, T>>>::leftStack.is_empty()) {
            return Queue<std::pair<T, std::pair<T, T>>>::rightStack.top().second.first;
        }
        if (Queue<std::pair<T, std::pair<T, T>>>::rightStack.is_empty()) {
            return Queue<std::pair<T, std::pair<T, T>>>::leftStack.top().second.first;
        }
        return std::min(Queue<std::pair<T, std::pair<T, T>>>::leftStack.top().second.first,
                        Queue<std::pair<T, std::pair<T, T>>>::rightStack.top().second.first);
    }

    T getMax() {
        if (this->is_empty()) {
            throw std::runtime_error("Monotonic queue is empty");
        }
        if (Queue<std::pair<T, std::pair<T, T>>>::leftStack.is_empty()) {
            return Queue<std::pair<T, std::pair<T, T>>>::rightStack.top().second.second;
        }
        if (Queue<std::pair<T, std::pair<T, T>>>::rightStack.is_empty()) {
            return Queue<std::pair<T, std::pair<T, T>>>::leftStack.top().second.second;
        }
        return std::max(Queue<std::pair<T, std::pair<T, T>>>::leftStack.top().second.second,
                        Queue<std::pair<T, std::pair<T, T>>>::rightStack.top().second.second);
    }
};

#endif //MINMAXQUEUE_MONOTONIC_QUEUE_H