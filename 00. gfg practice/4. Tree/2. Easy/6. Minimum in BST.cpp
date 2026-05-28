/*
Problem: Minimum in BST

Given the root of a Binary Search Tree, find the minimum element in this given BST.

Constraints:
0 <= number of nodes <= 10^5
0 <= node->data <= 10^5

--------------------------------------------------

Pattern:
BST Traversal

--------------------------------------------------

Key Observation:
- In a Binary Search Tree (BST), the left child of a node is strictly smaller than the node itself, while the right child is strictly greater.
- Because of this fundamental BST property, the absolute smallest element in the entire tree will identically always be located by continuously traversing to the left-most node until we can go left no further.

--------------------------------------------------

Approach:
1. Handle the edge case: If the given `root` is `nullptr`, return `-1` as dictated by the problem's examples.
2. Initialize a `while` loop that continuously moves the `root` pointer to its left child (`root = root->left`) strictly as long as `root->left` is not `nullptr`.
3. Once `root->left` becomes `nullptr`, we know we have officially reached the extreme left-most node. Return its `data` value.

--------------------------------------------------

Time Complexity: O(H) where H is the height of the tree. In the average case (a balanced tree), this scales gracefully to O(log N). In the absolute worst case (a fully skewed tree leaning left), this linearly degrades to O(N).
Space Complexity: O(1) since we are traversing the tree iteratively rather than recursively, maintaining no additional memory overhead!

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/minimum-element-in-bst/1
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node
struct Node {
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
    int minValue(Node* root) {
        // If the tree is completely empty
        if (root == nullptr) {
            return -1;
        }
        
        // Traverse to the extreme left to find the absolute minimum element
        while (root->left != nullptr) {
            root = root->left;
        }
        
        return root->data;
    }
};
