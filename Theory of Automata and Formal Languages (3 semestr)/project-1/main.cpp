#include <iostream>
#include <map>
#include <array>

struct ConfigFiniteMachine {
    // initialisation of alphabet
    std::map<char, int> alphabet = {
            {'c', 0},
            {'a', 1},
            {'b', 2}
    };
    // initialisation of transition table
    std::array<std::array<int, 3>, 6> transitionTable = {{
                                                                 {1, -1, -1},
                                                                 {-1, 2, -1},
                                                                 {-1, 4, 3},
                                                                 {-1, 4, 3},
                                                                 {5, 4, 3},
                                                                 {-1, -1, -1}
                                                         }};
    int endState = 5;
};

/**
 * Function returns end of subchain if it can be found, else returns -1
 * @param config configuration of finite machine
 * @param str string to process
 * @param start start of subchain
 * @return end of subchain if it can be found, else -1
 */
int getSubstringEnd(ConfigFiniteMachine &config, const std::string &str, int start) {
    int state = 0;
    for (int i = start; i < str.size(); ++i) {
        state = config.transitionTable[state][config.alphabet[str[i]]]; // get next state
        if (state == -1) {                                              // if state is -1, then subchain isn't found
            return -1;
        } else if (state == config.endState) {                          // if state is config.endState, then subchain is found
            return i;                                                   // return end of subchain
        }
    }
    return -1;
}

/**
 * Function prints all subchains in string
 * @param str string to process
 * @param config configuration of finite machine
 */
void printSubchains(const std::string& str, ConfigFiniteMachine &config) {
    int countChains = 0;
    for (int i = 0; i < str.size(); ++i) {
            if (config.transitionTable[0][config.alphabet[str[i]]] != -1) { // if first symbol is 'c'
            int end = getSubstringEnd(config, str, i);              // try to find subchain
            if (end != -1) {                                                // if subchain is found
                std::cout << i + 1 << ": " << str.substr(i, end - i + 1) << std::endl;
                ++countChains;
            }
        }
    }
    if (countChains == 0) {
        std::cout << "No chains found" << std::endl;
    }
}

int main() {
    ConfigFiniteMachine config;
    std::string str;
    int t = 10;
    while (t-- > 0) {
        std::cin >> str;
        printSubchains(str, config);
    }
    return 0;
}
