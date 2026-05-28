/*
GeeksforGeeks: Maximum Width of Tree
Difficulty: Easy

Problem:
Given a Binary Tree, find the maximum width of it.
Maximum width is defined as the maximum number of nodes actually present at any level.

Return:
int representing the maximum width.

Example:
Input: root = [1, 2, 3, 4, 5, 6, 7]
Output: 4
Explanation:
Level 1: [1] -> 1 node
Level 2: [2, 3] -> 2 nodes
Level 3: [4, 5, 6, 7] -> 4 nodes
Max width = 4

Core Idea:
Use Level Order Traversal (BFS) utilizing a queue.
At the exact beginning of each level loop, the size of the queue perfectly represents the number of nodes present at that specific depth.
Simply keep track of the maximum queue size encountered across all levels!

Approach:
1. If the root is null, return 0.
2. Initialize a queue `q` and push the `root` node. Also initialize `maxWidth = 0`.
3. Loop strictly while the queue is not empty:
   - Determine `level_size = q.size()`.
   - Dynamically update `maxWidth = max(maxWidth, level_size)`.
   - Loop exactly `level_size` times to fully process all nodes at the current level.
     - Pop a node, aggressively push its left child (if it exists), aggressively push its right child (if it exists).
4. Return `maxWidth`.

Time Complexity: O(N)
Space Complexity: O(W) 

(W = max width of the tree, which degrades to O(N) for a perfectly balanced tree)

GFG Link:
https://www.geeksforgeeks.org/problems/maximum-width-of-tree/1
*/

#include <iostream>
#include <queue>
#include <algorithm>

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
    int getMaxWidth(Node* root) {
        if (!root) {
            return 0;
        }
        
        int maxWidth = 0;
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int level_size = q.size();
            
            // Update max width if the current level has more nodes
            maxWidth = max(maxWidth, level_size);
            
            // Process all nodes at the current level synchronously
            for (int i = 0; i < level_size; ++i) {
                Node* curr = q.front();
                q.pop();
                
                if (curr->left) {
                    q.push(curr->left);
                }
                if (curr->right) {
                    q.push(curr->right);
                }
            }
        }
        
        return maxWidth;
    }
};

/*
Dry Run:

        1
       / \
      2   3
     / \   \
    4   5   8

Queue initialization: q = [1]
Level 1:
  level_size = 1
  maxWidth = max(0, 1) = 1
  pop 1 -> push 2, 3
  q = [2, 3]

Level 2:
  level_size = 2
  maxWidth = max(1, 2) = 2
  pop 2 -> push 4, 5
  pop 3 -> push 8
  q = [4, 5, 8]

Level 3:
  level_size = 3
  maxWidth = max(2, 3) = 3
  pop 4 -> no children
  pop 5 -> no children
  pop 8 -> no children
  q = []

Loop ends.
Return maxWidth = 3.
*/
