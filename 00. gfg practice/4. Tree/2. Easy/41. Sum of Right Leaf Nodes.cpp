/*
GeeksforGeeks: Sum of Right Leaf Nodes
Difficulty: Easy

Problem:
Given the root of a Binary Tree, return the sum of all right leaf nodes. 
A right leaf node is a node that is the right child of its parent and does not 
have any left or right child.

Example 1:
Input: root[] = [1, 2, 3, 4, 5, N, 8, N, 2, N, N, 6, 7]
          1
       /     \
      2       3
     / \       \
    4   5       8
     \         / \
      2       6   7
Output : 14
Explanation: 
The right leaf nodes present are:
- 2 (right child of 4)
- 5 (right child of 2)
- 7 (right child of 8)
Sum = 2 + 5 + 7 = 14.

Example 2:
Input: root[] = [1, -2, 3, N, 5, N, 8]
          1
       /     \
     -2       3
       \       \
        5       8
Output: 13
Explanation: 
The right leaf nodes present are 5 and 8. 
Sum = 5 + 8 = 13.

Core Idea:
This problem is the exact mirror image of "Sum of Left Leaf Nodes".
A node doesn't natively know if it is a left or right child; however, its parent knows!
Instead of checking properties on the current node, we check properties on `root->right`:
1. If `root->right` exists AND it is a leaf node (has no children), we have found a "right leaf".
2. If it isn't a leaf node, we recursively search inside `root->right`.
3. We *always* recursively search inside `root->left`, because a left subtree can absolutely 
   contain right leaves deep inside it.

Approach (Recursive DFS):
1. Base Case: If `root` is NULL, return 0.
2. Initialize `sum = 0`.
3. Always recursively call `rightLeafSum(root->left)` and add the result to `sum`.
4. Check the right child:
   a. If `root->right` exists and is a leaf node (`!root->right->left && !root->right->right`), 
      add its data to `sum`.
   b. Otherwise, recursively call `rightLeafSum(root->right)` and add the result to `sum`.
5. Return the total `sum`.

Time Complexity : O(N) — Every node is visited exactly once.
Space Complexity: O(H) — Recursion stack depth equals the height of the tree.

(N = number of nodes, H = height of the tree)

GFG Link:
https://www.geeksforgeeks.org/problems/sum-of-right-leaf-nodes/1
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
    int rightLeafSum(Node* root) {
        if (!root) {
            return 0;
        }
        
        int sum = 0;
        
        // We always recursively check the left subtree, 
        // because it might contain right leaves deep inside it
        sum += rightLeafSum(root->left);
        
        // Check if the right child exists and is a leaf node
        if (root->right && !root->right->left && !root->right->right) {
            // We found a right leaf! Add its data.
            sum += root->right->data;
        } else {
            // Otherwise, we recursively check the right subtree
            sum += rightLeafSum(root->right);
        }
        
        return sum;
    }
};

/*
Dry Run — Example 2:
          1
       /     \
     -2       3
       \       \
        5       8

rightLeafSum(1):
  - sum += rightLeafSum(-2)
  - check root->right (3):
      - Is 3 a leaf? No (has child 8).
      - sum += rightLeafSum(3)
  
  --> rightLeafSum(-2):
      - sum += rightLeafSum(NULL) (0)
      - check root->right (5):
          - Is 5 a leaf? Yes (!5->left && !5->right).
          - sum += 5.
      - Returns 5.
      
  --> rightLeafSum(3):
      - sum += rightLeafSum(NULL) (0)
      - check root->right (8):
          - Is 8 a leaf? Yes (!8->left && !8->right).
          - sum += 8.
      - Returns 8.
      
  - Returning to 1: sum = 5 (from left subtree) + 8 (from right subtree) = 13.
  
Final Result = 13. ✓
*/
