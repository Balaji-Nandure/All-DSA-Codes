/*
 * Problem: Diameter of Binary Tree (LeetCode 543)
 *
 * The diameter of a binary tree is the length of the longest path
 * between any two nodes in a tree. This path may or may not pass through the root.
 *
 * We only want the diameter, not the height.
 * For each node: diameter passing through it = leftDepth + rightDepth.
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
    // Returns diameter only (does not expose height to caller)
    // It is just a find height function with a maxDiameter variable(pass by reference)
    // we are only modifying maxDiameter variable for each node.
    int diameterUtil(TreeNode* root, int& maxDiameter) {
        if (!root) return 0;
        int left = diameterUtil(root->left, maxDiameter);
        int right = diameterUtil(root->right, maxDiameter);
        maxDiameter = max(maxDiameter, left + right);
        return 1 + max(left, right);
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        diameterUtil(root, diameter);
        return diameter;
    }
};
