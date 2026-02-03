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

// Problem: Pseudo-Palindromic Paths in a Binary Tree (LeetCode 1457)
// Given a binary tree where node values are digits from 1 to 9, a path from 
// root to leaf is pseudo-palindromic if at least one permutation of the node 
// values in the path is a palindrome.
// Return the number of pseudo-palindromic paths going from root to leaf.
//
// Example:
//     2
//    / \
//   3   1
//  / \   \
// 3   1   1
// Path [2,3,3]: can form palindrome "3,2,3" ✓
// Path [2,3,1]: cannot form palindrome ✗
// Path [2,1,1]: can form palindrome "1,2,1" ✓
//
// Key Insight:
// A sequence can form a palindrome if at most one digit has odd frequency.
// For example: [1,2,1,2,3] can form "12321" (only 3 has odd frequency)
//
// Approach: DFS with frequency tracking using bitmask
// 1. Use a bitmask to track odd/even frequency of each digit (1-9)
// 2. Bit i is 1 if digit i appears odd times, 0 if even times
// 3. Toggle bit when we encounter a digit (XOR operation)
// 4. At leaf node, check if at most one bit is set (at most one odd frequency)
// 5. A number has at most one bit set if it's 0 or a power of 2
//    Check: (mask & (mask - 1)) == 0
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(h) - recursion stack where h is height

class Solution {
public:
    int pseudoPalindromicPaths(TreeNode* root) {
        return dfs(root, 0);
    }
    
private:
    int dfs(TreeNode* node, int mask) {
        if (!node) return 0;
        
        // Toggle the bit for current node's value
        // If digit appears even times, bit becomes 0; if odd times, bit becomes 1
        mask ^= (1 << node->val);
        
        // If leaf node, check if path is pseudo-palindromic
        if (!node->left && !node->right) {
            // At most one bit should be set (at most one odd frequency)
            // mask & (mask - 1) removes the rightmost set bit
            // If result is 0, then mask had at most one bit set
            return (mask & (mask - 1)) == 0 ? 1 : 0;
        }
        
        // Recursively count pseudo-palindromic paths in left and right subtrees
        return dfs(node->left, mask) + dfs(node->right, mask);
    }
};

// Approach 2: DFS with frequency array
// Alternative approach using an array to track frequencies
// More intuitive but slightly more space

class Solution2 {
public:
    int pseudoPalindromicPaths(TreeNode* root) {
        vector<int> freq(10, 0);  // Digits 1-9
        return dfs(root, freq);
    }
    
private:
    int dfs(TreeNode* node, vector<int>& freq) {
        if (!node) return 0;
        
        // Increment frequency for current digit
        freq[node->val]++;
        
        int count = 0;
        
        // If leaf node, check if path is pseudo-palindromic
        if (!node->left && !node->right) {
            // Count digits with odd frequency
            int oddCount = 0;
            for (int i = 1; i <= 9; i++) {
                if (freq[i] % 2 == 1) {
                    oddCount++;
                }
            }
            // At most one digit can have odd frequency
            count = (oddCount <= 1) ? 1 : 0;
        } else {
            // Recursively count in left and right subtrees
            count = dfs(node->left, freq) + dfs(node->right, freq);
        }
        
        // Backtrack: decrement frequency when returning
        freq[node->val]--;
        
        return count;
    }
};

