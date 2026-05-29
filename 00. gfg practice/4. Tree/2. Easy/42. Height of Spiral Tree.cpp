/*
GeeksforGeeks: Height of Spiral Tree
Difficulty: Easy

Problem:
Given a special Binary Tree whose leaf nodes are connected to form a circular 
doubly linked list. Find the height of this special Binary Tree.

Example 1:
Input: root = [1, 2, 3, 4, 5, N, 6]
         1
       /   \
      2     3
     / \     \
    4   5     6
Output: 2
Explanation: The height of given tree is 2 (measured in edges).

Example 2:
Input: root = [1, 2, 3]
      1
    /   \
   2     3
Output: 1
Explanation: The height of given tree is 1 (measured in edges).

Core Idea:
The only challenge here is identifying when we have reached a "leaf" node, because 
in this special tree, the `left` and `right` pointers of a leaf node are NOT `NULL`. 
Instead, they point to other leaves to form a Circular Doubly Linked List (CDLL).
In a CDLL, for any node `L`, its next node is `L->right`, and the previous node of 
that next node must point back to `L` (`L->right->left == L`). Similarly for the left side.

So, a node is a leaf in this special tree if:
`node->left && node->left->right == node` AND `node->right && node->right->left == node`.
Internal nodes will never satisfy this because their left/right pointers point to their 
children, and the children's right/left pointers do not point back to the parent!

Approach (Recursive DFS):
1. Define a helper function `isLeaf(Node* node)` that checks the CDLL condition.
2. In the main `findTreeHeight(Node* root)` function:
   a. Base Case 1: If `root` is NULL, return 0.
   b. Base Case 2: If `isLeaf(root)` is true, return 0 (since height is in edges).
   c. Recursively compute `l = findTreeHeight(root->left)`.
   d. Recursively compute `r = findTreeHeight(root->right)`.
   e. Return `1 + max(l, r)`.

Time Complexity : O(N) — Every node is visited exactly once.
Space Complexity: O(H) — Recursion stack depth equals the height of the tree.

(N = number of nodes, H = height of the tree)

GFG Link:
https://www.geeksforgeeks.org/problems/height-of-spiral-tree/1
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
private:
    // Helper function to check if a node is a leaf in the special CDLL tree
    bool isLeaf(Node* node) {
        // A standard leaf check (just in case they test with a normal tree)
        if (!node->left && !node->right) {
            return true;
        }
        
        // CDLL check: if its left's right is itself, and right's left is itself
        if (node->left && node->left->right == node && 
            node->right && node->right->left == node) {
            return true;
        }
        
        return false;
    }

public:
    int findTreeHeight(Node* root) {
        if (!root) {
            return 0; 
        }
        
        // If it's a leaf, the height extending from it is 0 edges.
        if (isLeaf(root)) {
            return 0;
        }
        
        // Recursively find the height of left and right subtrees
        int leftHeight = findTreeHeight(root->left);
        int rightHeight = findTreeHeight(root->right);
        
        // Return 1 (for the current edge) + max of subtrees
        return 1 + max(leftHeight, rightHeight);
    }
};

/*
Dry Run — Example 1: root = [1, 2, 3, 4, 5, N, 6]
         1
       /   \
      2     3
     / \     \
    4   5     6

Here, 4, 5, 6 are connected in a CDLL: 4 <-> 5 <-> 6 <-> 4.
For node 4: 4->right is 5, 5->left is 4. (isLeaf returns true)
For node 5: 5->right is 6, 6->left is 5. (isLeaf returns true)
For node 6: 6->right is 4, 4->left is 6. (isLeaf returns true)

findTreeHeight(1):
  - isLeaf(1) -> false.
  
  --> l = findTreeHeight(2):
      - isLeaf(2) -> false.
      - l2 = findTreeHeight(4) -> isLeaf(4) is true -> returns 0.
      - r2 = findTreeHeight(5) -> isLeaf(5) is true -> returns 0.
      - Returns 1 + max(0, 0) = 1.
      
  --> r = findTreeHeight(3):
      - isLeaf(3) -> false.
      - l3 = findTreeHeight(NULL) -> returns 0.
      - r3 = findTreeHeight(6) -> isLeaf(6) is true -> returns 0.
      - Returns 1 + max(0, 0) = 1.
      
  - Returning to 1: 1 + max(1, 1) = 2.
  
Final Result = 2. ✓
*/
