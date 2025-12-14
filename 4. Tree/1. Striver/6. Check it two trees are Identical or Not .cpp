/*
 * Problem: Check if Two Trees are Identical (LeetCode 100)
 *
 * Two binary trees are considered identical if they are structurally identical,
 * and the nodes have the same value.
 *
 * Approach:
 * - If both nodes are null, they are identical
 * - If one is null and other is not, they are not identical
 * - If both exist, check data equality and recursively check left and right subtrees
 *
 * Time: O(n) where n is the number of nodes
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Both null - identical
        if (!p && !q) return true;
        
        // One null, other not - not identical
        if (!p || !q) return false;
        
        // Both exist - check val and recursively check subtrees
        return (p->val == q->val) &&
               isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }
};

