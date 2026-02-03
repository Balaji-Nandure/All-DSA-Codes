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

// Problem: Delete Leaves With a Given Value (LeetCode 1325)
// Given a binary tree root and an integer target, delete all the leaf nodes 
// with value target.
// Note that once you delete a leaf node with value target, if its parent node 
// becomes a leaf node and has the value target, it should also be deleted 
// (you need to continue doing that until you cannot).
//
// Example:
//       1
//      / \
//     2   3
//    /   / \
//   2   2   4
// target = 2
// Step 1: Delete leaf nodes with value 2 (leftmost 2 and middle 2)
//       1
//      / \
//     2   3
//          \
//           4
// Step 2: Node with value 2 (left child of root) becomes a leaf, delete it
//       1
//        \
//         3
//          \
//           4
//
// Key Insight:
// - Process children before parent (post-order traversal)
// - After deleting children, check if current node becomes a leaf with target value
// - If so, delete it by returning nullptr
//
// Approach: Post-order DFS
// 1. Recursively process left and right subtrees first
// 2. After processing children, check if current node is a leaf with target value
// 3. If yes, return nullptr (delete this node)
// 4. Otherwise, return the node itself
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(h) - recursion stack where h is height

class Solution {
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        if (!root) return nullptr;
        
        // Post-order: process children first
        root->left = removeLeafNodes(root->left, target);
        root->right = removeLeafNodes(root->right, target);
        
        // After processing children, check if current node is a leaf with target value
        if (!root->left && !root->right && root->val == target) {
            return nullptr;  // Delete this node
        }
        
        return root;
    }
};
