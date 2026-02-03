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

// Problem: Flip Equivalent Binary Trees (LeetCode 951)
// For a binary tree T, we can define a flip operation as follows: choose any node, 
// and swap the left and right child subtrees.
// A binary tree X is flip equivalent to a binary tree Y if and only if we can 
// make X equal to Y after some number of flip operations.
// Given the roots of two binary trees root1 and root2, return true if the two 
// trees are flip equivalent or false otherwise.
//
// Example:
//     1              1
//    / \            / \
//   2   3          3   2
//  / \              / \
// 4   5            5   4
// These trees are flip equivalent.
//
// Key Insights:
// 1. Two trees are flip equivalent if:
//    - Both are null, OR
//    - Both have same value AND
//    - Either (left1 matches left2 AND right1 matches right2) OR
//            (left1 matches right2 AND right1 matches left2)
// 2. Use recursion to check all possibilities
//
// Approach: Recursive DFS
// 1. Base cases: if both null, return true; if one null, return false
// 2. If values don't match, return false
// 3. Check two scenarios:
//    a) No flip: left matches left AND right matches right
//    b) Flip: left matches right AND right matches left
// 4. Return true if either scenario is true
//
// Time Complexity: O(min(n1, n2)) - visit nodes until mismatch found
// Space Complexity: O(min(h1, h2)) - recursion stack where h is height

class Solution {
public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        // Base cases
        if (!root1 && !root2) return true;
        if (!root1 || !root2) return false;
        if (root1->val != root2->val) return false;
        
        // Check two scenarios: no flip or flip
        bool noFlip = flipEquiv(root1->left, root2->left) && 
                      flipEquiv(root1->right, root2->right);
        
        bool withFlip = flipEquiv(root1->left, root2->right) && 
                        flipEquiv(root1->right, root2->left);
        
        return noFlip || withFlip;
    }
};
