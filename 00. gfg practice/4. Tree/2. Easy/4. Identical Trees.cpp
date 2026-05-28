/*
Problem: Identical Trees

Given two binary trees with their root nodes r1 and r2, return true if both of them are identical, otherwise return false.
Note: Two trees are identical when they have the same data and the arrangement of the data is also same.

Constraints:
1 <= number of nodes <= 10^5
1 <= node->data <= 10^9

--------------------------------------------------

Pattern:
Tree Traversal (DFS)

--------------------------------------------------

Key Observation:
- For two trees to be structurally and functionally identical, both the structure (arrangement of nodes) and the corresponding data values must match perfectly.
- We can simply perform a simultaneous Depth-First Search on both trees side-by-side.
- At any given position, the nodes must either both be NULL, or both be non-NULL and contain identical data.
- If they pass this check, we recursively verify their left subtrees and right subtrees.

--------------------------------------------------

Approach:
1. Base Case 1: If both `r1` and `r2` are `nullptr`, they are identical at this position (both reached the end perfectly). Return `true`.
2. Base Case 2: If one is `nullptr` and the other is not, the structure inherently differs. Return `false`.
3. Value Check: If the `data` of `r1` does not match the `data` of `r2`, they are not identical. Return `false`.
4. Recursively call `isIdentical` for their respective left children AND right children.
5. Return the logical AND (`&&`) of both recursive checks so that the entire tree must match.

--------------------------------------------------

Time Complexity: O(min(N, M)) where N and M are the number of nodes in the two trees. The traversal optimally stops as soon as a mismatch is found.
Space Complexity: O(min(H1, H2)) where H1 and H2 are the heights of the trees, corresponding to the maximum recursion stack depth.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/determine-if-two-trees-are-identical/1
*/

#include <iostream>

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
    // Function to check if two trees are identical.
    bool isIdentical(Node *r1, Node *r2) {
        // If both nodes are NULL, they are perfectly identical
        if (r1 == nullptr && r2 == nullptr) {
            return true;
        }
        
        // If one is NULL and the other is not, they differ structurally
        if (r1 == nullptr || r2 == nullptr) {
            return false;
        }
        
        // If the data differs, the trees are not identical
        if (r1->data != r2->data) {
            return false;
        }
        
        // Recursively check if both the left subtrees and right subtrees match
        return isIdentical(r1->left, r2->left) && isIdentical(r1->right, r2->right);
    }
};
