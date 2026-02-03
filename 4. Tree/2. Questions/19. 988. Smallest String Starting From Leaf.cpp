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

// Problem: Smallest String Starting From Leaf (LeetCode 988)
// Given the root of a binary tree where each node has a value from 0 to 25 
// representing letters 'a' to 'z', return the lexicographically smallest string 
// that starts at a leaf and ends at the root.
//
// Example:
//     0
//    / \
//   1   2
//  / \   \
// 3   4   5
// Paths from leaf to root:
// - 3->1->0 = "dba"
// - 4->1->0 = "eba"
// - 5->2->0 = "fca"
// Smallest: "dba"
//
// Key Insight:
// - Build strings from leaf to root (reverse order)
// - Compare strings lexicographically
// - Need to explore all paths to find the smallest
//
// Approach: DFS with path tracking
// 1. Use DFS to traverse from root to leaf
// 2. Build the string as we go (prepending characters since we go root to leaf)
// 3. At each leaf, compare with the current smallest string
// 4. Return the smallest string found
//
// Time Complexity: O(n * h) - visit each node once, string operations take O(h)
// Space Complexity: O(h) - recursion stack and string storage where h is height

class Solution {
public:
    string smallestFromLeaf(TreeNode* root) {
        string result = "";
        dfs(root, "", result);
        return result;
    }
    
private:
    void dfs(TreeNode* node, string path, string& result) {
        if (!node) return;
        
        // Prepend current character to path (building from leaf to root)
        path = char('a' + node->val) + path;
        
        // If leaf node, compare with result
        if (!node->left && !node->right) {
            if (result.empty() || path < result) {
                result = path;
            }
            return;
        }
        
        // Recursively explore left and right subtrees
        dfs(node->left, path, result);
        dfs(node->right, path, result);
    }
};

// Approach 2: DFS with string building in reverse
// Build string from root to leaf, then reverse at leaf nodes

class Solution2 {
public:
    string smallestFromLeaf(TreeNode* root) {
        string result = "";
        string path = "";
        dfs(root, path, result);
        return result;
    }
    
private:
    void dfs(TreeNode* node, string& path, string& result) {
        if (!node) return;
        
        // Add current character to path
        path.push_back('a' + node->val);
        
        // If leaf node, reverse path and compare
        if (!node->left && !node->right) {
            string reversed(path.rbegin(), path.rend());
            if (result.empty() || reversed < result) {
                result = reversed;
            }
        } else {
            // Explore children
            dfs(node->left, path, result);
            dfs(node->right, path, result);
        }
        
        // Backtrack: remove current character
        path.pop_back();
    }
};

