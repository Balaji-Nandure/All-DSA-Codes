/*
 * Problem: Top View of Binary Tree
 *
 * GeeksforGeeks: https://www.geeksforgeeks.org/print-nodes-top-view-binary-tree/
 *
 * Given the root of a binary tree, return the top view of the tree.
 * The top view of a binary tree is the set of nodes visible when the tree
 * is viewed from the top. For each vertical line, we only see the topmost node.
 *
 * Example:
 *       1
 *      / \
 *     2   3
 *    / \ / \
 *   4  5 6  7
 *
 * Coordinates:        Top View (first node in each column):
 *     (0,0) 1            col -2: 4
 *     /      \           col -1: 2
 * (1,-1)2  (1,1)3        col  0: 1
 *   / \      / \         col  1: 3
 * (2,-2)4 (2,0)5 (2,0)6 (2,2)7  col  2: 7
 *
 * Result: [4, 2, 1, 3, 7]
 *
 * Approach:
 * - Use BFS with column index only (no need to store row)
 * - Root starts at col = 0
 * - Left child: col-1, Right child: col+1
 * - Map each column to the first node encountered (topmost node)
 * - Since BFS processes level by level, first node in each column is the topmost
 * - Return nodes in column order (left to right)
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
#include <map>
using namespace std;

class Solution {
public:
    vector<int> topView(TreeNode* root) {
        if (!root) return {};
        // Step 1: Create a map to store the topmost node for each column
        map<int, int> mp; // col -> node_value
        
        // Step 2: BFS traversal with only col information
        // Queue stores: {node pointer, col}
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});
        
        // Step 3: Traverse the tree using BFS
        while (!q.empty()) {
            auto [node, col] = q.front();
            q.pop();

            // If this is the first time we're seeing this column, store the node
            if (mp.find(col) == mp.end()) {
                mp[col] = node->val;
            }
            
            if (node->left) q.push({node->left, col - 1});
            if (node->right) q.push({node->right, col + 1});
        }
        
        // Step 4: Build the result by extracting values in column order
        vector<int> result;
        for (auto& [col, val] : mp) {
            result.push_back(val);
        }
        
        // Step 5: Return result (columns are already sorted by map's key order)
        return result;
    }
};
