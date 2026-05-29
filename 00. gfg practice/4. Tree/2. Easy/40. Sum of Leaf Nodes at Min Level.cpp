/*
GeeksforGeeks: Sum of Leaf Nodes at Min Level
Difficulty: Easy

Problem:
Given a Binary Tree, find the sum of all the leaf nodes that are at the 
minimum level of the given binary tree.

Example 1:
Input: root[] = [1, 2, 3, 4, 5, N, 8, 7, 2, N, N, N, N]
         1
       /   \
      2     3
     / \     \
    4   5     8
   / \
  7   2
Output: 13
Explanation: 
Level 1: Node 1
Level 2: Nodes 2, 3
Level 3: Nodes 4, 5, 8. (Here 5 and 8 are leaf nodes)
Level 4: Nodes 7, 2. (Leaf nodes)
The minimum level containing leaf nodes is Level 3. 
The sum of leaf nodes at this level = 5 + 8 = 13.

Example 2:
Input: root[] = [1, 2, 3, 4, 5, 6, 7]
         1
       /   \
      2     3
     / \   / \
    4   5 6   7
Output: 22
Explanation: 
The minimum level containing leaf nodes is Level 3.
The sum of leaf nodes at this level = 4 + 5 + 6 + 7 = 22.

Core Idea:
Because we want leaf nodes at the "minimum level", a Level Order Traversal (BFS) 
using a Queue is the absolute best approach. 
Since BFS traverses the tree top-to-bottom, the very first time we encounter a 
leaf node, we are mathematically guaranteed to be at the "minimum level for leaf nodes". 
Once we are at this level, we simply sum up the values of all leaf nodes we encounter 
on this specific level, and then stop traversing entirely.

Approach:
1. Base Case: If `root` is NULL, return 0.
2. Initialize `queue<Node*> q` and push `root`.
3. Initialize `sum = 0` and a boolean `foundLeaf = false`.
4. While `q` is not empty:
   a. Get `level_size = q.size()`.
   b. Loop `level_size` times for the current level:
      i. Pop `curr`.
      ii. If `curr` is a leaf node (`!curr->left && !curr->right`), add its data to 
          `sum` and set `foundLeaf = true`.
      iii. Else, push its children if they exist.
   c. If `foundLeaf == true` after checking all nodes at the current level, it means 
      we have found the minimum level with leaves. We `break` out of the loop!
5. Return the calculated `sum`.

Time Complexity : O(N) — Every node is visited at most once. The traversal terminates early.
Space Complexity: O(W) — Space for the queue, where W is the maximum width of the tree.

GFG Link:
https://www.geeksforgeeks.org/problems/sum-of-leaf-nodes-at-min-level/1
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
    int minLeafSum(Node *root) {
        if (!root) {
            return 0;
        }
        
        queue<Node*> q;
        q.push(root);
        
        int sum = 0;
        bool foundLeaf = false;
        
        while (!q.empty()) {
            int level_size = q.size();
            
            for (int i = 0; i < level_size; ++i) {
                Node* curr = q.front();
                q.pop();
                
                // If it is a leaf node, add to sum and mark foundLeaf
                if (!curr->left && !curr->right) {
                    sum += curr->data;
                    foundLeaf = true;
                }
                
                // Push children for the next level
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            
            // If we found any leaves on this level, it is the minimum level.
            // We don't need to process any deeper levels.
            if (foundLeaf) {
                break;
            }
        }
        
        return sum;
    }
};

/*
Dry Run — Example 1:
         1
       /   \
      2     3
     / \     \
    4   5     8
   / \
  7   2

Initial:
q = [1], sum = 0, foundLeaf = false

Level 1 (size = 1):
- pop 1 (Internal): push 2, 3
q = [2, 3]

Level 2 (size = 2):
- pop 2 (Internal): push 4, 5
- pop 3 (Internal): push 8
q = [4, 5, 8]

Level 3 (size = 3):
- pop 4 (Internal): push 7, 2
- pop 5 (Leaf): sum += 5, foundLeaf = true
- pop 8 (Leaf): sum += 8, foundLeaf = true
q = [7, 2]

End of Level 3 loop:
`foundLeaf` is true, so we break!

Return sum = 13. ✓
*/
