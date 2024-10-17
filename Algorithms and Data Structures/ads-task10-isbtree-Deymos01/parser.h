#ifndef ISBTREE_PARSER_H
#define ISBTREE_PARSER_H

#include <fstream>
#include <cstring>
#include <iostream>
#include "BTreeNode.h"

BTreeNode *parseNode(std::ifstream &inFile) {
    auto *node = new BTreeNode();
    char type[8];
    memset(type, '\0', 8);
    inFile >> type;
    inFile.ignore(3);
    inFile >> node->nodeIndex;
    inFile.ignore(2);
    inFile >> node->numberOfKeys;
    inFile.ignore(2);
    node->keys = new int32_t[node->numberOfKeys];
    for (uint32_t i = 0; i < node->numberOfKeys; ++i) {
        inFile >> node->keys[i];
        inFile.ignore(1);
    }

    if (strcmp(type, "leaf:") == 0) {
        node->isLeaf = true;
        if (inFile.peek() != '\n') {
            delete node;
            return nullptr;
        }
    } else if (strcmp(type, "branch:") == 0) {
        node->isLeaf = false;
        inFile.ignore(2);
        inFile >> node->numberOfChildren;
        inFile.ignore(2);
        node->childrenIndexes = new uint32_t[node->numberOfChildren];
        for (uint32_t i = 0; i < node->numberOfChildren; ++i) {
            inFile >> node->childrenIndexes[i];
            inFile.ignore(1);
        }
    } else {
        delete node;
        return nullptr;
    }
    return node;
}

#endif  // ISBTREE_PARSER_H
