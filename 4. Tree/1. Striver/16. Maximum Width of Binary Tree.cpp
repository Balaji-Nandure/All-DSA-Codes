/*
 * Problem: Maximum Width of Binary Tree
 * 
 * LeetCode 662: Maximum Width of Binary Tree
 *
 * Given the root of a binary tree, return the maximum width of the given tree.
 * The maximum width of a tree is the maximum width among all levels.
 * The width of one level is defined as the length between the end-nodes
 * (the leftmost and rightmost non-null nodes), where the null nodes between
 * the end-nodes that would have been present in a complete binary tree
 * extending down to that level are also counted into the length calculation.
 *
 * Example 1:
 *       1
 *      / \
 *     3   2
 *    /     \
 *   5       9
 *
 * Level 0: [1] -> width = 1
 * Level 1: [3, 2] -> width = 2
 * Level 2: [5, null, null, 9] -> width = 4 (counting nulls)
 * Maximum width = 4
 *
 * Example 2:
 *       1
 *      / \
 *     3   2
 *    /
 *   5
 *
 * Level 0: [1] -> width = 1
 * Level 1: [3, 2] -> width = 2
 * Level 2: [5] -> width = 1
 * Maximum width = 2
 *
 * Approach 1: BFS with Indexing (Optimal)
 * - Assign index to each node (root = 0, left = 2*parent+1, right = 2*parent+2)
 * - For each level, calculate width = last_index - first_index + 1
 * - Track maximum width across all levels
 *
 * Approach 2: DFS with Indexing
 * - Use DFS to traverse and assign indices
 * - Track first index at each level
 * - Calculate width when visiting nodes
 *
 * Approach 3: BFS with Position Tracking
 * - Store position (level, position) for each node
 * - Calculate width using min and max positions at each level
 *
 * Time: O(n) - visit each node once
 * Space: O(n) - queue/stack storage
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
#include <algorithm>
#include <climits>
using namespace std;

// Solution 1: BFS with Indexing (Optimal - LeetCode 662 standard solution)
class BFSIndexingSolution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        
        queue<pair<TreeNode*, unsigned long long>> q; // {node, index}
        q.push({root, 0});
        int maxWidth = 0;
        
        while (!q.empty()) {
            int levelSize = q.size();
            unsigned long long firstIndex = q.front().second;
            unsigned long long lastIndex = firstIndex;
            
            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                auto [node, index] = q.front();
                q.pop();
                
                lastIndex = index;
                
                // Assign indices to children
                // Left child: 2*index + 1, Right child: 2*index + 2
                if (node->left) {
                    q.push({node->left, 2 * index + 1});
                }
                if (node->right) {
                    q.push({node->right, 2 * index + 2});
                }
            }
            
            // Calculate width for current level
            int width = lastIndex - firstIndex + 1;
            maxWidth = max(maxWidth, width);
        }
        
        return maxWidth;
    }
};