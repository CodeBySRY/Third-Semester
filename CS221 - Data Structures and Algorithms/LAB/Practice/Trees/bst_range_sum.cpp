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

// Function to calculate sum of all nodes in range [L, R]
// This uses the BST property to optimize the traversal
// Parameters:
//   root: current node being processed
//   L: lower bound of range (inclusive)
//   R: upper bound of range (inclusive)
// Returns: sum of all node values within [L, R]
int rangeSum(Node* root, int L, int R) {
    // Base case: if current node is NULL, return 0
    // No contribution to sum from empty subtree
    if (root == NULL) {
        return 0;
    }
    
    // Initialize sum to 0
    int sum = 0;
    
    // OPTIMIZATION 1: Check if current node is less than L
    // If current node < L, then ALL nodes in left subtree are also < L
    // (due to BST property: left < root)
    // So we can skip the entire left subtree
    if (root->data < L) {
        // Only explore right subtree (which might have values >= L)
        return rangeSum(root->right, L, R);
    }
    
    // OPTIMIZATION 2: Check if current node is greater than R
    // If current node > R, then ALL nodes in right subtree are also > R
    // (due to BST property: root < right)
    // So we can skip the entire right subtree
    if (root->data > R) {
        // Only explore left subtree (which might have values <= R)
        return rangeSum(root->left, L, R);
    }
    
    // If we reach here, it means L <= root->data <= R
    // Current node is within range, so include it in sum
    sum = root->data;
    
    // Recursively explore both subtrees
    // Left subtree might have values >= L (and <= current node)
    // Right subtree might have values <= R (and >= current node)
    sum += rangeSum(root->left, L, R);
    sum += rangeSum(root->right, L, R);
    
    return sum;
}

// Helper function to perform inorder traversal and display tree
// This helps visualize the BST structure
void inorderTraversal(Node* root) {
    if (root == NULL) return;
    
    // Traverse left subtree
    inorderTraversal(root->left);
    
    // Print current node
    cout << root->data << " ";
    
    // Traverse right subtree
    inorderTraversal(root->right);
}

int main() {
    // Initialize an empty BST
    Node* root = NULL;
    int n, value;
    
    // Get number of nodes from user
    cout << "Enter number of nodes in BST: ";
    cin >> n;
    
    // Build the BST by inserting values
    cout << "Enter " << n << " integer values:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> value;
        root = insert(root, value);
    }
    
    // Display the BST in sorted order (inorder traversal)
    cout << "\nBST (in sorted order): ";
    inorderTraversal(root);
    cout << endl;
    
    // Get the range [L, R] from user
    int L, R;
    cout << "\nEnter the range [L, R]:" << endl;
    cout << "Enter L (lower bound): ";
    cin >> L;
    cout << "Enter R (upper bound): ";
    cin >> R;
    
    // Calculate and display the range sum
    int result = rangeSum(root, L, R);
    
    cout << "\n========================================" << endl;
    cout << "Range: [" << L << ", " << R << "]" << endl;
    cout << "Sum of nodes in range: " << result << endl;
    cout << "========================================" << endl;
    
    return 0;
}