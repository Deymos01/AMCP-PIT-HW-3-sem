#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <climits>

void radixSortString(char **arr, const size_t &rows, const size_t &cols, const size_t &phase) {
    int count[CHAR_MAX];
    char **res = new char *[rows];

    for (int ph = 1; ph <= phase; ++ph) {
        for (int i = 0; i < CHAR_MAX; count[i] = 0, ++i);
        for (int i = 0; i < rows; ++i) {
            ++count[arr[i][cols - ph] - 'A'];
        }
        for (int i = 1; i < CHAR_MAX; ++i) {
            count[i] += count[i - 1];
        }
        for (int i = (int) (rows - 1); i >= 0; --i) {
            res[count[arr[i][cols - ph] - 'A'] - 1] = arr[i];
            --count[arr[i][cols - ph] - 'A'];
        }
        for (int i = 0; i < rows; ++i) {
            arr[i] = res[i];
        }
    }
    delete[] res;
}

#endif //ALGORITHM_H
