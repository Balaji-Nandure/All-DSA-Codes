/*
 * Problem: Check for Balanced Binary Tree (LeetCode 110)
 *
 * A binary tree is height-balanced if for every node,
 * |height(left) - height(right)| <= 1.
 *
 * Optimized DFS:
 * - Returns height if subtree is balanced
 * - Returns -1 if subtree is NOT balanced
 *
 * Time: O(n)
 * Space: O(h) recursion stack
 */

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
/*
 * Problem: Balanced Binary Tree
 *
 * LeetCode 110: Balanced Binary Tree
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/check-for-balanced-tree/1
 *
 * Check if binary tree is height-balanced.
 * Balanced: |height(left) - height(right)| <= 1 for every node.
 *
 * Time: O(n) - single pass
 * Space: O(h) - recursion stack
 */

class Solution {
public:
    // Returns height if balanced, -1 if unbalanced
    int heightOrUnbalanced(TreeNode* root) {
        // Base case: empty tree has height 0
        if (!root) return 0;

        // Get left subtree height
        int lh = heightOrUnbalanced(root->left);
        if (lh == -1) return -1; // Left subtree unbalanced

        // Get right subtree height
        int rh = heightOrUnbalanced(root->right);
        if (rh == -1) return -1; // Right subtree unbalanced

        // Check if current node is balanced
        if (abs(lh - rh) > 1) return -1; // Unbalanced
        
        // Return height of current subtree
        return 1 + max(lh, rh);
    }
    
    bool isBalanced(TreeNode* root) {
        // Tree is balanced if height is not -1
        return heightOrUnbalanced(root) != -1;
    }
};
