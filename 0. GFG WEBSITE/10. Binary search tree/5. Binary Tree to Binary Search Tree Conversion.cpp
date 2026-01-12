/*
Problem:
Binary Tree to Binary Search Tree Conversion

Given a Binary Tree, convert it into a Binary Search Tree (BST)
such that:
- The structure of the original binary tree is preserved.
- Only the node values are changed.
- The resulting tree satisfies BST properties.

Rules:
- Left subtree values < root value < right subtree values.
- No new nodes should be created.
- Tree structure must remain the same.

Example:
Input Binary Tree:
        10
       /  \
      2    7
     / \
    8   4

Output BST (one possible):
        7
       / \
      4   10
     / \
    2   8

Approach (Optimized – Inorder Replacement):
- Inorder traversal of a binary tree gives nodes in a fixed structural order.
- Convert tree values to BST by:
  1. Store all node values using inorder traversal.
  2. Sort the collected values.
  3. Replace node values again using inorder traversal from the sorted list.

Why this works:
- Inorder traversal of a BST produces sorted values.
- By assigning sorted values in inorder position order,
  BST property is guaranteed while preserving structure.

GeeksforGeeks:
https://www.geeksforgeeks.org/binary-tree-to-binary-search-tree-conversion/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N log N)

Space Complexity:
O(N)
*/

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = NULL;
        right = NULL;
    }
};

class Solution {
public:
    void storeInorder(Node* root, vector<int>& vals) {
        if (root == NULL) return;
        storeInorder(root->left, vals);
        vals.push_back(root->data);
        storeInorder(root->right, vals);
    }

    void replaceInorder(Node* root, vector<int>& vals, int& idx) {
        if (root == NULL) return;
        replaceInorder(root->left, vals, idx);
        root->data = vals[idx++];
        replaceInorder(root->right, vals, idx);
    }

    Node* binaryTreeToBST(Node* root) {

        vector<int> vals;
        storeInorder(root, vals);

        sort(vals.begin(), vals.end());

        int idx = 0;
        replaceInorder(root, vals, idx);

        return root;
    }
};
