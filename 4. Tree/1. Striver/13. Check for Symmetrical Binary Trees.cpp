/*
 * Problem: Symmetric Tree (LeetCode 101)
 *
 * Given the root of a binary tree, check whether it is a mirror of itself
 * (i.e., symmetric around its center).
 *
 * Example 1:
 *       1
 *      / \
 *     2   2
 *    / \ / \
 *   3  4 4  3
 * Output: true (symmetric)
 *
 * Example 2:
 *       1
 *      / \
 *     2   2
 *      \   \
 *       3   3
 * Output: false (not symmetric)
 *
 * Approach:
 * - A tree is symmetric if the left subtree is a mirror of the right subtree.
 * - Two trees are mirrors if:
 *     1. Their root values are equal
 *     2. Left subtree of first == Right subtree of second (mirror)
 *     3. Right subtree of first == Left subtree of second (mirror)
 * - Use recursive DFS to check mirror property.
 *
 * Time: O(n) - visit each node once
 * Space: O(h) - where h is the height of the tree (recursion stack)
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

#include <queue>
using namespace std;

class Solution {
public:
    // Main function to check if the tree is symmetric (recursive)
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isMirror(root->left, root->right);
    }

private:
    // Recursive helper function to check if two trees are mirrors
    bool isMirror(TreeNode* left, TreeNode* right) {
        // Both nodes are null: symmetric at this subtree
        if (!left && !right) return true;
        // Only one node is null: not symmetric
        if (!left || !right) return false;
        // Values don't match: not symmetric
        if (left->val != right->val) return false;
        // Check mirrored children recursively
        return isMirror(left->left, right->right) && isMirror(left->right, right->left);
    }

public:
    // Alternative iterative approach using BFS/queue
    bool isSymmetricIterative(TreeNode* root) {
        if (!root) return true;
        queue<TreeNode*> q;
        q.push(root->left);
        q.push(root->right);

        while (!q.empty()) {
            TreeNode* left = q.front(); q.pop();
            TreeNode* right = q.front(); q.pop();

            // Both null: skip to next pair
            if (!left && !right) continue;
            // Not symmetric: only one is null or values do not match
            if (!left || !right || left->val != right->val) return false;

            // Enqueue children in mirrored order
            q.push(left->left);
            q.push(right->right);

            q.push(left->right);
            q.push(right->left);
        }
        return true;
    }
};