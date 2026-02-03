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

// Problem: Find Duplicate Subtrees (LeetCode 652)
// Given the root of a binary tree, return all duplicate subtrees.
// Two trees are duplicate if they have the same structure with the same node values.
//
// Approach: Serialize subtrees and use hash map
// 1. Use post-order traversal to serialize each subtree
// 2. Serialization format: "val,left_serialization,right_serialization"
// 3. Use hash map to count occurrences of each serialization
// 4. When a serialization appears for the second time, add the root to result
//
// Time Complexity: O(n^2) - in worst case, serialization can be O(n) for each node
// Space Complexity: O(n^2) - storing all serializations

class Solution {
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        vector<TreeNode*> result;
        unordered_map<string, int> subtreeCount;
        serialize(root, subtreeCount, result);
        return result;
    }
    
private:
    // Serialize subtree and track duplicates
    string serialize(TreeNode* node, unordered_map<string, int>& subtreeCount, 
                     vector<TreeNode*>& result) {
        if (!node) return "#";
        
        // Post-order: serialize left, right, then current
        string left = serialize(node->left, subtreeCount, result);
        string right = serialize(node->right, subtreeCount, result);
        
        // Create serialization for current subtree
        string serialization = to_string(node->val) + "," + left + "," + right;
        
        // Track count and add to result when we see it for the second time
        subtreeCount[serialization]++;
        if (subtreeCount[serialization] == 2) {
            result.push_back(node);
        }
        
        return serialization;
    }
};

