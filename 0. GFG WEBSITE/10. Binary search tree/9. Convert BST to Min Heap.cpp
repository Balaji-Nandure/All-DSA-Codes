/*
Problem:
Convert BST to Min Heap

Given a Binary Search Tree (BST), convert it to a Min Heap
such that:
- The structure of the original tree is preserved.
- The Min Heap property holds (parent <= children).

Rules:
- Do NOT change the tree structure.
- Only node values can be modified.
- BST property is not required after conversion.

Example:
Input BST:
        4
       / \
      2   6
     / \ / \
    1  3 5  7

Output Min Heap (one possible):
        1
       / \
      2   5
     / \ / \
    3  4 6  7

Approach (Optimized – Inorder + Preorder):
- Inorder traversal of BST gives sorted values.
- Store inorder traversal in a vector.
- Perform preorder traversal on the tree:
  - Replace node values using the sorted array in sequence.
- Preorder ensures parent gets smaller value before children,
  maintaining Min Heap property.

GeeksforGeeks:
https://www.geeksforgeeks.org/convert-bst-min-heap/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

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
    void inorder(Node* root, vector<int>& vals) {
        if (root == NULL) return;
        inorder(root->left, vals);
        vals.push_back(root->data);
        inorder(root->right, vals);
    }

    void preorderAssign(Node* root, vector<int>& vals, int& idx) {
        if (root == NULL) return;

        root->data = vals[idx++];
        preorderAssign(root->left, vals, idx);
        preorderAssign(root->right, vals, idx);
    }

    void convertToMinHeap(Node* root) {

        vector<int> vals;
        inorder(root, vals);

        int idx = 0;
        preorderAssign(root, vals, idx);
    }
};
