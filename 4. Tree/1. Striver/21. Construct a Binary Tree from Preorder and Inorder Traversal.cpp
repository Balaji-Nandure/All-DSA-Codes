/*
 * Problem: Construct Binary Tree from Preorder and Inorder Traversal
 *
 * LeetCode 105: Construct Binary Tree from Preorder and Inorder Traversal
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/construct-tree-1/1
 *
 * Given two integer arrays preorder and inorder where preorder is the preorder traversal
 * of a binary tree and inorder is the inorder traversal of the same tree, construct and
 * return the binary tree.
 *
 * Example:
 * preorder = [3, 9, 20, 15, 7]
 * inorder = [9, 3, 15, 20, 7]
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
 * - First element of preorder is always the root
 * - Find root in inorder to split left and right subtrees
 * - Recursively build left and right subtrees
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        if (n == 0) return nullptr;
        
        // Build hash map for O(1) lookup of inorder indices
        unordered_map<int, int> inorderMap; // inorderMap[value] = index
        for (int i = 0; i < n; i++) {
            inorderMap[inorder[i]] = i;
        }
        
        int preIndex = 0;
        return build(preorder, inorder, 0, n - 1, preIndex, inorderMap);
    }
    
private:
/*
 * Problem: Construct Binary Tree from Preorder and Inorder Traversal
 *
 * LeetCode 105: Construct Binary Tree from Preorder and Inorder Traversal
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/construct-tree-1/1
 *
 * Build binary tree from preorder and inorder traversals.
 * Preorder gives root, inorder splits left and right subtrees.
 *
 * Time: O(n) with hash map, O(n^2) without
 * Space: O(n) - hash map and recursion stack
 */

    TreeNode* build(vector<int>& preorder, vector<int>& inorder, 
                   int inStart, int inEnd, int& preIndex,
                   unordered_map<int, int>& inorderMap) {
        // Base case: invalid range
        if (inStart > inEnd) return nullptr;
        
        // Root is next element in preorder
        int rootVal = preorder[preIndex++];
        TreeNode* root = new TreeNode(rootVal);
        
        // Find root position in inorder (O(1) with map)
        int rootIndex = inorderMap[rootVal];
        
        // Build left subtree: elements before root in inorder
        root->left = build(preorder, inorder, inStart, rootIndex - 1, preIndex, inorderMap);
        
        // Build right subtree: elements after root in inorder
        root->right = build(preorder, inorder, rootIndex + 1, inEnd, preIndex, inorderMap);
        
        return root;
    }
};

// Solution 2: Recursive without Hash Map (O(n^2) time)
class RecursiveNoHashMapSolution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        if (n == 0) return nullptr;
        
        int preIndex = 0;
        return build(preorder, inorder, 0, n - 1, preIndex);
    }
    
private:
    TreeNode* build(vector<int>& preorder, vector<int>& inorder, 
                   int inStart, int inEnd, int& preIndex) {
        if (inStart > inEnd) return nullptr;
        
        // Current root is the next element in preorder
        int rootVal = preorder[preIndex++];
        TreeNode* root = new TreeNode(rootVal);
        
        // Find root position in inorder (O(n) search)
        int rootIndex = inStart;
        for (int i = inStart; i <= inEnd; i++) {
            if (inorder[i] == rootVal) {
                rootIndex = i;
                break;
            }
        }
        
        // Build left subtree (elements before root in inorder)
        root->left = build(preorder, inorder, inStart, rootIndex - 1, preIndex);
        
        // Build right subtree (elements after root in inorder)
        root->right = build(preorder, inorder, rootIndex + 1, inEnd, preIndex);
        
        return root;
    }
};
