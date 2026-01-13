/*
Problem:
Maximum Element Between Two Nodes of a BST

Given a Binary Search Tree (BST) and two node values a and b,
find the maximum element present on the path between these two nodes
(inclusive).

Rules:
- BST property holds.
- Both a and b are present in the BST.
- a and b can appear in any order.

Example:
BST:
        20
       /  \
      8    22
     / \
    4   12
       /  \
      10  14

a = 10, b = 22

Path: 10 → 12 → 8 → 20 → 22
Maximum = 22

Approach (Optimal – LCA based):
1) Find Lowest Common Ancestor (LCA) of a and b.
2) Traverse from LCA to a and track maximum.
3) Traverse from LCA to b and track maximum.
4) Return the maximum found.

Time Complexity:
O(H)

Space Complexity:
O(1)
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
    Node* LCA(Node* root, int a, int b) {

        while (root) {
            if (a < root->data && b < root->data)
                root = root->left;
            else if (a > root->data && b > root->data)
                root = root->right;
            else
                return root;
        }
        return NULL;
    }

    int maxOnPath(Node* root, int target) {

        int mx = INT_MIN;

        while (root->data != target) {
            mx = max(mx, root->data);
            if (target < root->data)
                root = root->left;
            else
                root = root->right;
        }

        return max(mx, root->data);
    }

    int maxBetweenNodes(Node* root, int a, int b) {

        Node* lca = LCA(root, a, b);

        int max1 = maxOnPath(lca, a);
        int max2 = maxOnPath(lca, b);

        return max(max1, max2);
    }
};
