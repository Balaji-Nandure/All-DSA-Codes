/*
Problem:
Remove all Leaf Nodes from a Binary Search Tree (BST)

Given a BST, remove all its leaf nodes.
Return the root of the modified BST.

Rules:
- Leaf node = node with no children.
- BST property must remain valid after deletion.
- Deletion is in-place.

Example:
Input BST:
        8
       / \
      3   10
     / \    \
    1   6    14

Output BST:
        8
       / \
      3   10
       \    \
        6    14

Approach (Optimal – Postorder Traversal):
- Use postorder traversal (Left → Right → Root).
- If a node is a leaf (both children NULL), delete it by returning NULL.
- Otherwise, recursively update left and right subtrees.
- Postorder is mandatory so children are processed before parent.

GeeksforGeeks:
https://www.geeksforgeeks.org/remove-leaf-nodes-from-binary-search-tree/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(H)
*/

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = NULL;
        right = NULL;
    }
};

class Solution {
public:
    // Function to remove all leaf nodes from a BST
    Node* removeLeafNodes(Node* root) {

        // Base case: if node is NULL, return NULL
        if (root == NULL) return NULL;

        // If current node is a leaf node, delete it by returning NULL
        if (root->left == NULL && root->right == NULL) {
            return NULL;
        }

        // Recursively process left and right subtrees (postorder)
        root->left = removeLeafNodes(root->left);
        root->right = removeLeafNodes(root->right);

        // Return processed subtree
        return root;
    }
};
