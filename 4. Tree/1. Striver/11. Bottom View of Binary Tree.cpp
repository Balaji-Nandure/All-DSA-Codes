/* 
 * Problem: Bottom View of Binary Tree
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/bottom-view-of-binary-tree/1
 *
 * Given the root of a binary tree, return the bottom view of the tree.
 * The bottom view of a binary tree is the set of nodes visible when the tree
 * is viewed from the bottom. For each vertical line, we only see the bottommost node.
 *
 * Example:
 *       1
 *      / \
 *     2   3
 *    / \ / \
 *   4  5 6  7
 *
 * Coordinates:        Bottom View (last node in each column):
 *     (0,0) 1            col -2: 4
 *     /      \           col -1: 5 (or 2, depending on traversal)
 * (1,-1)2  (1,1)3        col  0: 5 or 6 (last node in column 0)
 *   / \      / \         col  1: 7
 * (2,-2)4 (2,0)5 (2,0)6 (2,2)7  col  2: 7
 *
 * Result: [4, 5, 6, 7] (or [4, 2, 5, 6, 7] depending on which nodes are bottommost)
 *
 * Approach:
 * - Use BFS with column index only (no need to store row)
 * - Root starts at col = 0
 * - Left child: col-1, Right child: col+1
 * - Map each column to the last node encountered (bottommost node)
 * - Since BFS processes level by level, we keep updating each column with the latest node
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
    vector<int> bottomView(TreeNode* root) {
        if (!root) return {};
        
        // Step 1: Create a map to store the bottommost node for each column
        // Key: column number (col)
        // Value: node value (we keep updating with the last node we see in each column)
        map<int, int> mp; // col -> node_value
        
        // Step 2: BFS traversal with only col information
        // Queue stores: {node pointer, col}
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});
        
        // Step 3: Traverse the tree using BFS
        while (!q.empty()) {
            auto [node, col] = q.front();
            q.pop();

            // Always update the column with the current node
            // This ensures we get the last (bottommost) node in each column
            mp[col] = node->val;
            
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