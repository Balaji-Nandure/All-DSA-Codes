/*
 * Problem: Insert a given Node in Binary Search Tree
 *
 * LeetCode 701: Insert into a Binary Search Tree
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/insert-a-node-in-a-bst/1
 *
 * You are given the root node of a binary search tree (BST) and a value to insert
 * into the tree. Return the root node of the BST after the insertion. It is
 * guaranteed that the new value does not exist in the original BST.
 *
 * Example:
 * Input:
 *       4
 *      / \
 *     2   7
 *    / \
 *   1   3
 *
 * val = 5
 * Output:
 *       4
 *      / \
 *     2   7
 *    / \  / \
 *   1   3 5
 *
 * BST Property:
 * - Left subtree contains nodes with values < root
 * - Right subtree contains nodes with values > root
 * - No duplicate values (typically)
 *
 * Approach 1: Recursive
 * - If root is NULL, create new node and return
 * - If val < root->val, insert in left subtree
 * - If val > root->val, insert in right subtree
 * - Return root after insertion
 *
 * Approach 2: Iterative
 * - Traverse down the tree to find insertion point
 * - Keep track of parent node
 * - Insert as left or right child of parent
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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        // Base case: if tree is empty, create new node
        if (root == NULL) {
            return new TreeNode(val);
        }
        
        // If val is less than root, insert in left subtree
        if (val < root->val) {
            root->left = insertIntoBST(root->left, val);
        } else {
            // If val is greater than root, insert in right subtree
            root->right = insertIntoBST(root->right, val);
        }
        
        return root;
    }
};

// Solution 2: Iterative Approach (O(1) space)
class IterativeSolution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        // If tree is empty, create new root
        if (root == NULL) {
            return new TreeNode(val);
        }
        
        TreeNode* current = root;
        
        while (true) {
            // If val is less than current, go to left subtree
            if (val < current->val) {
                // If left child is NULL, insert here
                if (current->left == NULL) {
                    current->left = new TreeNode(val);
                    break;
                } else {
                    current = current->left;
                }
            } else {
                // If val is greater than current, go to right subtree
                // If right child is NULL, insert here
                if (current->right == NULL) {
                    current->right = new TreeNode(val);
                    break;
                } else {
                    current = current->right;
                }
            }
        }
        
        return root;
    }
};
