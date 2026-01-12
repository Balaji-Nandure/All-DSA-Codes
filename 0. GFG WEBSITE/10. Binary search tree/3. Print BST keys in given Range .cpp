/*
Problem:
Print BST Keys in Given Range

Given a Binary Search Tree (BST) and two integers L and R,
print all the keys of the BST that lie in the inclusive range [L, R],
in sorted (increasing) order.

Rules:
- BST property holds.
- Output should be in sorted order.
- If no keys lie in the range, print nothing.

Example:
BST:
        10
       /  \
      5   20
     / \    \
    3   7    30

L = 5, R = 20

Output:
5 7 10 20

Approach (Optimized – Pruned Inorder Traversal):
- Inorder traversal of BST gives sorted order.
- Use BST property to prune unnecessary branches:
  - If current node < L, skip left subtree.
  - If current node > R, skip right subtree.
- Collect/print keys only when they lie in [L, R].

GeeksforGeeks:
https://www.geeksforgeeks.org/print-bst-keys-in-the-given-range/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(K + H) average, O(N) worst case
(K = number of nodes in range, H = height of BST)

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
    void inorderRange(Node* root, int L, int R, vector<int>& res) {

        if (root == NULL) return;

        if (root->data > L) {
            inorderRange(root->left, L, R, res);
        }

        if (root->data >= L && root->data <= R) {
            res.push_back(root->data);
        }

        if (root->data < R) {
            inorderRange(root->right, L, R, res);
        }
    }

    vector<int> printNearNodes(Node* root, int low, int high) {

        vector<int> res;
        inorderRange(root, low, high, res);
        return res;
    }
};
