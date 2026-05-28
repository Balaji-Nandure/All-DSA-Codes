/*
GeeksforGeeks: Remove Half Nodes
Difficulty: Easy

Problem:
You are given a binary tree and you need to remove all the half nodes (which have only one child).
Return the root node of the modified tree after removing all the half-nodes.

Return:
Node* representing the root of the newly modified tree.

Example:
Input:
            5
          /   \
         7     8
       / 
      2
Output: 2 5 8 (inorder traversal)
Explanation: The node 7 has only a single child (2). After removing 7, the tree becomes 2 <- 5 -> 8.

Core Idea:
Use a bottom-up DFS (Post-order traversal) approach.
By deliberately processing the children *before* evaluating the parent, we can safely replace any half-node with its only existing child without losing the rest of the subtree below it.
If a node intrinsically has only a left child, the node itself is fully bypassed and replaced by that left child.
If it has only a right child, it is identically bypassed and replaced by that right child.

Approach:
1. Base Case: If `root` is intrinsically null, simply return `nullptr`.
2. Recursively intelligently process the entire left subtree: `root->left = RemoveHalfNodes(root->left)`.
3. Recursively intelligently process the entire right subtree: `root->right = RemoveHalfNodes(root->right)`.
4. After both subtrees are thoroughly processed, definitively evaluate the current node:
   a. If it's physically a leaf node (both children null), simply return `root`.
   b. If it has only a right child (left is null), it is a half node! Return `root->right`.
   c. If it has only a left child (right is null), it is a half node! Return `root->left`.
5. If it structurally has both children, it is a full node, so confidently return `root`.

Time Complexity: O(N) as we rigorously visit every node exactly once.
Space Complexity: O(H) corresponding strictly to the recursion stack depth.

(H = tree height)

GFG Link:
https://www.geeksforgeeks.org/problems/remove-half-nodes/1
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
    Node *RemoveHalfNodes(Node *root) {
        if (!root) {
            return nullptr;
        }
        
        // Post-order: Process subtrees first
        root->left = RemoveHalfNodes(root->left);
        root->right = RemoveHalfNodes(root->right);
        
        // Leaf node -> keep it
        if (!root->left && !root->right) {
            return root;
        }
        
        // Half node (missing left child) -> replace with right child
        if (!root->left) {
            return root->right;
        }
        
        // Half node (missing right child) -> replace with left child
        if (!root->right) {
            return root->left;
        }
        
        // Node has both children -> keep it
        return root;
    }
};

/*
Dry Run:

        5
      /   \
     7     8
   / 
  2

RemoveHalfNodes(5):
  left = RemoveHalfNodes(7):
    left = RemoveHalfNodes(2) -> leaf -> returns 2
    right = RemoveHalfNodes(null) -> returns null
    7 now actively has left=2, right=null
    7 is a half node (missing right)! Returns its left child (2).
  
  right = RemoveHalfNodes(8):
    8 is completely a leaf -> returns 8
    
  5 now natively has left=2, right=8
  5 has both children securely -> returns 5.

Final structurally modified tree:
      5
    /   \
   2     8
*/
