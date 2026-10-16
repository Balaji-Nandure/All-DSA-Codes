/**
 * Problem: Find Largest Subtree Sum in a Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Diameter of a tree", we maximized path length across any two leaves.
 * - Here, we maximize the sum of an entire SUBTREE (a node and ALL its descendants).
 * - Values can be negative, so an optimal subtree might be a single node or a small branch rather than the whole tree.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Bottom-Up Post-Order Subtree Accumulation:
 *   - Base Case: Null node contributes 0 to the sum.
 *   - Recursive Subtree Sum:
 *     `currentSubtreeSum = root->data + findSubtreeSum(root->left) + findSubtreeSum(root->right)`.
 *   - At every node:
 *     - Update global `maxSum = max(maxSum, currentSubtreeSum)`.
 *     - Return `currentSubtreeSum` to the parent so that the parent can compute its own subtree sum.
 * 
 * TIME COMPLEXITY:
 * - O(N): Visits every node exactly once.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion stack space bounded by tree height.
 */

#include <iostream>
#include <algorithm>
#include <climits>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

int findLargestSubtreeSumUtil(Node* root, int& maxSum) {
    if (!root) return 0;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Compute total sum of current subtree: root + all nodes in left + all nodes in right.
    int currentSum = root->data + 
                     findLargestSubtreeSumUtil(root->left, maxSum) + 
                     findLargestSubtreeSumUtil(root->right, maxSum);

    maxSum = std::max(maxSum, currentSum);

    return currentSum;
}

int findLargestSubtreeSum(Node* root) {
    if (!root) return 0;
    int maxSum = INT_MIN;
    findLargestSubtreeSumUtil(root, maxSum);
    return maxSum;
}

int main() {
    //        1
    //      /   \
    //    -2     3
    //    / \   / \
    //   4   5 -6  2
    // Subtree rooted at -2: -2 + 4 + 5 = 7
    // Subtree rooted at 3: 3 - 6 + 2 = -1
    // Total tree sum: 1 + 7 + (-1) = 7
    // Max subtree sum = 7
    Node* root = new Node(1);
    root->left = new Node(-2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(-6);
    root->right->right = new Node(2);

    std::cout << "Largest subtree sum: " << findLargestSubtreeSum(root) << "\n"; // 7

    return 0;
}
