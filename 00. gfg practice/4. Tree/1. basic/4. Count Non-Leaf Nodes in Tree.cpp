/*
Problem: Count Non-Leaf Nodes in Tree

GFG: https://www.geeksforgeeks.org/problems/count-non-leaf-nodes-in-tree/1

Description:
Given the root of a binary tree, return the count of all non-leaf nodes.
A non-leaf node is a node having at least one child.

Examples:
Input tree: [1, 2, 3]
Output: 2

Input tree:
          8
        /   \
       3     9
      / \
     1   6
        / \
       4   7
Output: 3

Input tree:
          10
        /    \
       5      20
      / \    /  \
     3   7  15  25
Output: 3

Constraints:
1 <= number of nodes <= 10^5
1 <= node->data <= 10^5

Approach (DFS):
- If node is NULL, return 0.
- If node is a leaf, return 0.
- Otherwise, count current node (1) + counts from left and right subtrees.

Time Complexity: O(N)
Space Complexity: O(H) recursion stack (H = tree height)

Pattern: Tree Traversal / DFS
*/

#include <bits/stdc++.h>
using namespace std;

/*
struct Node{
    int data;
    Node* left;
    Node* right;
};
*/

class Solution {
  public:
    int countNonLeafNodes(Node* root) {
        if (root == nullptr) {
            return 0;
        }

        if (root->left == nullptr && root->right == nullptr) {
            return 0;
        }

        return 1 + countNonLeafNodes(root->left) + countNonLeafNodes(root->right);
    }
};

