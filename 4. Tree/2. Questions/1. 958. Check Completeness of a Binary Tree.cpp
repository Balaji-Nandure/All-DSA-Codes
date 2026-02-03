/*
 * Problem: Check Completeness of a Binary Tree
 * 
 * LeetCode 958: Check Completeness of a Binary Tree
 * 
 * Given the root of a binary tree, determine if it is a complete binary tree.
 * 
 * In a complete binary tree, every level, except possibly the last, is completely filled,
 * and all nodes in the last level are as far left as possible. It can have between 1 and
 * 2^h nodes inclusive at the last level h.
 * 
 * Example 1:
 *       1
 *      / \
 *     2   3
 *    / \  /
 *   4  5 6
 * 
 * Output: true
 * Explanation: Every level before the last is full, and all nodes in the last level are as far left as possible.
 * 
 * Example 2:
 *       1
 *      / \
 *     2   3
 *    / \   \
 *   4  5    7
 * 
 * Output: false
 * Explanation: The node with value 7 isn't as far left as possible.
 * 
 * Approach:
 * Use BFS (level-order traversal) with a flag to track if we've seen a null node.
 * In a complete binary tree, once we encounter a null node, all subsequent nodes must be null.
 * If we find a non-null node after seeing a null, the tree is not complete.
 * 
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(n) - queue can hold up to n/2 nodes at the last level
 */

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

#include <queue>
using namespace std;

class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        if (!root) return true;
        
        queue<TreeNode*> q;
        q.push(root);
        
        // Flag to track if we've encountered a null node
        bool seenNull = false;
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            // If current node is null
            if (!node) {
                seenNull = true;
            } else {
                // If we've seen a null before and now we see a non-null node,
                // the tree is not complete
                if (seenNull) {
                    return false;
                }
                
                // Add both children to queue (even if they are null)
                // This allows us to detect gaps in the tree
                q.push(node->left);
                q.push(node->right);
            }
        }
        
        return true;
    }
};

// Alternative Approach: Using indexing
// Assign indices to nodes like in a heap (root = 1, left child = 2*i, right child = 2*i+1)
// If the tree is complete, the maximum index should equal the number of nodes
class Solution2 {
private:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    
    bool checkComplete(TreeNode* root, int index, int totalNodes) {
        if (!root) return true;
        
        // If index exceeds total nodes, tree is not complete
        if (index > totalNodes) return false;
        
        // Check left and right subtrees
        return checkComplete(root->left, 2 * index, totalNodes) &&
               checkComplete(root->right, 2 * index + 1, totalNodes);
    }
    
public:
    bool isCompleteTree(TreeNode* root) {
        int totalNodes = countNodes(root);
        return checkComplete(root, 1, totalNodes);
    }
};

// Time Complexity: O(n)
// Space Complexity: O(h) for recursion stack, where h is height


