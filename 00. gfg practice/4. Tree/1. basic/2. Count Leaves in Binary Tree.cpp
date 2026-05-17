/*
Problem: Count Leaves in Binary Tree

GFG: https://www.geeksforgeeks.org/problems/count-leaves-in-binary-tree/1

Description:
Given the root of a binary tree, count the number of leaf nodes.
A leaf node is a node with no left and no right child.

Examples:
Output: 3
Output: 4
Output: 3

Constraints:
1 <= number of nodes <= 10^5
1 <= node->data <= 10^5

Approach (DFS):
Traverse the tree recursively:
- If node is NULL, return 0
- If node is a leaf, return 1
- Otherwise return count(left) + count(right)

Time Complexity: O(N)
Space Complexity: O(H) recursion stack (H = tree height)

Pattern: Tree Traversal / DFS
*/

#include <bits/stdc++.h>
using namespace std;

/*
struct Node{
    int data;
    Node *left,*right;
};
*/

class Solution {
  public:
    int countLeaves(Node* root) {
        if (root == nullptr) {
            return 0;
        }

        if (root->left == nullptr && root->right == nullptr) {
            return 1;
        }

        return countLeaves(root->left) + countLeaves(root->right);
    }
};

