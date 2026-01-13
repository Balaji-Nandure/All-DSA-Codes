/*
Problem:
K-th Smallest Element in a Binary Search Tree (BST)

Given the root of a BST and an integer K, find the K-th smallest
element present in the BST.

Rules:
- BST property holds (left < root < right).
- Inorder traversal of BST gives sorted order.
- 1 ≤ K ≤ number of nodes in BST.

Example:
BST:
        5
       / \
      3   6
     / \
    2   4
   /
  1

K = 3

Output:
3

Approach (Optimal – Inorder Traversal with Early Stopping):
- Perform inorder traversal (Left → Root → Right).
- Decrement K when visiting each node.
- When K becomes 0, current node is the answer.
- Stop traversal immediately after finding result.

GeeksforGeeks:
https://www.geeksforgeeks.org/find-k-th-smallest-element-in-bst/

LeetCode:
https://leetcode.com/problems/kth-smallest-element-in-a-bst/

Time Complexity:
O(H + K) average, O(N) worst case

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
    void inorder(Node* root, int& k, int& ans) {

        if (root == NULL || k == 0) return;

        inorder(root->left, k, ans);

        if (k == 0) return;

        k--;
        if (k == 0) {
            ans = root->data;
            return;
        }

        inorder(root->right, k, ans);
    }

    int kthSmallest(Node* root, int K) {

        int ans = -1;
        inorder(root, K, ans);
        return ans;
    }
};