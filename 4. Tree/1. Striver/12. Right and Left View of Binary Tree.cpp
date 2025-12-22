/*
 * Problem: Right View and Left View of Binary Tree
 * 
 * Right View (LeetCode 199): Binary Tree Right Side View
 * Left View (GeeksforGeeks Practice): https://practice.geeksforgeeks.org/problems/left-view-of-binary-tree/1
 *
 * Right View: Given the root of a binary tree, imagine yourself standing on the
 * right side of it, return the values of the nodes you can see ordered from top to bottom.
 *
 * Left View: Given the root of a binary tree, imagine yourself standing on the
 * left side of it, return the values of the nodes you can see ordered from top to bottom.
 *
 * Example:
 *       1
 *      / \
 *     2   3
 *    / \   \
 *   4   5   6
 *
 * Right View: [1, 3, 6]  (rightmost node at each level)
 * Left View:  [1, 2, 4]  (leftmost node at each level)
 *
 * Approach:
 * - Use BFS (level-order traversal)
 * - For Right View: Store the last node at each level
 * - For Left View: Store the first node at each level
 * - Track level information during traversal
 *
 * Time: O(n)
 * Space: O(n)
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

#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
/*
 * Problem: Right View and Left View of Binary Tree
 *
 * LeetCode 199: Binary Tree Right Side View
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/left-view-of-binary-tree/1
 *
 * Right View: rightmost node at each level.
 * Left View: leftmost node at each level.
 *
 * Time: O(n) - single pass
 * Space: O(n) - queue
 */

    // Right View: Store last node at each level
    vector<int> rightSideView(TreeNode* root) {
        if (!root) return {};
        
        vector<int> result;
        queue<TreeNode*> q;
        q.push(root);
        
        // BFS level by level
        while (!q.empty()) {
            int levelSize = q.size();
            
            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // Store last node (rightmost) at this level
                if (i == levelSize - 1) {
                    result.push_back(node->val);
                }
                
                // Add children for next level
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return result;
    }
    
    // Left View: Store first node at each level
    vector<int> leftSideView(TreeNode* root) {
        if (!root) return {};
        
        vector<int> result;
        queue<TreeNode*> q;
        q.push(root);
        
        // BFS level by level
        while (!q.empty()) {
            int levelSize = q.size();
            
            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // Store first node (leftmost) at this level
                if (i == 0) {
                    result.push_back(node->val);
                }
                
                // Add children for next level
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return result;
    }
};


// Recursive solution for Right View of Binary Tree (beautified)
class Solution {
public:
    // Helper DFS function for Right View
    void dfsRight(TreeNode* node, int depth, vector<int>& result) {
        if (!node) return;

        // If visiting this depth for the first time, add node value (rightmost at this level)
        if (depth == result.size()) result.push_back(node->val);

        // Recurse right first to ensure rightmost nodes are seen first
        dfsRight(node->right, depth + 1, result);
        dfsRight(node->left, depth + 1, result);
    }

    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        dfsRight(root, 0, result);
        return result;
    }

    // Recursive solution for Left View of Binary Tree (beautified)
    void dfsLeft(TreeNode* node, int depth, vector<int>& result) {
        if (!node) return;

        // If visiting this depth for the first time, add node value (leftmost at this level)
        if (depth == result.size()) result.push_back(node->val);

        // Recurse left first to ensure leftmost nodes are seen first
        dfsLeft(node->left, depth + 1, result);
        dfsLeft(node->right, depth + 1, result);
    }

    vector<int> leftSideView(TreeNode* root) {
        vector<int> result;
        dfsLeft(root, 0, result);
        return result;
    }
};



