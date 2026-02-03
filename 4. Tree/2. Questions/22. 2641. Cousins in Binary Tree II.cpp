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

// Problem: Cousins in Binary Tree II (LeetCode 2641)
// Given the root of a binary tree, replace the value of each node in the tree 
// with the sum of all its cousins' values.
// Two nodes are cousins if they have the same depth but different parents.
//
// Example:
//       5
//      / \
//     4   9
//    / \   \
//   1   10  7
// 
// Level 0: 5 -> no cousins -> 0
// Level 1: 4 and 9 are cousins -> 4 becomes 9, 9 becomes 4
// Level 2: 1, 10, 7 -> 1's cousins are 7 (sum=7), 10's cousins are 7 (sum=7), 7's cousins are 1+10 (sum=11)
// Result:
//       0
//      / \
//     9   4
//    / \   \
//   7   7  11
//
// Key Insights:
// 1. Cousins are nodes at the same level but with different parents
// 2. For each node, its new value = (sum of all nodes at its level) - (sum of its siblings) - (its own value)
// 3. Need to track level sums and sibling sums
//
// Approach: Two-pass BFS
// Pass 1: Calculate sum of each level
// Pass 2: Update each node's value using: levelSum - (node's value + sibling's value)
//
// Time Complexity: O(n) - visit each node twice
// Space Complexity: O(w) - queue size where w is maximum width of tree

// Approach 2: Single-pass BFS with parent tracking
// Track parent-child relationships to calculate sibling sums on the fly

class Solution2 {
public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        if (!root) return nullptr;
        
        queue<TreeNode*> q;
        q.push(root);
        int prevLevelSum = root->val;
        
        while (!q.empty()) {
            int size = q.size();
            int currLevelSum = 0;
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // Update current node's value
                node->val = prevLevelSum - node->val;
                
                // Calculate sibling sum for children
                int siblingSum = 0;
                if (node->left) siblingSum += node->left->val;
                if (node->right) siblingSum += node->right->val;
                
                // Add children to queue and update their values temporarily
                if (node->left) {
                    currLevelSum += node->left->val;
                    node->left->val = siblingSum;
                    q.push(node->left);
                }
                if (node->right) {
                    currLevelSum += node->right->val;
                    node->right->val = siblingSum;
                    q.push(node->right);
                }
            }
            
            prevLevelSum = currLevelSum;
        }
        
        return root;
    }
};

