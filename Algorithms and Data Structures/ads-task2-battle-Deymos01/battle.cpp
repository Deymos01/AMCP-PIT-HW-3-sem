#include <iostream>
#include <fstream>
#include <cstdint>

#include "queue.h"

void processCard(uint8_t &card);
bool isGreater(uint8_t card1, uint8_t card2);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Not enough arguments" << std::endl;
        return -1;
    }
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Can't open file: " << argv[1] << std::endl;
        return -2;
    }

    auto deck1 = Queue(26);
    auto deck2 = Queue(26);
    size_t ind = 0;
    // filling players' decks
    while (inputFile.peek() != EOF) {
        uint8_t tmp;
        inputFile >> tmp;
        processCard(tmp);
        inputFile.ignore(6, '\n');
        if (ind < 26) {
            deck1[ind++] = tmp;
        } else {
            deck2[ind - 26] = tmp;
            ++ind;
        }
    }
    inputFile.close();

    // Simulate game process
    size_t it = 1;
    auto argueDeck = Queue(0);
    while (it < 1'000'000 && !deck1.is_empty() && !deck2.is_empty()) {
        uint8_t card1 = deck1.pop();
        uint8_t card2 = deck2.pop();

        // processing a disputed situation
        while (card1 == card2 && it < 1'000'000 && !deck1.is_empty() && !deck2.is_empty()) {
            argueDeck.push_back(card1);
            argueDeck.push_back(card2);
            card1 = deck1.pop();
            card2 = deck2.pop();
            ++it;
        }

        if (it >= 1'000'000 || deck1.is_empty() || deck2.is_empty()) {
            break;
        }

        // if there was a dispute
        if (!argueDeck.is_empty()) {
            if (isGreater(card1, card2)) {
                while (!argueDeck.is_empty()) {
                    deck1.push_back(argueDeck.pop());
                }
            } else {
                while (!argueDeck.is_empty()) {
                    deck2.push_back(argueDeck.pop());
                }
            }
        }

        // playing a match
        if (isGreater(card1, card2)) {
            deck1.push_back(card1);
            deck1.push_back(card2);
        } else {
            deck2.push_back(card1);
            deck2.push_back(card2);
        }
        ++it;
    }

    if (it >= 1'000'000) {
        std::cout << "unknown" << std::endl;
    } else if (deck1.is_empty() && deck2.is_empty()) {
        std::cout << "draw" << std::endl;
    } else if (deck2.is_empty()) {
        std::cout << "first" << std::endl;
    } else {
        std::cout << "second" << std::endl;
    }
    return 0;
}

void processCard(uint8_t &card) {
    switch (card) {
        case '1':
            card = '9' + 1;
            break;
        case 'J':
            card = '9' + 2;
            break;
        case 'Q':
            card = '9' + 3;
            break;
        case 'K':
            card = '9' + 4;
            break;
        case 'A':
            card = '9' + 5;
            break;
        default:
            return;
    }
}

bool isGreater(uint8_t card1, uint8_t card2) {
    return !(card1 == '9' + 5 && card2 == '2') && (card1 > card2 || card1 == '2' && card2 == '9' + 5);
}