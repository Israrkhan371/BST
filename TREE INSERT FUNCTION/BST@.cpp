#include <iostream>
using namespace std;

// Class to model a node of the BST
class TNode {
public:
    int data;
    TNode* left;
    TNode* right;

    TNode() : data(0), left(nullptr), right(nullptr) {}
    TNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Class to create and manage the BST
class BST {
public:
    TNode* root;

    BST() : root(nullptr) {}

    ~BST() {
        destroyTree(root);
    }

    void destroyTree(TNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void insert(TNode*& node, int value) {
        if (node == nullptr) {
            node = new TNode(value);
        } else if (value < node->data) {
            insert(node->left, value);
        } else if (value > node->data) {
            insert(node->right, value);
        }
    }

    void insert(int value) {
        insert(root, value);
    }

    bool search(TNode* node, int value) {
        if (node == nullptr) {
            return false;
        } else if (node->data == value) {
            return true;
        } else if (value < node->data) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    TNode* findmin(TNode* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TNode* findmax(TNode* node) {
        while (node && node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    void in_orderTraverse(TNode* node) {
        if (node != nullptr) {
            in_orderTraverse(node->left);
            cout << node->data << " ";
            in_orderTraverse(node->right);
        }
    }
};

// Non-member function to print the path from root to a given node
void printPath(TNode* node, int value) {
    if (node == nullptr) {
        cout << "Value not found in the tree.\n";
        return;
    }
    cout << node->data << " ";
    if (value < node->data) {
        printPath(node->left, value);
    } else if (value > node->data) {
        printPath(node->right, value);
    }
}

// Non-member function to find the maximum value in the BST
int findMaxValue(TNode* node) {
    if (node == nullptr) {
        throw runtime_error("Tree is empty.");
    }
    while (node->right != nullptr) {
        node = node->right;
    }
    return node->data;
}

// Non-member function to find the sibling of a given node
int findSibling(TNode* node, TNode* parent, int value) {
    if (node == nullptr || parent == nullptr) {
        cout << "Value not found or has no sibling.\n";
        return -1; // Indicates no sibling
    }

    if (parent->left != nullptr && parent->left->data == value) {
        if (parent->right != nullptr) {
            return parent->right->data;
        }
    } else if (parent->right != nullptr && parent->right->data == value) {
        if (parent->left != nullptr) {
            return parent->left->data;
        }
    }

    cout << "No sibling exists for the given node.\n";
    return -1; // Indicates no sibling
}

// Helper function to get the parent of a given node
TNode* getParent(TNode* node, int value) {
    if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
        return nullptr;
    }

    if ((node->left != nullptr && node->left->data == value) ||
        (node->right != nullptr && node->right->data == value)) {
        return node;
    }

    if (value < node->data) {
        return getParent(node->left, value);
    } else {
        return getParent(node->right, value);
    }
}

// Main function to test the implementation
int main() {
    BST tree;

    // Insert values into the BST
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "In-order Traversal: ";
    tree.in_orderTraverse(tree.root);
    cout << endl;

    // Task 1: Print the path of a node
    int target = 40;
    cout << "Path to node " << target << ": ";
    printPath(tree.root, target);
    cout << endl;

    // Task 2: Find the maximum value in the BST
    try {
        int maxValue = findMaxValue(tree.root);
        cout << "Maximum value in the BST: " << maxValue << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Task 3: Find the sibling of a node
    target = 40;
    TNode* parent = getParent(tree.root, target);
    int sibling = findSibling(tree.root, parent, target);
    if (sibling != -1) {
        cout << "Sibling of node " << target << ": " << sibling << endl;
    }

    return 0;
}
