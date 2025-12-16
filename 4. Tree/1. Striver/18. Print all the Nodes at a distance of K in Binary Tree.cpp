/*
 * Problem: All Nodes Distance K in Binary Tree
 *
 * LeetCode 863: All Nodes Distance K in Binary Tree
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/nodes-at-given-distance-in-binary-tree/1
 *
 * Given the root of a binary tree, the value of a target node target, and an integer k,
 * return an array of the values of all nodes that have a distance k from the target node.
 *
 * Example:
 *        3
 *      /   \
 *     5     1
 *    / \   / \
 *   6  2  0  8
 *     / \
 *    7   4
 *
 * Target = 5, k = 2
 * Output: [7, 4, 1]
 *
 * Explanation: Nodes at distance 2 from node 5 are: 7, 4, and 1
 *
 * Approach 1: Build Parent Map + BFS (Optimal)
 * - Build a parent map for all nodes
 * - Use BFS starting from target node
 * - Traverse in three directions: left, right, and parent
 * - Track distance and collect nodes at distance k
 *
 * Approach 2: DFS to Find Target + BFS from Target
 * - First DFS to find target node and build parent map
 * - Then BFS from target to find nodes at distance k
 *
 * Approach 3: Two-Pass DFS
 * - First pass: Find target and build path from root to target
 * - Second pass: For each node on path, find nodes at distance k-i
 *
 * Time: O(n) - visit each node once
 * Space: O(n) - parent map and queue storage
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Solution 1: Build Parent Map + BFS (Optimal - LeetCode 863 standard solution)
class ParentMapBFSSolution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        if (!root || !target) return {};
        
        // Build parent map
        unordered_map<TreeNode*, TreeNode*> parent;
        buildParentMap(root, nullptr, parent);
        
        // BFS starting from target
        queue<TreeNode*> q;
        unordered_set<TreeNode*> visited;
        q.push(target);
        visited.insert(target);
        
        int distance = 0;
        while (!q.empty() && distance < k) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // Traverse in three directions: left, right, parent
                if (node->left && visited.find(node->left) == visited.end()) {
                    q.push(node->left);
                    visited.insert(node->left);
                }
                if (node->right && visited.find(node->right) == visited.end()) {
                    q.push(node->right);
                    visited.insert(node->right);
                }
                if (parent[node] && visited.find(parent[node]) == visited.end()) {
                    q.push(parent[node]);
                    visited.insert(parent[node]);
                }
            }
            distance++;
        }
        
        // Collect nodes at distance k
        vector<int> result;
        while (!q.empty()) {
            result.push_back(q.front()->val);
            q.pop();
        }
        
        return result;
    }
    
private:
    void buildParentMap(TreeNode* node, TreeNode* par, unordered_map<TreeNode*, TreeNode*>& parent) {
        if (!node) return;
        parent[node] = par;
        buildParentMap(node->left, node, parent);
        buildParentMap(node->right, node, parent);
    }
};