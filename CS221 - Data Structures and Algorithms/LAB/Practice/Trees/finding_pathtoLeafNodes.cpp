#include <iostream>
using namespace std;

// Definition of a single node in the Binary Search Tree
struct Node {
    int data;           // Value stored in the node
    Node* left;         // Pointer to the left child
    Node* right;        // Pointer to the right child
    
    // Constructor to initialize a new node with given value
    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

// Function to insert a new value into the BST
// Returns the root of the modified tree
Node* insert(Node* root, int value) {
    // Base case: if tree is empty or we reached a NULL position
    // Create and return a new node
    if (root == NULL) {
        return new Node(value);
    }
    
    // Recursive case: traverse left or right based on BST property
    // If value is smaller, insert in left subtree
    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    // If value is greater, insert in right subtree
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    // If value already exists, do nothing (no duplicates)
    
    return root;
}

// Helper function to print a single path stored in the array
// Prints from index 0 to pathLength-1 with arrow separators
void printPath(int path[], int pathLength) {
    cout << "Path: ";
    for (int i = 0; i < pathLength; i++) {
        cout << path[i];
        // Add arrow separator between nodes, but not after the last node
        if (i < pathLength - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

// Recursive function to find and print all root-to-leaf paths
// Parameters:
//   node: current node being processed
//   path: array storing the current path from root to this node
//   pathLength: number of nodes in the current path
void printAllPaths(Node* node, int path[], int pathLength) {
    // Base case: if current node is NULL, return immediately
    if (node == NULL) {
        return;
    }
    
    // Add current node's data to the path array
    path[pathLength] = node->data;
    pathLength++;  // Increment path length after adding current node
    
    // Check if current node is a leaf node
    // A leaf node has no left child and no right child
    if (node->left == NULL && node->right == NULL) {
        // We've reached a leaf, so print the complete path
        printPath(path, pathLength);
    }
    else {
        // Not a leaf node, so continue traversing both subtrees
        // Recursively traverse left subtree
        printAllPaths(node->left, path, pathLength);
        
        // Recursively traverse right subtree
        printAllPaths(node->right, path, pathLength);
    }
    
    // Backtracking happens automatically when function returns
    // The pathLength parameter is passed by value, so it resets
    // when we return to the previous recursive call
}

// Wrapper function to initiate the path printing process
void findAllPaths(Node* root) {
    // Handle edge case: empty tree
    if (root == NULL) {
        cout << "Tree is empty!" << endl;
        return;
    }
    
    // Array to store the current path during traversal
    // Maximum possible height of BST is the number of nodes
    // Allocating 1000 as a safe upper limit for path storage
    int path[1000];
    
    // Start the recursive traversal from root with empty path
    printAllPaths(root, path, 0);
}

int main() {
    // Initialize an empty BST
    Node* root = NULL;
    
    // Build the example BST from the problem statement
    //           50
    //          /  \
    //        30    70
    //       / \    / \
    //      20 40  60 80
    
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    cout << "All paths from root to leaf nodes:" << endl;
    cout << "====================================" << endl;
    
    // Find and print all root-to-leaf paths
    findAllPaths(root);
    
    return 0;
}