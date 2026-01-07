## AVL Tree Insertion Procedure

To insert a node into an **AVL Tree**, we first perform a normal **Binary Search Tree (BST)** insertion and then restore balance if required. The complete procedure is outlined below.

---

### Step i — Perform Normal BST Insertion

Insert the new key following standard BST insertion rules:
- Keys smaller than the current node go to the left subtree
- Keys larger than the current node go to the right subtree

---

### Step ii — Update Height of the Ancestor Node

After insertion, update the height of each ancestor node while backtracking in the recursion.

```cpp
root->height = 1 + max(getHeight(root->left), getHeight(root->right));
```
The height of a node is defined as:  
```1 + maximum height of its left and right subtrees```

---

### Step iii — Compute Balance Factor
The balance factor of a node determines whether it is balanced.

```cpp
int balance = getBalance(root);
```
---

### Step iv — Handle the Four Imbalance Cases
Depending on the balance factor and the inserted key, one of the following four cases may occur.

#### Case I — LL (Left-Left) Imbalance
Occurs when:
- The tree is left-heavy, and
- The key is inserted into the left subtree of the left child

**Fix**: Perform a single right rotation.

```cpp
if (balance > 1 && key < root->left->key)
    return rightRotate(root);
```
#### Case II — RR (Right-Right) Imbalance
Occurs when:
- The tree is right-heavy, and
- The key is inserted into the right subtree of the right child

**Fix**: Perform a single left rotation.

```cpp
if (balance < -1 && key > root->right->key)
    return leftRotate(root);
```

#### Case III — LR (Left-Right) Imbalance
Occurs when:
- The tree is left-heavy, and
- The key is inserted into the right subtree of the left child

**Fix**:
- Perform a left rotation on the left child
- Perform a right rotation on the root

```cpp
if (balance > 1 && key > root->left->key) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
}
```

#### Case IV — RL (Right-Left) Imbalance
Occurs when:
- The tree is right-heavy, and
- The key is inserted into the left subtree of the right child

**Fix**:
- Perform a right rotation on the right child
- Perform a left rotation on the root

```cpp
if (balance < -1 && key < root->right->key) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
}
```

---

> [!IMPORTANT]
> This ensures that the AVL Tree maintains a height of **O(log n)** after every insertion.