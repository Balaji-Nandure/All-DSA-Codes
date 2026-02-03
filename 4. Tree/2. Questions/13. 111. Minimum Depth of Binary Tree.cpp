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

// Problem: Minimum Depth of Binary Tree (LeetCode 111)
// Given a binary tree, find its minimum depth.
// The minimum depth is the number of nodes along the shortest path from the 
// root node down to the nearest leaf node.
// Note: A leaf is a node with no children.
//
// Approach 1: BFS (Level-order traversal) - Optimal
// 1. Use BFS to traverse level by level
// 2. Return depth as soon as we encounter the first leaf node
// 3. This is optimal because we stop as soon as we find the shallowest leaf
//
// Time Complexity: O(n) - worst case visit all nodes
// Space Complexity: O(w) - queue size where w is maximum width of tree

class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        
        queue<TreeNode*> q;
        q.push(root);
        int depth = 1;
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // If we find a leaf node, return current depth
                if (!node->left && !node->right) {
                    return depth;
                }
                
                // Add children to queue for next level
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            depth++;
        }
        
        return depth;
    }
};

// Approach 2: DFS (Recursive)
// 1. If node is null, return 0
// 2. If node is a leaf, return 1
// 3. If only one child exists, recurse on that child
// 4. If both children exist, return min of both + 1
//
// Time Complexity: O(n) - visit all nodes
// Space Complexity: O(h) - recursion stack where h is height

class Solution2 {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        
        // If only right child exists, recurse on right
        if (!root->left) return 1 + minDepth(root->right);
        
        // If only left child exists, recurse on left
        if (!root->right) return 1 + minDepth(root->left);
        
        // Both children exist, return minimum of both
        return 1 + min(minDepth(root->left), minDepth(root->right));
    }
};

