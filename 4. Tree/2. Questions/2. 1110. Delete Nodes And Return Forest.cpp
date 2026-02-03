// 1110. Delete Nodes And Return Forest
// Given the root of a binary tree, each node in the tree has a distinct value.
// After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).
// Return the roots of the trees in the remaining forest. You may return the result in any order.

#include <vector>
#include <unordered_set>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Alternative Approach: Post-order traversal with explicit parent tracking
class Solution2 {
private:
    TreeNode* dfs(TreeNode* node, unordered_set<int>& toDeleteSet, vector<TreeNode*>& result) {
        if (!node) return nullptr;
        
        // Post-order: process children first
        node->left = dfs(node->left, toDeleteSet, result);
        node->right = dfs(node->right, toDeleteSet, result);
        
        // If current node should be deleted
        if (toDeleteSet.count(node->val)) {
            // Add non-null children to result (they become new roots)
            if (node->left) result.push_back(node->left);
            if (node->right) result.push_back(node->right);
            
            // Return nullptr to disconnect from parent
            return nullptr;
        }
        
        // Keep the node
        return node;
    }
    
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_set<int> toDeleteSet(to_delete.begin(), to_delete.end());
        vector<TreeNode*> result;
        
        // Process the tree
        root = dfs(root, toDeleteSet, result);
        
        // If root wasn't deleted, add it to result
        if (root) {
            result.push_back(root);
        }
        
        return result;
    }
};

// Time Complexity: O(n) where n is the number of nodes in the tree
// Space Complexity: O(n + m) where m is the size of to_delete array (for the set)
//                   O(h) for recursion stack where h is the height of the tree

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
 // Alternative Approach: q (Level-order traversal)
 class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        // Handle empty tree
        if (!root) {
            return {};
        }

        // Convert to_delete array to set for O(1) lookup
        unordered_set<int> toDelete(to_delete.begin(), to_delete.end());
        vector<TreeNode*> forest;

        // q queue to traverse the tree level by level
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            // Process left child
            if (curr->left) {
                q.push(curr->left);
                // If left child should be deleted, disconnect it from parent
                if (toDelete.find(curr->left->val) != toDelete.end()) {
                    curr->left = nullptr;
                }
            } 

            // Process right child
            if (curr->right) {
                q.push(curr->right);
                // If right child should be deleted, disconnect it from parent
                if (curr->right && toDelete.find(curr->right->val) != toDelete.end()) {
                    curr->right = nullptr;
                }
            } 

            // If current node should be deleted
            if (toDelete.find(curr->val) != toDelete.end()) {
                // Add non-null children to forest (they become new roots)
                if (curr->left) forest.push_back(curr->left);
                if (curr->right) forest.push_back(curr->right);
            }
        }

        // If root wasn't deleted, add it to the forest
        if (toDelete.find(root->val) == toDelete.end()) {
            forest.push_back(root);
        }
        return forest;
    }
};