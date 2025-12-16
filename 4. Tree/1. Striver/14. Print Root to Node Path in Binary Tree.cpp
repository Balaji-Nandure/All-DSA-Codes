/*
 * Problem: Print Root to Node Path in Binary Tree
 * 
 * LeetCode 257: Binary Tree Paths (print all root-to-leaf paths)
 * GeeksforGeeks Practice (Root to Node): https://practice.geeksforgeeks.org/problems/root-to-leaf-paths/1
 *
 * Problem 1: Find path from root to a specific target node
 *
 * Problem 1: Find path from root to a specific target node
 * Given a binary tree and a target node value, return the path from root to that node.
 *
 * Problem 2: Print all root-to-leaf paths (LeetCode 257)
 * Given a binary tree, return all root-to-leaf paths.
 *
 * Example:
 *       1
 *      / \
 *     2   3
 *    /   / \
 *   4   5   6
 *
 * Path to node 5: [1, 3, 5]
 * All root-to-leaf paths: ["1->2->4", "1->3->5", "1->3->6"]
 *
 * Approach:
 * - Use DFS (recursive) to traverse the tree
 * - Maintain a path vector during traversal
 * - When target is found (or leaf is reached), store/print the path
 * - Backtrack by removing current node from path before returning
 *
 * Time: O(n) - visit each node once
 * Space: O(h) - where h is the height (for recursion stack and path storage)
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
#include <string>
using namespace std;

// Solution 1: Find path from root to a specific target node
class RootToNodePathSolution {
public:
    vector<int> rootToNodePath(TreeNode* root, int target) {
        vector<int> path;
        findPath(root, target, path);
        return path;
    }
private:
    bool findPath(TreeNode* node, int target, vector<int>& path) {
        if (!node) return false;
        path.push_back(node->val);
        if (node->val == target) return true;
        if (findPath(node->left, target, path)) return true;
        if (findPath(node->right, target, path)) return true;
        path.pop_back();
        return false;
    }
};

// Solution 2: Print all root-to-leaf paths as strings (LeetCode 257)
class BinaryTreePathsSolution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        if (!root) return result;
        string currentPath;
        dfs(root, currentPath, result);
        return result;
    }
private:
    void dfs(TreeNode* node, string currentPath, vector<string>& result) {
        if (!node) return;
        if (!currentPath.empty()) {
            currentPath += "->";
        }
        currentPath += to_string(node->val);
        if (!node->left && !node->right) {
            result.push_back(currentPath);
            return;
        }
        dfs(node->left, currentPath, result);
        dfs(node->right, currentPath, result);
    }
};

// Solution 3: Print all root-to-leaf paths as vector of vectors
class AllRootToLeafPathsSolution {
public:
    vector<vector<int>> allPaths(TreeNode* root) {
        vector<vector<int>> result;
        vector<int> path;
        findAllPaths(root, path, result);
        return result;
    }
private:
    void findAllPaths(TreeNode* node, vector<int>& path, vector<vector<int>>& result) {
        if (!node) return;
        path.push_back(node->val);
        if (!node->left && !node->right) {
            result.push_back(path);
        } else {
            findAllPaths(node->left, path, result);
            findAllPaths(node->right, path, result);
        }
        path.pop_back();
    }
};
