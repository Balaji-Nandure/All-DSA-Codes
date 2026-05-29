/*
GeeksforGeeks: Tilt of Binary Tree
Difficulty: Easy

Problem:
Given a binary tree, your task is to complete the function tiltTree(), that 
returns the tilt of the whole tree. The tilt of a tree node is defined as the 
absolute difference between the sum of all left subtree node values and the 
sum of all right subtree node values. Null nodes are assigned tilt to be zero. 
Therefore, tilt of the whole tree is defined as the sum of all nodes’ tilt.

Example 1:
Input: root = [1, 2, 3]
       1
      / \
     2   3
Output: 1
Explanation: 
Tilt of node 2 : |0 - 0| = 0
Tilt of node 3 : |0 - 0| = 0
Tilt of node 1 : |2 - 3| = 1
Tilt of tree : 0 + 0 + 1 = 1

Example 2:
Input: root = [4, 2, 9, 3, 5, N, 7]
        4 
       / \
      2   9 
     / \   \
    3   5   7 
Output: 15 
Explanation: 
Tilt of node 3 : 0 
Tilt of node 5 : 0
Tilt of node 7 : 0
Tilt of node 2 : |3 - 5| = 2
Tilt of node 9 : |0 - 7| = 7
Tilt of node 4 : |(3+5+2) - (9+7)| = |10 - 16| = 6
Tilt of binary tree : 0 + 0 + 0 + 2 + 7 + 6 = 15

Core Idea:
To calculate the tilt of a node, we need the sum of all values in its left subtree 
and its right subtree. We can efficiently compute this using a bottom-up Depth-First 
Search (Post-order Traversal).
At any given node, our helper function should:
1. Recursively calculate the sum of its left subtree.
2. Recursively calculate the sum of its right subtree.
3. Calculate the current node's tilt (`abs(leftSum - rightSum)`) and add it to a 
   running `totalTilt` variable.
4. Return the total sum of the current subtree (`root->data + leftSum + rightSum`) 
   to pass it up to the parent.

Approach:
1. Initialize a class member variable `totalTilt = 0`.
2. Define a helper function `solve(Node* root)`:
   a. Base Case: If `root` is NULL, return 0.
   b. `leftSum = solve(root->left)`.
   c. `rightSum = solve(root->right)`.
   d. `totalTilt += abs(leftSum - rightSum)`.
   e. Return `root->data + leftSum + rightSum`.
3. In `tiltTree(Node* root)`, set `totalTilt = 0`, call `solve(root)`, and 
   return `totalTilt`.

Time Complexity : O(N) — Every node is visited exactly once.
Space Complexity: O(H) — Recursion stack depth equals the height of the tree.

(N = number of nodes, H = height of the tree)

GFG Link:
https://www.geeksforgeeks.org/problems/tilt-of-binary-tree/1
*/

#include <iostream>
#include <cmath>

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
private:
    int totalTilt;
    
    int solve(Node* root) {
        if (!root) {
            return 0;
        }
        
        // Post-order traversal: calculate left and right subtree sums first
        int leftSum = solve(root->left);
        int rightSum = solve(root->right);
        
        // The tilt of the current node is the absolute difference 
        // between the left and right subtree sums
        totalTilt += abs(leftSum - rightSum);
        
        // Return the sum of the entire subtree rooted at the current node
        return root->data + leftSum + rightSum;
    }

public:
    int tiltTree(Node* root) {
        totalTilt = 0;
        solve(root);
        return totalTilt;
    }
};

/*
Dry Run — Example 2:
        4 
       / \
      2   9 
     / \   \
    3   5   7 

tiltTree(4):
  totalTilt = 0
  solve(4):
    --> solve(2):
        --> solve(3) -> leaves, return 3. tilt = |0-0| = 0. totalTilt = 0
        --> solve(5) -> leaves, return 5. tilt = |0-0| = 0. totalTilt = 0
        - For 2: tilt = |3 - 5| = 2. totalTilt = 0 + 2 = 2.
        - Return 2 + 3 + 5 = 10.
        
    --> solve(9):
        --> solve(NULL) -> return 0.
        --> solve(7) -> leaves, return 7. tilt = 0. totalTilt = 2
        - For 9: tilt = |0 - 7| = 7. totalTilt = 2 + 7 = 9.
        - Return 9 + 0 + 7 = 16.
        
    - For 4: tilt = |10 - 16| = 6. totalTilt = 9 + 6 = 15.
    - Return 4 + 10 + 16 = 30.
    
Output = totalTilt = 15. ✓
*/
