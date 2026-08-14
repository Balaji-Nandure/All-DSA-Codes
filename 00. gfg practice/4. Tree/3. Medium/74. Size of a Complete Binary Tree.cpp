/*
    Problem Name: Size of a Complete Binary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a Complete Binary Tree, return the total count of nodes.
    - A Complete Binary Tree is a binary tree where all levels except possibly the last are
      completely filled, and all nodes in the last level are as far left as possible.

    Note: Design an algorithm that runs better than O(N) (specifically, in O(log^2 N) time).

    Examples:
    Input:
               1
             /   \
            2     3
           / \   / \
          4   5 6   7
    Output: 7

    Input:
               1
             /   \
            2     3
           / \
          4   5
    Output: 5

    Constraints:
    0 <= N <= 5 * 10^4
    0 <= node->data <= 5 * 10^4

    Expected Complexities:
    Time Complexity: O(log^2 N), using height comparison of left & right boundaries.
    Space Complexity: O(log N), for recursion stack.

    Love Babbar Style Approach:
    Height Comparison & Perfect Subtree Formula (O(log^2 N)):

    1. INTUITION:
       - In a Complete Binary Tree:
         * If the height along the extreme left path (`lh`) equals the height along the extreme right path (`rh`),
           the tree is a PERFECT BINARY TREE!
         * Total nodes in a Perfect Binary Tree of height `lh` is given by formula:
           `Total Nodes = (2^lh) - 1`  (or `(1 << lh) - 1`).
         * We can calculate this in O(1) time without traversing individual nodes!
       - If `lh != rh`:
         * The tree is not perfect.
         * Recursively compute: `1 + countNodes(root->left) + countNodes(root->right)`.
       - Since at every step at least one of the subtrees is guaranteed to be a Perfect Binary Tree,
         the recursion only goes down ONE non-perfect path!
       - Thus, total operations = O(height * height) = O(log^2 N), which is far faster than O(N).

    2. ALGORITHM:
       - `findLeftHeight(root)`: move `root = root->left` and count height.
       - `findRightHeight(root)`: move `root = root->right` and count height.
       - `countNodes(root)`:
         * `if (!root) return 0;`
         * `int lh = findLeftHeight(root);`
         * `int rh = findRightHeight(root);`
         * `if (lh == rh) return (1 << lh) - 1;`
         * Return `1 + countNodes(root->left) + countNodes(root->right);`

    Dry Run:
               1
             /   \
            2     3
           / \
          4   5

    - countNodes(1): lh(1)=3, rh(1)=2 -> lh != rh. Return 1 + countNodes(2) + countNodes(3).
      * countNodes(2): lh(2)=2, rh(2)=2 -> lh == rh. Return (1<<2) - 1 = 3.
      * countNodes(3): lh(3)=1, rh(3)=1 -> lh == rh. Return (1<<1) - 1 = 1.
    Total = 1 + 3 + 1 = 5 ✓
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
private:
    // Helper function to find extreme left height
    int findLeftHeight(Node* root) {
        int h = 0;
        while (root) {
            h++;
            root = root->left;
        }
        return h;
    }

    // Helper function to find extreme right height
    int findRightHeight(Node* root) {
        int h = 0;
        while (root) {
            h++;
            root = root->right;
        }
        return h;
    }

public:
    // GFG Signature - O(log^2 N) Node Counting
    int countNodes(Node* root) {
        if (!root) return 0;

        int lh = findLeftHeight(root);
        int rh = findRightHeight(root);

        // If extreme left and right heights match, tree is a Perfect Binary Tree
        if (lh == rh) {
            return (1 << lh) - 1; // Formula: 2^lh - 1
        }

        // Otherwise, count root + left subtree + right subtree
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};

int main() {
    Solution ob;

    // Example 1: Perfect tree of 7 nodes
    //            1
    //          /   \
    //         2     3
    //        / \   / \
    //       4   5 6   7
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);
    root1->right->left = new Node(6);
    root1->right->right = new Node(7);

    cout << "Example 1 Complete Tree Node Count: " << ob.countNodes(root1) << "\n";

    // Example 2: Complete tree of 5 nodes
    //            1
    //          /   \
    //         2     3
    //        / \
    //       4   5
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);
    root2->left->left = new Node(4);
    root2->left->right = new Node(5);

    cout << "Example 2 Complete Tree Node Count: " << ob.countNodes(root2) << "\n";

    return 0;
}
