/*
GeeksforGeeks: BST Insert
Difficulty: Easy

Problem:
Given the root of a binary search tree and a value key. Insert a new node with a value equal to key into the tree and return the root of the modified tree after inserting the value. 
Note: All the nodes have distinct values in the BST and the new value to be inserted is not present in the BST.

Example 1:
Input: root = [2, 1, 3], key = 4
Output: [2, 1, 3, N, N, N, 4]
Explanation: After inserting the node 4, the new tree will be [2, 1, 3, N, N, N, 4].

Example 2:
Input: root = [2, 1, 3, N, N, N, 6], key = 4
Output: [2, 1, 3, N, N, N, 4, N, 6]
Explanation: After inserting the node 4, the new tree will be [2, 1, 3, N, N, N, 4, N, 6].

Core Idea:
In a Binary Search Tree (BST), the left subtree of a node contains only nodes with values less than the node's value, and the right subtree contains only nodes with values greater than the node's value. 
To insert a new key, we traverse the tree from the root. If the key is less than the current node's data, we go left; if it's greater, we go right. We continue this until we reach a null pointer, at which point we insert the new node.

Approach:
1. If the root is null, create a new node with the given key and return it.
2. Maintain a `curr` pointer initialized to `root`.
3. Loop until `curr` is not null:
   - If the key is less than `curr->data`:
     - If `curr->left` is null, create the new node here, attach it to `curr->left`, and break.
     - Else, move `curr` to `curr->left`.
   - If the key is greater than `curr->data`:
     - If `curr->right` is null, create the new node here, attach it to `curr->right`, and break.
     - Else, move `curr` to `curr->right`.
   - If the key is equal to `curr->data`, the key is already in the BST. Since the problem guarantees distinct values, we can just break.
4. Return the original `root`.

Time Complexity: O(H), where H is the height of the BST. In the worst case (skewed tree), it's O(N). For a balanced BST, it's O(log N).
Space Complexity: O(1) auxiliary space (iterative approach).

GFG Link: https://www.geeksforgeeks.org/problems/insert-a-node-in-a-bst/1
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
    // Function to insert a node in a BST.
    Node* insert(Node* root, int key) {
        // If the tree is empty, return a new node
        if (root == nullptr) {
            return new Node(key);
        }
        
        Node* curr = root;
        while (true) {
            if (key < curr->data) {
                // If key is smaller, go to the left subtree
                if (curr->left != nullptr) {
                    curr = curr->left;
                } else {
                    // Found the correct spot, insert the node
                    curr->left = new Node(key);
                    break;
                }
            } else if (key > curr->data) {
                // If key is larger, go to the right subtree
                if (curr->right != nullptr) {
                    curr = curr->right;
                } else {
                    // Found the correct spot, insert the node
                    curr->right = new Node(key);
                    break;
                }
            } else {
                // Key is already present, no duplicates allowed in standard BST
                break;
            }
        }
        
        return root;
    }
};

/*
Dry Run — Example 1:
Input: root = [2, 1, 3], key = 4

Initial state:
      2
    /   \
   1     3

Call: insert(root, 4)

1. root is not null. curr = root (Node 2).
2. Loop iteration 1:
   - key (4) > curr->data (2)
   - curr->right is Node 3 (not null).
   - curr = curr->right (Node 3).
3. Loop iteration 2:
   - key (4) > curr->data (3)
   - curr->right is null.
   - We attach new Node(4) to curr->right.
   - Break loop.

Final state:
      2
    /   \
   1     3
          \
           4

Returns root (Node 2).
*/
