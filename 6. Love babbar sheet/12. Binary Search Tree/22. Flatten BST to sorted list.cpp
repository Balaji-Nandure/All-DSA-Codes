/**
 * Problem: Flatten BST to Sorted List (Increasing Order)
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Convert Binary tree into Doubly Linked List", we maintained bidirectional `left` and `right` links.
 * - Here, we flatten the tree into a strictly RIGHT-SKEWED singly linked list of tree nodes:
 *   every node's `left` pointer must be set to `nullptr`, and `right` must point to its Inorder successor.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Inorder Traversal with Dummy Head Pointer:
 *   - Create a dummy sentinel node `dummy = new Node(-1)`.
 *   - Maintain a pointer `prev = dummy`.
 *   - Traverse the BST in standard Inorder (Left -> Root -> Right):
 *     1. Recursively flatten left subtree.
 *     2. Link previous node's right pointer to current node: `prev->right = curr`.
 *     3. Nullify current node's left pointer: `curr->left = nullptr`.
 *     4. Advance `prev = curr`.
 *     5. Recursively flatten right subtree.
 *   - Finally, set `prev->left = nullptr` and `prev->right = nullptr`.
 *   - Return `dummy->right` as the new root of the right-skewed sorted list.
 * 
 * TIME COMPLEXITY:
 * - O(N): Traverses each node once.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion depth bounded by tree height.
 */

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void inorderFlatten(Node* curr, Node*& prev) {
    if (!curr) return;

    inorderFlatten(curr->left, prev);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Rewire prev's right pointer to curr, nullify curr's left pointer, and advance prev.
    prev->right = curr;
    curr->left = nullptr;
    prev = curr;

    inorderFlatten(curr->right, prev);
}

Node* flattenBST(Node* root) {
    Node* dummy = new Node(-1);
    Node* prev = dummy;

    inorderFlatten(root, prev);

    prev->left = nullptr;
    prev->right = nullptr;

    Node* newRoot = dummy->right;
    delete dummy;
    return newRoot;
}

void printFlattened(Node* root) {
    Node* curr = root;
    while (curr) {
        std::cout << curr->data << " -> ";
        curr = curr->right;
    }
    std::cout << "null\n";
}

int main() {
    //        5
    //       / \
    //      3   7
    //     / \   \
    //    2   4   8
    Node* root = new Node(5);
    root->left = new Node(3);
    root->right = new Node(7);
    root->left->left = new Node(2);
    root->left->right = new Node(4);
    root->right->right = new Node(8);

    Node* flattened = flattenBST(root);
    std::cout << "Flattened sorted list: ";
    printFlattened(flattened); // 2 -> 3 -> 4 -> 5 -> 7 -> 8 -> null

    return 0;
}
