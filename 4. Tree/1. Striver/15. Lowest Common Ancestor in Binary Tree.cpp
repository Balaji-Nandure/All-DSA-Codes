/*
 * Problem: Lowest Common Ancestor in Binary Tree
 * 
 * LeetCode 236: Lowest Common Ancestor of a Binary Tree
 *
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes
 * in the tree. The lowest common ancestor is defined between two nodes p and q as
 * the lowest node in T that has both p and q as descendants (where we allow a
 * node to be a descendant of itself).
 *
 * Example:
 *       3
 *      / \
 *     5   1
 *    / \ / \
 *   6  2 0  8
 *     / \
 *    7   4
 *
 * LCA(5, 1) = 3
 * LCA(5, 4) = 5
 * LCA(6, 7) = 5
 *
 * Approach 1: Recursive DFS (Optimal)
 * - Traverse the tree recursively
 * - If current node is p or q, return it
 * - Recursively search in left and right subtrees
 * - If both subtrees return non-null, current node is LCA
 * - If one subtree returns non-null, return that result
 *
 * Approach 2: Find paths and compare
 * - Find path from root to p
 * - Find path from root to q
 * - Compare paths and find last common node
 *
 * Approach 3: Iterative with parent pointers
 * - Build parent map for all nodes
 * - Build path from p to root
 * - Traverse from q to root, find first common node
 *
 * Time: O(n) - visit each node once
 * Space: O(h) - recursion stack or path storage, where h is height
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
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Solution 1: Recursive DFS (Optimal - LeetCode 236 standard solution)
class RecursiveLCASolution {
public:
/*
 * Problem: Lowest Common Ancestor in Binary Tree
 *
 * LeetCode 236: Lowest Common Ancestor of a Binary Tree
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/lowest-common-ancestor-in-a-binary-tree/1
 *
 * Find the lowest common ancestor of two nodes in binary tree.
 * LCA is the lowest node that has both nodes as descendants.
 *
 * Time: O(n) - visit each node once
 * Space: O(h) - recursion stack
 */

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // Base case: null or found one of the target nodes
        if (!root || root == p || root == q) {
            return root;
        }
        
        // Search in left and right subtrees
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        
        // If both subtrees return non-null, current node is LCA
        // (p and q are in different subtrees)
        if (left && right) {
            return root;
        }
        
        // If one subtree returns non-null, return that result
        // (either found one node, or LCA is in that subtree)
        return left ? left : right;
    }
};

// Solution 2: Find paths and compare (using root to node path approach)
class PathComparisonLCASolution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;
        
        // Find paths from root to p and q
        vector<TreeNode*> pathP, pathQ;
        findPath(root, p, pathP);
        findPath(root, q, pathQ);
        
        // If either path is empty, nodes don't exist
        if (pathP.empty() || pathQ.empty()) {
            return nullptr;
        }
        
        // Find the last common node in both paths
        TreeNode* lca = nullptr;
        int minLen = min(pathP.size(), pathQ.size());
        
        for (int i = 0; i < minLen; i++) {
            if (pathP[i] == pathQ[i]) {
                lca = pathP[i];
            } else {
                break;
            }
        }
        
        return lca;
    }
    
private:
    bool findPath(TreeNode* root, TreeNode* target, vector<TreeNode*>& path) {
        if (!root) return false;
        
        path.push_back(root);
        
        // whenever i reach the target i return back;
        if (root == target) {
            return true;
        }
        
        // pruning or returning from here if any of the case is true;
        if (findPath(root->left, target, path) || 
            findPath(root->right, target, path)) {
            return true;
        }
        
        path.pop_back();
        return false;
    }
};
