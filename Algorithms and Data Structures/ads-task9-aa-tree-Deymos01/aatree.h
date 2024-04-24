#ifndef AATREE_AATREE_H
#define AATREE_AATREE_H

class AATree {
private:
    struct Node {
        int val;
        int level;
        Node *left;
        Node *right;

        static Node emptyNode;

        Node(int val, int level, Node *left, Node *right) : val(val), level(level), left(left), right(right) {}

        static Node *skew(Node *node) {
            if (node == &Node::emptyNode) { return &Node::emptyNode; }
            if (node->left == &Node::emptyNode) { return node; }
            if (node->left->level == node->level) {
                Node *left = node->left;
                node->left = left->right;
                left->right = node;
                return left;
            }
            return node;
        }

        static Node *split(Node *node) {
            if (node == &Node::emptyNode) { return &Node::emptyNode; }
            if (node->right == &Node::emptyNode || node->right->right == &Node::emptyNode) { return node; }
            if (node->level == node->right->right->level) {
                Node *right = node->right;
                node->right = right->left;
                right->left = node;
                ++right->level;
                return right;
            }
            return node;
        }

        static Node *decreaseLevel(Node *node) {
            int shouldBe = std::min(node->left->level, node->right->level) + 1;
            if (shouldBe < node->level) {
                node->level = shouldBe;
                if (node->right->level > shouldBe) {
                    node->right->level = shouldBe;
                }
            }
            return node;
        }

        ~Node() {
            if (left != &emptyNode) { delete left; }
            if (right != &emptyNode) { delete right; }
        }
    };

    Node *root;
public:
    AATree() : root(&Node::emptyNode) {}

    ~AATree() {
        if (root != &Node::emptyNode) delete root;
    };

    [[nodiscard]] int getRootLevel() const {
        return root->level;
    }

    Node *insert(int val, Node *node = nullptr) {
        if (node == &Node::emptyNode) {
            return new Node(val, 1, &Node::emptyNode, &Node::emptyNode);
        }
        if (!node) { node = root; }
        if (root == &Node::emptyNode) {
            root = new Node(val, 1, &Node::emptyNode, &Node::emptyNode);
            return root;
        }

        if (val <= node->val) {
            node->left = insert(val, node->left);
        } else {
            node->right = insert(val, node->right);
        }

        if (node == root) {
            root = Node::skew(root);
            root = Node::split(root);
            return root;
        }

        node = Node::skew(node);
        node = Node::split(node);
        return node;
    }

    bool find(int val) const {
        Node *node = root;
        while (node != &Node::emptyNode) {
            if (val == node->val) { return true; }
            if (val < node->val) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return false;
    }

    Node *erase(int val, Node *node = nullptr) {
        if (!node) { node = root; }
        if (node == &Node::emptyNode) { return &Node::emptyNode; }
        if (val < node->val) {
            node->left = erase(val, node->left);
        } else if (val > node->val) {
            node->right = erase(val, node->right);
        } else {
            if (node->left == &Node::emptyNode && node->right == &Node::emptyNode) {
                if (node == root) { root = &Node::emptyNode; }
                delete node;
                return &Node::emptyNode;
            }
            if (node->left == &Node::emptyNode) {
                if (node == root) {
                    root = node->right;
                    node->right = nullptr;
                    delete node;
                    return root;
                }

                Node *right = node->right;
                node->right = nullptr;
                delete node;
                return right;
            }
            if (node->right == &Node::emptyNode) {
                if (node == root) {
                    root = node->left;
                    node->left = nullptr;
                    delete node;
                    return root;
                }
                Node *left = node->left;
                node->left = &Node::emptyNode;
                delete node;
                return left;
            }
            Node *minNode = node->right;
            while (minNode->left != &Node::emptyNode) {
                minNode = minNode->left;
            }
            node->val = minNode->val;
            node->right = erase(minNode->val, node->right);
        }
        node = Node::decreaseLevel(node);
        if (node == root) {
            root = Node::skew(node);
            root->right = Node::skew(root->right);
            if (root->right != &Node::emptyNode) {
                root->right->right = Node::skew(root->right->right);
            }
            root = Node::split(root);
            root->right = Node::split(root->right);
            return root;
        }
        node = Node::decreaseLevel(node);
        node = Node::skew(node);
        node->right = Node::skew(node->right);
        if (node->right != &Node::emptyNode) {
            node->right->right = Node::skew(node->right->right);
        }
        node = Node::split(node);
        node->right = Node::split(node->right);
        return node;
    }
};

AATree::Node AATree::Node::emptyNode = AATree::Node(0, 0, &Node::emptyNode, &Node::emptyNode);

#endif  // AATREE_AATREE_H
