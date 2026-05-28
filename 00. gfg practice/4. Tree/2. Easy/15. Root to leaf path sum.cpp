/*
Problem: Root to leaf path sum

Given a binary tree and an integer target, check whether there is a root-to-leaf path with its sum as target.

Constraints:
1 <= number of nodes <= 10^4
1 <= target <= 10^6

--------------------------------------------------

Pattern:
Tree Traversal (DFS with Subtraction/Running Target)

--------------------------------------------------

Key Observation:
- We need to find a contiguous path that strictly starts at the `root` and strictly ends at a `leaf`.
- As we thoughtfully traverse downwards from the root, we can functionally "consume" the current node's value from our overarching target sum.
- When we eventually arrive at a leaf node (a node with no children), the *remaining* `target` must perfectly mathematically equal the leaf node's `data` for the path to be considered valid!
- If the current path fails, the standard DFS recursive calls naturally backtrack upwards and try alternative branches.

--------------------------------------------------

Approach:
1. Base case: If `root` is `nullptr`, there's obviously no valid path, so assertively return `false`.
2. Check if the current node is a true leaf node (`root->left == nullptr && root->right == nullptr`).
    a. If it is a leaf, strictly check if the *current remaining* `target` is exactly equal to the leaf's `data`. If it matches, return `true`. Otherwise, return `false`.
3. If it's explicitly not a leaf, we must forcefully continue extending our path downwards. We intuitively subtract the current node's `data` from our `target` to compute the newly required sum for the rest of the deeper subtrees.
4. Recursively heavily aggressively check the left child: `hasPathSum(root->left, target - root->data)`.
5. Recursively heavily aggressively check the right child: `hasPathSum(root->right, target - root->data)`.
6. Return the logical OR (`||`) of both recursive calls. If *any* individual branch manages to find a valid path, the overall answer correctly cascades up as `true`.

--------------------------------------------------

Time Complexity: O(N) as we naturally might have to traverse every single node in the absolute worst case (if the valid path is completely at the very end or simply doesn't exist).
Space Complexity: O(H) representing the maximum physical recursion stack depth, where H is the maximum height of the binary tree. In the worst case (a completely skewed tree), this degrades linearly to O(N).

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/root-to-leaf-path-sum/1
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
public:
    bool hasPathSum(Node *root, int target) {
        // Base case: if we hit a null node, no valid path structurally exists here
        if (root == nullptr) {
            return false;
        }
        
        // If we reach a physical leaf node, assertively verify if its value identically matches the remaining target
        if (root->left == nullptr && root->right == nullptr) {
            return target == root->data;
        }
        
        // Subtract the current node's data mathematically from the remaining target
        int remainingTarget = target - root->data;
        
        // Recursively aggressively check if ANY of the subtrees possess a valid remaining path sum
        return hasPathSum(root->left, remainingTarget) || 
               hasPathSum(root->right, remainingTarget);
    }
};
