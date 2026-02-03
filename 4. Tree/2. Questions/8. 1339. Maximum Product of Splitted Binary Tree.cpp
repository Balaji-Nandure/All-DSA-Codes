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

// Problem: Maximum Product of Splitted Binary Tree (LeetCode 1339)
// Given a binary tree, split it into two subtrees by removing one edge.
// Return the maximum product of the sums of the two subtrees.
// Return the answer modulo 10^9 + 7.
//
// Approach: Two-pass DFS
// 1. First pass: Calculate total sum of all nodes
// 2. Second pass: For each subtree, calculate its sum and the product with remaining tree
//    - If we remove edge above a subtree with sum S, we get two parts: S and (total - S)
//    - Product = S * (total - S)
// 3. Track maximum product
//
// Time Complexity: O(n) - two passes through the tree
// Space Complexity: O(h) - recursion stack where h is height

class Solution {
public:
    int maxProduct(TreeNode* root) {
        const int MOD = 1e9 + 7;
        
        // First pass: calculate total sum
        long long totalSum = calculateSum(root);
        
        // Second pass: find maximum product
        long long maxProd = 0;
        findMaxProduct(root, totalSum, maxProd);
        
        return maxProd % MOD;
    }
    
private:
    // Calculate total sum of all nodes
    long long calculateSum(TreeNode* node) {
        if (!node) return 0;
        return node->val + calculateSum(node->left) + calculateSum(node->right);
    }
    
    // Find maximum product by trying each possible split
    long long findMaxProduct(TreeNode* node, long long totalSum, long long& maxProd) {
        if (!node) return 0;
        
        // Calculate sum of current subtree
        long long leftSum = findMaxProduct(node->left, totalSum, maxProd);
        long long rightSum = findMaxProduct(node->right, totalSum, maxProd);
        long long subtreeSum = node->val + leftSum + rightSum;
        
        // If we remove the edge above this subtree:
        // One part has sum = subtreeSum
        // Other part has sum = totalSum - subtreeSum
        long long product = subtreeSum * (totalSum - subtreeSum);
        maxProd = max(maxProd, product);
        
        return subtreeSum;
    }
};
