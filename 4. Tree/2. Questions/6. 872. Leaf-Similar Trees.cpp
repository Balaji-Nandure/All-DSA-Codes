// 872. Leaf-Similar Trees
// Consider all the leaves of a binary tree, from left to right order, the values of those leaves form a leaf value sequence.
// Two binary trees are considered leaf-similar if their leaf value sequence is the same.
// Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.

// Example 1:
// Input: root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
//        3                    3
//       / \                  / \
//      5   1                5   1
//     / \ / \              / \ / \
//    6  2 9  8            6  7 4  2
//      / \                        / \
//     7   4                      9   8
// Output: true
// Explanation: The leaf value sequence for both trees is [6,7,4,9,8]

// Example 2:
// Input: root1 = [1,2,3], root2 = [1,3,2]
// Output: false

#include <vector>
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

// Approach: DFS to collect leaf sequences, then compare
// Key Insight: A node is a leaf if it has no left and right children
// - Use DFS (any traversal works) to collect leaf values in order
// - Collect leaves for both trees
// - Compare the two sequences
//
// Algorithm:
// 1. Perform DFS on root1 to collect all leaf values in left-to-right order
// 2. Perform DFS on root2 to collect all leaf values in left-to-right order
// 3. Compare the two sequences
//
// Time Complexity: O(n + m) where n and m are the number of nodes in the two trees
// Space Complexity: O(h1 + h2) for recursion stack + O(l1 + l2) for storing leaves

class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> leaves1, leaves2;
        
        // Collect leaf sequences from both trees
        collectLeaves(root1, leaves1);
        collectLeaves(root2, leaves2);
        
        // Compare the sequences
        return leaves1 == leaves2;
    }
    
private:
    // Helper function to collect leaf values using DFS
    void collectLeaves(TreeNode* node, vector<int>& leaves) {
        if (!node) {
            return;
        }
        
        // If it's a leaf node, add its value
        if (!node->left && !node->right) {
            leaves.push_back(node->val);
            return;
        }
        
        // Recursively collect from left and right subtrees
        collectLeaves(node->left, leaves);
        collectLeaves(node->right, leaves);
    }
};

// Alternative Approach: Iterative DFS using stack
class Solution2 {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> leaves1 = getLeaves(root1);
        vector<int> leaves2 = getLeaves(root2);
        return leaves1 == leaves2;
    }
    
private:
    vector<int> getLeaves(TreeNode* root) {
        vector<int> leaves;
        if (!root) return leaves;
        
        vector<TreeNode*> stack;
        stack.push_back(root);
        
        while (!stack.empty()) {
            TreeNode* node = stack.back();
            stack.pop_back();
            
            // If leaf, add to result
            if (!node->left && !node->right) {
                leaves.push_back(node->val);
            }
            
            // Push right first so left is processed first (for left-to-right order)
            if (node->right) stack.push_back(node->right);
            if (node->left) stack.push_back(node->left);
        }
        
        return leaves;
    }
};

