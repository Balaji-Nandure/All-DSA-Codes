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

// Problem: Add a row of nodes with value val at depth depth
// Approach: BFS to reach depth-1, then insert new nodes
class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        // Special case: if depth is 1, create new root
        if (depth == 1) {
            TreeNode* newRoot = new TreeNode(val);
            newRoot->left = root;
            return newRoot;
        }
        
        // BFS to reach depth - 1
        queue<TreeNode*> q;
        q.push(root);
        int currentDepth = 1;
        
        while (!q.empty() && currentDepth < depth - 1) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            currentDepth++;
        }
        
        // Now we're at depth - 1, insert new nodes
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop(); 
            
            // Insert new node on the left
            TreeNode* newLeft = new TreeNode(val);
            newLeft->left = node->left;
            node->left = newLeft;
            
            // Insert new node on the right
            TreeNode* newRight = new TreeNode(val);
            newRight->right = node->right;
            node->right = newRight;
        }
        
        return root;
    }
};

