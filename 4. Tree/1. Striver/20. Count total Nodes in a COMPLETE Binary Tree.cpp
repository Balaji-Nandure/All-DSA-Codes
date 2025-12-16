/*
 * Problem: Count Complete Tree Nodes
 *
 * LeetCode 222: Count Complete Tree Nodes
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/count-nodes-of-complete-binary-tree/1
 *
 * Given the root of a complete binary tree, return the number of the nodes in the tree.
 * In a complete binary tree, every level, except possibly the last, is completely filled,
 * and all nodes in the last level are as far left as possible.
 *
 * Approach: Optimized Recursive (Using Complete Tree Property)
 * - Calculate left and right heights.
 * - If they are equal, the tree is perfect (all nodes present): return 2^h - 1 nodes.
 * - Otherwise, recursively count for left and right.
 * - Time: O{(log n) * (log n)}
 * - Space: O(log n) for the recursion stack.
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

class Solution {
public:
    int countNodes(TreeNode* root) {
        if(root == NULL) return 0;
        int lh = findHeightLeft(root);
        int rh = findHeightRight(root);
        if(lh == rh) return (1<<lh) - 1;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    
    int findHeightLeft(TreeNode* node) {
        int hght = 0;
        while(node) {
            hght++;
            node = node->left;
        }
        return hght;
    }
    
    int findHeightRight(TreeNode* node) {
        int hght = 0;
        while(node) {
            hght++;
            node = node->right;
        }
        return hght;
    }
};

// Solution 2: Simple Inorder Traversal (for comparison, not optimal for complete BT)
//
// This solution uses a straightforward inorder traversal to count nodes.
// Time: O(n)
// Space: O(h) for the recursion stack (h = tree height).
class InorderSolution {
public:
    int countNodes(TreeNode* root) {
        // Inorder traversal, count nodes
        int count = 0;
        inorder(root, count);
        return count;
    }
private:
    void inorder(TreeNode* node, int &count) {
        if (!node) return;
        inorder(node->left, count);
        count++;
        inorder(node->right, count);
    }
};

