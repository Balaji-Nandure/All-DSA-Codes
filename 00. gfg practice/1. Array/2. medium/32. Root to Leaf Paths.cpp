/*
PROBLEM: Root to Leaf Paths (Binary Tree)

Given a binary tree, return all paths from root to leaf nodes.
Leaf node = node with no left and no right child.

Example:
Input:
        1
      /   \
     2     3
    / \
   4   5

Output:
[[1,2,4], [1,2,5], [1,3]]

--------------------------------------------------

INTUITION / APPROACH:

This is a DFS + Backtracking problem.

We maintain a vector called "path" which stores the current path
from root to the current node.

Algorithm:
1. Add current node to path
2. If the node is a leaf → store the path in answer
3. Recur for left subtree
4. Recur for right subtree
5. Remove the current node from path (Backtracking)

Why backtracking?
Because the same path vector is reused for left and right subtree.
So we must remove the node when returning.

IMPORTANT:
Left subtree paths must come before right subtree paths → so call left first.

--------------------------------------------------

PATTERN:
"Print all paths" → DFS + Backtracking

--------------------------------------------------

TIME COMPLEXITY:
O(N * H)
N = number of nodes
H = height of tree (copying path each time)

SPACE COMPLEXITY:
O(H) recursion stack

--------------------------------------------------

GFG:
https://practice.geeksforgeeks.org/problems/root-to-leaf-paths/1

LeetCode:
https://leetcode.com/problems/binary-tree-paths/

--------------------------------------------------
*/

class Solution {
  public:

    void dfs(Node* root, vector<int>& path, vector<vector<int>>& ans) {
        
        // Base case
        if(root == NULL)
            return;
        
        // Step 1: Add current node to path
        path.push_back(root->data);
        
        // Step 2: If leaf node → store path
        if(root->left == NULL && root->right == NULL) {
            ans.push_back(path);
        }
        else {
            // Step 3: Traverse left then right
            dfs(root->left, path, ans);
            dfs(root->right, path, ans);
        }
        
        // Step 4: Backtrack → remove current node
        path.pop_back();
    }

    vector<vector<int>> Paths(Node* root) {
        
        vector<vector<int>> ans;
        vector<int> path;
        
        dfs(root, path, ans);
        
        return ans;
    }
};


/*
---------------- DRY RUN ----------------

Tree:
        1
      /   \
     2     3
    / \
   4   5

Path flow:
1 → 2 → 4 → store
Backtrack to 2
1 → 2 → 5 → store
Backtrack to 1
1 → 3 → store

Output:
[ [1,2,4], [1,2,5], [1,3] ]

--------------------------------------------------

FINAL SUMMARY:

Category: Binary Tree
Pattern: DFS + Backtracking
Key Idea: Maintain path vector and backtrack after recursion

Whenever problem says:
- Print all paths
- Root to leaf
- All combinations
→ Think Backtracking
*/
