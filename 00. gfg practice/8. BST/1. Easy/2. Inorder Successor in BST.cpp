/*
GeeksforGeeks: Inorder Successor in BST
Difficulty: Easy

Problem:
Given a BST, and a reference to a Node k in the BST. Find the Inorder Successor of the given node in the BST. If there is no successor, return -1. 

Examples :
Input: root = [2, 1, 3], k = 2
Output: 3 
Explanation: Inorder traversal : 1 2 3 Hence, inorder successor of 2 is 3.

Input: root = [20, 8, 22, 4, 12, N, N, N, N, 10, 14], k = 8     
Output: 10
Explanation: Inorder traversal: 4 8 10 12 14 20 22. Hence, successor of 8 is 10.

Core Idea:
The inorder successor of a node `k` is the node that comes immediately after `k` in the inorder traversal (Left-Root-Right). 
In a BST, if a node has a right subtree, its inorder successor is the minimum value in its right subtree. 
If the node does not have a right subtree, its successor is one of its ancestors. Specifically, it's the closest ancestor for which the node is in its left subtree.
Instead of keeping track of parent pointers, we can do a standard BST search from the root for the node `k`. While searching, whenever we branch left, the current node is a potential successor (because all nodes in its left subtree are smaller than it, meaning it comes after them in inorder). We keep updating the potential successor. If we branch right, the current node cannot be the successor.

Approach:
1. Initialize a `successor` pointer to `nullptr`.
2. Start traversing from `curr = root`.
3. Loop while `curr != nullptr`:
   - If `x->data < curr->data`: The successor must be `curr` or in its left subtree. Update `successor = curr` and go left (`curr = curr->left`).
   - If `x->data >= curr->data`: The successor must be in the right subtree. We don't update `successor` (since `curr` comes before `x`), just go right (`curr = curr->right`). 
     (Note: Even if `x->data == curr->data`, its successor would be in its right subtree. The logic correctly searches the right subtree.)
4. Return `successor`.

Time Complexity: O(H) where H is the height of the BST. In the worst case (skewed tree), it's O(N). For a balanced BST, it's O(log N).
Space Complexity: O(1) auxiliary space as we are using an iterative approach.

GFG Link: https://www.geeksforgeeks.org/problems/inorder-successor-in-bst/1
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
    // returns the inorder successor of the Node x in BST (rooted at 'root')
    Node* inOrderSuccessor(Node* root, Node* x) {
        Node* successor = nullptr;
        Node* curr = root;
        
        while (curr != nullptr) {
            if (x->data < curr->data) {
                // If x is smaller, curr is a potential successor. 
                // Go to left subtree to find a closer (smaller) potential successor.
                successor = curr;
                curr = curr->left;
            } else {
                // If x is greater than or equal to curr, 
                // the successor must be in the right subtree.
                curr = curr->right;
            }
        }
        
        return successor;
    }
};

/*
Dry Run — Example 2:
Input: root = [20, 8, 22, 4, 12, N, N, N, N, 10, 14], k = 8
Tree Structure:
         20
       /    \
      8     22
     / \
    4  12
       / \
      10 14

Call: inOrderSuccessor(root, Node(8))

1. root is Node(20). x->data is 8.
   successor = NULL, curr = Node(20)

2. Loop iteration 1:
   - x->data (8) < curr->data (20).
   - successor = Node(20).
   - curr = curr->left (Node 8).

3. Loop iteration 2:
   - x->data (8) >= curr->data (8). (Actually they are equal)
   - curr = curr->right (Node 12).

4. Loop iteration 3:
   - x->data (8) < curr->data (12).
   - successor = Node(12).
   - curr = curr->left (Node 10).

5. Loop iteration 4:
   - x->data (8) < curr->data (10).
   - successor = Node(10).
   - curr = curr->left (NULL).

6. Loop terminates since curr is NULL.
7. Return successor (Node 10).

Output: 10
*/
