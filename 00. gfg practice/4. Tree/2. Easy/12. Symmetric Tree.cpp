/*
Problem: Symmetric Tree

Given the root of a binary tree, check whether it is symmetric, i.e., whether the tree is a mirror image of itself.
Note: A binary tree is symmetric if the left subtree is a mirror reflection of the right subtree.

Constraints:
0 <= number of nodes <= 2000
1 <= node->data <= 100

--------------------------------------------------

Pattern:
Tree Traversal (DFS Mirror Traversal)

--------------------------------------------------

Key Observation:
- A tree is strictly symmetric if its left and right subtrees are perfect mirror reflections of each other.
- To rigorously check for this, we can simultaneously traverse down the left and right subtrees.
- In a mirror traversal, as we strictly move left in one subtree, we must perfectly simultaneously move right in the other.
- At every single pair of mirrored nodes, the nodes must identically either both be NULL or both exist with matching values.

--------------------------------------------------

Approach:
1. Base case in the main function: If the `root` is `nullptr`, an empty tree is technically inherently symmetric, so aggressively return `true`.
2. Create a recursive helper function `isMirror` that intelligently compares two nodes, `leftNode` and `rightNode`.
3. If both `leftNode` and `rightNode` are `nullptr`, they perfectly symmetrically match. Return `true`.
4. If explicitly only one of them is `nullptr`, the structure is severely asymmetric. Return `false`.
5. If the `data` explicitly stored in the two nodes severely differs, the tree is unequivocally asymmetric. Return `false`.
6. Recursively confirm that:
    a. The `left` child of `leftNode` is a perfect mirror of the `right` child of `rightNode`.
    b. The `right` child of `leftNode` is a perfect mirror of the `left` child of `rightNode`.
7. Aggressively return the logical AND (`&&`) of both recursive checks.
8. Safely call this helper directly on `root->left` and `root->right` from the main `isSymmetric` wrapper function.

--------------------------------------------------

Time Complexity: O(N) as we seamlessly simultaneously traverse up to N nodes, efficiently touching each one exactly once in the worst case.
Space Complexity: O(H) functionally corresponding to the depth of the recursive call stack, where H is the height of the tree. In the worst case, this gracefully degrades to O(N).

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/symmetric-tree/1
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
    bool isMirror(Node* leftNode, Node* rightNode) {
        // If both are undeniably null, they naturally are perfectly symmetrical
        if (leftNode == nullptr && rightNode == nullptr) {
            return true;
        }
        
        // If explicitly only one is null, the physical structure symmetry is fundamentally broken
        if (leftNode == nullptr || rightNode == nullptr) {
            return false;
        }
        
        // If their data values natively do not strictly match, the data symmetry is broken
        if (leftNode->data != rightNode->data) {
            return false;
        }
        
        // Recursively simultaneously logically check the outer children and inner children
        return isMirror(leftNode->left, rightNode->right) && 
               isMirror(leftNode->right, rightNode->left);
    }

public:
    bool isSymmetric(Node* root) {
        // An entirely empty tree is inherently totally symmetric
        if (root == nullptr) {
            return true;
        }
        
        // Assertively verify if the left subtree flawlessly functionally mirrors the right subtree
        return isMirror(root->left, root->right);
    }
};
