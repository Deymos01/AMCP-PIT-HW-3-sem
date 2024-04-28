#include <iostream>
#include <stack>
#include <unordered_map>
#include <cstdint>

//struct AutomataConfig {
//    // Automata Configurations
//    std::unordered_map<std::string, std::pair<uint8_t, std::string>> transitionFunc;
//    uint8_t startState{};
//    uint8_t finalState{};
//};

std::pair<int, char> isStrCorrect(const std::string &str, const AutomataConfig &config) {
    // Check the string
    std::stack<char> stack; // Stack for the automata
    stack.push('Z'); // Push the start symbol
    uint8_t currState = config.startState; // Current state

    // Iterate over the string
    for (auto i = 0; i < str.size(); ++i) {
        std::string key = std::to_string(currState) + str[i] + stack.top(); // Get the key

        if (config.transitionFunc.contains(key)) { // Check if the key exists
            auto val = (*config.transitionFunc.find(key)).second; // Get the value

            currState = val.first; // Update the current state
            stack.pop(); // Pop the stack
            if (val.second.empty()) { continue; } // If the value is empty, continue

            for (int j = static_cast<int>(val.second.size()) - 1; j >= 0; --j) { // Push the value to the stack
                stack.push(val.second[j]);
            }

        } else { // If the key doesn't exist, return the position and the symbol
            return {i + 1, str[i]};
        }
    }

    // Check if the string belongs to the language
    if (currState == config.finalState && stack.top() == 'Z') {
        return {0, '\0'};
    }
    // If the string doesn't belong to the language, return the position and the symbol
    return {str.size(), str[str.size() - 1]};
}

int main() {
    // Set up the automata
    AutomataConfig config;
    config.transitionFunc = {
            {"0-Z", {1, "-Z"}},
            {"10-", {1, "00-"}},
            {"100", {1, "000"}},
            {"1--", {4, ""}},
            {"11-", {5, "1-"}},
            {"511", {5, ""}},
            {"51-", {5, "1-"}},
            {"5--", {4, ""}},
            {"110", {2, "10"}},
            {"211", {2, ""}},
            {"210", {2, "10"}},
            {"200", {3, ""}},
            {"300", {3, ""}},
            {"3--", {4, ""}}
    };
    config.startState = 0;
    config.finalState = 4;

    // Get the input string
    std::string input_str;
    std::cin >> input_str;

    // Check the string
    std::pair<int, char> checking = isStrCorrect(input_str, config);
    if (checking.first == 0) {
        std::cout << "String \"" << input_str << "\" belongs the language" << std::endl;
    } else {
        std::cout << "FATAL ERROR: non-expected symbol " << checking.second << " at position "
                  << checking.first << std::endl;
    }
    return 0;
}
