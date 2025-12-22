/*
 * Problem: Minimum Time to Burn Tree / Burning Tree
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/burning-tree/1
 *
 * Given a binary tree and a target node value (int target). Find the minimum time required to burn
 * the complete binary tree if the target node (by value) is set on fire. It is known that in 1
 * second all nodes connected to a given node get burned. That is, its left child,
 * right child, and parent.
 *
 * Example:
 *       1
 *      / \
 *     2   3
 *    /     \
 *   4       5
 *
 * Target = 2
 * Time to burn: 3 seconds
 * Explanation:
 * - At t=0: Node 2 is burning
 * - At t=1: Nodes 1, 4 are burning (connected to 2)
 * - At t=2: Node 3 is burning (connected to 1)
 * - At t=3: Node 5 is burning (connected to 3)
 *
 * Approach 1: Build Parent Map + BFS (Optimal)
 * - Build parent map for all nodes
 * - Use BFS starting from target node
 * - Traverse in three directions: left, right, and parent
 * - Track time/distance and return maximum time to burn all nodes
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
#include <algorithm>
using namespace std;

// Solution 1: Build Parent Map + BFS, with target as int value
class ParentMapBFSSolution {
public:
/*
 * Problem: Minimum Time to Burn Binary Tree
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/burning-tree/1
 *
 * Find minimum time to burn entire tree starting from target node.
 * In 1 second, all nodes connected to burning node get burned (left, right, parent).
 *
 * Time: O(n) - build parent map + BFS
 * Space: O(n) - parent map, queue, visited set
 */

    int minTime(TreeNode* root, int target) {
        if (!root) return 0;

        // Build parent map to traverse upward
        unordered_map<TreeNode*, TreeNode*> parent;
        buildParentMap(root, nullptr, parent);

        // Find target node by value
        TreeNode* targetNode = findTargetNode(root, target);
        if (!targetNode) return 0;

        // BFS starting from target (like graph BFS)
        queue<TreeNode*> q;
        unordered_set<TreeNode*> visited;
        q.push(targetNode);
        visited.insert(targetNode);

        int time = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            bool burnedAny = false;

            // Process all nodes at current time
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();

                // Burn connected nodes: left, right, parent
                if (node->left && visited.find(node->left) == visited.end()) {
                    q.push(node->left);
                    visited.insert(node->left);
                    burnedAny = true;
                }
                if (node->right && visited.find(node->right) == visited.end()) {
                    q.push(node->right);
                    visited.insert(node->right);
                    burnedAny = true;
                }
                if (parent[node] && visited.find(parent[node]) == visited.end()) {
                    q.push(parent[node]);
                    visited.insert(parent[node]);
                    burnedAny = true;
                }
            }

            // Increment time if any new nodes were burned
            if (burnedAny) {
                time++;
            }
        }

        return time;
    }

private:
    void buildParentMap(TreeNode* node, TreeNode* par, unordered_map<TreeNode*, TreeNode*>& parent) {
        if (!node) return;
        parent[node] = par;
        buildParentMap(node->left, node, parent);
        buildParentMap(node->right, node, parent);
    }

    // Helper to find the pointer to node with value == target
    TreeNode* findTargetNode(TreeNode* node, int target) {
        if (!node) return nullptr;
        if (node->val == target) return node;
        TreeNode* left = findTargetNode(node->left, target);
        if (left) return left;
        TreeNode* right = findTargetNode(node->right, target);
        if (right) return right;
        return nullptr;
    }
};
