/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// Problem: Longest ZigZag Path in a Binary Tree (LeetCode 1372)
// A ZigZag path is a path where we alternate between going left and right.
// For example: root->left->right->left or root->right->left->right
// Find the length of the longest ZigZag path (number of edges, not nodes).
//
// Approach: DFS with direction tracking
// 1. At each node, track two values:
//    - Length of zigzag path ending here coming from left (going right)
//    - Length of zigzag path ending here coming from right (going left)
// 2. When we go left from a node, we can extend the "right" zigzag path
// 3. When we go right from a node, we can extend the "left" zigzag path
// 4. Track the maximum length seen
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(h) - recursion stack where h is height

class Solution {
public:
    int longestZigZag(TreeNode* root) {
        int maxLength = 0;
        dfs(root, true, 0, maxLength);   // Start going left
        dfs(root, false, 0, maxLength);  // Start going right
        return maxLength;
    }
    
private:
    // isLeft: true if we came from parent's left child, false if from right
    // length: current zigzag path length
    void dfs(TreeNode* node, bool isLeft, int length, int& maxLength) {
        if (!node) return;
        
        // Update maximum length
        maxLength = max(maxLength, length);
        
        if (isLeft) {
            // We came from left, so we should go right to continue zigzag
            dfs(node->right, false, length + 1, maxLength);  // Continue zigzag
            dfs(node->left, true, 1, maxLength);             // Start new zigzag
        } else {
            // We came from right, so we should go left to continue zigzag
            dfs(node->left, true, length + 1, maxLength);    // Continue zigzag
            dfs(node->right, false, 1, maxLength);           // Start new zigzag
        }
    }
};

