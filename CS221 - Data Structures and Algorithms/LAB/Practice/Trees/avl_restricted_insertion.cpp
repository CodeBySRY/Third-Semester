#include <iostream>
using namespace std;

struct AVLNode {
    int data;
    int height;
    AVLNode* left;
    AVLNode* right;
    
    AVLNode(int value) {
        data = value;
        height = 0;
        left = right = NULL;
    }
};

class AVLTree {
private:
    AVLNode* root;
    int imbalanceCount;
    
    int getHeight(AVLNode* node) {
        if (node == NULL) return -1;
        return node->height;
    }
    
    int getBalanceFactor(AVLNode* node) {
        if (node == NULL) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    
    void updateHeight(AVLNode* node) {
        if (node == NULL) return;
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
    
    AVLNode* copyTree(AVLNode* node) {
        if (node == NULL) return NULL;
        AVLNode* newNode = new AVLNode(node->data);
        newNode->height = node->height;
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }
    
    void deleteTree(AVLNode* node) {
        if (node == NULL) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
    AVLNode* insertBST(AVLNode* node, int value) {
        if (node == NULL) return new AVLNode(value);
        
        if (value < node->data) {
            node->left = insertBST(node->left, value);
        } else if (value > node->data) {
            node->right = insertBST(node->right, value);
        } else {
            return node;
        }
        
        updateHeight(node);
        int balance = getBalanceFactor(node);
        
        // CORRECTED: Check if |BF| > 1 (not just == 2 or == -2)
        if (balance > 1 || balance < -1) {
            imbalanceCount++;
        }
        
        return node;
    }
    
    void inorderDisplay(AVLNode* node) {
        if (node == NULL) return;
        inorderDisplay(node->left);
        cout << node->data << " ";
        inorderDisplay(node->right);
    }
    
public:
    AVLTree() {
        root = NULL;
        imbalanceCount = 0;
    }
    
    ~AVLTree() {
        deleteTree(root);
    }
    
    bool insert(int value) {
        AVLNode* backup = copyTree(root);
        imbalanceCount = 0;
        root = insertBST(root, value);
        
        if (imbalanceCount > 1) {
            deleteTree(root);
            root = backup;
            return false;
        } else {
            deleteTree(backup);
            return true;
        }
    }
    
    void displayInorder() {
        if (root == NULL) {
            cout << "Tree is empty!" << endl;
        } else {
            cout << "Tree (inorder): ";
            inorderDisplay(root);
            cout << endl;
        }
    }
};

int main() {
    AVLTree avl;
    int value;
    
    cout << "AVL Tree with Special Insertion Rule" << endl;
    cout << "Keep entering values. Program stops if insertion causes multiple imbalances.\n" << endl;
    
    
    cout << "Insert values in a balanced pattern (middle-first, alternating, etc.):" << endl << endl;
    
    while (true) {
        cout << "Enter value: ";
        cin >> value;
        
        if (avl.insert(value)) {
            cout << "Inserted " << value << " successfully.\n" << endl;
        } else {
            cout << "\nINSERTION REJECTED! Value " << value << " causes multiple imbalances." << endl;
            cout << "Program stopped.\n" << endl;
            break;
        }
    }
    
    cout << "Final tree (inorder): ";
    avl.displayInorder();
    
    return 0;
}