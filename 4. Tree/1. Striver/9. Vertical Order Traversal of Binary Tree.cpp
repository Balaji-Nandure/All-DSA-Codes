/*
 * Problem: Vertical Order Traversal of a Binary Tree (LeetCode 987)
 *
 * Given the root of a binary tree, calculate the vertical order traversal
 * of the binary tree. For each position (row, col), collect all nodes at
 * that position. Sort nodes with the same position by their values.
 *
 * Example:
 *       3
 *      / \
 *     9   20
 *        /  \
 *       15   7
 *
 * Coordinates:        Vertical Lines:
 *     (0,0) 3            col -1: [9]
 *     /      \           col  0: [3, 15]
 * (1,-1)9  (1,1)20       col  1: [20]
 *         /    \         col  2: [7]
 *   (2,0)15  (2,2)7
 *
 * Result: [[9], [3,15], [20], [7]]
 *
 * Approach:
 * - Use BFS with coordinates (row, col)
 * - Root starts at (0, 0)
 * - Left child: (row+1, col-1), Right child: (row+1, col+1)
 * - Map vertical lines (col) to nodes with their row and value
 * - Sort nodes at same position by row, then by value
 * - Group by vertical line and return result
 *
 * Time: O(n log n) due to sorting
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
class Solution {
public:
/*
 * Problem: Vertical Order Traversal of a Binary Tree
 *
 * LeetCode 987: Vertical Order Traversal of a Binary Tree
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/print-a-binary-tree-in-vertical-order/1
 *
 * Traverse tree vertically. Nodes at same position (row, col) sorted by value.
 *
 * Time: O(n log n) - sorting nodes at same position
 * Space: O(n) - map and queue
 */

    vector<vector<int>> verticalTraversal(TreeNode* root) {
        // Map: column -> list of (row, value) pairs
        map<int, vector<pair<int, int>>> mp; // col -> [(row, val), ...]
        
        // BFS with coordinates: root at (0, 0)
        queue<pair<TreeNode*, pair<int, int>>> q; // {node, {row, col}}
        q.push({root, {0, 0}});
        
        // Traverse tree level by level
        while (!q.empty()) {
            auto [node, coord] = q.front();
            auto [row, col] = coord;
            q.pop();
            
            // Store node with its coordinates
            mp[col].push_back({row, node->val});
            
            // Left child: (row+1, col-1), Right child: (row+1, col+1)
            if (node->left) q.push({node->left, {row + 1, col - 1}});
            if (node->right) q.push({node->right, {row + 1, col + 1}});
        }
        
        // Build result: sort nodes at same position, then extract values
        vector<vector<int>> result;
        for (auto& [col, nodes] : mp) {
            // Sort by row first, then by value
            sort(nodes.begin(), nodes.end());
            
            // Extract values
            vector<int> vertical;
            for (auto& [row, val] : nodes) {
                vertical.push_back(val); 
            }
            result.push_back(vertical);
        }
        
        return result;
    }
};