/*
 * Problem: Binary Tree Zigzag Level Order Traversal (LeetCode 103)
 *
 * Given the root of a binary tree, return the zigzag level order traversal
 * of its nodes' values. (i.e., from left to right, then right to left for
 * the next level and alternate between).
 *
 * Approach:
 * - Use BFS (level order traversal) with a flag to alternate direction
 * - For even levels: left to right (normal)
 * - For odd levels: right to left (reverse)
 * - Can use deque or reverse the level vector based on level number
 *
 * Time: O(n)
 * Space: O(n) for queue and result
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;
        
        while (!q.empty()) {
            int size = q.size();
            vector<int> level(size);
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // Fill level array based on direction
                int index = leftToRight ? i : (size - 1 - i);
                level[index] = node->val;
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            result.push_back(level);
            leftToRight = !leftToRight; // Toggle direction
        }
        
        return result;
    }
};

