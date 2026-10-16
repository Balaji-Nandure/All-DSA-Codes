/**
 * Problem: Check if a Binary Tree is Height-Balanced
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Height of a tree", we unconditionally calculated the subtree depth.
 * - Here, we must determine if `|height(left) - height(right)| <= 1` holds true for EVERY SINGLE NODE.
 * - Calling height independently at each node causes an inefficient O(N^2) complexity.
 * - Here, we short-circuit the bottom-up height computation to fail fast in strictly O(N) time.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Bottom-Up Post-Order with Sentinel Return (-1):
 *   - The recursive function `checkHeight(node)` returns:
 *     - `-1` if the subtree rooted at `node` is NOT balanced.
 *     - The true integer height `1 + max(lh, rh)` if it IS balanced.
 *   - At each node:
 *     - If `lh == -1` or `rh == -1`, propagate `-1` up immediately without further calculations!
 *     - If `abs(lh - rh) > 1`, report unbalance by returning `-1`.
 *     - Otherwise, return `1 + max(lh, rh)`.
 *   - The tree is balanced if and only if `checkHeight(root) != -1`.
 * 
 * TIME COMPLEXITY:
 * - O(N): Every node is visited at most once, with early termination if an imbalance is found.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion stack space bounded by tree height.
 */

#include <iostream>
#include <algorithm>
#include <cmath>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

int checkHeight(Node* root) {
    if (!root) return 0;

    int lh = checkHeight(root->left);
    if (lh == -1) return -1; // Left subtree is already unbalanced

    int rh = checkHeight(root->right);
    if (rh == -1) return -1; // Right subtree is already unbalanced

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // If height difference between subtrees exceeds 1, immediately flag with -1 (short-circuit).
    if (std::abs(lh - rh) > 1) return -1;

    return 1 + std::max(lh, rh);
}

bool isBalanced(Node* root) {
    return checkHeight(root) != -1;
}

int main() {
    // Balanced:
    //        1
    //       / \
    //      2   3
    //     /
    //    4
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);

    std::cout << "Tree 1 is balanced: " << (isBalanced(root1) ? "Yes" : "No") << "\n"; // Yes

    // Unbalanced:
    //    1
    //   /
    //  2
    // /
    //3
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->left->left = new Node(3);

    std::cout << "Tree 2 is balanced: " << (isBalanced(root2) ? "Yes" : "No") << "\n"; // No

    return 0;
}
