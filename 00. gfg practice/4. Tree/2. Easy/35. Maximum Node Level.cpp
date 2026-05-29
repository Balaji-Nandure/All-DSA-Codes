/*
GeeksforGeeks: Maximum Node Level
Difficulty: Easy

Problem:
Given a Binary tree, find the level in the binary tree which has the maximum 
number of nodes. Root is considered at level 0.

Example 1:
Input: root = [2, 1, 3, 4, 6, N, 8, N, N, 5]   
         2
       /   \
      1     3
     / \     \
    4   6     8
       /
      5
Output: 2
Explanation: 
Level 0: 1 node (2)
Level 1: 2 nodes (1, 3)
Level 2: 3 nodes (4, 6, 8)
Level 3: 1 node (5)
The level 2 with nodes 4, 6 and 8 is the level with maximum number of nodes. 

Example 2:
Input: root = [2, 1, 3, 4, 7, N, 8, N, N, 5]                   
         2
       /   \
      1     3
     / \     \
    4   7     8
       /
      5
Output: 2
Explanation: The level 2 with nodes 4, 7 and 8 is the level with maximum number of nodes. 

Core Idea:
Since we need to count the number of nodes level by level, Level Order Traversal (BFS) 
using a Queue is the most efficient and natural approach.
By keeping track of `q.size()` at the beginning of each level's processing loop, 
we get the exact number of nodes on that level. We can simply maintain the `maxNodes` 
seen so far and update the `maxLevel` whenever we find a level with more nodes.

Approach:
1. Base Case: If `root` is NULL, return 0 (or -1 depending on convention, but constraints say N >= 1).
2. Initialize `queue<Node*> q`, and push `root`.
3. Initialize `maxNodes = 0`, `maxLevel = 0`, and `currentLevel = 0`.
4. While `q` is not empty:
   a. Get `level_size = q.size()`.
   b. If `level_size > maxNodes`, update `maxNodes = level_size` and `maxLevel = currentLevel`.
   c. Loop `level_size` times:
      i. Pop the front node `curr`.
      ii. Push `curr->left` and `curr->right` into `q` if they exist.
   d. Increment `currentLevel`.
5. Return `maxLevel`.

Time Complexity : O(N) — Every node is pushed and popped from the queue exactly once.
Space Complexity: O(W) — The queue will at most hold W nodes, where W is the maximum width of the tree.

(N = number of nodes, W = max width)

GFG Link:
https://www.geeksforgeeks.org/problems/maximum-node-level/1
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
    int maxNodeLevel(Node *root) {
        if (!root) {
            return 0; 
        }
        
        queue<Node*> q;
        q.push(root);
        
        int maxNodes = 0;
        int maxLevel = 0;
        int currentLevel = 0;
        
        while (!q.empty()) {
            // Number of nodes at the current level
            int level_size = q.size();
            
            // Check if this level has strictly more nodes than previous levels
            if (level_size > maxNodes) {
                maxNodes = level_size;
                maxLevel = currentLevel;
            }
            
            // Process all nodes at the current level and enqueue their children
            for (int i = 0; i < level_size; ++i) {
                Node* curr = q.front();
                q.pop();
                
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            
            // Move to the next level
            currentLevel++;
        }
        
        return maxLevel;
    }
};

/*
Dry Run — Example 1:
         2
       /   \
      1     3
     / \     \
    4   6     8
       /
      5

Initial:
queue = [2]
maxNodes = 0, maxLevel = 0, currentLevel = 0

Level 0 (size = 1):
- size (1) > maxNodes (0) -> maxNodes = 1, maxLevel = 0
- pop 2, push 1, 3
- currentLevel becomes 1
queue = [1, 3]

Level 1 (size = 2):
- size (2) > maxNodes (1) -> maxNodes = 2, maxLevel = 1
- pop 1, push 4, 6
- pop 3, push 8
- currentLevel becomes 2
queue = [4, 6, 8]

Level 2 (size = 3):
- size (3) > maxNodes (2) -> maxNodes = 3, maxLevel = 2
- pop 4
- pop 6, push 5
- pop 8
- currentLevel becomes 3
queue = [5]

Level 3 (size = 1):
- size (1) is NOT > maxNodes (3)
- pop 5
- currentLevel becomes 4
queue = []

Loop ends.
Return maxLevel = 2. ✓
*/
