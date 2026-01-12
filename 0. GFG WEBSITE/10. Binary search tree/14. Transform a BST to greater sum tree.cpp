/*
Problem:
Transform a BST to Greater Sum Tree (GST)

Given a Binary Search Tree (BST), transform it into a Greater Sum Tree
such that each node’s value is replaced by the sum of all values
greater than or equal to it in the original BST.

Rules:
- BST property holds initially.
- Tree structure must remain unchanged.
- Modification is done in-place.

Example:
Input BST:
        4
       / \
      1   6
         / \
        5   7

Output GST:
        22
       /  \
     28    13
          /  \
         18   7

Approach (Optimized – Reverse Inorder Traversal):
- Reverse inorder traversal (Right → Root → Left) visits nodes
  in descending order.
- Maintain a running sum.
- Add running sum to current node value.

GeeksforGeeks:
https://www.geeksforgeeks.org/transform-bst-greater-sum-tree/

LeetCode:
https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/

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
    void reverseInorder(Node* root, int& sum) {

        if (root == NULL) return;

        reverseInorder(root->right, sum);

        sum += root->data;
        root->data = sum;

        reverseInorder(root->left, sum);
    }

    Node* transformTree(Node* root) {

        int sum = 0;
        reverseInorder(root, sum);
        return root;
    }
};
