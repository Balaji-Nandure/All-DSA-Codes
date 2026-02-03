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

// Approach 1: Level Order Traversal (BFS) - Reverse values at odd levels
class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        if (!root) return nullptr;
        
        queue<TreeNode*> q;
        q.push(root);
        int level = 0;
        
        while (!q.empty()) {
            int size = q.size();
            vector<TreeNode*> nodes;
            
            // Collect all nodes at current level
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                nodes.push_back(node);
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            // If odd level, reverse the values
            if (level % 2 == 1) {
                int left = 0, right = nodes.size() - 1;
                while (left < right) {
                    swap(nodes[left]->val, nodes[right]->val);
                    left++;
                    right--;
                }
            }
            
            level++;
        }
        
        return root;
    }
};

// Approach 2: DFS - Swap values of nodes at odd levels
class Solution2 {
public:
    TreeNode* reverseOddLevels(TreeNode* root) {
        dfs(root->left, root->right, 1);
        return root;
    }
    
private:
    void dfs(TreeNode* left, TreeNode* right, int level) {
        if (!left || !right) return;
        
        // If odd level, swap values
        if (level % 2 == 1) {
            swap(left->val, right->val);
        }
        
        // Recursively process next level
        // Mirror traversal: left's left with right's right, left's right with right's left
        dfs(left->left, right->right, level + 1);
        dfs(left->right, right->left, level + 1);
    }
};

