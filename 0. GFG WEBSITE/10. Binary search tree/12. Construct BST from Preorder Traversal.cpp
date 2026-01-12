/*
Problem:
Construct BST from Preorder Traversal

Given an array representing the preorder traversal of a Binary
Search Tree (BST), construct the BST and return its root.

Rules:
- BST property holds (left < root < right).
- No duplicate elements.
- All elements must be used.
- Do NOT sort the array.

Example:
Input:
preorder = [8, 5, 1, 7, 10, 12]

Output BST:
        8
       / \
      5   10
     / \    \
    1   7    12

Approach (Optimized – Bound Based Recursion):
- Preorder traversal visits nodes as: Root → Left → Right.
- Use an index that moves forward in preorder array.
- Maintain valid range (min, max) for current subtree.
- If current value lies outside range, it does not belong to this subtree.
- This constructs BST in one pass.

GeeksforGeeks:
https://www.geeksforgeeks.org/construct-bst-from-given-preorder-traversal/

LeetCode:
https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/

Time Complexity:
O(N)

Space Complexity:
O(H)
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
    Node* buildBST(vector<int>& preorder, int& idx, int low, int high) {

        if (idx >= preorder.size()) return NULL;

        int val = preorder[idx];
        if (val <= low || val >= high) return NULL;

        Node* root = new Node(val);
        idx++;

        root->left = buildBST(preorder, idx, low, val);
        root->right = buildBST(preorder, idx, val, high);

        return root;
    }

    Node* bstFromPreorder(vector<int>& preorder) {

        int idx = 0;
        return buildBST(preorder, idx, INT_MIN, INT_MAX);
    }
};
