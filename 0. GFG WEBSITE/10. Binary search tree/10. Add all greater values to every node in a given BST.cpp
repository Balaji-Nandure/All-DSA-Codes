/*
Problem:
Add all Greater and Equal Values to Every Node in a BST

Given a Binary Search Tree (BST), modify it such that
for every node, its value is replaced by the sum of
all values greater than or equal to it in the BST.

Rules:
- BST property holds initially.
- Tree structure must remain unchanged.
- Update node values in-place.

Example:
Input BST:
        5
      /   \
     2     13

Output BST:
        18
      /    \
    20      13

Explanation:
- Node 13 → 13
- Node 5  → 5 + 13 = 18
- Node 2  → 2 + 5 + 13 = 20

Approach (Optimized – Reverse Inorder Traversal):
- Reverse inorder traversal of BST (Right → Root → Left)
  visits nodes in decreasing order.
- Maintain a running sum of visited nodes.
- Add the running sum to current node value.

GeeksforGeeks:
https://www.geeksforgeeks.org/add-greater-values-every-node-given-bst/

LeetCode:
Equivalent to "Binary Search Tree to Greater Sum Tree"

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

    void addGreater(Node* root) {

        int sum = 0;
        reverseInorder(root, sum);
    }
};
