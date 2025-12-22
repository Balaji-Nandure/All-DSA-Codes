/*
 * Problem: Check if a Binary Tree is a Binary Search Tree (BST)
 *
 * LeetCode 98: Validate Binary Search Tree
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/check-for-bst/1
 *
 * Given the root of a binary tree, determine if it is a valid Binary Search Tree (BST).
 *
 * A valid BST is defined as:
 * - The left subtree of a node contains only nodes with keys < node->val.
 * - The right subtree of a node contains only nodes with keys > node->val.
 * - Both the left and right subtrees must also be binary search trees.
 *
 * Example (Valid BST):
 *       2
 *      / \
 *     1   3
 *
 * Example (NOT a BST):
 *       5
 *      / \
 *     1   4
 *        / \
 *       3   6
 *  Here, 3 is in the right subtree of 5 but 3 < 5, so it's invalid.
 *
 * Approach 1: Recursive with Min/Max Bounds (Most Common)
 * - For each node, maintain a range (minVal, maxVal) that the node's value must lie in.
 * - Initially, the range is (-inf, +inf).
 * - For left child: new range is (minVal, node->val)
 * - For right child: new range is (node->val, maxVal)
 * - If any node violates the range, it's not a BST.
 *
 * Approach 2: Inorder Traversal (Recursive)
 * - Inorder traversal of BST yields a strictly increasing sequence.
 * - Keep track of the previous node's value; current must be > previous.
 *
 * Approach 3: Inorder Traversal (Iterative with Stack)
 * - Same idea as Approach 2 but using an explicit stack.
 *
 * Time: O(n) for all approaches (visit each node once)
 * Space: O(h) for recursion/stack where h is tree height (O(log n) for balanced, O(n) for skewed)
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

#include <climits>
#include <stack>
using namespace std;

// Solution 1: Recursive with Min/Max Bounds
class BoundsSolution {
public:
    bool isValidBST(TreeNode* root) {
        return helper(root, LLONG_MIN, LLONG_MAX);
    }

private:
    bool helper(TreeNode* node, long long minVal, long long maxVal) {
        if (node == nullptr) return true;
        
        // Current node must lie strictly between (minVal, maxVal)
        if (node->val <= minVal || node->val >= maxVal) return false;
        
        // Left subtree: values < node->val
        // Right subtree: values > node->val
        return helper(node->left, minVal, node->val) &&
               helper(node->right, node->val, maxVal);
    }
};

// Solution 2: Recursive Inorder Traversal (Check Sorted Order)
class InorderRecursiveSolution {
public:
    bool isValidBST(TreeNode* root) {
        TreeNode* prev = nullptr;
        return inorder(root, prev);
    }

private:
    bool inorder(TreeNode* node, TreeNode*& prev) {
        if (node == nullptr) return true;
        
        // Check left subtree
        if (!inorder(node->left, prev)) return false;
        
        // Current node must be greater than previous inorder node
        if (prev != nullptr && node->val <= prev->val) return false;
        prev = node;
        
        // Check right subtree
        return inorder(node->right, prev);
    }
};
