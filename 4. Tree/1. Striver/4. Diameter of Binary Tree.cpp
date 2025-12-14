/*
 * Problem: Diameter of Binary Tree (LeetCode 543)
 *
 * The diameter of a binary tree is the length of the longest path
 * between any two nodes in a tree. This path may or may not pass through the root.
 *
 * We only want the diameter, not the height.
 * For each node: diameter passing through it = leftDepth + rightDepth.
 * Time: O(n)
 * Space: O(h)
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Returns diameter only (does not expose height to caller)
// It is just a find height function with a maxDiameter variable(pass by reference)
// we are only modifying maxDiameter variable for each node.
int diameterUtil(Node* root, int& maxDiameter) {
    if (!root) return 0;
    int left = diameterUtil(root->left, maxDiameter);
    int right = diameterUtil(root->right, maxDiameter);
    maxDiameter = max(maxDiameter, left + right); // new line
    return 1 + max(left, right);
}

int diameterOfBinaryTree(Node* root) {
    int diameter = 0;
    diameterUtil(root, diameter);
    return diameter;
}

int main() {
    // Example 1:
    //        1
    //      /   \
    //     2     3
    //    / \
    //   4   5
    // Diameter: 3
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);

    cout << "Example 1 - Diameter: " << diameterOfBinaryTree(root1) << "\n";

    // Example 2:
    //        1
    //      /   \
    //     2     3
    //      \
    //       5
    // Diameter: 3
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);
    root2->left->right = new Node(5);

    cout << "Example 2 - Diameter: " << diameterOfBinaryTree(root2) << "\n";

    // Example 3: Single node
    Node* root3 = new Node(1);
    cout << "Example 3 (single node) - Diameter: " << diameterOfBinaryTree(root3) << "\n";

    return 0;
}
