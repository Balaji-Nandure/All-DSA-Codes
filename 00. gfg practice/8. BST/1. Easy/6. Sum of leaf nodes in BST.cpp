/*
GeeksforGeeks: Sum of leaf nodes in BST
Difficulty: Easy

Problem:
Given a Binary Search Tree with n nodes, find the sum of all leaf nodes. BST has the following property (duplicate nodes are possible):
The left subtree of a node contains only nodes with keys less than the node’s key.
The right subtree of a node contains only nodes with keys greater than or equal to the node’s key.
Your task is to determine the total sum of the values of the leaf nodes.

Note: Input array arr doesn't represent the actual BST, it represents the order in which the elements will be added into the BST.

Example 1:
Input:
n = 6
arr = {67, 34, 82, 12, 45, 78}
Output: 135
Explanation:
In first test case, the BST for the given input will be-
                67
             /     \
           34       82
          /   \    /
         12   45  78
Hence, the required sum= 12 + 45 + 78 = 135

Example 2:
Input:
n = 1
arr = {45}
Output: 45
Explanation:
As the root node is a leaf node itself, the required sum will be 45

Core Idea:
A leaf node is a node that has no left child and no right child (`left == nullptr` and `right == nullptr`).
We can simply traverse the tree using a simple recursive Depth First Search (DFS). 
When we encounter a leaf node, we return its value so it gets added to our total sum.
If the current node is null, we return 0.
Otherwise, we recursively calculate the sum of leaf nodes in the left subtree and the sum of leaf nodes in the right subtree, and return their sum.

Approach (Simple Recursion):
1. Base Case 1: If `root` is `nullptr`, return 0.
2. Base Case 2: If both `root->left` and `root->right` are `nullptr`, it's a leaf node. Return `root->data`.
3. Recursive Step: Return `sumOfLeafNodes(root->left) + sumOfLeafNodes(root->right)`.

Time Complexity: O(N), where N is the number of nodes in the BST. We visit each node exactly once.
Space Complexity: O(H) for the recursion stack, where H is the height of the tree. In the worst case (skewed tree), this is O(N). For a balanced tree, it's O(log N).

GFG Link: https://www.geeksforgeeks.org/problems/sum-of-leaf-nodes-in-bst/1
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
    /*You are required to complete below method */
    int sumOfLeafNodes(Node *root) {
        // Base case: if tree is empty
        if (root == nullptr) {
            return 0;
        }
        
        // If the current node is a leaf node, return its data
        if (root->left == nullptr && root->right == nullptr) {
            return root->data;
        }
        
        // Recursively find the sum of leaf nodes in left and right subtrees
        return sumOfLeafNodes(root->left) + sumOfLeafNodes(root->right);
    }
};

/*
Dry Run — Example 1:
Input: arr = {67, 34, 82, 12, 45, 78}
BST:
                67
             /     \
           34       82
          /   \    /
         12   45  78

Call: sumOfLeafNodes(67)
-> not a leaf. Returns sum(34) + sum(82).

Call: sumOfLeafNodes(34)
-> not a leaf. Returns sum(12) + sum(45).

Call: sumOfLeafNodes(12)
-> is a leaf! Returns 12.

Call: sumOfLeafNodes(45)
-> is a leaf! Returns 45.

=> sumOfLeafNodes(34) returns 12 + 45 = 57.

Call: sumOfLeafNodes(82)
-> not a leaf. Returns sum(78) + sum(null).

Call: sumOfLeafNodes(78)
-> is a leaf! Returns 78.

Call: sumOfLeafNodes(null)
-> is null. Returns 0.

=> sumOfLeafNodes(82) returns 78 + 0 = 78.

=> sumOfLeafNodes(67) returns 57 + 78 = 135.

Output: 135
*/
