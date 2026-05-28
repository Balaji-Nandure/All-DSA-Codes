/*
Problem: Kth largest element in BST

Given a Binary Search Tree. Your task is to complete the function which will return the kth largest element without doing any modification in the Binary Search Tree.

Constraints:
1 <= number of nodes <= 10^5
1 <= node->data <= 10^5
1 <= k <= number of nodes

--------------------------------------------------

Pattern:
BST Traversal (Reverse Inorder)

--------------------------------------------------

Key Observation:
- A standard Inorder Traversal (Left -> Root -> Right) of a Binary Search Tree perfectly visits the nodes in strictly ascending (increasing) order.
- It logically follows that a Reverse Inorder Traversal (Right -> Root -> Left) will visit the nodes in strictly descending (decreasing) order.
- By simply performing a Reverse Inorder Traversal and maintaining a counter, the `k`th node we visit will exactly be the `k`th largest element in the BST!

--------------------------------------------------

Approach:
1. Initialize two member variables: `count = 0` to accurately track how many nodes we've visited, and `ans = -1` to safely store the answer once found.
2. Create a recursive `reverseInorder` helper function taking the `root` and `k`.
3. Base case: If `root` is `nullptr` or if `count >= k` (meaning we've already found the answer and can efficiently prune remaining recursive calls), safely return.
4. Recursively traverse the right subtree to evaluate the largest elements first: `reverseInorder(root->right, k)`.
5. Process the current node:
    a. Increment `count`.
    b. If `count == k`, we found our target! Save `ans = root->data` and deliberately return to halt further execution.
6. Recursively traverse the left subtree: `reverseInorder(root->left, k)`.
7. Return `ans` from the main wrapper `kthLargest` function.

--------------------------------------------------

Time Complexity: O(H + K) where H is the height of the tree. We first spend O(H) time rapidly diving down to the largest element, and then do K constant-time visits. In the worst case (skewed tree), this strictly degrades to O(N).
Space Complexity: O(H) corresponding to the recursion stack depth.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/kth-largest-element-in-bst/1
*/

#include <iostream>

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
    void reverseInorder(Node* root, int k, int& count, int& ans) {
        // Base case: null node or we undeniably already found the answer (pruning)
        if (root == nullptr || count >= k) {
            return;
        }
        
        // 1. Traverse the right subtree (strictly larger elements)
        reverseInorder(root->right, k, count, ans);
        
        // 2. Process the current node
        count++;
        if (count == k) {
            ans = root->data;
            return; // Exit early since we found the k-th largest
        }
        
        // 3. Traverse the left subtree (strictly smaller elements)
        reverseInorder(root->left, k, count, ans);
    }

public:
    int kthLargest(Node *root, int k) {
        int count = 0;
        int ans = -1;
        reverseInorder(root, k, count, ans);
        return ans;
    }
};
