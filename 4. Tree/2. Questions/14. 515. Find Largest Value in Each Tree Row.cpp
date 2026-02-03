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

// Problem: Find Largest Value in Each Tree Row (LeetCode 515)
// Given the root of a binary tree, return an array of the largest value 
// in each row of the tree (0-indexed).
//
// Approach 1: BFS (Level-order traversal)
// 1. Use BFS to traverse the tree level by level
// 2. For each level, track the maximum value among all nodes
// 3. Add the maximum value to result array
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(w) - queue size where w is maximum width of tree

class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        if (!root) return {};
        
        vector<int> result;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            int maxVal = INT_MIN;
            
            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // Update maximum value for this level
                maxVal = max(maxVal, node->val);
                
                // Add children to queue for next level
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            result.push_back(maxVal);
        }
        
        return result;
    }
};

// Approach 2: DFS (Recursive)
// 1. Use DFS to traverse the tree, tracking current depth
// 2. For each depth, update the maximum value if current node is larger
// 3. Use a result vector where index represents the level
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(h) - recursion stack where h is height

class Solution2 {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> result;
        dfs(root, 0, result);
        return result;
    }
    
private:
    void dfs(TreeNode* node, int depth, vector<int>& result) {
        if (!node) return;
        
        // If this is the first node at this depth, add it to result
        if (depth == result.size()) {
            result.push_back(node->val);
        } else {
            // Update maximum value at this depth
            result[depth] = max(result[depth], node->val);
        }
        
        // Recursively process left and right subtrees
        dfs(node->left, depth + 1, result);
        dfs(node->right, depth + 1, result);
    }
};



