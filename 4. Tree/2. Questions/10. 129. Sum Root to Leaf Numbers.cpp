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

// Problem: Sum Root to Leaf Numbers (LeetCode 129)
// Given a binary tree where each node contains a digit (0-9),
// each root-to-leaf path represents a number.
// Return the sum of all root-to-leaf numbers.
//
// Example: 
//     1
//    / \
//   2   3
// Paths: 12 and 13, Sum = 12 + 13 = 25
//
// Approach: DFS with path number tracking
// 1. Traverse tree using DFS, building the number as we go down
// 2. At each node, current number = previous_number * 10 + current_node_value
// 3. When we reach a leaf, add the complete number to total sum
// 4. Return sum of all leaf numbers
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(h) - recursion stack where h is height

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        return dfs(root, 0);
    }
    
private:
    int dfs(TreeNode* node, int currentNumber) {
        if (!node) return 0;
        
        // Build the number: previous digits * 10 + current digit
        currentNumber = currentNumber * 10 + node->val;
        
        // If leaf node, return the complete number
        if (!node->left && !node->right) {
            return currentNumber;
        }
        
        // Recursively sum numbers from left and right subtrees
        return dfs(node->left, currentNumber) + dfs(node->right, currentNumber);
    }
};

