/*
Problem:
Shortest Distance between Two Nodes in a Binary Search Tree (BST)

Given a Binary Search Tree (BST) and two node values a and b,
find the shortest distance (number of edges) between the two nodes.

Rules:
- BST property holds (left < root < right).
- Both a and b are present in the BST.
- Distance is measured in number of edges.

Example:
BST:
        20
       /  \
      8    22
     / \
    4   12
       /  \
      10  14

a = 10, b = 14

Output:
2

Path:
10 → 12 → 14

Approach (Optimal – LCA + Depth Calculation):
1) Find Lowest Common Ancestor (LCA) of a and b using BST property.
2) Compute distance from LCA to a.
3) Compute distance from LCA to b.
4) Sum both distances.

GeeksforGeeks:
https://www.geeksforgeeks.org/shortest-distance-between-two-nodes-in-bst/

LeetCode:
No direct equivalent problem.

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

    int distanceFromRoot(Node* root, int val) {

        int dist = 0;
        while (root->data != val) {
            if (val < root->data)
                root = root->left;
            else
                root = root->right;
            dist++;
        }
        return dist;
    }

    int shortestDistance(Node* root, int a, int b) {

        Node* lca = LCA(root, a, b);
        return distanceFromRoot(lca, a) + distanceFromRoot(lca, b);
    }
};
