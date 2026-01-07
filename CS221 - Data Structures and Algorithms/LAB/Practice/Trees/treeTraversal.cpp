#include <iostream>
using namespace std;

struct Tree {
    int data;
    Tree* left;
    Tree* right;
    Tree(const int& num) {
        data = num;
        left = right = NULL;
    }
};

void InorderTraversal(Tree* node) {
    if (node == NULL) {
        return;
    }
    InorderTraversal(node->left);
    cout << node->data << "->";
    InorderTraversal(node->right);
}

void DeleteTree(Tree*& node) {  // Take reference to pointer, since it needs to be modified
    if (node == NULL) {
        return;
    }
    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
    node = NULL;  // Set to NULL after deletion
}

int main() {
    cout << "Hello World!" << endl;
    Tree* root = new Tree(5);
    root->left = new Tree(10);
    root->right = new Tree(15);
    root->left->left = new Tree(25);
    root->right->left = new Tree(25);
    root->right->right = new Tree(17);

    InorderTraversal(root);
    cout << endl;

    DeleteTree(root);
    // Now root is NULL, so this is safe
    InorderTraversal(root);  // Will print nothing (safe)
    cout << "Tree deleted successfully!" << endl;

    return 0;
}