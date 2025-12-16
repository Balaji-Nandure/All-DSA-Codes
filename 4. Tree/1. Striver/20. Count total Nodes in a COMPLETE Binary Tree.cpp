/*
 * Problem: Count Complete Tree Nodes
 *
 * LeetCode 222: Count Complete Tree Nodes
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/count-nodes-of-linked-list/1
 *
 * Given the root of a complete binary tree, return the number of the nodes in the tree.
 * In a complete binary tree, every level, except possibly the last, is completely filled,
 * and all nodes in the last level are as far left as possible.
 *
 * Example:
 *       1
 *      / \
 *     2   3
 *    / \ /
 *   4  5 6
 *
 * Output: 6
 *
 * Approach 1: Binary Search on Last Level (Optimal)
 * - For complete binary tree, we can use the property that it's filled left to right
 * - Find the height of the tree
 * - Use binary search to find the last node in the last level
 * - Calculate total nodes = 2^h - 1 + nodes in last level
 *
 * Approach 4: Optimized Recursive (Using Complete Tree Property)
 * - Check if left and right subtrees have same height
 * - If yes, left subtree is perfect: 2^h - 1 nodes
 * - If no, right subtree is perfect: 2^(h-1) - 1 nodes
 * - Recursively count the other subtree
 *
 * Approach 5: Iterative Level Order with Early Termination (Optimized for Complete Tree)
 * - Compute height via leftmost path
 * - If the tree is perfect, return 2^(h+1)-1
 * - Otherwise, do level order count
 *
 * Approach 2: Recursive DFS (Simple but O(n))
 * - Traverse the entire tree and count nodes
 * - Works for any binary tree, not just complete
 *
 * Approach 3: Iterative BFS
 * - Use level-order traversal to count all nodes
 * - Works for any binary tree
 *
 * Time: O(log^2 n) for optimal, O(n) for simple approaches
 * Space: O(log n) for recursion stack
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

#include <queue>
#include <cmath>
using namespace std;

// Solution 1: Binary Search on Last Level (Optimal - O(log^2 n))
class BinarySearchLastLevelSolution {
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;

        int height = getHeight(root);
        if (height == 0) return 1;

        // Number of nodes in upper levels (perfect tree): 2^h - 1
        int upperNodes = (1 << height) - 1;

        // Binary search to find the last node in the last level
        int left = 0, right = (1 << height) - 1;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (exists(root, height, mid)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        return upperNodes + left + 1;
    }

private:
    int getHeight(TreeNode* root) {
        int height = 0;
        while (root->left) {
            height++;
            root = root->left;
        }
        return height;
    }

    bool exists(TreeNode* root, int height, int idx) {
        int left = 0, right = (1 << height) - 1;
        for (int i = 0; i < height; i++) {
            int mid = left + (right - left) / 2;
            if (idx <= mid) {
                root = root->left;
                right = mid;
            } else {
                root = root->right;
                left = mid + 1;
            }
        }
        return root != nullptr;
    }
};

// Solution 4: Optimized Recursive Using Complete Tree Property (O(log^2 n))
class OptimizedRecursiveSolution {
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;

        int leftHeight = getLeftHeight(root);
        int rightHeight = getRightHeight(root);

        // If left and right subtrees have same height, left subtree is perfect
        if (leftHeight == rightHeight) {
            // Left subtree is perfect: 2^h - 1 nodes
            // Plus root (1) + recursively count right subtree
            return (1 << leftHeight) - 1 + 1 + countNodes(root->right);
        } else {
            // Right subtree is perfect: 2^(h-1) - 1 nodes
            // Plus root (1) + recursively count left subtree
            return (1 << rightHeight) - 1 + 1 + countNodes(root->left);
        }
    }

private:
    int getLeftHeight(TreeNode* root) {
        int height = 0;
        while (root) {
            height++;
            root = root->left;
        }
        return height;
    }

    int getRightHeight(TreeNode* root) {
        int height = 0;
        while (root) {
            height++;
            root = root->right;
        }
        return height;
    }
};

// Solution 5: Iterative Level Order with Early Termination (Optimized for Complete Tree)
class IterativeOptimizedSolution {
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;

        int height = 0;
        TreeNode* node = root;
        while (node->left) {
            height++;
            node = node->left;
        }

        // If tree is perfect, return 2^(h+1) - 1
        if (isPerfect(root, height)) {
            return (1 << (height + 1)) - 1;
        }

        // Otherwise, count normally
        int count = 0;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            count++;

            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }

        return count;
    }

private:
    bool isPerfect(TreeNode* root, int height) {
        for (int i = 0; i < height; i++) {
            if (!root->right) return false;
            root = root->right;
        }
        return true;
    }
};

// Solution 2: Recursive DFS (Simple - O(n))
class RecursiveDFSSolution {
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};

// Solution 3: Iterative BFS (O(n))
class IterativeBFSSolution {
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;

        queue<TreeNode*> q;
        q.push(root);
        int count = 0;

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            count++;

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        return count;
    }
};
