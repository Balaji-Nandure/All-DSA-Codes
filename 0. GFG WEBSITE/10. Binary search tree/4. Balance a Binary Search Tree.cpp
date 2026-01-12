/*
Problem:
Balance a Binary Search Tree

Given the root of a Binary Search Tree (BST),
convert it into a height-balanced BST.

A height-balanced BST is one where the height difference
between left and right subtrees of every node is at most 1.

Rules:
- BST property must be preserved.
- Relative ordering of elements must remain sorted.

Example:
Input BST (skewed):
1
 \
  2
   \
    3
     \
      4

Output BST (balanced):
      2
     / \
    1   3
         \
          4

Approach (Optimized – Inorder + Divide & Conquer):
- Inorder traversal of BST gives sorted sequence.
- Store inorder traversal in a vector.
- Build a balanced BST from sorted array:
  - Choose middle element as root.
  - Recursively build left and right subtrees.

GeeksforGeeks:
https://www.geeksforgeeks.org/balance-a-binary-search-tree/

LeetCode:
https://leetcode.com/problems/balance-a-binary-search-tree/

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

    Node* build(vector<int>& vals, int l, int r) {
        if (l > r) return NULL;

        int mid = l + (r - l) / 2;
        Node* root = new Node(vals[mid]);

        root->left = build(vals, l, mid - 1);
        root->right = build(vals, mid + 1, r);

        return root;
    }

    Node* balanceBST(Node* root) {

        vector<int> vals;
        inorder(root, vals);

        return build(vals, 0, vals.size() - 1);
    }
};
