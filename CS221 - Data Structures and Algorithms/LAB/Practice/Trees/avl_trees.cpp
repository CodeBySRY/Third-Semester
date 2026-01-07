#include <iostream>
using namespace std;

// AVL Tree Node structure
struct AVLNode {
    int data;           // Value stored in node
    int height;         // Height of node (for balance calculation)
    int rebalanceCount; // Counter for rebalancing activities
    AVLNode* left;      // Pointer to left child
    AVLNode* right;     // Pointer to right child
    
    // Constructor to initialize node
    AVLNode(int value) {
        data = value;
        height = 0;     // New node has height 0 (leaf)
        rebalanceCount = 0;
        left = right = NULL;
    }
};

// AVL Tree Class
class AVLTree {
private:
    AVLNode* root;      // Root of the AVL tree
    
    // Helper: Get height of a node (handles null case)
    int getHeight(AVLNode* node) {
        if (node == NULL) {
            return -1;  // Empty node has height -1
        } else {
            return node->height;
        }
    }
    
    // Helper: Calculate balance factor (height difference between subtrees)
    // Positive = left heavy, Negative = right heavy
    int getBalanceFactor(AVLNode* node) {
        if (node == NULL) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    
    // Helper: Update height based on children's heights
    void updateHeight(AVLNode* node) {
        if (node == NULL) return;
        
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        
        // Height is max of children's heights + 1
        if (leftHeight > rightHeight) {
            node->height = leftHeight + 1;
        } else {
            node->height = rightHeight + 1;
        }
    }
    
    // Right Rotation (for left-left imbalance)
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        // Perform rotation
        x->right = y;
        y->left = T2;
        
        // Update heights after rotation
        updateHeight(y);
        updateHeight(x);
        
        return x; // New root after rotation
    }
    
    // Left Rotation (for right-right imbalance)
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        // Perform rotation
        y->left = x;
        x->right = T2;
        
        // Update heights after rotation
        updateHeight(x);
        updateHeight(y);
        
        return y; // New root after rotation
    }
    
    // Balance the tree and increment rebalance counter when needed
    // This function checks if a node is unbalanced and performs rotations
    AVLNode* balanceTree(AVLNode* node) {
        if (node == NULL) return node;
        
        // Update height of current node first
        updateHeight(node);
        
        // Calculate balance factor to check if rebalancing is needed
        int balance = getBalanceFactor(node);
        
        // KEY FIX: Only increment counter if this node is actually unbalanced
        // A node is unbalanced when |balance factor| > 1
        // This means it needs rebalancing through rotations
        if (balance > 1 || balance < -1) {
            // This node IS unbalanced, so increment its counter
            node->rebalanceCount++;
        }
        
        // Now perform the appropriate rotations based on imbalance type
        
        // Case 1: Left-Left (LL) - node is left heavy, left child is also left heavy or balanced
        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }
        
        // Case 2: Left-Right (LR) - node is left heavy, but left child is right heavy
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Case 3: Right-Right (RR) - node is right heavy, right child is also right heavy or balanced
        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }
        
        // Case 4: Right-Left (RL) - node is right heavy, but right child is left heavy
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node; // No rotation needed, tree is balanced
    }
    
    // Recursive insertion with balancing
    // Inserts a value and rebalances the tree on the way back up
    AVLNode* insertRecursive(AVLNode* node, int value) {
        // Step 1: Standard BST insertion
        if (node == NULL) {
            return new AVLNode(value);
        }
        
        // Insert in left subtree if value is smaller
        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        } 
        // Insert in right subtree if value is larger
        else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        } 
        // Duplicate values not allowed
        else {
            return node;
        }
        
        // Step 2: After insertion, balance this node on the way back up
        // This checks if current node became unbalanced due to insertion
        // and performs rotations if needed
        return balanceTree(node);
    }
    
    // Inorder traversal to display rebalance counts
    // Visits nodes in sorted order (left, root, right)
    void displayRebalanceCounts(AVLNode* node) {
        if (node == NULL) return;
        
        // Traverse left subtree
        displayRebalanceCounts(node->left);
        
        // Display current node's rebalance count
        cout << "Node " << node->data << " was rebalanced " 
             << node->rebalanceCount << " time";
        if (node->rebalanceCount != 1) {
            cout << "s";
        }
        cout << endl;
        
        // Traverse right subtree
        displayRebalanceCounts(node->right);
    }
    
    // Helper to delete tree (clean up memory)
    void deleteTree(AVLNode* node) {
        if (node == NULL) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
public:
    // Constructor
    AVLTree() {
        root = NULL;
    }
    
    // Destructor
    ~AVLTree() {
        deleteTree(root);
    }
    
    // Public method to insert value
    void insert(int value) {
        root = insertRecursive(root, value);
    }
    
    // Public method to display rebalance counts
    void displayRebalanceStats() {
        if (root == NULL) {
            cout << "Tree is empty!" << endl;
            return;
        }
        
        cout << "\n--- Rebalancing Statistics ---" << endl;
        displayRebalanceCounts(root);
    }
    
    // Get height of tree
    int getTreeHeight() {
        return getHeight(root);
    }
    
    // Check if tree is balanced at root level
    bool isBalanced() {
        int balance = getBalanceFactor(root);
        if (balance < 0) balance = -balance; // Get absolute value
        return balance <= 1;
    }
};

// Main function to demonstrate AVL Tree with rebalancing tracking
int main() {
    AVLTree avl;
    int n, value;
    
    // Get number of elements
    cout << "Enter number of elements to insert: ";
    cin >> n;
    
    // Insert elements one by one
    cout << "Enter " << n << " integer elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> value;
        avl.insert(value);
    }
    
    // Display rebalancing statistics for all nodes
    avl.displayRebalanceStats();
    
    // Additional validation information
    cout << "\n--- Validation ---" << endl;
    cout << "Tree height: " << avl.getTreeHeight() << endl;
    cout << "Tree is ";
    if (avl.isBalanced()) {
        cout << "balanced";
    } else {
        cout << "NOT balanced";
    }
    cout << endl;
    
    return 0;
}