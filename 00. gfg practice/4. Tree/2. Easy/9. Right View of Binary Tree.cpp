/*
Problem: Right View of Binary Tree

Given the root of a binary Tree. Return the right view of the binary tree. The right view of a Binary Tree is the set of nodes visible when the tree is viewed from the right side.

Constraints:
1 <= number of nodes <= 10^5
0 <= node->data <= 10^5

--------------------------------------------------

Pattern:
Tree Traversal (DFS & BFS variants)

--------------------------------------------------

Key Observation:
- The right view of a tree mathematically maps to the very *last* node encountered horizontally at each depth level.
- Solution 1 (DFS): If we perform a standard Depth-First Search while strictly prioritizing the right child before the left child, the very first time we reach a new depth, the node we are at is guaranteed to be the rightmost visible node of that depth.
- Solution 2 (BFS): If we perform a Level Order Traversal utilizing a Queue, we process the tree strictly level by level. The very last node we process at every new level loop is simply the rightmost node!

--------------------------------------------------

Approach:
[Solution 1 - DFS]
1. Create a recursive `dfs` helper function that tracks the current `level`.
2. If the current `level` is equal to `res.size()`, append `Node->data` into `res` (since we prioritize visiting right subtrees first, this must be the rightmost node).
3. Recursively call `dfs` on `Node->right` and then `Node->left` with `level + 1`.

[Solution 2 - BFS]
1. Create a `queue<Node*> q` and push the `root` into it.
2. Run a `while` loop until the queue is completely empty.
3. Determine the number of nodes at the current level using `q.size()`.
4. Loop exactly `q.size()` times. If it's the very last node of the loop (`i == level_size - 1`), push its data to `res`.
5. Push the left and right children of the popped nodes to the queue for the next level iteration.
6. Return `res`.

--------------------------------------------------

Time Complexity: O(N) for both approaches, as we touch each node exactly once.
Space Complexity: O(H) for DFS (recursion stack height) and O(W) for BFS (queue size, where W is max width of the tree). In the absolute worst cases (skewed tree for DFS, perfectly balanced for BFS), both can degrade to O(N).

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/right-view-of-binary-tree/1
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Definition for a binary tree node
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
};

// Solution 1: DFS (Pre-order variant, right-first)
class Solution {
private:
    void dfs(Node* root, int level, vector<int>& res) {
        if (root == nullptr) {
            return;
        }
        
        // If this is the first node we're visiting at this level (coming from right)
        if (res.size() == level) {
            res.push_back(root->data);
        }
        
        // Prioritize right side first
        dfs(root->right, level + 1, res);
        
        // Visit left side for nodes that might be visible if right is missing
        dfs(root->left, level + 1, res);
    }

public:
    vector<int> rightView(Node *root) {
        vector<int> res;
        dfs(root, 0, res);
        return res;
    }
};

// Solution 2: BFS (Level Order Traversal)
class Solution2 {
public:
    vector<int> rightView(Node *root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int level_size = q.size();
            
            for (int i = 0; i < level_size; ++i) {
                Node* curr = q.front();
                q.pop();
                
                // The last node processed at any level is the right view
                if (i == level_size - 1) {
                    res.push_back(curr->data);
                }
                
                if (curr->left != nullptr) q.push(curr->left);
                if (curr->right != nullptr) q.push(curr->right);
            }
        }
        
        return res;
    }
};
