/**
 * Problem: Diameter of a Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Height measured the longest path from the ROOT down to a leaf.
 * - Diameter is the longest simple path between ANY TWO arbitrary nodes in the tree, which may or may not pass through the root!
 * - A naive implementation calls `height()` inside `diameter()` leading to O(N^2) complexity.
 * - Here, we compute height and update diameter concurrently in a single bottom-up O(N) pass.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Combined Post-Order Traversal (O(N)):
 *   - At every node `curr`, the longest path passing through `curr` as its turning point (apex)
 *     spans from the deepest leaf of its left subtree to the deepest leaf of its right subtree.
 *   - Path length (in nodes) = `leftHeight + rightHeight + 1` (or `leftHeight + rightHeight` in edges).
 *   - We maintain a global/reference variable `maxDiameter`.
 *   - The recursive function returns the HEIGHT of the current subtree `1 + max(lh, rh)` to its parent,
 *     while continuously updating `maxDiameter = max(maxDiameter, lh + rh + 1)`.
 * 
 * TIME COMPLEXITY:
 * - O(N): Each node is visited exactly once.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion stack depth proportional to tree height.
 */

#include <iostream>
#include <algorithm>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

int calculateDiameterAndHeight(Node* root, int& maxDiameter) {
    if (!root) return 0;

    int lh = calculateDiameterAndHeight(root->left, maxDiameter);
    int rh = calculateDiameterAndHeight(root->right, maxDiameter);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // The longest path turning at this node connects its deepest left leaf to its deepest right leaf.
    maxDiameter = std::max(maxDiameter, lh + rh + 1);

    // Return height of current subtree to parent
    return 1 + std::max(lh, rh);
}

int diameter(Node* root) {
    int maxDiameter = 0;
    calculateDiameterAndHeight(root, maxDiameter);
    return maxDiameter;
}

int main() {
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    std::cout << "Diameter (number of nodes): " << diameter(root) << "\n"; // 4 (Path: 4-2-1-3 or 5-2-1-3)

    return 0;
}
