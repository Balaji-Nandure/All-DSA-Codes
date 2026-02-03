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

// Problem: Even Odd Tree (LeetCode 1609)
// A binary tree is named Even-Odd if it meets the following conditions:
// - The root of the binary tree is at level index 0, its children are at level 1, etc.
// - For every even-indexed level, all nodes at the level have odd integer values 
//   in strictly increasing order (from left to right).
// - For every odd-indexed level, all nodes at the level have even integer values 
//   in strictly decreasing order (from left to right).
// Return true if the binary tree is Even-Odd, otherwise return false.
//
// Example:
//         1
//       /   \
//      10    4
//     /  \    \
//    3    7    9
//   / \    \
//  12  8    6
//
// Level 0 (even): [1] - odd values, increasing ✓
// Level 1 (odd): [10, 4] - even values, decreasing ✓
// Level 2 (even): [3, 7, 9] - odd values, increasing ✓
// Level 3 (odd): [12, 8, 6] - even values, decreasing ✓
// Result: true
//
// Approach: BFS (Level-order traversal)
// 1. Use BFS to traverse the tree level by level
// 2. For each level, track the previous value to check ordering
// 3. Check conditions based on level index (even or odd)
// 4. Even levels: all odd values, strictly increasing
// 5. Odd levels: all even values, strictly decreasing
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(w) - queue size where w is maximum width of tree

class Solution {
public:
    bool isEvenOddTree(TreeNode* root) {
        if (!root) return true;
        
        queue<TreeNode*> q;
        q.push(root);
        int level = 0;
        
        while (!q.empty()) {
            int size = q.size();
            int prevVal = (level % 2 == 0) ? INT_MIN : INT_MAX;
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                int val = node->val;
                
                // Check conditions based on level
                if (level % 2 == 0) {
                    // Even level: values must be odd and strictly increasing
                    if (val % 2 == 0 || val <= prevVal) {
                        return false;
                    }
                } else {
                    // Odd level: values must be even and strictly decreasing
                    if (val % 2 == 1 || val >= prevVal) {
                        return false;
                    }
                }
                
                prevVal = val;
                
                // Add children to queue
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            level++;
        }
        
        return true;
    }
};

