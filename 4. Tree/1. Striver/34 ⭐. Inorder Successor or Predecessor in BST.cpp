/*
 * Problem: Inorder Successor and Predecessor in Binary Search Tree
 *
 * LeetCode 285: Inorder Successor in BST
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/inorder-successor-in-bst/1
 *
 * Inorder Successor: The next node in the inorder traversal (smallest node > given node).
 * Inorder Predecessor: The previous node in the inorder traversal (largest node < given node).
 *
 * Time: O(h) where h is the height of the tree
 * Space: O(1) for iterative
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Solution 1: Inorder Successor (Compact Iterative)
class Solution {
public:
/*
 * Problem: Inorder Successor and Predecessor in BST
 *
 * LeetCode 285: Inorder Successor in BST
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/inorder-successor-in-bst/1
 *
 * Inorder Successor: smallest node > given node.
 * Inorder Predecessor: largest node < given node.
 *
 * Time: O(h) - where h is height
 * Space: O(1) - iterative approach
 */

    // Inorder Successor: smallest value > p
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* successor = NULL; // Track potential successor
        
        while (root != NULL) {
            // p >= root: successor in right subtree
            if (p->val >= root->val) {
                root = root->right;
            } else {
                // p < root: root is potential successor, check left for smaller
                successor = root; // Save as candidate
                root = root->left; // Try to find smaller candidate
            }
        }
        return successor;
    }
};

// Solution 2: Inorder Predecessor (Compact Iterative)
class PredecessorSolution {
public:
    // Inorder Predecessor: largest value < p
    TreeNode* inorderPredecessor(TreeNode* root, TreeNode* p) {
        TreeNode* predecessor = NULL; // Track potential predecessor
        
        while (root != NULL) {
            // p <= root: predecessor in left subtree
            if (p->val <= root->val) {
                root = root->left;
            } else {
                // p > root: root is potential predecessor, check right for larger
                predecessor = root; // Save as candidate
                root = root->right; // Try to find larger candidate
            }
        }
        return predecessor;
    }
};
