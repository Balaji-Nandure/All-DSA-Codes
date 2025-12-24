/*
 * Problem: Largest BST in Binary Tree
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/largest-bst/1
 * 
 * Given a binary tree. Find the size of its largest subtree that is a Binary Search Tree.
 * Note: Here Size is equal to the number of nodes in the subtree.
 *
 * Example 1:
 * Input:
 *        1
 *      /   \
 *     4     4
 *   /   \
 *  6     8
 *
 * Output: 1
 * Explanation: There's no sub-tree with size greater than 1 which forms a BST.
 *
 * Example 2:
 * Input: 6 6 3 N 2 9 3 N 8 8 2
 *            6
 *          /   \
 *         6     3
 *          \   / \
 *           2 9   3
 *            / \
 *           8   8
 *          /
 *         2
 *
 * Output: 2
 * Explanation: The following subtree is a BST of size 2:
 *        2
 *      /   \
 *     8     8
 *    /
 *   2
 *
 * Example 3:
 * Input:
 *        50
 *      /    \
 *    30      60
 *   /  \    /  \
 *  5   20  45  70
 *              /  \
 *            65    80
 *
 * Output: 5
 * Explanation: The following subtree is a BST of size 5:
 *        60
 *      /  \
 *    45   70
 *         /  \
 *       65   80
 *
 * Key Insight:
 * - For each node, we need to know if the subtree rooted at it is a BST
 * - If it is a BST, we need its size, min value, and max value
 * - Use bottom-up approach: process children first, then parent
 * - A subtree is BST if:
 *   1. Left subtree is BST
 *   2. Right subtree is BST
 *   3. max(left) < root->val < min(right)
 *
 * Approach: Post-order Traversal with Info Structure
 * - Return a structure containing: isBST, size, min, max
 * - For each node:
 *   - Get info from left and right subtrees
 *   - Check if current subtree is BST
 *   - If BST, calculate size and update global max
 *   - Return info to parent
 *
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(h) - recursion stack where h is height
 */

/**
 * Definition for a binary tree node.
 * struct Node {
 *     int data;
 *     Node *left;
 *     Node *right;
 *     Node() : data(0), left(nullptr), right(nullptr) {}
 *     Node(int x) : data(x), left(nullptr), right(nullptr) {}
 *     Node(int x, Node *left, Node *right) : data(x), left(left), right(right) {}
 * };
 */
#include <climits>
#include <algorithm>
using namespace std;

// Best solution: No struct, just use reference parameters.
class Solution {
private:
    // Helper function:
    // Returns: size of BST in this subtree if valid BST; otherwise returns -1.
    // minVal and maxVal represent the min/max values in this subtree after the call.

    // minVal and maxVal passed by ref because we need to update the min and max values of the subtree.
    int largestBST(Node* root, int& minVal, int& maxVal, int& maxBSTSize) {
        if (!root) {
            minVal = INT_MAX;
            maxVal = INT_MIN;
            return 0; // Null tree is BST of size 0
        }

        int lMin, lMax, rMin, rMax;
        int leftSize = largestBST(root->left, lMin, lMax, maxBSTSize);
        int rightSize = largestBST(root->right, rMin, rMax, maxBSTSize);

        // Is subtree rooted at root a BST?
        if (leftSize != -1 && rightSize != -1 && lMax < root->data && root->data < rMin) {
            // It is BST!
            minVal = (root->left) ? lMin : root->data;
            maxVal = (root->right) ? rMax : root->data;
            int curSize = leftSize + rightSize + 1;
            maxBSTSize = max(maxBSTSize, curSize);
            return curSize;
        }

        // Not BST
        return -1;
    }

public:
    int largestBst(Node* root) {
        int maxBSTSize = 0;
        int minVal, maxVal;
        largestBST(root, minVal, maxVal, maxBSTSize);
        return maxBSTSize;
    }
};
