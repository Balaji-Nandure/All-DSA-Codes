/**
 * Problem: Check if a Tree is a BST or Not (Validate BST)
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A naive misconception checks only that `node->left->data < node->data < node->right->data` for direct children.
 * - This local check fails! E.g. in tree: `[10, 5, 15, null, null, 6, 20]`, direct children are valid,
 *   but node `6` in the right subtree violates `6 < 10`!
 * - Global ancestral range bounds must be propagated to every single node.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Method 1: Range-Bounded Recursive DFS:
 *   - Every node must lie strictly within an open interval: `(minBound, maxBound)`.
 *   - The root begins with interval `(-INF, +INF)`.
 *   - When moving LEFT: upper bound tightens to `node->data` -> `(minBound, node->data)`.
 *   - When moving RIGHT: lower bound tightens to `node->data` -> `(node->data, maxBound)`.
 * - Method 2: Monotonic Inorder Verification:
 *   - Inorder traversal of a valid BST must produce a strictly monotonically increasing sequence.
 *   - Track `prevNode`; if `curr->data <= prevNode->data`, return false immediately!
 * 
 * TIME COMPLEXITY:
 * - O(N): Visits every node once.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion depth bounded by tree height.
 */

#include <iostream>
#include <climits>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

bool isValidBSTUtil(Node* root, long long minVal, long long maxVal) {
    if (!root) return true;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Every node must satisfy the global ancestral boundary inherited from all its ancestors.
    if (root->data <= minVal || root->data >= maxVal) {
        return false;
    }

    // Left child must be < root->data; Right child must be > root->data
    return isValidBSTUtil(root->left, minVal, root->data) &&
           isValidBSTUtil(root->right, root->data, maxVal);
}

bool isBST(Node* root) {
    return isValidBSTUtil(root, LLONG_MIN, LLONG_MAX);
}

int main() {
    // Valid BST:
    //      2
    //     / \
    //    1   3
    Node* root1 = new Node(2);
    root1->left = new Node(1);
    root1->right = new Node(3);
    std::cout << "Tree 1 is valid BST: " << (isBST(root1) ? "Yes" : "No") << "\n"; // Yes

    // Invalid BST:
    //      10
    //     /  \
    //    5    15
    //        /  \
    //       6    20 (6 is in right subtree of 10 but 6 < 10!)
    Node* root2 = new Node(10);
    root2->left = new Node(5);
    root2->right = new Node(15);
    root2->right->left = new Node(6);
    root2->right->right = new Node(20);
    std::cout << "Tree 2 is valid BST: " << (isBST(root2) ? "Yes" : "No") << "\n"; // No

    return 0;
}
