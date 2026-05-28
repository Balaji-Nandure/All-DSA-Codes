/*
Problem: Inorder Traversal

Given a root of a Binary Tree, your task is to return its Inorder Traversal.
Note: An inorder traversal first visits the left child (including its entire subtree), then visits the node, and finally visits the right child (including its entire subtree).

Constraints:
1 <= number of nodes <= 3*10^4
0 <= node->data <= 10^5

--------------------------------------------------

Pattern:
Tree Traversal (DFS)

--------------------------------------------------

Key Observation:
- Inorder traversal logically follows the classic order: Left -> Root -> Right.
- For actual Binary Search Trees, this specific traversal perfectly guarantees visiting the nodes in strictly increasing (sorted) order!
- We can seamlessly accomplish this using a simple, highly elegant recursive Depth-First Search strategy.

--------------------------------------------------

Approach:
1. Initialize an empty `vector<int> res` to meticulously collect our traversal output.
2. Create a standard recursive `dfs` helper function that takes the current `node` and a reference to `res`.
3. Base case: If the current `node` is `nullptr`, immediately return (bottom out of recursion).
4. Recursively traverse the left subtree: `dfs(node->left, res)`.
5. Process the current node by gracefully pushing its data into our list: `res.push_back(node->data)`.
6. Recursively traverse the right subtree: `dfs(node->right, res)`.
7. Return the neatly populated `res` array from the main wrapper function.

--------------------------------------------------

Time Complexity: O(N) since we strictly visit every single node in the tree exactly once.
Space Complexity: O(N) overall. O(H) for the internal recursion stack where H is the height of the tree (degrading to O(N) in the absolute worst-case skewed tree), plus O(N) to explicitly store the final answers array.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/inorder-traversal/1
*/

#include <iostream>
#include <vector>

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
private:
    void dfs(Node* root, vector<int>& res) {
        if (root == nullptr) {
            return;
        }
        
        // 1. Visit the entirely of the left subtree first
        dfs(root->left, res);
        
        // 2. Process the current node
        res.push_back(root->data);
        
        // 3. Visit the entirely of the right subtree last
        dfs(root->right, res);
    }

public:
    vector<int> inOrder(Node* root) {
        vector<int> res;
        dfs(root, res);
        return res;
    }
};
