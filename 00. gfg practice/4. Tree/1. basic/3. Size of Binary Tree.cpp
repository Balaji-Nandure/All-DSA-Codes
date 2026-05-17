/*
Problem: Size of Binary Tree

GFG: https://www.geeksforgeeks.org/problems/size-of-binary-tree/1

Description:
Given the root of a binary tree, return the size of the tree.
Size means total number of nodes present in the tree.

Examples:
Output: 3
Output: 6

Constraints:
1 <= number of nodes <= 10^5
1 <= node->data <= 10^5

Approach (DFS):
For every node:
size = 1 (current node) + size(left subtree) + size(right subtree)

Base case:
If node is NULL, size is 0.

Time Complexity: O(N)
Space Complexity: O(H) recursion stack (H = tree height)

Pattern: Tree Traversal / DFS
*/

#include <bits/stdc++.h>
using namespace std;

/*
struct Node {
    int data;
    Node* left;
    Node* right;
};
*/

class Solution {
  public:
    int getSize(Node* root) {
        if (root == nullptr) {
            return 0;
        }

        return 1 + getSize(root->left) + getSize(root->right);
    }
};

