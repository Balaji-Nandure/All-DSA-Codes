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
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        // Step 1: Create a map to store nodes grouped by their column (vertical line)
        // Key: column number (col)
        // Value: vector of pairs {row, node_value} for all nodes in that column
        map<int, vector<pair<int, int>>> mp; // col -> [(row, val), ...]
        
        // Step 2: BFS traversal with coordinates
        // Queue stores: {node pointer, {row, col}}
        // Root is at position (0, 0)
        queue<pair<TreeNode*, pair<int, int>>> q; // {node, {row, col}}
        q.push({root, {0, 0}});
        
        // Step 3: Traverse the tree using BFS
        while (!q.empty()) {
            // Get the front node and its coordinates
            auto [node, coord] = q.front();
            auto [row, col] = coord;
            q.pop();
            
            // Store this node in the map with its column as key
            // We store {row, value} so we can sort later
            mp[col].push_back({row, node->val});
            
            // For left child: move down (row+1) and left (col-1)
            if (node->left) q.push({node->left, {row + 1, col - 1}});
            
            // For right child: move down (row+1) and right (col+1)
            if (node->right) q.push({node->right, {row + 1, col + 1}});
        }
        
        // Step 4: Build the result by processing each column
        vector<vector<int>> result;
        for (auto& [col, nodes] : mp) {
            // Sort nodes in the same column:
            // First by row (top to bottom), then by value (if same row)
            // Since pair<int,int> compares first element (row), then second (val)
            sort(nodes.begin(), nodes.end());
            
            // Extract just the values (ignore row info now)
            vector<int> vertical;
            for (auto& [row, val] : nodes) {
                vertical.push_back(val); 
            }
            result.push_back(vertical);
        }
        
        // Step 5: Return result (columns are already sorted by map's key order)
        return result;
    }
};