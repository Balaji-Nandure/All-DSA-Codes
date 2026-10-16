/**
 * Problem: Height (Maximum Depth) of a Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Level order traversed horizontally across all nodes.
 * - Finding the height measures vertical depth along the single longest simple path from root to leaf.
 * - This serves as the core sub-problem for almost every tree metric (balance factor, diameter, AVL rotations).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Bottom-Up Post-Order Recursion:
 *   - Base Case: An empty subtree has height 0.
 *   - Hypothesis: Height of left subtree is `lh`, height of right subtree is `rh`.
 *   - Induction Step: The current node adds 1 level of height atop whichever subtree extends deeper:
 *     `height = 1 + max(lh, rh)`.
 *   - This solves the problem in a single elegant O(N) post-order pass.
 * 
 * TIME COMPLEXITY:
 * - O(N): Every node is visited once.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Where H is tree height (O(log N) for balanced trees, O(N) for degenerate trees) for recursion stack.
 */

#include <iostream>
#include <algorithm>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

int height(Node* node) {
    // Base Case
    if (!node) return 0;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Tree height is 1 plus the maximum depth reached by either the left or right child.
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    return 1 + std::max(leftHeight, rightHeight);
}

int main() {
    //        1
    //       / \
    //      2   3
    //     /
    //    4
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);

    std::cout << "Height of tree: " << height(root) << "\n"; // 3

    return 0;
}
