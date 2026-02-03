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

// Problem: Create Binary Tree From Descriptions (LeetCode 2196)
// You are given a 2D integer array descriptions where 
// descriptions[i] = [parent_i, child_i, isLeft_i] indicates that parent_i is 
// the parent of child_i in a binary tree of unique values.
// - If isLeft_i == 1, then child_i is the left child of parent_i.
// - If isLeft_i == 0, then child_i is the right child of parent_i.
// Construct the binary tree and return its root.
//
// Example:
// descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
//     50
//    /  \
//   20   80
//  / \    \
// 15  17  19
//
// Key Insights:
// 1. Need to create nodes and establish parent-child relationships
// 2. Root is the only node that is never a child
// 3. Use hash map to store created nodes to avoid duplicates
// 4. Track which nodes are children to identify the root
//
// Approach: Hash Map + Set
// 1. Create a map to store all nodes by their values
// 2. Create a set to track all children
// 3. Process each description:
//    - Create parent and child nodes if they don't exist
//    - Establish the parent-child relationship
//    - Mark child as a child node
// 4. Find the root (node that is not in children set)
//
// Time Complexity: O(n) - process each description once
// Space Complexity: O(n) - store all nodes in map and children in set

// Approach 2: Optimized with single pass
// Similar approach but slightly cleaner

class Solution2 {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode*> nodes;
        unordered_set<int> hasParent;
        
        for (const auto& d : descriptions) {
            int parent = d[0], child = d[1], isLeft = d[2];
            
            // Get or create parent node
            if (!nodes[parent]) nodes[parent] = new TreeNode(parent);
            
            // Get or create child node
            if (!nodes[child]) nodes[child] = new TreeNode(child);
            
            // Link parent to child
            if (isLeft) {
                nodes[parent]->left = nodes[child];
            } else {
                nodes[parent]->right = nodes[child];
            }
            
            // Mark child as having a parent
            hasParent.insert(child);
        }
        
        // Root is the node without a parent
        for (const auto& [val, node] : nodes) {
            if (hasParent.find(val) == hasParent.end()) {
                return node;
            }
        }
        
        return nullptr;
    }
};

