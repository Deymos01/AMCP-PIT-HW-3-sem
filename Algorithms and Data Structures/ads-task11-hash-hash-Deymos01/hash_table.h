#ifndef HASH_HASH_HASH_TABLE_H
#define HASH_HASH_HASH_TABLE_H

template<typename T>
class hash_table {
private:
    struct Node {
        T value;
        bool isDeleted;

        explicit Node(const T &val) : value(val), isDeleted(false) {};
    };

    static const size_t defaultSizeTable = 128;
    constexpr static const double defaultLoadFactor = 0.8;
    size_t sizeTable; // Size of table in memory
    size_t sizeData; // Number of elements in table (without deleted elements)
    size_t sizeDeleted; // Number of deleted elements in table
    Node **data;

    void resizeTable() {
        size_t prevSize = sizeTable;
        sizeTable *= 2;
        sizeDeleted = 0;
        sizeData = 0;

        Node **tmp = new Node *[sizeTable];
        for (size_t i = 0; i < sizeTable; ++i) {
            tmp[i] = nullptr;
        }
        std::swap(tmp, data);
        for (size_t i = 0; i < prevSize; ++i) {
            if (tmp[i] && !tmp[i]->isDeleted) {
                add(tmp[i]->value);
            }
        }
        for (size_t i = 0; i < prevSize; ++i) {
            delete tmp[i];
        }
        delete[] tmp;
    }

    void rehashTable() {
        sizeDeleted = 0;
        sizeData = 0;

        Node **tmp = new Node *[sizeTable];
        for (size_t i = 0; i < sizeTable; ++i) {
            tmp[i] = nullptr;
        }
        std::swap(tmp, data);
        for (size_t i = 0; i < sizeTable; ++i) {
            if (tmp[i] && !tmp[i]->isDeleted) {
                add(tmp[i]->value);
            }
        }
        for (size_t i = 0; i < sizeTable; ++i) {
            delete tmp[i];
        }
        delete[] tmp;
    }

    size_t hash1(const T &key) {
        return key % 2287;
    }

    size_t hash2(const T &key) {
        return key % 3733;
    }

    size_t hashFunction(const T &key, const size_t &i = 0) {
        return (hash1(key) + i * hash2(key)) % sizeTable;
    }

public:
    hash_table() {
        sizeTable = defaultSizeTable;
        sizeData = 0;
        sizeDeleted = 0;
        data = new Node *[sizeTable];
        for (size_t i = 0; i < sizeTable; ++i) {
            data[i] = nullptr;
        }
    };

    ~hash_table() {
        for (size_t i = 0; i < sizeTable; ++i) {
            delete data[i];
        }
        delete[] data;
    };

    bool find(const T &val) {
        size_t h = hashFunction(val);
        size_t i = 1;
        auto check = data[h];
        while (data[h] && i < sizeTable) {
            if (data[h]->value == val) {
                if (data[h]->isDeleted) { return false; }
                return true;
            }
            h = hashFunction(val, i);
            ++i;
        }
        return false;
    }

    void add(const T &val) {
        if (sizeData + 1 > (size_t)(defaultLoadFactor * sizeTable)) {
            resizeTable();
        } else if ((double)(sizeDeleted) / sizeData > 0.5) {
            rehashTable();
        }

        size_t h = hashFunction(val);
        size_t i = 1;
        size_t delHash = -1;
        while (data[h] && i < sizeTable) {
            if (data[h]->isDeleted) {
                delHash = h;
                break;
            }
            h = hashFunction(val, i);
            ++i;
        }
        if (delHash == -1) {
            data[h] = new Node(val);
        } else {
            data[delHash]->value = val;
            data[delHash]->isDeleted = false;
            --sizeDeleted;
        }
        ++sizeData;
    }

    void erase(const T &val) {
        size_t h = hashFunction(val);
        size_t i = 1;
        while (data[h] && i < sizeTable) {
            if (data[h]->value == val) {
                data[h]->isDeleted = true;
                ++sizeDeleted;
                --sizeData;
                return;
            }
            h = hashFunction(val, i);
            ++i;
        }
    }
};

#endif //HASH_HASH_HASH_TABLE_H
