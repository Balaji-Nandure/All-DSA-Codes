/*
 * Problem: Ceil in a Binary Search Tree
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/implementing-ceil-in-bst/1
 *
 * Given a Binary Search Tree and a number X, find Ceil of X.
 * Ceil(X) is a number that is either equal to X or is immediately greater than X.
 * If Ceil doesn't exist, return -1.
 *
 * Example:
 * Input:
 *       8
 *      / \
 *     4   12
 *    / \  / \
 *   2   6 10 14
 *
 * X = 5
 * Output: 6 (smallest value >= 5)
 *
 * X = 4
 * Output: 4 (exact match)
 *
 * X = 15
 * Output: -1 (no value >= 15)
 *
 * BST Property:
 * - Left subtree contains nodes with values < root
 * - Right subtree contains nodes with values > root
 *
 * Approach 1: Recursive
 * - If root is NULL, return -1
 * - If root->val == X, return root->val
 * - If root->val < X, search in right subtree
 * - If root->val > X, ceil might be root or in left subtree
 *
 * Approach 2: Iterative
 * - Traverse down the tree
 * - Keep track of potential ceil value
 * - Update ceil when we find a value >= X
 *
 * Time: O(h) where h is the height of the tree
 * - O(log n) for balanced BST
 * - O(n) for skewed BST
 * Space: O(1) for iterative, O(h) for recursive
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

// Solution 1: Recursive Approach
class RecursiveSolution {
public:
    int findCeil(TreeNode* root, int X) {
        if (root == NULL) return -1;
        
        // If exact match found, return it
        if (root->val == X) {
            return root->val;
        }
        
        // If root value is less than X, ceil must be in right subtree
        if (root->val < X) {
            return findCeil(root->right, X);
        }
        
        // If root value is greater than X, ceil might be root or in left subtree
        int leftCeil = findCeil(root->left, X);
        
        // If we found a valid ceil in left subtree, return it
        // Otherwise, root is the ceil
        return (leftCeil >= X) ? leftCeil : root->val;
    }
};

// Solution 2: Iterative Approach (O(1) space)
class IterativeSolution {
public:
    int findCeil(TreeNode* root, int X) {
        int ceil = -1;
        TreeNode* current = root;
        
        while (current != NULL) {
            // If exact match found, return it
            if (current->val == X) {
                return current->val;
            }
            
            // If current value is greater than X, it's a potential ceil
            if (current->val > X) {
                ceil = current->val;
                // Try to find a smaller value in left subtree
                current = current->left;
            } else {
                // Current value is less than X, ceil must be in right subtree
                current = current->right;
            }
        }
        
        return ceil;
    }
};

