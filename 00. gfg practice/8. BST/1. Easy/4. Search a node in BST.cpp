/*
GeeksforGeeks: Search a node in BST
Difficulty: Easy

Problem:
Given the root of a Binary Search Tree and a node value key, return true if the node with value key is present in the BST; otherwise, return false.

Examples:
Input: root = [6, 2, 8, N, N, 7, 9], key = 8
Output: true
Explanation: 8 is present in the BST as right child of root.

Input: root = [16, 12, 18, 10, N, 17, 19], key = 14
Output: false
Explanation: 14 is not present in the BST

Core Idea:
In a Binary Search Tree, for any given node, all elements in its left subtree are smaller than the node, and all elements in its right subtree are greater. 
We can use this property to efficiently search for a key. Starting from the root, we compare the key with the current node's value. 
If it matches, we found the node. If the key is smaller, we only need to search the left subtree. If the key is larger, we only need to search the right subtree. 
This process is repeated until the key is found or we reach a null pointer (indicating the key is not in the tree).

Approach:
1. Start with a pointer `curr` pointing to the `root`.
2. Loop while `curr` is not `nullptr`:
   - If `curr->data == key`: The key is found, return `true`.
   - If `key < curr->data`: The key might be in the left subtree, so update `curr = curr->left`.
   - If `key > curr->data`: The key might be in the right subtree, so update `curr = curr->right`.
3. If the loop terminates because `curr` becomes `nullptr`, the key was not found, return `false`.

Time Complexity: O(H) where H is the height of the BST. In the worst case (skewed tree), it's O(N). For a balanced BST, it's O(log N).
Space Complexity: O(1) auxiliary space, as we are using an iterative approach.

GFG Link: https://www.geeksforgeeks.org/problems/search-a-node-in-bst/1
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node.
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

class Solution {
public:
    // Function to search a node in BST.
    bool search(Node* root, int x) {
        Node* curr = root;
        
        while (curr != nullptr) {
            if (curr->data == x) {
                return true; // Found the key
            } else if (x < curr->data) {
                curr = curr->left; // Key is smaller, go to left subtree
            } else {
                curr = curr->right; // Key is larger, go to right subtree
            }
        }
        
        return false; // Reached a leaf and didn't find the key
    }
};

/*
Dry Run — Example 1:
Input: root = [6, 2, 8, N, N, 7, 9], key = 8
Tree Structure:
         6
       /   \
      2     8
           / \
          7   9

Call: search(root, 8)

1. curr = Node(6).

2. Loop iteration 1:
   - curr is not NULL.
   - x (8) > curr->data (6).
   - curr = curr->right (Node 8).

3. Loop iteration 2:
   - curr is not NULL.
   - curr->data (8) == x (8).
   - Match found! Return true.

Output: true
*/
