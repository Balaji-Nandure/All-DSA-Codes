/*
GeeksforGeeks: Deletion in a Binary Tree
Difficulty: Easy

Problem:
Given a binary tree with nodes where all elements are unique, implement a function 
that deletes a node with a specified value (key) from the tree. When a node is deleted, 
the tree should shrink from the bottom, meaning the deleted node is replaced by the 
bottom-most, right-most node in the tree.

Example 1:
Input: root[] = [10, 20, 30], key = 10
      10
     /  \
   20    30
Output: [20, 30] (Inorder traversal)
Explanation:
The node 10 is deleted. The bottom-most, right-most node is 30.
We replace 10's data with 30, and then delete the original node 30.
Tree becomes:
      30
     /  
   20    

Example 2:
Input: root[] = [10, 20, 30, N, N, N, 40], key = 20
         10
       /    \
      20    30
             \
             40
Output: [40, 10, 30] (Inorder traversal)
Explanation: 
Node 20 is deleted. The bottom-most, right-most node is 40.
We replace 20's data with 40, and then delete the original node 40.
Tree becomes:
         10
       /    \
      40    30

Core Idea:
Since the tree shrinks from the "bottom-most, right-most" node, this perfectly 
matches the last node visited in a standard Level Order Traversal (BFS).
The algorithm follows three logical steps:
1. Find the node to be deleted (`keyNode`).
2. Find the bottom-most, right-most node (`lastNode`). In a full BFS, the last 
   node popped from the queue is exactly this `lastNode`.
3. If `keyNode` was found, copy the `data` of `lastNode` into `keyNode`. Then, 
   delete the original `lastNode` by finding its parent and setting the parent's 
   left or right child pointer to NULL.

Approach:
1. Base cases: If `root` is NULL, return NULL. If `root` has no children and its 
   data matches `key`, delete it and return NULL.
2. Perform a BFS using a queue. Keep updating a pointer `lastNode` for every 
   node popped. Also, if a node's data matches `key`, store it in `keyNode`.
3. After the loop, `lastNode` will naturally point to the bottom-most, right-most node.
4. If `keyNode` is found:
   a. Set `keyNode->data = lastNode->data`.
   b. Perform a second BFS to find the parent of `lastNode`.
   c. Once the parent is found, set its `left` or `right` pointer (whichever points 
      to `lastNode`) to NULL, and `delete lastNode`.
5. Return the original `root`.

Time Complexity : O(N) — We do at most two full traversals of the tree.
Space Complexity: O(W) — We use a queue for BFS, where W is the max width.

(N = number of nodes, W = max width)

GFG Link:
https://www.geeksforgeeks.org/problems/deletion-in-a-binary-tree/1
*/

#include <iostream>
#include <queue>

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
    Node* deletionBT(Node* root, int key) {
        if (!root) {
            return NULL;
        }
        
        // Edge case: Tree has only one node
        if (!root->left && !root->right) {
            if (root->data == key) {
                delete root;
                return NULL;
            }
            return root;
        }
        
        // Step 1: Find keyNode and lastNode using BFS
        queue<Node*> q;
        q.push(root);
        
        Node* keyNode = NULL;
        Node* lastNode = NULL;
        
        while (!q.empty()) {
            lastNode = q.front();
            q.pop();
            
            // Keep track of the node to be deleted
            if (lastNode->data == key) {
                keyNode = lastNode;
            }
            
            if (lastNode->left) q.push(lastNode->left);
            if (lastNode->right) q.push(lastNode->right);
        }
        
        // Step 2: If keyNode exists, replace its data and delete the physical lastNode
        if (keyNode != NULL) {
            // Copy data from the deepest, rightmost node to the target node
            int lastNodeData = lastNode->data;
            keyNode->data = lastNodeData;
            
            // Now we need to delete the physical lastNode
            // We do a second BFS to find its parent
            queue<Node*> q2;
            q2.push(root);
            
            while (!q2.empty()) {
                Node* curr = q2.front();
                q2.pop();
                
                if (curr->left) {
                    if (curr->left == lastNode) {
                        curr->left = NULL;
                        delete lastNode;
                        break;
                    } else {
                        q2.push(curr->left);
                    }
                }
                
                if (curr->right) {
                    if (curr->right == lastNode) {
                        curr->right = NULL;
                        delete lastNode;
                        break;
                    } else {
                        q2.push(curr->right);
                    }
                }
            }
        }
        
        return root;
    }
};

/*
Dry Run — Example 1: root = [10, 20, 30], key = 10
      10
     /  \
   20    30

First BFS:
- q = [10], pop 10. keyNode = 10, push 20, 30.
- q = [20, 30], pop 20. lastNode = 20.
- q = [30], pop 30. lastNode = 30.
End of loop.
keyNode = 10
lastNode = 30

Replacement phase:
- keyNode != NULL.
- lastNodeData = 30.
- keyNode->data = 30. 
Tree is now:
      30
     /  \
   20    30 (this is the physical lastNode)

Second BFS (to delete physical lastNode):
- q2 = [30 (root)]
- curr = 30 (root)
- curr->left is 20 (not lastNode), push 20
- curr->right is 30 (IS lastNode).
  - curr->right = NULL
  - delete lastNode
  - break

Tree is now:
      30
     /  
   20    

Return root. ✓
*/
