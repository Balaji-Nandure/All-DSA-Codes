/*
 * Problem: Diameter of Binary Tree (LeetCode 543)
 *
 * The diameter of a binary tree is the length of the longest path
 * between any two nodes in a tree. This path may or may not pass through the root.
 *
 * We only want the diameter, not the height.
 * For each node: diameter passing through it = leftDepth + rightDepth.
 * Time: O(n)
 * Space: O(h)
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
/*
 * Problem: Diameter of Binary Tree
 *
 * LeetCode 543: Diameter of Binary Tree
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/diameter-of-binary-tree/1
 *
 * Find the diameter (longest path between any two nodes).
 * Path may or may not pass through root.
 *
 * Time: O(n) - single pass
 * Space: O(h) - recursion stack
 */

class Solution {
public:
    // Helper: Returns height, updates maxDiameter for each node
    // Diameter through a node = leftHeight + rightHeight
    int diameterUtil(TreeNode* root, int& maxDiameter) {
        // Base case: empty tree has height 0
        if (!root) return 0;
        
        // Get heights of left and right subtrees
        int left = diameterUtil(root->left, maxDiameter);
        int right = diameterUtil(root->right, maxDiameter);
        
        // Update maxDiameter: diameter through current node = left + right
        maxDiameter = max(maxDiameter, left + right);
        
        // Return height of current subtree
        return 1 + max(left, right);
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        diameterUtil(root, diameter);
        return diameter;
    }
};
