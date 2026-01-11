/*
Problem:
Search a Node in a Binary Tree

Given a binary tree and a target value X,
check whether a node with value X exists in the tree.

Rules:
- Tree is NOT necessarily a BST.
- Return true if found, else false.

Example:
Input:
        1
      /   \
     2     3
    / \
   4   5

X = 5

Output:
true

Approach (Optimized – DFS / Recursive):
- Traverse the tree using Depth First Search.
- At each node:
  - If node value equals X, return true.
  - Recursively search left and right subtrees.
- If traversal ends, return false.

GeeksforGeeks:
https://www.geeksforgeeks.org/search-an-element-in-a-binary-tree/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(H)  (H = height of tree due to recursion)
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
    bool search(Node* root, int x) {

        if (root == NULL) return false;

        if (root->data == x) return true;

        return search(root->left, x) || search(root->right, x);
    }
};
