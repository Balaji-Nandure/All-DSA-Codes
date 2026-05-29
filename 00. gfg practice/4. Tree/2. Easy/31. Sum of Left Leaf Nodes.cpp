/*
GeeksforGeeks: Sum of Left Leaf Nodes
Difficulty: Easy

Problem:
Given a Binary Tree. Find the sum of all the leaf nodes that are left child 
of their parent of the given binary tree.

Example 1:
Input:
       1
     /   \
    2     3
Output: 2
Explanation: 2 is a leaf node and it is the left child of its parent 1.

Example 2:
Input : 
         1
        /  \
       2    3
     /  \     \
    4    5     8 
  /  \        /  \
 7    2      6    9
Output: 13
Explanation: 
Left leaves are:
- 7 (left child of 4)
- 6 (left child of 8)
Sum = 7 + 6 = 13.
(Note: 2 under 4 is a right child, 5 under 2 is a right child, 9 under 8 is a right child).

Core Idea:
To identify a "left leaf", we need to check two conditions:
1. It must be a leaf node (both left and right children are NULL).
2. It must be the left child of its parent.
We can check this directly from the parent node: if `root->left` exists and is a leaf, 
we add its value. Otherwise, we continue recursively down the left subtree. We always 
continue recursively down the right subtree (right children can have left leaves inside them).

Approach:
1. Base Case: If `root` is NULL, return 0.
2. Initialize `sum = 0`.
3. Check the left child:
   a. If `root->left` exists and is a leaf node (`!root->left->left && !root->left->right`), 
      add its data to `sum`.
   b. Otherwise, recursively call `leftLeavesSum(root->left)` and add the result to `sum`.
4. Recursively call `leftLeavesSum(root->right)` and add the result to `sum`.
5. Return the total `sum`.

Time Complexity : O(N) — Every node is visited exactly once.
Space Complexity: O(H) — Recursion stack depth equals the height of the tree.

(N = number of nodes, H = height of the tree)

GFG Link:
https://www.geeksforgeeks.org/problems/sum-of-left-leaf-nodes/1
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
    int leftLeavesSum(Node *root) {
        if (!root) {
            return 0;
        }
        
        int sum = 0;
        
        // If left child exists and is a leaf node
        if (root->left && !root->left->left && !root->left->right) {
            // We found a left leaf
            sum += root->left->data;
        } else {
            // Otherwise, we need to recursively check the left subtree
            sum += leftLeavesSum(root->left);
        }
        
        // We always recursively check the right subtree, 
        // because it might contain left leaves inside it
        sum += leftLeavesSum(root->right);
        
        return sum;
    }
};

/*
Dry Run — Example 1:
       1
     /   \
    2     3

leftLeavesSum(1):
  - root = 1
  - check root->left (2):
      - Is 2 a leaf? Yes (!2->left && !2->right).
      - sum += 2->data (sum = 2).
  - sum += leftLeavesSum(3)
  
  --> leftLeavesSum(3):
      - check root->left (NULL)
      - sum += leftLeavesSum(NULL) (0)
      - sum += leftLeavesSum(NULL) (0)
      - returns 0
      
  - Returning from 1: sum = 2 + 0 = 2.
  
Final Result = 2. ✓
*/
