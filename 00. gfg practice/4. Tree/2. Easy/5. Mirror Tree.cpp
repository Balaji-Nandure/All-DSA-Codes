/*
Problem: Mirror Tree

Given the root of a binary tree, convert the binary tree to its Mirror tree.
Note: Mirror of a Binary Tree T is another Binary Tree M(T) with left and right children of all non-leaf nodes interchanged.

Constraints:
1 <= number of nodes <= 10^4
1 <= node->data <= 10^5

--------------------------------------------------

Pattern:
Tree Traversal (Post-order / Pre-order DFS)

--------------------------------------------------

Key Observation:
- Mirroring a tree means simply swapping the left and right children for *every* node in the entire tree.
- A standard Depth-First Search easily accomplishes this by systematically visiting each node and swapping its child pointers.

--------------------------------------------------

Approach:
1. Base Case: If the current `node` is `nullptr`, there's nothing to mirror, so just return.
2. Recursively call the `mirror` function for `node->left` to successfully mirror the entire left subtree.
3. Recursively call the `mirror` function for `node->right` to successfully mirror the entire right subtree.
4. Swap the actual child pointers: `swap(node->left, node->right)`. (Note: Swapping can also be done before the recursive calls, corresponding to a Pre-order traversal instead of a Post-order).

--------------------------------------------------

Time Complexity: O(N) as we visit every single node in the tree exactly once.
Space Complexity: O(H) where H is the maximum height of the tree, representing the recursion stack depth. In the absolute worst case (a perfectly skewed tree), this degrades to O(N).

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/mirror-tree/1
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
    // Function to convert a binary tree into its mirror tree.
    void mirror(Node* node) {
        // Base case
        if (node == nullptr) {
            return;
        }
        
        // Recursively mirror the left and right subtrees
        mirror(node->left);
        mirror(node->right);
        
        // Swap the left and right child pointers of the current node
        swap(node->left, node->right);
    }
};
