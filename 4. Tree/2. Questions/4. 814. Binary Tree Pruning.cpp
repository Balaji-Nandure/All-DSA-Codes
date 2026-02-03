// 814. Binary Tree Pruning
// Given the root of a binary tree, return the same tree where every subtree (of the given tree) not containing a 1 has been removed.
// A subtree of a node is node plus every node that is a descendant of node.

// Example 1:
// Input: root = [1,null,0,0,1]
//        1
//         \
//          0
//         / \
//        0   1
// Output: [1,null,0,null,1]
//         1
//          \
//           0
//            \
//             1

// Example 2:
// Input: root = [1,0,1,0,0,0,1]
//        1
//       / \
//      0   1
//     / \ / \
//    0  0 0  1
// Output: [1,null,1,null,1]
//         1
//          \
//           1
//            \
//             1

#include <iostream>
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

// Approach: Post-order DFS (Bottom-up pruning)
// Key Insight: We need to check if a subtree contains any 1s before deciding to prune it
// - Process children before parent (post-order traversal)
// - A subtree should be pruned if:
//   1. The node's value is 0, AND
//   2. Both left and right subtrees are null (already pruned or don't exist)
// - Return nullptr to prune the subtree, otherwise return the node
//
// Algorithm:
// 1. Recursively process left and right subtrees first
// 2. If a child returns nullptr, it means that subtree was pruned
// 3. After processing children, check if current node should be pruned:
//    - If node value is 0 and both children are null, prune it (return nullptr)
//    - Otherwise, keep the node (return node)
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(h) - recursion stack where h is the height of the tree

class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        // Base case: empty tree
        if (!root) {
            return nullptr;
        }
        
        // Post-order: recursively prune left and right subtrees first
        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);
        
        // After pruning children, check if current node should be pruned
        // Prune if: node value is 0 AND both children are null
        if (root->val == 0 && !root->left && !root->right) {
            return nullptr;
        }
        
        // Keep the node (it either has value 1 or has children with 1s)
        return root;
    }
};

// Alternative Approach: Helper function with explicit containsOne check
class Solution2 {
private:
    // Returns true if the subtree rooted at node contains at least one 1
    bool containsOne(TreeNode* node) {
        if (!node) return false;
        
        // Check if current node is 1 or any subtree contains 1
        bool leftContains = containsOne(node->left);
        bool rightContains = containsOne(node->right);
        
        // Prune children that don't contain 1
        if (!leftContains) node->left = nullptr;
        if (!rightContains) node->right = nullptr;
        
        // Current subtree contains 1 if node is 1 or any child contains 1
        return node->val == 1 || leftContains || rightContains;
    }
    
public:
    TreeNode* pruneTree(TreeNode* root) {
        // If root doesn't contain any 1, return nullptr
        return containsOne(root) ? root : nullptr;
    }
};

// Time Complexity: O(n)
// Space Complexity: O(h) for recursion stack

