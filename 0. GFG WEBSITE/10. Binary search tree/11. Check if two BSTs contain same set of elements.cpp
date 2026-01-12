/*
Problem:
Check if Two BSTs Contain the Same Set of Elements

Given roots of two Binary Search Trees (BSTs), check whether
both BSTs contain the same set of elements, irrespective of
their structure.

Rules:
- BST property holds for both trees.
- Order/shape of trees does NOT matter.
- Only element values matter.
- Return true if both contain exactly the same elements.

Example:
BST1:            BST2:
   5                10
  / \              /  \
 3   7            5    15
                    \
                     7

Output:
true

Approach (Optimized – Inorder Traversal Comparison):
- Inorder traversal of a BST produces sorted elements.
- Perform inorder traversal on both BSTs.
- Store results in two arrays.
- Compare the arrays for equality.

GeeksforGeeks:
https://www.geeksforgeeks.org/check-two-bsts-contain-set-elements/

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
    void inorder(Node* root, vector<int>& arr) {
        if (root == NULL) return;
        inorder(root->left, arr);
        arr.push_back(root->data);
        inorder(root->right, arr);
    }

    bool sameSet(Node* root1, Node* root2) {

        vector<int> a, b;

        inorder(root1, a);
        inorder(root2, b);

        return a == b;
    }
};
