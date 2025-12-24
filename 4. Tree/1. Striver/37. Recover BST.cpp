/*
 * Problem: Recover Binary Search Tree
 *
 * LeetCode 99: Recover Binary Search Tree
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/fixed-two-nodes-of-a-bst/1
 *
 * You are given the root of a binary search tree (BST), where the values of exactly
 * two nodes of the tree were swapped by mistake. Recover the tree without changing
 * its structure.
 *
 * Note: A solution using O(n) space is pretty straight-forward. Could you devise a
 * constant O(1) space solution?
 *
 * Example 1:
 * Input: root = [1,3,null,null,2]
 * Output: [3,1,null,null,2]
 * Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.
 *
 *       1                   3
 *      /                   /
 *     3         ->        1
 *      \                   \
 *       2                   2
 *
 * Example 2:
 * Input: root = [3,1,4,null,null,2]
 * Output: [2,1,4,null,null,3]
 * Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.
 *
 *       3                   2
 *      / \                 / \
 *     1   4       ->      1   4
 *        /                   /
 *       2                   3
 *
 * Key Insight:
 * - In a valid BST, inorder traversal gives strictly increasing sequence
 * - If two nodes are swapped, inorder traversal will have violations
 * - Case 1: Two adjacent nodes swapped -> one violation (prev > current)
 * - Case 2: Two non-adjacent nodes swapped -> two violations
 *   - First violation: larger node (first)
 *   - Second violation: smaller node (second)
 *
 * Approach 1: Inorder Traversal + Store Violations (O(n) space)
 * - Perform inorder traversal
 * - Find nodes where prev->val > current->val
 * - Swap the first and last violating nodes
 *
 * Approach 2: Inorder Traversal (O(1) space with Morris Traversal)
 * - Use Morris traversal to avoid recursion/stack
 * - Track first, middle, last violating nodes
 * - Swap first and last (or first and middle if only one violation)
 *
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(h) for recursion, O(1) for Morris traversal
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
#include <stack>
using namespace std;

// Solution 1: Inorder Traversal with Array (O(n) space)
class ArraySolution {
private:
    void inorderTraversal(TreeNode* root, vector<TreeNode*>& nodes) {
        if (root == nullptr) return;
        inorderTraversal(root->left, nodes);
        nodes.push_back(root);
        inorderTraversal(root->right, nodes);
    }
    
public:
    void recoverTree(TreeNode* root) {
        vector<TreeNode*> nodes;
        inorderTraversal(root, nodes);
        
        // Find two nodes that are out of order
        TreeNode* first = nullptr;
        TreeNode* second = nullptr;
        
        for (int i = 0; i < nodes.size() - 1; i++) {
            if (nodes[i]->val > nodes[i + 1]->val) {
                if (first == nullptr) {
                    first = nodes[i];      // First violation: larger node
                }
                second = nodes[i + 1];     // Second violation: smaller node
            }
        }
        
        // Swap the values
        if (first != nullptr && second != nullptr) {
            int temp = first->val;
            first->val = second->val;
            second->val = temp;
        }
    }
};