#include <iostream>
using namespace std;

// Class to model a node of the BST
class TNode {
public:
    int data;
    TNode* left;
    TNode* right;

    // Default constructor
    TNode() : data(0), left(nullptr), right(nullptr) {}

    // Parameterized constructor
    TNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Class to create and manage the BST
class BST {
public:
    TNode* root;

    // Default constructor
    BST() : root(nullptr) {}

    // Check if the BST is empty
    bool isEmpty() {
        return root == nullptr;
    }

    // Insert a node with a given value
    void insert(TNode*& node, int value) {
        if (node == nullptr) {
            node = new TNode(value);
        } else if (value < node->data) {
            insert(node->left, value);
        } else if (value > node->data) {
            insert(node->right, value);
        }
    }

    // Search for a node with a given value
    bool search(TNode* node, int value) {
        if (node == nullptr) {
            return false;
        } else if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    // Find the minimum value in a subtree
    TNode* findmin(TNode* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Delete a node with a given value
    void delete_node(TNode*& node, int value) {
        if (node == nullptr) {
            return;
        } else if (value < node->data) {
            delete_node(node->left, value);
        } else if (value > node->data) {
            delete_node(node->right, value);
        } else {
            // Node with one or no child
            if (node->left == nullptr) {
                TNode* temp = node->right;
                delete node;
                node = temp;
            } else if (node->right == nullptr) {
                TNode* temp = node->left;
                delete node;
                node = temp;
            } else {
                // Node with two children
                TNode* temp = findmin(node->right);
                node->data = temp->data;
                delete_node(node->right, temp->data);
            }
        }
    }

    // Get the parent of a given node
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

    // In-order traversal to display values in ascending order
    void in_orderTraverse(TNode* node) {
        if (node != nullptr) {
            in_orderTraverse(node->left);
            cout << node->data << " ";
            in_orderTraverse(node->right);
        }
    }
};

// Main function to test the implementation
int main() {
    BST tree;

    // Insert values
    tree.insert(tree.root, 50);
    tree.insert(tree.root, 30);
    tree.insert(tree.root, 70);
    tree.insert(tree.root, 20);
    tree.insert(tree.root, 40);
    tree.insert(tree.root, 60);
    tree.insert(tree.root, 80);

    // Display values in ascending order
    cout << "In-order Traversal: ";
    tree.in_orderTraverse(tree.root);
    cout << endl;

    // Search for a value
    int searchValue = 40;
    if (tree.search(tree.root, searchValue)) {
        cout << "Value " << searchValue << " found in the tree.\n";
    } else {
        cout << "Value " << searchValue << " not found in the tree.\n";
    }

    // Delete a node
    int deleteValue = 30;
    tree.delete_node(tree.root, deleteValue);
    cout << "In-order Traversal after deleting " << deleteValue << ": ";
    tree.in_orderTraverse(tree.root);
    cout << endl;
    TNode* n = tree.findmin(tree.root);
    cout << "Min value = " << n->data;
    cout << endl;

    return 0;
}
