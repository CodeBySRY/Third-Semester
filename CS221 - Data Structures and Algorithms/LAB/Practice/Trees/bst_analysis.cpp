#include <iostream>
using namespace std;

// Node structure for Binary Search Tree
struct TreeNode {
    int data;           // Value stored in node
    TreeNode* left;     // Pointer to left child
    TreeNode* right;    // Pointer to right child
    
    // Constructor to initialize node
    TreeNode(int value) {
        data = value;
        left = right = NULL;
    }
};

// Class for Binary Search Tree operations
class BST {
private:
    TreeNode* root;     // Root of the BST
    
    // Helper function to insert a value recursively
    TreeNode* insertRecursive(TreeNode* node, int value) {
        // If current position is empty, create new node
        if (node == NULL) {
            return new TreeNode(value);
        }
        
        // BST property: smaller values go left, larger values go right
        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }
        
        return node;
    }
    
    int countLeafNodes(TreeNode* node) {
        // Base case: empty node
        if (node == NULL) {
            return 0;
        }
        
        // Base case: leaf node (no children)
        if (node->left == NULL && node->right == NULL) {
            return 1;
        }
        
        // Recursive case: node has children
        // Count leaves in left subtree + count leaves in right subtree
        return countLeafNodes(node->left) + countLeafNodes(node->right);
    }
    
    // Helper function to count internal nodes recursively
    int countInternalNodes(TreeNode* node) {
        // Base case: empty node or leaf node
        if (node == NULL || (node->left == NULL && node->right == NULL)) {
            return 0;
        }
        
        // Current node is internal (has at least one child)
        // Count it and recursively count internal nodes in subtrees
        return 1 + countInternalNodes(node->left) + countInternalNodes(node->right);
    }
    
        void InorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    
    InorderTraversal(root->left);
    cout << root->data << "->";
    InorderTraversal(root->right);
    
}

    void DeleteTree(TreeNode*& root) { // pass the pointer by reference, so that the original pointer can be modified (avoid segmentation faults)
        if (root == NULL) {
            return;
        }
        
        DeleteTree(root->left);
        DeleteTree(root->right);
        delete root;
        root = NULL; // set the pointer to NULL so that the dangling pointer does not point to any garbage value;
    }
    
public:
    // Constructor initializes empty tree
    BST() {
        root = NULL;
    }
    
    // Public method to insert value into BST
    void insert(int value) {
        root = insertRecursive(root, value);
    }
    
    // Public method to count leaf nodes
    int getLeafCount() {
        return countLeafNodes(root);
    }
    
    // Public method to count internal nodes
    int getInternalCount() {
        return countInternalNodes(root);
    }
    
    // Public method to get root value
    int getRootValue() {
        if (root == NULL) {
            cout << "Tree is empty!" << endl;
            return -1; // Return -1 for empty tree
        }
        else {
            return root->data;
        }
        
    }
    
    void getInorderTraversal() {
        InorderTraversal(root);
    }
    
    
    
};

int main() {
    BST tree;
    int n, value;
    
    // Get number of elements from user
    cout << "Enter number of elements to insert: ";
    cin >> n;
    
    // Insert elements into BST
    cout << "Enter " << n << " integer elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> value;
        tree.insert(value);
    }
    
    // Display required information
    cout << "\n--- BST Analysis ---" << endl;
    cout << "Inorder Traversal: ";
    tree.getInorderTraversal();
    cout << endl;
    cout << "1. Root node value: " << tree.getRootValue() << endl;
    cout << "2. Number of leaf nodes: " << tree.getLeafCount() << endl;
    cout << "3. Number of internal nodes: " << tree.getInternalCount() << endl;
    
    return 0;
}