/*
Problem: Preorder Traversal

GFG: https://www.geeksforgeeks.org/problems/preorder-traversal/1

Description:
Given the root of a binary tree, return its preorder traversal.

Preorder order:
1) Visit current node
2) Traverse left subtree
3) Traverse right subtree

Examples:

Input: root = [1, 4, N, 4, 2]
Output: [1, 4, 4, 2]

Input: root = [6, 3, 2, N, 1, 2, N]
Output: [6, 3, 1, 2, 2]

Constraints:
1 <= number of nodes <= 3 * 10^4
0 <= node->data <= 10^5

Approach (Recursive DFS):
Use a helper function:
- If node is NULL, return.
- Push node->data into answer.
- Recur on left child.
- Recur on right child.

Time Complexity: O(N)
Space Complexity: O(H) recursion stack (H = tree height)

Pattern: Tree Traversal / DFS
*/

#include <bits/stdc++.h>
using namespace std;

/*
struct Node
{
    int data;
    Node* left;
    Node* right;
};
*/

class Solution {
  public:
    void preorderDFS(Node* root, vector<int>& ans) {
        if (root == nullptr) {
            return;
        }

        ans.push_back(root->data);      // Visit node
        preorderDFS(root->left, ans);   // Left subtree
        preorderDFS(root->right, ans);  // Right subtree
    }

    vector<int> preorder(Node* root) {
        vector<int> ans;
        preorderDFS(root, ans);
        return ans;
    }
};

