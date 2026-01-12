/*
Problem:
BST to a Tree with Sum of All Smaller Keys

Given a Binary Search Tree (BST), convert it into a tree such that
every node contains the sum of all keys smaller than the original
key of that node.

Rules:
- BST property holds initially.
- Tree structure must remain unchanged.
- Update node values in-place.
- “Smaller” is strictly smaller (exclude the node’s original value).

Example:
Input BST:
        5
       / \
      3   7
     / \   \
    2   4   8

Output Tree:
        9
       / \
      2   15
     / \    \
    0   5    20

Explanation:
- Node 2  → sum of smaller = 0
- Node 3  → 2
- Node 4  → 2 + 3 = 5
- Node 5  → 2 + 3 + 4 = 9
- Node 7  → 2 + 3 + 4 + 5 = 14 (then updated tree reflects values)
- Node 8  → 2 + 3 + 4 + 5 + 7 = 21

Approach (Optimized – Inorder Traversal):
- Inorder traversal (Left → Root → Right) visits nodes in increasing order.
- Maintain a running prefix sum of previously visited nodes.
- Replace current node’s value with the running sum (before adding its original value).
- Then add the original value to the running sum.

GeeksforGeeks:
https://www.geeksforgeeks.org/bst-to-a-tree-with-sum-of-all-smaller-keys/

LeetCode:
No direct equivalent problem.

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
    void inorder(Node* root, int& prefixSum) {

        if (root == NULL) return;

        inorder(root->left, prefixSum);

        int original = root->data;
        root->data = prefixSum;
        prefixSum += original;

        inorder(root->right, prefixSum);
    }

    Node* transformTree(Node* root) {

        int prefixSum = 0;
        inorder(root, prefixSum);
        return root;
    }
};
