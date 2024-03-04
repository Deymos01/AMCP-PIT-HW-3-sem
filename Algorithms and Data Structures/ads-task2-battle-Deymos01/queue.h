#ifndef BATTLE_QUEUE_H
#define BATTLE_QUEUE_H

#include <cstdint>
#include <stdexcept>

class Queue {
private:
    uint8_t array[52]{0};
    uint8_t topIndex;
    uint8_t sizeCardDeck;

    void incTopIndex() {
        ++topIndex;
        if (topIndex == 52) {
            topIndex = 0;
        }
    }
public:
    explicit Queue(int sizeInitDeck) {
        topIndex = 0;
        sizeCardDeck = sizeInitDeck;
    }

    uint8_t &operator[](size_t index) {
        if (index >= 52) {
            throw std::invalid_argument("Index out of range");
        }
        return array[index];
    }

    bool is_empty() const {
        return sizeCardDeck == 0;
    }

    uint8_t pop() {
        size_t res = array[topIndex];
        array[topIndex] = 0;
        incTopIndex();
        --sizeCardDeck;
        return res;
    }

    void push_back(uint8_t elem) {
        array[(topIndex + sizeCardDeck) % 52] = elem;
        ++sizeCardDeck;
    }
};

#endif  // BATTLE_QUEUE_H
