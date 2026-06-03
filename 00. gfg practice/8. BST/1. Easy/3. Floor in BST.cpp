/*
GeeksforGeeks: Floor in BST
Difficulty: Easy

Problem:
Given the root of a binary search tree and a number k, find the greatest number in the binary search tree that is less than or equal to k.
Note: If no such node value exists that is smaller than k, then return -1.

Examples:
Input: root = [10, 7, 15, 2, 8, 11, 16],  k  =  14
Output: 11
Explanation: The greatest element in the tree which is less than or equal to 14, is 11.

Input: root = [5, 2, 12, 1, 3, 9, 21, N, N, N, N, N, N, 19, 25],  k  = 24
Output: 21
Explanation: The greatest element in the tree which is less than or equal to 24, is 21. 

Input: root = [5, 2, 12, 1, 3, 9, 21, N, N, N, N, N, N, 19, 25], k = 4
Output: 3
Explanation: The greatest element in the tree which is less than or equal to 4, is 3.

Core Idea:
The floor of `k` is the largest node value in the BST that is `<= k`.
To find the floor, we can traverse the BST starting from the root:
- If we find a node with value exactly equal to `k`, it is the floor, and we can return it immediately.
- If the current node's value is greater than `k`, the floor must lie in the left subtree, because all nodes in the right subtree and the current node itself are greater than `k`. We move to the left child.
- If the current node's value is less than `k`, it is a potential candidate for the floor. We record its value and search the right subtree to see if we can find a larger value that is still `<= k`. We move to the right child.

Approach:
1. Initialize `floorVal = -1`.
2. Start with `curr = root`.
3. Loop while `curr != nullptr`:
   - If `curr->data == k`: We found the exact match, so `floorVal = curr->data`. Break or return immediately.
   - If `curr->data > k`: The floor cannot be `curr` or any node in its right subtree. We go left (`curr = curr->left`).
   - If `curr->data < k`: The current node is a potential floor. We update `floorVal = curr->data` and look for a closer (larger) value in the right subtree by going right (`curr = curr->right`).
4. Return `floorVal`.

Time Complexity: O(H) where H is the height of the BST. In the worst case (skewed tree), it's O(N). For a balanced BST, it's O(log N).
Space Complexity: O(1) auxiliary space.

GFG Link: https://www.geeksforgeeks.org/problems/floor-in-bst/1
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
    int floor(Node* root, int k) {
        int floorVal = -1;
        Node* curr = root;
        
        while (curr != nullptr) {
            if (curr->data == k) {
                // Exact match found, it's the floor.
                floorVal = curr->data;
                break;
            } else if (curr->data > k) {
                // Current value is greater than k, so floor must be in left subtree.
                curr = curr->left;
            } else {
                // Current value is less than k. It's a potential floor.
                // Update floorVal and check right subtree for a closer value.
                floorVal = curr->data;
                curr = curr->right;
            }
        }
        
        return floorVal;
    }
};

/*
Dry Run — Example 1:
Input: root = [10, 7, 15, 2, 8, 11, 16], k = 14
Tree Structure:
         10
       /    \
      7     15
     / \   /  \
    2   8 11  16

Call: floor(root, 14)

1. Initialize floorVal = -1. curr = Node(10).

2. Loop iteration 1:
   - curr->data (10) < k (14).
   - floorVal = 10.
   - curr = curr->right (Node 15).

3. Loop iteration 2:
   - curr->data (15) > k (14).
   - curr = curr->left (Node 11).

4. Loop iteration 3:
   - curr->data (11) < k (14).
   - floorVal = 11.
   - curr = curr->right (NULL).

5. Loop terminates since curr is NULL.

6. Return floorVal = 11.

Output: 11
*/
