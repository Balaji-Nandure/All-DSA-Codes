/*
GeeksforGeeks: Odd even level difference
Difficulty: Easy

Problem:
Given a Binary Tree. Find the difference between the sum of node values 
at odd levels and the sum of node values at even levels.
(The root is at level 1, which is an odd level).

Example 1:
Input: root = [1, 2, 3]
      1
    /   \
   2     3
Output: -4
Explanation: 
Sum at odd levels (level 1) = 1
Sum at even levels (level 2) = 2 + 3 = 5
Difference = 1 - 5 = -4

Example 2:
Input: root = [10, 20, 30, N, N, 40, 60]
        10
      /    \
     20    30
         /    \
        40    60
Output: 60
Explanation: 
Sum at odd levels (1, 3) = 10 + 40 + 60 = 110
Sum at even levels (2) = 20 + 30 = 50
Difference = 110 - 50 = 60 

Core Idea:
We want to calculate: (Odd Level Sum) - (Even Level Sum).
We can do this using a very elegant recursive property.
Consider a tree:
        A (Level 1)
       / \
      B   C (Level 2)
     /
    D (Level 3)

The difference is: (A + D) - (B + C)
This can be rewritten as: A - (B - D + C)
Which is exactly: A - (difference of left subtree) - (difference of right subtree)

Therefore, the function can just return:
`root->data - getLevelDiff(root->left) - getLevelDiff(root->right)`

Alternatively, a standard Level Order Traversal (BFS) using a queue can also be used 
to compute the sum level by level, adding or subtracting based on the current depth.

Approach (Recursive DFS):
1. Base Case: If `root` is NULL, return 0.
2. Return `root->data - getLevelDiff(root->left) - getLevelDiff(root->right)`.

Time Complexity : O(N) — Every node is visited exactly once.
Space Complexity: O(H) — Recursion stack depth equals the height of the tree.

(N = number of nodes, H = height of the tree)

GFG Link:
https://www.geeksforgeeks.org/problems/odd-even-level-difference/1
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
    int getLevelDiff(Node *root) {
        // Base case: empty tree contributes 0 to the difference
        if (!root) {
            return 0;
        }
        
        // Difference = current node (odd relative to its children) 
        //              - difference of left subtree 
        //              - difference of right subtree
        return root->data - getLevelDiff(root->left) - getLevelDiff(root->right);
    }
    
    /*
    // Alternative BFS Approach (Level Order Traversal)
    int getLevelDiffBFS(Node *root) {
        if (!root) return 0;
        
        queue<Node*> q;
        q.push(root);
        
        int diff = 0;
        bool isOdd = true; // root is at level 1 (odd)
        
        while (!q.empty()) {
            int size = q.size();
            int levelSum = 0;
            
            for (int i = 0; i < size; ++i) {
                Node* curr = q.front();
                q.pop();
                
                levelSum += curr->data;
                
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            
            if (isOdd) diff += levelSum;
            else diff -= levelSum;
            
            isOdd = !isOdd; // flip for the next level
        }
        
        return diff;
    }
    */
};

/*
Dry Run — Example 1:
      1
    /   \
   2     3

getLevelDiff(1):
  - returns 1 - getLevelDiff(2) - getLevelDiff(3)
  
  --> getLevelDiff(2):
      - returns 2 - getLevelDiff(NULL) - getLevelDiff(NULL)
      - returns 2 - 0 - 0 = 2
      
  --> getLevelDiff(3):
      - returns 3 - getLevelDiff(NULL) - getLevelDiff(NULL)
      - returns 3 - 0 - 0 = 3
      
  - Returning to root: 1 - 2 - 3 = -4.
  
Final Result = -4. ✓
*/
