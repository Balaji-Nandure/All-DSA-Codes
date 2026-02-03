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

class Solution {
private:
    // Returns the node if it should be kept, nullptr if it should be deleted
    TreeNode* helper(TreeNode* node, bool isRoot, unordered_set<int>& toDeleteSet, vector<TreeNode*>& forest) {
        if (!node) return nullptr;
        
        // Check if current node should be deleted
        bool shouldDelete = toDeleteSet.count(node->val);
        
        // If current node is a root (either original root or becomes root after parent deletion)
        // and it's not being deleted, add it to the forest
        if (isRoot && !shouldDelete) {
            forest.push_back(node);
        }
        
        // Process children
        // If current node is deleted, its children become potential roots
        node->left = helper(node->left, shouldDelete, toDeleteSet, forest);
        node->right = helper(node->right, shouldDelete, toDeleteSet, forest);
        
        // Return nullptr if node should be deleted, otherwise return the node
        return shouldDelete ? nullptr : node;
    }
    
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        // Convert to_delete to set for O(1) lookup
        unordered_set<int> toDeleteSet(to_delete.begin(), to_delete.end());
        vector<TreeNode*> forest;
        
        // Start DFS with root as a potential root
        helper(root, true, toDeleteSet, forest);
        
        return forest;
    }
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

