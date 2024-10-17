#ifndef MST_MST_H
#define MST_MST_H

class MST {
private:
    int *arr;
public:
    explicit MST(int n) : arr(new int[n]) {
        for (int i = 0; i < n; ++i) {
            arr[i] = i;
        }
    }
    ~MST() {
        delete[] arr;
    }

    int find(int i) {
        if (arr[i] == i) {
            return i;
        }
        return arr[i] = find(arr[i]);
    }

    void unite(int i, int j) {
        arr[find(i)] = find(j);
    }

    void printArr(int n) {
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    }
};

#endif //MST_MST_H
