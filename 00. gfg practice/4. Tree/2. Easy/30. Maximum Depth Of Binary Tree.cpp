/*
GeeksforGeeks: Maximum Depth Of Binary Tree
Difficulty: Easy

Problem:
Given a binary tree, find its maximum depth. 
A binary tree's maximum depth is the number of nodes along the longest path from 
the root node down to the farthest leaf node.

Example 1:
Input: root = [1, 3, 2, 4, N, N, N]
         1
       /   \
      3     2
     /
    4
Output: 3
Explanation: Maximum depth is for leaf 4, which is 3 (nodes 1 -> 3 -> 4).

Example 2:
Input: root = [10, 20, 30, N, 40, N, 60, N, N, 2, N, N, N]
         10
       /    \
      20    30
       \      \
       40     60
       /
      2
Output: 4
Explanation: Maximum depth is for leaf 2, which is 4 (nodes 10 -> 20 -> 40 -> 2).

Core Idea:
The maximum depth of a tree is equal to the height of the tree.
It can be defined recursively: 
- An empty tree has a depth of 0.
- A non-empty tree's depth is 1 (for the root) plus the maximum depth of its 
  left and right subtrees.

Approach:
1. Base Case: If `root` is NULL, return 0.
2. Recursive Step: Compute the depth of the left subtree: `leftDepth = maxDepth(root->left)`.
3. Compute the depth of the right subtree: `rightDepth = maxDepth(root->right)`.
4. Return `1 + max(leftDepth, rightDepth)`.

Time Complexity : O(N) — Every node is visited exactly once.
Space Complexity: O(H) — Recursion stack depth equals the height of the tree.

(N = number of nodes, H = height of the tree)

GFG Link:
https://www.geeksforgeeks.org/problems/maximum-depth-of-binary-tree/1
*/

#include <iostream>
#include <algorithm>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int x) {
        data = x;
        left = right = NULL;
    }
};

class Solution {
public:
    int maxDepth(Node *root) {
        // Base case: empty tree has depth 0
        if (!root) {
            return 0;
        }
        
        // Recursively find the max depth of left and right subtrees
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        
        // The max depth is 1 (for current node) + max of left and right depths
        return 1 + max(leftDepth, rightDepth);
    }
};

/*
Dry Run — Example 1:
         1
       /   \
      3     2
     /
    4

maxDepth(1):
  - maxDepth(3):
      - maxDepth(4):
          - maxDepth(NULL) = 0
          - maxDepth(NULL) = 0
          -> returns 1 + max(0, 0) = 1
      - maxDepth(NULL) = 0
      -> returns 1 + max(1, 0) = 2
  - maxDepth(2):
      - maxDepth(NULL) = 0
      - maxDepth(NULL) = 0
      -> returns 1 + max(0, 0) = 1
  -> returns 1 + max(2, 1) = 1 + 2 = 3.

Final Result = 3. ✓
*/
