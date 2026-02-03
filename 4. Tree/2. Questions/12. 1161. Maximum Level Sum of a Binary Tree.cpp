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

// Problem: Maximum Level Sum of a Binary Tree (LeetCode 1161)
// Given a binary tree, return the smallest level X such that the sum of all 
// the values of nodes at level X is maximal.
// Level numbering starts from 1 (root is at level 1).
//
// Approach: Level-order traversal (BFS)
// 1. Use BFS to traverse the tree level by level
// 2. For each level, calculate the sum of all node values
// 3. Track the level with maximum sum
// 4. If there's a tie, return the smallest level number
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(w) - queue size where w is maximum width of tree

class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        if (!root) return 0;
        
        queue<TreeNode*> q;
        q.push(root);
        
        int maxSum = INT_MIN;
        int maxLevel = 1;
        int currentLevel = 1;
        
        while (!q.empty()) {
            int levelSize = q.size();
            int levelSum = 0;
            
            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                levelSum += node->val;
                
                // Add children to queue for next level
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            // Update max level if current level has greater sum
            if (levelSum > maxSum) {
                maxSum = levelSum;
                maxLevel = currentLevel;
            }
            
            currentLevel++;
        }
        
        return maxLevel;
    }
};

