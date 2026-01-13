/*
Problem:
Lowest Common Ancestor (LCA) in a Binary Search Tree (BST)

Given a Binary Search Tree (BST) and two node values n1 and n2,
find their Lowest Common Ancestor (LCA).

Definition:
- LCA is the lowest node in the tree that has both n1 and n2
  as descendants (a node can be a descendant of itself).

Rules:
- BST property holds (left < root < right).
- Both keys are guaranteed to be present in the BST.

Example:
BST:
        20
       /  \
      8    22
     / \
    4   12
       /  \
      10  14

n1 = 10, n2 = 14

Output:
12

Approach (Optimal – BST Property Based Traversal):
- If both n1 and n2 are smaller than root → go left.
- If both n1 and n2 are greater than root → go right.
- Otherwise, current root is the LCA.
- Stop immediately once LCA is found.

GeeksforGeeks:
https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-search-tree/

LeetCode:
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/

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
    Node* LCA(Node* root, int n1, int n2) {

        while (root != NULL) {

            if (n1 < root->data && n2 < root->data) {
                root = root->left;
            }
            else if (n1 > root->data && n2 > root->data) {
                root = root->right;
            }
            else {
                return root;
            }
        }

        return NULL;
    }
};
