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
    
    // Insert a value recursively
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
    
    // Helper function for inorder traversal (Left-Root-Right)
    void inorderRecursive(TreeNode* node) {
        if (node == NULL) {
            return;
        }
        
        // Recursively traverse left subtree
        inorderRecursive(node->left);
        
        // Visit current node
        cout << node->data << " ";
        
        // Recursively traverse right subtree
        inorderRecursive(node->right);
    }
    
    // Helper function to create mirror image recursively
    TreeNode* mirrorRecursive(TreeNode* node) {
        // Base case: empty node
        if (node == NULL) {
            return NULL;
        }
        
        // Recursively mirror left and right subtrees
        TreeNode* mirroredLeft = mirrorRecursive(node->left);
        TreeNode* mirroredRight = mirrorRecursive(node->right);
        
        // Swap the mirrored subtrees
        node->left = mirroredRight;
        node->right = mirroredLeft;
        
        return node;
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
    
    // Public method for inorder traversal
    void inorderTraversal() {
        inorderRecursive(root);
        cout << endl;
    }
    
    // Public method to create mirror image
    void mirror() {
        root = mirrorRecursive(root);
    }
    
    // Getter for root (not used in main but useful for testing)
    TreeNode* getRoot() {
        return root;
    }
};

int main() {
    BST tree;
    int n, value;
    
    // Get number of elements from user
    cout << "Enter number of nodes: ";
    cin >> n;
    
    // Insert elements into BST
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        tree.insert(value);
    }
    
    // Display original BST using inorder traversal
    cout << "\nInorder traversal of original BST: ";
    tree.inorderTraversal();
    
    // Create mirror image of BST
    tree.mirror();
    
    // Display mirror BST using inorder traversal
    cout << "Inorder traversal of mirror image BST: ";
    tree.inorderTraversal();
    
    return 0;
}