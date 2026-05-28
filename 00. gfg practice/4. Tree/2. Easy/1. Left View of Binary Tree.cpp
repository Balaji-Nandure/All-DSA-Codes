/*
Problem: Left View of Binary Tree

Given the root of a binary tree. Your task is to return the left view of the binary tree. The left view of a binary tree is the set of nodes visible when the tree is viewed from the left side.

Constraints:
0 <= number of nodes <= 10^5
0 <= node->data <= 10^5

--------------------------------------------------

Pattern:
Tree Traversal (DFS & BFS variants)

--------------------------------------------------

Key Observation:
- The left view of a tree mathematically maps to the very first node encountered at each horizontal depth level.
- Solution 1 (DFS): If we perform a standard Depth-First Search while strictly prioritizing the left child before the right child, the very first time we reach a new depth, the node we are at is guaranteed to be the leftmost visible node of that depth.
- Solution 2 (BFS): If we perform a Level Order Traversal utilizing a Queue, we process the tree level by level. The very first node we pop out at every new level is simply the leftmost node!

--------------------------------------------------

Approach:
[Solution 1 - DFS]
1. Create a recursive `dfs` helper function that tracks the current `level`.
2. If the current `level` is equal to `res.size()`, append `Node->data` into `res`.
3. Recursively call `dfs` on `Node->left` and then `Node->right` with `level + 1`.

[Solution 2 - BFS]
1. Create a `queue<Node*> q` and push the `root` into it.
2. Run a `while` loop until the queue is completely empty.
3. Determine the number of nodes at the current level using `q.size()`.
4. Loop exactly `q.size()` times. If it's the very first node of the loop (`i == 0`), push its data to `res`.
5. Push the left and right children of the popped nodes to the queue for the next level iteration.
6. Return `res`.

--------------------------------------------------

Time Complexity: O(N) for both approaches, as we touch each node exactly once.
Space Complexity: O(H) for DFS (recursion stack height) and O(W) for BFS (queue size, where W is max width of the tree). In the absolute worst cases (skewed tree for DFS, perfectly balanced for BFS), both can degrade to O(N).

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/left-view-of-binary-tree/1
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

// Solution 1: DFS (Pre-order variant)
class Solution {
private:
    void dfs(Node* root, int level, vector<int>& res) {
        if (root == nullptr) {
            return;
        }
        
        // If this is the first node we're visiting at this level
        if (res.size() == level) {
            res.push_back(root->data);
        }
        
        // Prioritize left side first
        dfs(root->left, level + 1, res);
        
        // Visit right side for nodes that might be visible if left is missing
        dfs(root->right, level + 1, res);
    }

public:
    vector<int> leftView(Node *root) {
        vector<int> res;
        dfs(root, 0, res);
        return res;
    }
};

// Solution 2: BFS (Level Order Traversal)
class Solution2 {
public:
    vector<int> leftView(Node *root) {
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
                
                // The first node processed at any level is the left view
                if (i == 0) {
                    res.push_back(curr->data);
                }
                
                if (curr->left != nullptr) q.push(curr->left);
                if (curr->right != nullptr) q.push(curr->right);
            }
        }
        
        return res;
    }
};
