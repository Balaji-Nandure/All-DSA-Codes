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

// Problem: Find Bottom Left Tree Value (LeetCode 513)
// Given the root of a binary tree, return the leftmost value in the last row of the tree.
//
// Example:
//     2
//    / \
//   1   3
// Bottom left value: 1
//
// Example:
//       1
//      / \
//     2   3
//    /   / \
//   4   5   6
//      /
//     7
// Bottom left value: 7 (leftmost node in the deepest row)
//
// Approach 1: BFS (Level-order traversal) - Right to Left
// 1. Use BFS to traverse the tree level by level
// 2. Process nodes from right to left at each level
// 3. The last node we visit will be the bottom-left node
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(w) - queue size where w is maximum width of tree

class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* node = nullptr;
        
        while (!q.empty()) {
            node = q.front();
            q.pop();
            
            // Add right child first, then left child
            // This ensures the last node processed is the leftmost
            if (node->right) q.push(node->right);
            if (node->left) q.push(node->left);
        }
        
        return node->val;
    }
};
