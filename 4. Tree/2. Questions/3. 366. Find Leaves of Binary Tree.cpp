// 366. Find Leaves of Binary Tree
// Given the root of a binary tree, collect a tree's nodes as if you were doing this:
// 1. Collect all the leaf nodes.
// 2. Remove all the leaf nodes.
// 3. Repeat until the tree is empty.
// Return a 2D array where each inner array contains the values of the leaves collected at each step.

// Example:
// Input: root = [1,2,3,4,5]
//        1
//       / \
//      2   3
//     / \
//    4   5
// Output: [[4,5,3],[2],[1]]
// Explanation:
// Step 1: Remove leaves [4,5,3] -> remaining tree: [1,2]
// Step 2: Remove leaves [2] -> remaining tree: [1]
// Step 3: Remove leaves [1] -> tree is empty

#include <vector>
#include <algorithm>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Approach: Height-based grouping using DFS
// Key Insight: Instead of actually removing nodes, we can group nodes by their "height" from leaves
// - Leaf nodes have height 0 (they will be removed first)
// - A node's height = max(left child height, right child height) + 1
// - Nodes with the same height will be removed in the same step
// 
// Algorithm:
// 1. Use post-order DFS traversal (process children before parent)
// 2. For each node, calculate its height based on children's heights
// 3. Group nodes by their height in the result array
// 4. Height 0 nodes go in result[0], height 1 in result[1], etc.
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(n) - for result array and O(h) for recursion stack


class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> result;
        getHeight(root, result);
        return result;
    }
    
private:
    // Returns the height of the node (distance from leaf)
    // Leaf nodes have height 0
    int getHeight(TreeNode* node, vector<vector<int>>& result) {
        if (!node) {
            return -1;
        }
        
        // Get heights of left and right subtrees
        int leftHeight = getHeight(node->left, result);
        int rightHeight = getHeight(node->right, result);
        
        // Current node's height is max of children's heights + 1
        int height = max(leftHeight, rightHeight) + 1;
        
        // Ensure result has enough vectors
        if (result.size() <= height) {
            result.push_back(vector<int>());
        }
        
        // Add current node's value to the appropriate level
        result[height].push_back(node->val);
        
        return height;
    }
};