#ifndef ISBTREE_BTREENODE_H
#define ISBTREE_BTREENODE_H

#include <cstdint>

struct BTreeNode {
    bool isLeaf;
    uint32_t leafLevel;
    uint32_t nodeIndex;
    uint32_t numberOfKeys;
    uint32_t numberOfChildren;
    int32_t *keys;
    uint32_t *childrenIndexes;

    BTreeNode() : isLeaf(true), leafLevel(0), nodeIndex(0), numberOfKeys(0), numberOfChildren(0), keys(nullptr), childrenIndexes(nullptr) {}

    bool operator<(const BTreeNode &other) const {
        return nodeIndex < other.nodeIndex;
    }

    [[nodiscard]] bool isAscending() const {
        for (int i = 1; i < numberOfKeys; ++i) {
            if (keys[i - 1] > keys[i]) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] bool isKeyCountsValid(uint32_t t, bool isRoot=false) const {
        if (isRoot) {
            return numberOfKeys >= 1 && numberOfKeys <= 2 * t - 1;
        }
        return numberOfKeys >= t - 1 && numberOfKeys <= 2 * t - 1;
    }

    [[nodiscard]] bool isChildrenCountsValid(uint32_t t) const {
        if (isLeaf) {
            return numberOfChildren == 0;
        }
        return numberOfChildren == numberOfKeys + 1;
    }

    ~BTreeNode() {
        delete[] keys;
        delete[] childrenIndexes;
    }
};

int find(BTreeNode** arr, uint32_t sz, uint32_t index) {
    int left = 0;
    int right = sz - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid]->nodeIndex == index) {
            return mid;
        } else if (arr[mid]->nodeIndex < index) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

std::ostream &operator<<(std::ostream &out, const BTreeNode &node) {
    out << "Node type: " << (node.isLeaf ? "leaf" : "branch") << '\n';
    if (node.isLeaf) { out << "Leaf Level: " << node.leafLevel << '\n'; }
    out << "Node Index: " << node.nodeIndex << '\n';
    out << "Number of Keys: " << node.numberOfKeys << '\n';
    out << "Keys: ";
    for (uint32_t i = 0; i < node.numberOfKeys; ++i) {
        out << node.keys[i] << " ";
    }
    if (!node.isLeaf) {
        out << '\n';
        out << "Number of Children: " << node.numberOfChildren << '\n';
        out << "Children Indexes: ";
        for (uint32_t i = 0; i < node.numberOfChildren; ++i) {
            out << node.childrenIndexes[i] << " ";
        }
    }
    return out;
}

#endif //ISBTREE_BTREENODE_H
