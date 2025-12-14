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
class Solution {
public:
    int heightOrUnbalanced(TreeNode* root) {
        if (!root) return 0;

        int lh = heightOrUnbalanced(root->left);
        if (lh == -1) return -1;

        int rh = heightOrUnbalanced(root->right);
        if (rh == -1) return -1;

        if (abs(lh - rh) > 1) return -1;
        return 1 + max(lh, rh);
    }
    
    bool isBalanced(TreeNode* root) {
        return heightOrUnbalanced(root) != -1;
    }
};
