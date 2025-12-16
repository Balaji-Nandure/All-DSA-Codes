/*
 * Problem: Search in a Binary Search Tree
 *
 * LeetCode 700: Search in a Binary Search Tree
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/search-a-node-in-bst/1
 *
 * You are given the root of a binary search tree (BST) and an integer val.
 * Find the node in the BST that the node's value equals val and return the
 * subtree rooted with that node. If such a node does not exist, return null.
 *
 * Example:
 * Input:
 *       4
 *      / \
 *     2   7
 *    / \
 *   1   3
 *
 * val = 2
 * Output:
 *     2
 *    / \
 *   1   3
 *
 * BST Property:
 * - Left subtree contains nodes with values < root
 * - Right subtree contains nodes with values > root
 * - No duplicate values (typically)
 *
 * Approach 1: Recursive
 * - If root is NULL or root->val == val, return root
 * - If val < root->val, search in left subtree
 * - If val > root->val, search in right subtree
 *
 * Approach 2: Iterative
 * - Use a loop to traverse down the tree
 * - Compare val with current node and move left or right accordingly
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
    TreeNode* searchBST(TreeNode* root, int val) {
        // Base case: root is NULL or we found the value
        if (root == NULL || root->val == val) {
            return root;
        }
        
        // If val is less than root, search in left subtree
        if (val < root->val) {
            return searchBST(root->left, val);
        }
        
        // If val is greater than root, search in right subtree
        return searchBST(root->right, val);
    }
};

// Solution 2: Iterative Approach (O(1) space)
class IterativeSolution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        TreeNode* current = root;
        
        while (current != NULL) {
            // Found the node
            if (current->val == val) {
                return current;
            }
            
            // Move to left subtree if val is smaller
            if (val < current->val) {
                current = current->left;
            } else {
                // Move to right subtree if val is larger
                current = current->right;
            }
        }
        
        // Value not found
        return NULL;
    }
};

// Solution 3: Recursive with Early Return (Alternative style)
class RecursiveEarlyReturnSolution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == NULL) return NULL;
        
        if (root->val == val) return root;
        
        // Use ternary operator for concise code
        return (val < root->val) ? searchBST(root->left, val) 
                                  : searchBST(root->right, val);
    }
};

// Solution 4: Iterative with Explicit Comparison
class IterativeExplicitSolution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == NULL) return NULL;
        
        TreeNode* node = root;
        
        while (node != NULL) {
            if (node->val == val) {
                return node;
            } else if (val < node->val) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        
        return NULL;
    }
};
