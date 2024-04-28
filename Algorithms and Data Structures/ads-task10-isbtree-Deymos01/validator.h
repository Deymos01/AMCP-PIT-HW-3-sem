#ifndef ISBTREE_VALIDATOR_H
#define ISBTREE_VALIDATOR_H

#include "BTreeNode.h"

class BTreeValidator {
private:
    bool isOK = true;
    uint32_t rootIndex_;
    uint32_t rootPos_;
    uint32_t t_;
    uint32_t N_;
    BTreeNode **nodes_;

    uint32_t dfs(uint32_t nodeIndex, uint32_t currLevel, int currMin = INT32_MIN, int currMax = INT32_MAX) {
        if (!isOK) {
            return currLevel;
        }
        int nodePos = find(nodes_, N_, nodeIndex);
        uint32_t nNodeKeys = nodes_[nodePos]->numberOfKeys;
        uint32_t nChilds = nodes_[nodePos]->numberOfChildren;
        if (!nodes_[nodePos]->isKeyCountsValid(t_, nodePos == rootPos_) || !nodes_[nodePos]->isChildrenCountsValid(t_) ||
            !nodes_[nodePos]->isAscending()) {
            isOK = false;
            return currLevel;
        }
        // Check bounds of the keys of curr node
        // Если первый элемент данной ноды меньше текущего минимума или последний элемент данной ноды меньше текущего максимума
        if (nodes_[nodePos]->keys[0] < currMin || nodes_[nodePos]->keys[nNodeKeys - 1] > currMax) {
            isOK = false;
            return currLevel;
        }

        if (!nodes_[nodePos]->isLeaf) {
            int leafLevel = 0;
            for (int i = 0; i < nChilds; ++i) {
                int childPos = find(nodes_, N_, nodes_[nodePos]->childrenIndexes[i]);
                if (childPos == -1) {
                    isOK = false;
                    return currLevel;
                }
                if (i == 0) {
                    leafLevel = dfs(nodes_[nodePos]->childrenIndexes[i], currLevel + 1, currMin, nodes_[nodePos]->keys[i]);
                } else if (i == nChilds - 1) {
                    if (dfs(nodes_[nodePos]->childrenIndexes[i], currLevel + 1, nodes_[nodePos]->keys[i - 1], currMax) != leafLevel) {
                        // Если первый элемент последнего ребенка больше текущего максимума или левел
                        isOK = false;
                        return currLevel;
                    }
                } else if (dfs(nodes_[nodePos]->childrenIndexes[i], currLevel + 1,
                               nodes_[nodePos]->keys[i - 1], nodes_[nodePos]->keys[i]) != leafLevel) {
                    isOK = false;
                    return currLevel;
                }
            }
            return leafLevel;
        }
        return currLevel;
    }

public:
    BTreeValidator(BTreeNode **nodes, uint32_t N, uint32_t t, uint32_t rootIndex) : nodes_(nodes), N_(N), t_(t), rootIndex_(rootIndex) {
        rootPos_ = find(nodes_, N_, rootIndex);
    };

    bool isValidBTree() {
        if (rootPos_ == -1 || nodes_[rootPos_]->numberOfKeys > 2 * t_ - 1) {
            return false;
        }
        dfs(rootIndex_, 0);
        return isOK;
    }
};

#endif //ISBTREE_VALIDATOR_H
