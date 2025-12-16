/*
 * Problem: Morris Traversal (Inorder, Preorder, Postorder)
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/inorder-traversal/1
 *
 * Morris Traversal is a method to traverse a binary tree without using recursion or stack,
 * achieving O(1) space complexity. It uses threading to temporarily modify the tree structure.
 *
 * Key Idea:
 * - For inorder/preorder: Create temporary links (threads) from rightmost node of left subtree
 *   to current node, then remove them after traversal
 * - Allows us to traverse back up the tree without using stack
 *
 * Example:
 *       1
 *      / \
 *     2   3
 *    / \
 *   4   5
 *
 * Inorder Morris: 4 2 5 1 3
 * Preorder Morris: 1 2 4 5 3
 *
 * Approach: Threaded Binary Tree
 * - For each node, find its inorder predecessor (rightmost node in left subtree)
 * - If predecessor's right is NULL, link it to current node and move left
 * - If predecessor's right is current node, unlink it and process current node, move right
 *
 * Time: O(n) - each edge is traversed at most twice
 * Space: O(1) - only using pointers, no extra space
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

#include <vector>
#include <algorithm>
using namespace std;

// Solution 1: Morris Inorder Traversal
class MorrisInorderSolution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        TreeNode* current = root;
        
        while (current != NULL) {
            // If left child is NULL, process current and move right
            if (current->left == NULL) {
                result.push_back(current->val);
                current = current->right;
            } else {
                // Find inorder predecessor (rightmost node in left subtree)
                TreeNode* predecessor = current->left;
                while (predecessor->right != NULL && predecessor->right != current) {
                    predecessor = predecessor->right;
                }
                
                // If predecessor's right is NULL, create thread and move left
                if (predecessor->right == NULL) {
                    predecessor->right = current;  // Create thread
                    current = current->left;
                } else {
                    // Thread already exists, remove it and process current
                    predecessor->right = NULL;  // Remove thread
                    result.push_back(current->val);
                    current = current->right;
                }
            }
        }
        
        return result;
    }
};

// Solution 2: Morris Preorder Traversal
class MorrisPreorderSolution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        TreeNode* current = root;
        
        while (current != NULL) {
            // If left child is NULL, process current and move right
            if (current->left == NULL) {
                result.push_back(current->val);
                current = current->right;
            } else {
                // Find inorder predecessor (rightmost node in left subtree)
                TreeNode* predecessor = current->left;
                while (predecessor->right != NULL && predecessor->right != current) {
                    predecessor = predecessor->right;
                }
                
                // If predecessor's right is NULL, create thread and process current
                if (predecessor->right == NULL) {
                    predecessor->right = current;  // Create thread
                    result.push_back(current->val);  // Process before going left
                    current = current->left;
                } else {
                    // Thread already exists, remove it and move right
                    predecessor->right = NULL;  // Remove thread
                    current = current->right;
                }
            }
        }
        
        return result;
    }
};

// Solution 3: Morris Postorder Traversal (More Complex)
// Uses reverse of right boundary nodes approach
class MorrisPostorderSolution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        TreeNode* current = root;
        
        while (current != NULL) {
            // If right child is NULL, process current and move left
            if (current->right == NULL) {
                result.push_back(current->val);
                current = current->left;
            } else {
                // Find inorder successor (leftmost node in right subtree)
                TreeNode* successor = current->right;
                while (successor->left != NULL && successor->left != current) {
                    successor = successor->left;
                }
                
                // If successor's left is NULL, create thread and move right
                if (successor->left == NULL) {
                    successor->left = current;  // Create thread
                    result.push_back(current->val);  // Process before going right
                    current = current->right;
                } else {
                    // Thread already exists, remove it and move left
                    successor->left = NULL;  // Remove thread
                    current = current->left;
                }
            }
        }
        
        // Reverse the result to get postorder
        reverse(result.begin(), result.end());
        return result;
    }
};