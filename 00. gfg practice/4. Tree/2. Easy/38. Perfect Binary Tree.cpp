/*
GeeksforGeeks: Perfect Binary Tree
Difficulty: Easy

Problem:
Given a Binary Tree, check whether the given Binary Tree is a perfect Binary Tree or not. 
A Binary tree is Perfect Binary Tree in which all internal nodes have two children 
and all leaves are at the same level.

Example 1:
Input: root[] = [7, 4, 9]
      7
    /   \
   4     9
Output: true
Explanation: 
The root node 7 has two children and both leaf nodes 4 and 9 are at the same level.

Example 2:
Input: root[] = [7, 3, 8, 2, 5, N, 10, 1, N, N, N, N, N]
         7
       /   \
      3     8
     / \     \
    2   5    10
   /
  1
Output: false
Explanation: 
Node 8 has only one child (10). Node 2 has one child (1). Leaves are at different levels.

Core Idea:
A Perfect Binary Tree has two strict rules:
1. Every internal node must have EXACTLY two children. (No node can have just 1 child).
2. All leaves must be at the EXACT SAME level.

If we traverse the tree level by level using BFS, these rules translate to:
1. If we find a node with exactly 1 child, immediately return false.
2. A single level in the tree must consist ENTIRELY of internal nodes, OR ENTIRELY of 
   leaf nodes. If a level mixes internal nodes and leaf nodes, it means some paths 
   terminated early while others continued, meaning leaves are on different levels!

Approach:
1. Base Case: If `root` is NULL, it is technically a perfect tree of height 0. Return true.
2. Initialize a `queue<Node*> q` and push `root`.
3. Loop while `q` is not empty:
   a. Get `level_size = q.size()`.
   b. Reset two boolean flags for the current level: `levelHasLeaf = false` and 
      `levelHasInternal = false`.
   c. For each node in the current level:
      i. Pop `curr`.
      ii. If `curr` has exactly 1 child (`!curr->left || !curr->right` but not both null), 
          return false.
      iii. If `curr` is a leaf (`!curr->left && !curr->right`), set `levelHasLeaf = true`.
      iv. If `curr` has 2 children, set `levelHasInternal = true`, and push both children.
   d. After processing the level, check: `if (levelHasLeaf && levelHasInternal) return false;`
4. If BFS completes without failing any rules, return true.

Time Complexity : O(N) — Every node is visited exactly once.
Space Complexity: O(W) — The queue stores nodes level by level, where W is max width.

(N = number of nodes, W = max width)

GFG Link:
https://www.geeksforgeeks.org/problems/perfect-binary-tree/1
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
    bool isPerfect(Node *root) {
        if (!root) {
            return true;
        }
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int level_size = q.size();
            
            bool levelHasLeaf = false;
            bool levelHasInternal = false;
            
            for (int i = 0; i < level_size; ++i) {
                Node* curr = q.front();
                q.pop();
                
                // Rule 1: A node cannot have exactly 1 child.
                if ((curr->left && !curr->right) || (!curr->left && curr->right)) {
                    return false;
                }
                
                // Rule 2 Check: Is it a leaf or an internal node?
                if (!curr->left && !curr->right) {
                    levelHasLeaf = true;
                } else {
                    levelHasInternal = true;
                    q.push(curr->left);
                    q.push(curr->right);
                }
            }
            
            // Rule 2 Enforcement: A level cannot mix leaves and internal nodes
            if (levelHasLeaf && levelHasInternal) {
                return false;
            }
        }
        
        return true;
    }
};

/*
Dry Run — Example 2:
         7
       /   \
      3     8
     / \     \
    2   5    10
   /
  1

Initial:
q = [7]

Level 0:
- curr = 7 (Internal). levelHasInternal = true. push 3, 8.
- levelHasLeaf = false, levelHasInternal = true. (Valid)
q = [3, 8]

Level 1:
- curr = 3 (Internal). levelHasInternal = true. push 2, 5.
- curr = 8 (1 child! left is NULL, right is 10). 
- The condition `(!curr->left && curr->right)` triggers.
- Returns false.

Final Result = false. ✓

Dry Run — Asymmetric Leaves:
      1
    /   \
   2     3
  / \
 4   5

Level 1 (nodes 2, 3):
- curr = 2 (Internal). levelHasInternal = true. push 4, 5.
- curr = 3 (Leaf). levelHasLeaf = true.
- After Level 1 loop: levelHasLeaf (true) && levelHasInternal (true).
- Returns false. (Validates that leaves are at different depths)

Final Result = false. ✓
*/
