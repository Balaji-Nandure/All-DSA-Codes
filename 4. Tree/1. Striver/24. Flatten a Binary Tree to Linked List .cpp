/*
 * Problem: Flatten Binary Tree to Linked List
 *
 * LeetCode 114: Flatten Binary Tree to Linked List
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/flatten-binary-tree-to-linked-list/1
 *
 * Given the root of a binary tree, flatten the tree into a "linked list":
 * - The "linked list" should use the same TreeNode class where the right child pointer
 *   points to the next node in the list and the left child pointer is always null.
 * - The "linked list" should be in the same order as a pre-order traversal of the binary tree.
 *
 * Example:
 * Input:
 *       1
 *      / \
 *     2   5
 *    / \   \
 *   3   4   6
 *
 * Output (flattened):
 * 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL
 
 * Time: O(n) - visit each node once
 * Space: O(h) for recursion/stack, O(1) for Morris approach
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#include <stack>
using namespace std;

// Solution 4: Morris-like Traversal (O(1) space)
// This approach uses O(1) space by re-wiring the tree "in-place" using rightmost nodes of left subtrees.
class MorrisLikeSolution {
public:
/*
 * Problem: Flatten Binary Tree to Linked List
 *
 * LeetCode 114: Flatten Binary Tree to Linked List
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/flatten-binary-tree-to-linked-list/1
 *
 * Flatten tree to linked list in preorder: use right pointer, left = NULL.
 * Example: [1,2,3,4,5,6] -> 1->2->3->4->5->6
 *
 * Time: O(n) - visit each node once
 * Space: O(1) for Morris-like, O(h) for recursive
 */

    // Morris-like approach: O(1) space
    void flatten(TreeNode* root) {
        TreeNode* current = root;

        while (current != NULL) {
            // If left child exists, need to rewire
            if (current->left != NULL) {
                // Find rightmost node in left subtree (predecessor)
                TreeNode* predecessor = current->left;
                while (predecessor->right != NULL) {
                    predecessor = predecessor->right;
                }

                // Attach right subtree to predecessor's right
                predecessor->right = current->right;

                // Move left subtree to right
                current->right = current->left;
                current->left = NULL; // Set left to NULL
            }

            // Move to next node (in preorder)
            current = current->right;
        }
    }
};

// Solution 5: Reverse Preorder (Right -> Left -> Root)
// This method recursively traverses the tree in reverse preorder and "connects" each node to the previously visited node.
class ReversePreorderSolution {
public:
    void flatten(TreeNode* root) {
        TreeNode* prev = NULL; // This will keep track of the previously visited node in reverse preorder
        reversePreorder(root, prev);
    }

private:
    // Helper function for reverse preorder traversal
    // prev tracks the next node in the flattened linked list
    void reversePreorder(TreeNode* root, TreeNode* &prev) {
        if (root == NULL) return;

        // Visit right subtree first (so that in the flattened list, left nodes come before right nodes)
        reversePreorder(root->right, prev);
        // Visit left subtree
        reversePreorder(root->left, prev);

        // Set the right pointer to previous node (creating the "linked list" rightward)
        root->right = prev;
        // Always set the left pointer to NULL in the flattened list
        root->left = NULL;
        // Move prev to current node before unwinding recursion
        prev = root;
    }
};
