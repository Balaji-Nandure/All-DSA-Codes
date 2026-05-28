/*
Problem: Balanced Tree Check

Given the root of a binary tree, determine if it is height-balanced or not.
A binary tree is considered height-balanced if the absolute difference in heights of the left and right subtrees is at most 1 for every node in the tree.

Constraints:
1 <= number of nodes <= 1000
1 <= node->data <= 10^4

--------------------------------------------------

Pattern:
Tree Traversal (Bottom-Up DFS)

--------------------------------------------------

Key Observation:
- A naive approach would be to calculate the height of the left and right subtrees for every single node. However, this takes O(N^2) time because we repeatedly calculate heights for the same lower-level nodes.
- We can optimize this by calculating the height from the bottom up! 
- If we find that any subtree is unbalanced, we don't need to continue calculating normal heights. We can simply return `-1` to strictly indicate "Unbalanced".
- If a subtree is balanced, we just return its actual height, allowing the parent node to easily use it for its own calculation.

--------------------------------------------------

Approach:
1. Create a helper function `checkHeight` that recursively performs a Depth-First Search.
2. Base case: If the node is `NULL`, return a height of `0`.
3. Recursively call `checkHeight` on the left child:
    a. If it returns `-1`, it means the left subtree is unbalanced, so immediately return `-1` upwards.
4. Recursively call `checkHeight` on the right child:
    a. If it returns `-1`, it means the right subtree is unbalanced, so immediately return `-1` upwards.
5. If both subtrees are balanced, check their absolute height difference: `abs(leftHeight - rightHeight)`.
    a. If the difference is strictly greater than 1, the current node is unbalanced. Return `-1`.
6. Otherwise, the current node is perfectly balanced! Return its height: `max(leftHeight, rightHeight) + 1`.
7. In the main `isBalanced` function, just return `true` if `checkHeight(root) != -1`, else `false`.

--------------------------------------------------

Time Complexity: O(N) as we traverse every node exactly once from the bottom up.
Space Complexity: O(H) where H is the height of the binary tree, corresponding to the recursion stack depth. In the worst case (skewed tree), this degrades to O(N).

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/check-for-balanced-tree/1
*/

#include <iostream>
#include <algorithm>
#include <cmath>

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
private:
    int checkHeight(Node* root) {
        // Base case: an empty tree is always balanced and has a height of 0
        if (root == nullptr) {
            return 0;
        }
        
        // Check the left subtree
        int leftHeight = checkHeight(root->left);
        if (leftHeight == -1) {
            return -1; // Propagate the failure upwards
        }
        
        // Check the right subtree
        int rightHeight = checkHeight(root->right);
        if (rightHeight == -1) {
            return -1; // Propagate the failure upwards
        }
        
        // If the current node is unbalanced, return -1
        if (abs(leftHeight - rightHeight) > 1) {
            return -1;
        }
        
        // If balanced, return the actual height of this subtree
        return max(leftHeight, rightHeight) + 1;
    }

public:
    bool isBalanced(Node *root) {
        // If checkHeight doesn't return -1, the entire tree is balanced
        return checkHeight(root) != -1;
    }
};
