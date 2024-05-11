#ifndef PRIORITYQUEUE_PRIORITY_QUEUE_H
#define PRIORITYQUEUE_PRIORITY_QUEUE_H

#include <fstream>
#include "vector.h"

class priority_queue {
private:
    struct Data {
        int val;
        uint32_t index;

        Data() : val(0) {};

        explicit Data(int val, uint32_t index) : val(val), index(index) {};
    };

    void upSifting(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index]->val < heap[parent]->val) {
                std::swap(heap[index], heap[parent]);
                indexes[heap[index]->index] = index;
                indexes[heap[parent]->index] = parent;
                index = parent;
            } else {
                return;
            }
        }
    }

    void downSifting(int index) {
        while (2 * index + 1 < heap.size()) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            if (right < heap.size() && heap[right]->val < heap[left]->val) {
                ++left;
            }
            if (heap[index]->val <= heap[left]->val) {
                return;
            }
            std::swap(heap[index], heap[left]);
            indexes[heap[index]->index] = index;
            indexes[heap[left]->index] = left;
            index = left;
        }
    }

    vector<Data *> heap;
    vector<int> indexes;
public:
    priority_queue() = default;

    ~priority_queue() = default;

    [[nodiscard]] bool isEmpty() const {
        return heap.empty();
    }

    void push(int val, uint32_t index) {
        --index;
        heap.push_back(new Data(val, index));
        if (indexes.size() <= index) {
            indexes.resize((index + 1) * 2);
        }

        indexes[index] = (int) (heap.size()) - 1;
        upSifting((int) (heap.size()) - 1);
    }

    void extract_min(std::ostream &outFile) {
        if (heap.empty()) {
            outFile << "*\n";
            return;
        }
        indexes[heap[0]->index] = -1;
        outFile << heap[0]->val << "\n";
        delete heap[0];
        heap[0] = heap[heap.size() - 1];
        indexes[0] = indexes[indexes.size() - 1];
        heap.pop_back();
        indexes.pop_back();
        downSifting(0);
    }

    void decrease_key(int line, int newVal) {
        int index = indexes[line - 1];
        heap[index]->val = newVal;
        upSifting(index);
    }
};

#endif //PRIORITYQUEUE_PRIORITY_QUEUE_H
