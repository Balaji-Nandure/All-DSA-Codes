/*
 * Problem: Construct Binary Tree from Postorder and Inorder Traversal
 *
 * LeetCode 106: Construct Binary Tree from Inorder and Postorder Traversal
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/tree-from-postorder-and-inorder/1
 *
 * Given two integer arrays inorder and postorder where inorder is the inorder traversal
 * of a binary tree and postorder is the postorder traversal of the same tree, construct and
 * return the binary tree.
 *
 * Example:
 * inorder = [9, 3, 15, 20, 7]
 * postorder = [9, 15, 7, 20, 3]
 *
 * Result:
 *       3
 *      / \
 *     9   20
 *        /  \
 *       15   7
 *
 * Approach 1: Recursive with Hash Map (Optimal)
 * - Use hash map to store inorder indices for O(1) lookup
 * - Last element of postorder is always the root
 * - Find root in inorder to split left and right subtrees
 * - Recursively build right and left subtrees (note right first)
 *
 * Approach 2: Recursive without Hash Map (O(n^2))
 * - Same logic but search for root in inorder array each time
 * - Less efficient but simpler
 *
 * Time: O(n) with hash map, O(n^2) without
 * Space: O(n) for hash map and recursion stack
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
#include <unordered_map>
#include <stack>
using namespace std;

// Solution 1: Recursive with Hash Map (Optimal - O(n) time)
class RecursiveHashMapSolution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        if (n == 0) return nullptr;

        // Build hash map for O(1) lookup of inorder indices
        unordered_map<int, int> inorderMap; // inorderMap[value] = index
        for (int i = 0; i < n; i++) {
            inorderMap[inorder[i]] = i;
        }

        int postIndex = n - 1;
        return build(postorder, inorder, 0, n - 1, postIndex, inorderMap);
    }

private:
/*
 * Problem: Construct Binary Tree from Postorder and Inorder Traversal
 *
 * LeetCode 106: Construct Binary Tree from Inorder and Postorder Traversal
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/tree-from-postorder-and-inorder/1
 *
 * Build binary tree from postorder and inorder traversals.
 * Postorder gives root (from end), inorder splits left and right subtrees.
 *
 * Time: O(n) with hash map, O(n^2) without
 * Space: O(n) - hash map and recursion stack
 */

    TreeNode* build(vector<int>& postorder, vector<int>& inorder,
                   int inStart, int inEnd, int& postIndex,
                   unordered_map<int, int>& inorderMap) {
        // Base case: invalid range
        if (inStart > inEnd) return nullptr;

        // Root is next element in postorder (from the end, decrementing)
        int rootVal = postorder[postIndex--];
        TreeNode* root = new TreeNode(rootVal);

        // Find root position in inorder (O(1) with map)
        int rootIndex = inorderMap[rootVal];

        // Build right subtree first (since postIndex decrements)
        root->right = build(postorder, inorder, rootIndex + 1, inEnd, postIndex, inorderMap);

        // Build left subtree
        root->left = build(postorder, inorder, inStart, rootIndex - 1, postIndex, inorderMap);

        return root;
    }
};

// Solution 2: Recursive without Hash Map (O(n^2) time)
class RecursiveNoHashMapSolution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        if (n == 0) return nullptr;

        int postIndex = n - 1;
        return build(postorder, inorder, 0, n - 1, postIndex);
    }

private:
    TreeNode* build(vector<int>& postorder, vector<int>& inorder,
                   int inStart, int inEnd, int& postIndex) {
        if (inStart > inEnd) return nullptr;

        // Current root is next element in postorder (from the end)
        int rootVal = postorder[postIndex--];
        TreeNode* root = new TreeNode(rootVal);

        // Find root position in inorder (O(n) search)
        int rootIndex = inStart;
        for (int i = inStart; i <= inEnd; i++) {
            if (inorder[i] == rootVal) {
                rootIndex = i;
                break;
            }
        }

        // Build right subtree first, then left subtree
        root->right = build(postorder, inorder, rootIndex + 1, inEnd, postIndex);

        root->left = build(postorder, inorder, inStart, rootIndex - 1, postIndex);

        return root;
    }
};
