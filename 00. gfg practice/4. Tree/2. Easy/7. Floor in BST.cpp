/*
Problem: Floor in BST

Given the root of a binary search tree and a number k, find the greatest number in the binary search tree that is less than or equal to k.
Note: If no such node value exists that is smaller than k, then return -1.

Constraints:
1 <= number of nodes <= 10^5
1 <= node->data, k <= 10^5
All nodes are unique in the BST

--------------------------------------------------

Pattern:
BST Traversal

--------------------------------------------------

Key Observation:
- We want to find the largest value in the BST that is `<= k`.
- As we thoughtfully traverse the BST:
  - If we find a node identically equal to `k`, it is perfectly our floor.
  - If the current node's value is strictly greater than `k`, it cannot possibly be the floor. The only valid candidates must lie in its left subtree.
  - If the current node's value is less than `k`, it *could* very well be our floor. We remember this value as our best candidate so far, and then explore the right subtree to see if we can find a better (larger) candidate that is still `<= k`.

--------------------------------------------------

Approach:
1. Initialize a variable `floor_val` to `-1` to store our best candidate found so far.
2. Use a `while` loop to traverse as long as `root` is not `nullptr`.
3. If `root->data == k`, we found an exact match. We can aggressively return `root->data` immediately.
4. If `root->data > k`, this node and its right children are undeniably too large. Move strictly to the left child: `root = root->left`.
5. If `root->data < k`, this is an absolutely valid floor candidate! Update `floor_val = root->data`, and then deliberately move to the right child to aggressively search for a larger, tighter valid value: `root = root->right`.
6. Return `floor_val` once the traversal naturally bottoms out at a `NULL` leaf.

--------------------------------------------------

Time Complexity: O(H) where H is the height of the BST. In the best case (perfectly balanced tree), this scales down to O(log N). In the absolute worst case (a skewed tree), this degrades linearly to O(N).
Space Complexity: O(1) as we optimally iterate via pointers, explicitly avoiding utilizing any extra data structures or memory-heavy recursion stacks.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/floor-in-bst/1
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
    int floor(Node* root, int k) {
        int ans = -1;
        
        while (root != nullptr) {
            // Exact match is naturally the best possible floor
            if (root->data == k) {
                return root->data;
            }
            
            if (root->data > k) {
                // Too large, must seek strictly smaller values
                root = root->left;
            } else {
                // Valid candidate found! Save it and cautiously seek larger ones
                ans = root->data;
                root = root->right;
            }
        }
        
        return ans;
    }
};
