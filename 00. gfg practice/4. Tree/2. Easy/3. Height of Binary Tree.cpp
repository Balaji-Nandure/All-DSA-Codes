/*
Problem: Height of Binary Tree

Given the root of a binary tree, your task is to find the maximum depth of the tree.
Note: The maximum depth or height of the tree is the number of edges in the tree from the root to the deepest node.

Constraints:
1 <= number of nodes <= 3*10^4
0 <= node->data <= 10^5

--------------------------------------------------

Pattern:
Tree Traversal (DFS)

--------------------------------------------------

Key Observation:
- The height of a binary tree in terms of nodes is simply `max(left_height, right_height) + 1` where a leaf returns 1.
- However, this problem explicitly defines height as the number of *edges* from the root to the deepest node.
- A single isolated node (leaf) has 0 edges connecting it to anything below, so its height should be 0.
- If we set our base case to return `-1` when a node is `NULL`, the calculation `max(-1, -1) + 1` naturally evaluates to `0` for leaf nodes, perfectly shifting our calculation from "nodes" to "edges".

--------------------------------------------------

Approach:
1. Create a recursive `height` function taking a `Node*`.
2. Base case: If the node is `nullptr`, return `-1`. This naturally accounts for the 0-edge requirement of leaf nodes.
3. Recursively calculate the height of the left subtree: `leftHeight = height(node->left)`.
4. Recursively calculate the height of the right subtree: `rightHeight = height(node->right)`.
5. Return the maximum of the two subtree heights, plus 1 for the current edge: `max(leftHeight, rightHeight) + 1`.

--------------------------------------------------

Time Complexity: O(N) as we visit every node in the binary tree exactly once.
Space Complexity: O(H) where H is the height of the binary tree, corresponding to the recursion stack depth. In the worst case (a completely skewed tree), this degrades to O(N).

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/height-of-binary-tree/1
*/

#include <iostream>
#include <algorithm>

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

class Solution {
public:
    int height(struct Node* node) {
        // Base case: return -1 so that leaf nodes evaluate to exactly 0 (edges)
        if (node == nullptr) {
            return -1;
        }
        
        // Recursively compute the height of the left and right subtrees
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        
        // Return the maximum height of the subtrees, plus 1 for the current edge
        return max(leftHeight, rightHeight) + 1;
    }
};
