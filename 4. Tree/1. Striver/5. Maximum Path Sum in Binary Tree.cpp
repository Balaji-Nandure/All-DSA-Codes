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
/*
 * Problem: Binary Tree Maximum Path Sum
 *
 * LeetCode 124: Binary Tree Maximum Path Sum
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/maximum-path-sum/1
 *
 * Find maximum path sum between any two nodes.
 * Path may start and end at any node.
 *
 * Time: O(n) - single pass
 * Space: O(h) - recursion stack
 */

class Solution {
public:
    // Helper: Returns max single path from current node going downward
    // Updates ans with max path sum through current node
    int maxPathSumUtil(TreeNode* root, int& ans) {
        // Base case: empty tree contributes 0
        if (!root) return 0;

        // Get max path sum from left and right (only positive contributions)
        // max(0, ...) ensures we don't include negative paths
        int l = max(0, maxPathSumUtil(root->left, ans));
        int r = max(0, maxPathSumUtil(root->right, ans));

        // Update global answer: path through current node = root + left + right
        ans = max(ans, root->val + l + r);

        // Return max single path going upward (for parent)
        // Can only take one path: root + max(left, right)
        return root->val + max(l, r);
    }
    
    int maxPathSum(TreeNode* root) {
        int ans = INT_MIN;
        maxPathSumUtil(root, ans);
        return ans;
    }
};

