/*
 * Problem: Two Sum In BST
 *
 * LeetCode 653: Two Sum IV - Input is a BST
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/find-a-pair-with-given-target-in-bst/1
 *
 * Given the root of a Binary Search Tree and a target number k, return true if
 * there exist two elements in the BST such that their sum is equal to the given target.
 *
 * Example 1:
 * Input: root = [5,3,6,2,4,null,7], k = 9
 * Output: true
 * Explanation:
 *       5
 *      / \
 *     3   6
 *    / \   \
 *   2   4   7
 * 
 * 3 + 6 = 9, so return true
 *
 * Example 2:
 * Input: root = [5,3,6,2,4,null,7], k = 28
 * Output: false
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [1, 10^4]
 * - -10^4 <= Node.val <= 10^4
 * - root is a valid binary search tree
 * - -10^5 <= k <= 10^5
 *
 * Approach 1: Inorder Traversal + Two Pointers (Optimal)
 * - Perform inorder traversal to get sorted array
 * - Use two pointers (left and right) to find pair
 * - Time: O(n), Space: O(n)
 *
 * Approach 2: Hash Set (Simple)
 * - Traverse tree and store values in set
 * - For each node, check if (k - node->val) exists in set
 * - Time: O(n), Space: O(n)
 *
 * Approach 3: Two BST Iterators (Space Optimized)
 * - Use BSTIterator for forward traversal (left to right)
 * - Use reverse BSTIterator for backward traversal (right to left)
 * - Similar to two pointers on sorted array
 * - Time: O(n), Space: O(h) where h is height
 *
 * Time Complexity: O(n) - visit each node at most once
 * Space Complexity: O(n) for array/hash, O(h) for iterator approach
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
#include <unordered_set>
#include <stack>
using namespace std;

// Solution 1: Inorder Traversal + Two Pointers (Optimal)
class Solution {
private:
    void inorderTraversal(TreeNode* root, vector<int>& inorder) {
        if (root == nullptr) return;
        inorderTraversal(root->left, inorder);
        inorder.push_back(root->val);
        inorderTraversal(root->right, inorder);
    }
    
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> inorder;
        inorderTraversal(root, inorder);
        
        // Two pointers approach on sorted array
        int left = 0, right = inorder.size() - 1;
        while (left < right) {
            int sum = inorder[left] + inorder[right];
            if (sum == k) {
                return true;
            } else if (sum < k) {
                left++; // Need larger sum
            } else {
                right--; // Need smaller sum
            }
        }
        return false;
    }
};

// Most optimal
// Solution 3: Two Pointer BST Iterator in a Single Class (Space Optimized - O(h) Space)
class SingleIteratorSolution {
private:
    stack<TreeNode*> leftStack, rightStack;

    // Push all left children (for forward/inorder iterator)
    void pushLeft(TreeNode* node) {
        while (node) {
            leftStack.push(node);
            node = node->left;
        }
    }
    // Push all right children (for reverse/inorder iterator)
    void pushRight(TreeNode* node) {
        while (node) {
            rightStack.push(node);
            node = node->right;
        }
    }

    // Get next smallest value from leftStack
    int getNextLeft() {
        TreeNode* node = leftStack.top();
        leftStack.pop();
        pushLeft(node->right);
        return node->val;
    }
    // Get next largest value from rightStack
    int getNextRight() {
        TreeNode* node = rightStack.top();
        rightStack.pop();
        pushRight(node->left);
        return node->val;
    }

    // Return true if left stack (forward pointer) still has values
    bool hasLeft() { return !leftStack.empty(); }
    // Return true if right stack (reverse pointer) still has values
    bool hasRight() { return !rightStack.empty(); }

public:
    bool findTarget(TreeNode* root, int k) {
        if (!root) return false;
        pushLeft(root);
        pushRight(root);

        int leftVal = getNextLeft();
        int rightVal = getNextRight();

        // Loop until the two pointers meet (ensure not the same node)
        while (leftVal < rightVal) {
            int sum = leftVal + rightVal;
            if (sum == k)
                return true;
            else if (sum < k) {
                if (hasLeft())
                    leftVal = getNextLeft();
                else
                    break;
            } else {
                if (hasRight())
                    rightVal = getNextRight();
                else
                    break;
            }
        }
        return false;
    }
};

