/*
 Problem: Construct Binary Search Tree from Preorder Traversal

 LeetCode 1008: Construct Binary Search Tree from Preorder Traversal
 GFG: https://practice.geeksforgeeks.org/problems/construct-bst-from-preorder-traversal/1

 Given an array of integers `preorder` representing the preorder traversal of a BST,
 construct the tree and return its root.

 Assumptions:
 - It is guaranteed that a BST can always be constructed for the input.

 Example:
 Input:  preorder = [8, 5, 1, 7, 10, 12]
 Output: 
           8
         /   \
        5     10
       / \      \
      1   7      12

 BST Properties:
 - Left subtree: nodes < root
 - Right subtree: nodes > root
 - Preorder: Root → Left → Right

 Approaches:
 1. Recursive with Bounds (min/max)
    - Use bounds to restrict placement of nodes (left: (min, root->val), right: (root->val, max))
 2. Recursive with Index Tracking
    - Use index to process preorder and find subtree splits
 3. Iterative with Stack
    - Simulate recursion via explicit stack

 Time Complexity:  O(n) (each element visited once)
 Space Complexity: O(h) (call stack or stack, h = tree height)
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
#include <climits>
using namespace std;

// Solution 4: Recursive Simple (Using Upper Bound)
class RecursiveUpperBoundSolution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int index = 0;
        return build(preorder, index, INT_MAX);
    }

private:
/*
 * Problem: Construct Binary Search Tree from Preorder Traversal
 *
 * LeetCode 1008: Construct Binary Search Tree from Preorder Traversal
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/construct-bst-from-preorder-traversal/1
 *
 * Build BST from preorder array.
 * First element is root, then left subtree (all < root), then right subtree (all > root).
 *
 * Time: O(n) - visit each element once
 * Space: O(h) - recursion stack
 */

    // Helper: Build tree using upper bound to restrict placement
    TreeNode* build(vector<int>& preorder, int& index, int upperBound) {
        // Base case: all processed or current value exceeds bound
        if (index >= (int)preorder.size() || preorder[index] > upperBound)
            return nullptr;

        // Create root from current preorder element
        int val = preorder[index++];
        TreeNode* root = new TreeNode(val);

        // Left subtree: values < val (bound = val)
        root->left  = build(preorder, index, val);
        // Right subtree: values > val but <= upperBound
        root->right = build(preorder, index, upperBound);

        return root;
    }
};