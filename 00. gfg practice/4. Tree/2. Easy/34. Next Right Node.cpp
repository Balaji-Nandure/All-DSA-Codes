/*
GeeksforGeeks: Next Right Node
Difficulty: Easy

Problem:
Given a Binary tree and a key in the binary tree, find the node right to the 
given key. If there is no node on right side, then return a node with value -1.

Example 1:
Input: root = [10 2 6 8 4 N 5] and key = 2
         10
       /    \
      2      6
     / \      \
    8   4      5
Output: 6
Explanation: We can see in the above tree that the next right node of 2 is 6.

Example 2:
Input: root = [10 2 6 8 4 N 5] and key = 5
         10
       /    \
      2      6
     / \      \
    8   4      5
Output: -1
Explanation: 5 is the rightmost node at its level. There is no node on its 
right side. So, the output is -1.

Core Idea:
To find the node immediately to the right on the same level, Level Order 
Traversal (BFS) using a Queue is the most natural approach. 
We traverse the tree level by level. By keeping track of the `size` of the queue 
at the start of each level, we know exactly how many nodes are in that current level.
When we encounter the target `key`:
- If it is NOT the last node in the current level, its "next right node" is simply 
  the next node in the queue (which is exactly `q.front()`).
- If it IS the last node in the current level, it has no next right node, so we 
  return a dummy node with value `-1`.

Approach:
1. Base Case: If `root` is NULL, return `new Node(-1)`.
2. Initialize a queue `q` and push `root`.
3. Loop while `q` is not empty:
   a. Get `n = q.size()` (number of nodes in current level).
   b. Loop `i` from 0 to `n-1`:
      i. Pop a node `curr`.
      ii. If `curr->data == key`:
          - If `i == n - 1` (last node in level), return `new Node(-1)`.
          - Else, return `q.front()`.
      iii. Push left and right children of `curr` if they exist.
4. If the loop completes without finding the key, return `new Node(-1)`.

Time Complexity : O(N) — We process every node at most once.
Space Complexity: O(W) — We store nodes in a queue. W is the max width of the tree.

(N = number of nodes, W = max width)

GFG Link:
https://www.geeksforgeeks.org/problems/next-right-node/1
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
    Node *nextRight(Node *root, int key) {
        if (!root) {
            return new Node(-1);
        }
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int level_size = q.size();
            
            for (int i = 0; i < level_size; ++i) {
                Node* curr = q.front();
                q.pop();
                
                // If we found the target key
                if (curr->data == key) {
                    // Check if it is the last element of this level
                    if (i == level_size - 1) {
                        return new Node(-1);
                    } else {
                        // The next node in the queue is on its right
                        return q.front();
                    }
                }
                
                // Add children for the next level
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }
        
        // If the key is not found in the tree at all
        return new Node(-1);
    }
};

/*
Dry Run — Example 1: key = 2
         10
       /    \
      2      6
     / \      \
    8   4      5

Initial:
queue = [10]

Level 1 (size = 1):
- curr = 10 (i=0) -> not 2. Push 2, 6.
queue = [2, 6]

Level 2 (size = 2):
- curr = 2 (i=0) -> FOUND!
- Is i == size - 1 ? (0 == 1) -> No.
- Return q.front() -> 6.

Final Result = Node(6). ✓
*/
