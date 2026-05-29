/*
GeeksforGeeks: Max Level Sum in Binary Tree
Difficulty: Easy

Problem:
Given a Binary Tree having positive and negative nodes. Find the maximum sum 
of a level in the given Binary Tree.

Example 1:
Input :               
             4
          /    \
         2     -5
        / \    / \
      -1   3  -2  6

Output: 6
Explanation :
Sum of all nodes of 0'th level is 4
Sum of all nodes of 1'th level is 2 + (-5) = -3
Sum of all nodes of 2'th level is (-1) + 3 + (-2) + 6 = 6
Hence maximum sum is 6

Example 2:
Input :          
            1
          /   \
         2     3
        / \     \
       4   5     8
                / \
               6   7  

Output :  17
Explanation: 
Level 0 sum: 1
Level 1 sum: 2 + 3 = 5
Level 2 sum: 4 + 5 + 8 = 17
Level 3 sum: 6 + 7 = 13
Maximum sum is at level 2 which is 17.

Core Idea:
Just like finding the level with the most nodes, finding the level with the maximum 
sum is perfectly suited for a Level Order Traversal (BFS) using a Queue.
By processing the queue level by level (using the size of the queue at the start of 
the iteration), we can calculate the total sum of the nodes at that level. We simply 
keep track of the maximum sum encountered so far.
Since node values can be negative, we must initialize our `maxSum` to `INT_MIN`.

Approach:
1. Base Case: If `root` is NULL, return 0 (Constraints specify N >= 1, but this is safe).
2. Initialize `queue<Node*> q`, and push `root`.
3. Initialize `maxSum = INT_MIN`.
4. While `q` is not empty:
   a. Get `level_size = q.size()`.
   b. Initialize `currentLevelSum = 0`.
   c. Loop `level_size` times:
      i. Pop the front node `curr`.
      ii. Add `curr->data` to `currentLevelSum`.
      iii. Push `curr->left` and `curr->right` into `q` if they exist.
   d. Update `maxSum = max(maxSum, currentLevelSum)`.
5. Return `maxSum`.

Time Complexity : O(N) — Every node is visited exactly once.
Space Complexity: O(W) — The queue stores nodes level by level, where W is the max width of the tree.

(N = number of nodes, W = max width)

GFG Link:
https://www.geeksforgeeks.org/problems/max-level-sum-in-binary-tree/1
*/

#include <iostream>
#include <queue>
#include <climits>
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
public:
    int maxLevelSum(Node* root) {
        if (!root) {
            return 0;
        }
        
        queue<Node*> q;
        q.push(root);
        
        int maxSum = INT_MIN; // Important: nodes can be negative
        
        while (!q.empty()) {
            int level_size = q.size();
            int currentLevelSum = 0;
            
            // Process all nodes at the current level
            for (int i = 0; i < level_size; ++i) {
                Node* curr = q.front();
                q.pop();
                
                currentLevelSum += curr->data;
                
                // Enqueue children for the next level
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            
            // Update maxSum if the current level's sum is greater
            maxSum = max(maxSum, currentLevelSum);
        }
        
        return maxSum;
    }
};

/*
Dry Run — Example 1:
             4
          /    \
         2     -5
        / \    / \
      -1   3  -2  6

Initial:
queue = [4]
maxSum = INT_MIN

Level 0 (size = 1):
- currentLevelSum = 0
- pop 4: currentLevelSum += 4 (is 4), push 2, -5
- loop ends. 
- maxSum = max(INT_MIN, 4) = 4
queue = [2, -5]

Level 1 (size = 2):
- currentLevelSum = 0
- pop 2: currentLevelSum += 2 (is 2), push -1, 3
- pop -5: currentLevelSum += -5 (is -3), push -2, 6
- loop ends.
- maxSum = max(4, -3) = 4
queue = [-1, 3, -2, 6]

Level 2 (size = 4):
- currentLevelSum = 0
- pop -1: currentLevelSum += -1 (is -1)
- pop 3: currentLevelSum += 3 (is 2)
- pop -2: currentLevelSum += -2 (is 0)
- pop 6: currentLevelSum += 6 (is 6)
- loop ends.
- maxSum = max(4, 6) = 6
queue = []

Loop terminates.
Return maxSum = 6. ✓
*/
