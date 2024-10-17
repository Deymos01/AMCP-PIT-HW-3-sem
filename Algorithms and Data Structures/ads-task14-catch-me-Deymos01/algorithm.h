#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstring>
#include <cstdint>

int64_t P = 1e9 + 7;
int64_t x = 2;

size_t countOccurrenceHash(const char *line, const char *pattern);
int64_t hash(const char *beg, const char *end);
bool compareStr(const char *str1_beg, const char *str1_end, const char *str2_beg, const char *str2_end);

size_t countOccurrenceKMP(const char *line, const char *pattern, const int *suffix, size_t patternLength);
void fillSuffix(const char *pattern, int *suffix, size_t patternLength);

size_t countOccurrenceHash(const char *line, const char *pattern) {
    size_t res = 0;
    size_t lineLength = std::strlen(line);
    size_t patternLength = std::strlen(pattern);
    if (patternLength > lineLength) { return res; }
    int64_t hashPatt = hash(pattern, pattern + patternLength);

    int64_t prevLineHash = hash(line, line + patternLength);
    if (prevLineHash == hashPatt &&
        compareStr(line, line + patternLength, pattern, pattern + patternLength)) {
        ++res;
    }

    for (int i = 1; i < lineLength - patternLength + 1; ++i) {
        int64_t nextLineHash = (prevLineHash * x - line[i - 1] * (1 << patternLength) + line[i + patternLength - 1]) % P;
        if (nextLineHash == hashPatt &&
            compareStr(line + i, line + i + patternLength, pattern, pattern + patternLength)) {
            ++res;
        }
        prevLineHash = nextLineHash;
    }

    return res;
}

int64_t hash(const char *beg, const char *end) {
    int64_t res = 0;
    for (int i = 0; i < end - beg; ++i) {
        res = (res * x + beg[i]) % P;
    }
    return res;
}

bool compareStr(const char *str1_beg, const char *str1_end, const char *str2_beg, const char *str2_end) {
    if (str1_end - str1_beg != str2_end - str2_beg) {
        return false;
    }

    for (int i = 0; i < str1_end - str1_beg; ++i) {
        if (str1_beg[i] != str2_beg[i]) {
            return false;
        }
    }
    return true;
}

size_t countOccurrenceKMP(const char *line, const char *pattern, const int *suffix, size_t patternLength) {
    size_t res = 0;
    size_t lineLength = std::strlen(line);
    if (patternLength > lineLength) { return res; }

    size_t patternIndex = 0;
    for (size_t lineIndex = 0; lineIndex < lineLength; ++lineIndex) {
        if (line[lineIndex] == pattern[patternIndex]) {
            ++patternIndex;
            if (patternIndex == patternLength) {
                ++res;
                lineIndex = lineIndex - patternIndex + 1;
                patternIndex = 0;
            }
        } else {
            if (patternIndex > 0) {
                patternIndex = suffix[patternIndex - 1];
                --lineIndex;
            }
        }
    }
    return res;
}

void fillSuffix(const char *pattern, int *suffix, size_t patternLength) {
    suffix[0] = 0;
    int j = 0;
    for (int i = 1; i < patternLength; ++i) {
        if (pattern[i] != pattern[j]) {
            if (j == 0) { suffix[i] = 0; }
            else {
                j = suffix[j - 1];
                --i;
            }
        } else {
            suffix[i] = j + 1;
            ++j;
        }
    }
}

#endif  // ALGORITHM_H
