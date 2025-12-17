/*
 * Problem: K-th Smallest or Largest Element in BST
 *
 * LeetCode 230: Kth Smallest Element in a BST
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/find-k-th-smallest-element-in-bst/1
 *
 * Given the root of a binary search tree, and an integer k, return the kth
 * smallest value (1-indexed) of all the values of the nodes in the tree.
 *
 * Example:
 * Input:
 *       5
 *      / \
 *     3   6
 *    / \
 *   2   4
 *  /
 * 1
 *
 * k = 3
 * Output: 3 (3rd smallest element)
 *
 * BST Property:
 * - Left subtree contains nodes with values < root
 * - Right subtree contains nodes with values > root
 * - Inorder traversal gives elements in sorted order
 *
 * Approach 1: Inorder Traversal (Recursive)
 * - Perform inorder traversal (Left -> Root -> Right)
 * - Count nodes visited, return kth node
 *
 * Approach 2: Inorder Traversal (Iterative with Stack)
 * - Use stack to simulate inorder traversal
 * - Pop k times to get kth smallest
 *
 * Approach 3: Morris Traversal (O(1) space)
 * - Use threading for inorder traversal without stack
 *
 * For K-th Largest:
 * - Use reverse inorder (Right -> Root -> Left)
 * - Or find (n-k+1)th smallest
 *
 * Time: O(h + k) where h is height
 * - O(log n + k) for balanced BST
 * - O(n + k) for skewed BST
 * Space: O(h) for recursion/stack, O(1) for Morris
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

#include <stack>
using namespace std;
// Solution 1: Recursive Inorder Traversal
class Solution {
public:
    int helper(TreeNode *root, int &k){
        // Base case: if root is NULL, return -1
        if(!root) return -1;
        // Traverse left subtree
        int left = helper(root->left, k);
        // If left subtree has a valid result, return it
        if(left != -1) return left;
        // Process current node
        k--;
        // If k is 0, we've found the kth smallest element
        if(!k) return root->val;
        // Traverse right subtree
        return helper(root->right, k);
    }

    int kthSmallest(TreeNode* root, int k) {
        int ans = helper(root, k);
        return ans;
    }
};
 
// Solution 3: Recursive with Early Return (Optimized)
class RecursiveOptimizedSolution {
public:
    int kthSmallest(TreeNode* root, int k) {
        int result = -1;
        int count = 0;
        helper(root, k, count, result);
        return result;
    }
    
private:
    bool helper(TreeNode* root, int k, int& count, int& result) {
        if (root == NULL) return false;
        
        // Check left subtree
        if (helper(root->left, k, count, result)) {
            return true;
        }
        
        // Process current node
        count++;
        if (count == k) {
            result = root->val;
            return true;
        }
        
        // Check right subtree
        return helper(root->right, k, count, result);
    }
};

// Solution 4: K-th Largest Element (Reverse Inorder)
class KthLargestSolution {
public:
    int kthLargest(TreeNode* root, int k) {
        int count = 0;
        int result = -1;
        reverseInorder(root, k, count, result);
        return result;
    }
    
private:
    void reverseInorder(TreeNode* root, int k, int& count, int& result) {
        if (root == NULL || result != -1) return;
        
        // Traverse right subtree first (largest values)
        reverseInorder(root->right, k, count, result);
        
        // Process current node
        count++;
        if (count == k) {
            result = root->val;
            return;
        }
        
        // Traverse left subtree
        reverseInorder(root->left, k, count, result);
    }
};

// Solution 5: K-th Largest using Iterative Stack
class KthLargestIterativeSolution {
public:
    int kthLargest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        TreeNode* current = root;
        int count = 0;
        
        while (current != NULL || !st.empty()) {
            // Go to rightmost node
            while (current != NULL) {
                st.push(current);
                current = current->right;
            }
            
            // Process node
            current = st.top();
            st.pop();
            count++;
            
            if (count == k) {
                return current->val;
            }
            
            // Move to left subtree
            current = current->left;
        }
        
        return -1;
    }
};
