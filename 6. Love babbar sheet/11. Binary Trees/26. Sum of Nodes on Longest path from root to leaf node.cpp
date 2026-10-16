/**
 * Problem: Sum of Nodes on Longest Path from Root to Leaf Node
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Simple path-sum problems optimize for the maximum sum regardless of path length.
 * - Here, path LENGTH is the PRIMARY metric, and the node SUM is strictly a SECONDARY tie-breaker:
 *   Lexicographically maximize `(path_length, path_sum)`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Top-Down Preorder DFS with Pair Tracking:
 *   - Carry `currentLen` and `currentSum` downwards along each path from the root.
 *   - When reaching a leaf node (`!root->left && !root->right`):
 *     - If `currentLen > maxLen`:
 *       - A strictly longer path has been discovered! Update both `maxLen = currentLen` and `maxSum = currentSum`.
 *     - Else if `currentLen == maxLen`:
 *       - Lengths are tied! Break the tie by maximizing: `maxSum = max(maxSum, currentSum)`.
 * 
 * TIME COMPLEXITY:
 * - O(N): Visits every node exactly once.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion depth bounded by tree height.
 */

#include <iostream>
#include <algorithm>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void solve(Node* root, int currentSum, int currentLen, int& maxLen, int& maxSum) {
    if (!root) return;

    currentSum += root->data;
    currentLen++;

    // At leaf node, evaluate criteria
    if (!root->left && !root->right) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Primary criterion is maximum length; secondary tie-breaker is maximum sum.
        if (currentLen > maxLen) {
            maxLen = currentLen;
            maxSum = currentSum;
        } else if (currentLen == maxLen) {
            maxSum = std::max(maxSum, currentSum);
        }
        return;
    }

    solve(root->left, currentSum, currentLen, maxLen, maxSum);
    solve(root->right, currentSum, currentLen, maxLen, maxSum);
}

int sumOfLongRootToLeafPath(Node* root) {
    if (!root) return 0;
    int maxLen = 0;
    int maxSum = 0;
    solve(root, 0, 0, maxLen, maxSum);
    return maxSum;
}

int main() {
    //        4
    //       / \
    //      2   5
    //     / \   \
    //    7   1   2
    //       /
    //      6
    // Path 4->2->1->6 has length 4, sum = 13
    // Path 4->2->7 has length 3, sum = 13
    // Path 4->5->2 has length 3, sum = 11
    Node* root = new Node(4);
    root->left = new Node(2);
    root->right = new Node(5);
    root->left->left = new Node(7);
    root->left->right = new Node(1);
    root->right->right = new Node(2);
    root->left->right->left = new Node(6);

    std::cout << "Sum on longest path: " << sumOfLongRootToLeafPath(root) << "\n"; // 13

    return 0;
}
