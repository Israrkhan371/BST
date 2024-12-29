#include <iostream>
using namespace std;

class TNode {
public:
    int data;
    TNode* left;
    TNode* right;

    // Constructor
    TNode(int value) {
        data = value;
        left = right = nullptr;
    }
};

// Function to insert a node in the first available position (generic tree) without using a queue
void insert(TNode* root, int value) {
    // We perform a recursive DFS (pre-order) to find the first available spot
    if (root == nullptr) {
        root = new TNode(value);  // This won't work for the root since root is passed by value
        return;
    }

    // Check left child first
    if (root->left == nullptr) {
        root->left = new TNode(value);
        return;
    }
    
    // If the left child is not empty, check the right child
    if (root->right == nullptr) {
        root->right = new TNode(value);
        return;
    }

    // Recurse on the left and right subtrees
    insert(root->left, value);  // Left first
    insert(root->right, value);  // Right after
}

// Function to print the tree (in-order traversal)
void inorder(TNode* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    TNode* root = new TNode(10);
    root->left = new TNode(20);
    root->right = new TNode(30);
    root->left->left = new TNode(40);

    // Insert a new node
    insert(root, 50);

    // Print the tree after insertion
    cout << "In-order traversal after insertion: ";
    inorder(root);
    cout << endl;

    return 0;
}
