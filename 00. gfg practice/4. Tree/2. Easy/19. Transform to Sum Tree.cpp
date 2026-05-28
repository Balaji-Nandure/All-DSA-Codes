/*
GeeksforGeeks: Transform to Sum Tree
Difficulty: Easy

Problem:
Given a root of a binary tree, convert it into a tree such that each node’s new value is equal to the sum of all values in its left and right subtrees (based on the original tree).
For leaf nodes, update their values to 0.

Return:
Modify the tree in-place. (Return nothing)

Example:
Input: root = [10, -2, 6, 8, -4, 7, 5]
Output: modified tree where root is 20, left is 4, right is 12, etc.
Explanation: 
Leaf nodes 8, -4, 7, 5 become 0.
Left child of root: 8 + (-4) = 4.
Right child of root: 7 + 5 = 12.
Root: 4 (left sum) - 2 (original left) + 12 (right sum) + 6 (original right) = 20.

Core Idea:
Use a bottom-up DFS (Post-order traversal) so that we can intelligently compute the total sum of the children's subtrees *before* modifying the parent.
A helper function should recursively calculate and return the total sum of the subtree (including the original root value).
At each node, securely cache its original value, update its data to the sum of its left and right subtrees, and then dynamically return the cached original value + the newly computed left and right subtree sums.

Approach:
1. Create a helper function `solve(root)` that returns an integer.
2. Base case: If `root` is null, safely return 0.
3. Cache the current node's original value: `old_val = root->data`.
4. Recursively find the sum of the entirely of the left subtree: `left_sum = solve(root->left)`.
5. Recursively find the sum of the entirely of the right subtree: `right_sum = solve(root->right)`.
6. Update the current node's value strictly based on its children: `root->data = left_sum + right_sum`.
7. Return `old_val + root->data` (which optimally represents the total sum of this entire subtree including its original node value) so the parent can flawlessly use it.
8. Safely call `solve` natively from the main `toSumTree` wrapper function.

Time Complexity: O(N)
Space Complexity: O(H)

(H = tree height)

GFG Link:
https://www.geeksforgeeks.org/problems/transform-to-sum-tree/1
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
};

class Solution {
public:
    int solve(Node* root) {
        if (!root) {
            return 0;
        }
        
        // Cache the original value before we dynamically overwrite it
        int old_val = root->data; 
        
        // Recursively securely get the total sum of the physical left and right subtrees
        int left_sum = solve(root->left);
        int right_sum = solve(root->right);
        
        // Update the current node to strictly be the sum of its subtrees
        root->data = left_sum + right_sum;
        
        // Return the total sum of this subtree (original value + children's sums)
        return old_val + root->data;
    }

    void toSumTree(Node *node) {
        solve(node);
    }
};

/*
Dry Run:

        10
       /  \
     -2    6
     / \  / \
    8 -4 7   5

solve(8):
  left = 0, right = 0
  old = 8, data = 0
  returns 8
solve(-4):
  left = 0, right = 0
  old = -4, data = 0
  returns -4
solve(-2):
  left = solve(8) = 8
  right = solve(-4) = -4
  old = -2, data = 8 + (-4) = 4
  returns -2 + 4 = 2

solve(7): returns 7, data = 0
solve(5): returns 5, data = 0
solve(6):
  left = 7, right = 5
  old = 6, data = 12
  returns 6 + 12 = 18

solve(10):
  left = solve(-2) = 2
  right = solve(6) = 18
  old = 10, data = 2 + 18 = 20
  returns 10 + 20 = 30
*/
