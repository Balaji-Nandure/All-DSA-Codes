/*
 * Problem: Check for Balanced Binary Tree
 *
 * A binary tree is height-balanced if for every node,
 * |height(left) - height(right)| <= 1.
 *
 * Optimized DFS:
 * - Returns height if subtree is balanced
 * - Returns -1 if subtree is NOT balanced
 *
 * Time: O(n)
 * Space: O(h) recursion stack
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

int heightOrUnbalanced(Node* root) {
    if (!root) return 0;

    int lh = heightOrUnbalanced(root->left);
    if (lh == -1) return -1; // new line

    int rh = heightOrUnbalanced(root->right);
    if (rh == -1) return -1; // new line

    if (abs(lh - rh) > 1) return -1; // new line
    return 1 + max(lh, rh); 
}

bool isBalanced(Node* root) {
    return heightOrUnbalanced(root) != -1;
}

int main() {
    // Balanced example:
    //        1
    //      /   \
    //     2     3
    //      \
    //       5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(5);

    cout << "Balanced? " << (isBalanced(root) ? "Yes" : "No") << "\n";

    // Make it unbalanced by adding a deeper chain on one side:
    // 2 -> right -> 5 -> right -> 6 -> right -> 7
    root->left->right->right = new Node(6);
    root->left->right->right->right = new Node(7);

    cout << "Balanced after adding nodes? " << (isBalanced(root) ? "Yes" : "No") << "\n";

    return 0;
}
