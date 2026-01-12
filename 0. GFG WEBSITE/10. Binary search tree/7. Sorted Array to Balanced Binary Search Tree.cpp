/*
Problem:
Sorted Array to Balanced Binary Search Tree

Given a sorted array of integers (in increasing order),
construct a height-balanced Binary Search Tree (BST).

A height-balanced BST is defined as a tree where the difference
between heights of left and right subtrees for every node is at most 1.

Rules:
- Use all elements of the array.
- The resulting tree must be height-balanced.
- BST property must be preserved.

Example:
Input:
arr = [1, 2, 3, 4, 5, 6, 7]

Output (one possible BST):
        4
       / \
      2   6
     / \ / \
    1  3 5  7

Approach (Optimized – Divide and Conquer):
- Since the array is already sorted:
  - Choose the middle element as root.
  - Recursively construct left subtree from left half.
  - Recursively construct right subtree from right half.
- This guarantees minimum height.

GeeksforGeeks:
https://www.geeksforgeeks.org/sorted-array-to-balanced-bst/

LeetCode:
https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

Time Complexity:
O(N)

Space Complexity:
O(H)  (recursion stack), H = log N for balanced tree
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
    Node* build(vector<int>& arr, int l, int r) {

        if (l > r) return NULL;

        int mid = l + (r - l) / 2;
        Node* root = new Node(arr[mid]);

        root->left = build(arr, l, mid - 1);
        root->right = build(arr, mid + 1, r);

        return root;
    }

    Node* sortedArrayToBST(vector<int>& arr) {

        return build(arr, 0, arr.size() - 1);
    }
};
