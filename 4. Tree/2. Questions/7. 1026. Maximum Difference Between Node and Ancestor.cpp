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

// Problem: Find the maximum difference between a node and its ancestor
// Approach: Track min and max values along each path from root to leaf
// Time: O(n), Space: O(h) where h is height

class Solution {
public:
    int maxAncestorDiff(TreeNode* root) {
        if (!root) return 0;
        return helper(root, root->val, root->val);
    }
    
private:
    int helper(TreeNode* node, int minVal, int maxVal) {
        if (!node) {
            // At leaf, return the difference between max and min in this path
            return maxVal - minVal;
        }
        
        // Update min and max values along the path
        minVal = min(minVal, node->val);
        maxVal = max(maxVal, node->val);
        
        // Recursively explore left and right subtrees
        int leftDiff = helper(node->left, minVal, maxVal);
        int rightDiff = helper(node->right, minVal, maxVal);
        
        // Return the maximum difference found
        return max(leftDiff, rightDiff);
    }
};

