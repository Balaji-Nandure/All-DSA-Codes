/*
 * Problem: Maximum Path Sum in Binary Tree (LeetCode 124)
 *
 * Find the maximum path sum between any two nodes in a binary tree.
 * The path may start and end at any node in the tree.
 *
 * Approach:
 * - For each node: max path sum through it = node->val + max(0, leftMax) + max(0, rightMax)
 * - Helper returns max sum of path starting from current node going downward
 * - We update maxSum for each node
 *
 * Time: O(n)
 * Space: O(h)
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
    int maxPathSumUtil(TreeNode* root, int& ans) {
        if (!root) return 0;

        // Get max path sum from left and right
        int l = max(0, maxPathSumUtil(root->left, ans));
        int r = max(0, maxPathSumUtil(root->right, ans));

        // Update global answer considering path through this node
        ans = max(ans, root->val + l + r);

        // Return max single path going up
        return root->val + max(l, r);
    }
    
    int maxPathSum(TreeNode* root) {
        int ans = INT_MIN;
        maxPathSumUtil(root, ans);
        return ans;
    }
};

