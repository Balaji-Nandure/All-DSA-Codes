/*
GeeksforGeeks: Sum of Leaf Nodes
Difficulty: Easy

Problem:
Given a binary tree, find the sum of values of all the leaf nodes.

Example 1:
Input: root = [10, 20, 30, 40, 60, N, N]
           10
         /   \
        20    30
      /    \
    40     60
Output: 130
Explanation: The sum of all the leaf nodes is 30 (from right child of 10) + 40 + 60.

Example 2:
Input: root = [1, 3, 2]
      1
    /   \
   3     2
Output: 5
Explanation: The sum of all the leaf nodes is 3 + 2 = 5.

Example 3:
Input: root = [1, 2, N, 4, N]
           1
         /     
        2    
      /   
    4     
Output: 4
Explanation: The sum of all the leaf nodes is 4.

Core Idea:
A leaf node is defined as a node that has NO left child and NO right child.
We can traverse the tree (using simple recursion/DFS). If we encounter a leaf node, 
we return its value. If we encounter a non-leaf node, we recursively find the sum 
of leaf nodes in its left and right subtrees and return their sum.

Approach:
1. Base Case 1: If `root` is NULL, return 0 (no nodes, sum is 0).
2. Base Case 2: If `root->left` is NULL and `root->right` is NULL, it's a leaf node. 
   Return `root->data`.
3. Recursive Step: Return `sumOfLeafNodes(root->left) + sumOfLeafNodes(root->right)`.

Time Complexity : O(N) — Every node is visited exactly once.
Space Complexity: O(H) — Recursion stack depth equals the height of the tree.

(N = number of nodes, H = height of the tree)

GFG Link:
https://www.geeksforgeeks.org/problems/sum-of-leaf-nodes/1
*/

#include <iostream>

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
    int sumOfLeafNodes(Node *root) {
        // Base case: empty tree contributes 0 to sum
        if (!root) {
            return 0;
        }
        
        // If current node is a leaf, return its data
        if (!root->left && !root->right) {
            return root->data;
        }
        
        // Otherwise, recursively sum leaves in left and right subtrees
        return sumOfLeafNodes(root->left) + sumOfLeafNodes(root->right);
    }
};

/*
Dry Run — Example 1:
           10
         /   \
        20    30
      /    \
    40     60

sumOfLeafNodes(10):
  - Is leaf? No.
  - Returns sumOfLeafNodes(20) + sumOfLeafNodes(30)
  
  --> sumOfLeafNodes(20):
      - Is leaf? No.
      - Returns sumOfLeafNodes(40) + sumOfLeafNodes(60)
      
      ----> sumOfLeafNodes(40):
            - Is leaf? YES (!left && !right). Returns 40.
            
      ----> sumOfLeafNodes(60):
            - Is leaf? YES (!left && !right). Returns 60.
            
      - Returning from 20: 40 + 60 = 100.
      
  --> sumOfLeafNodes(30):
      - Is leaf? YES (!left && !right). Returns 30.
      
  - Returning from 10: 100 (from left) + 30 (from right) = 130.

Final Result = 130. ✓
*/
