/*
 * Problem: Boundary Traversal in Binary Tree
 *
 * Print the boundary nodes of a binary tree in anti-clockwise direction.
 * Boundary includes:
 * 1. Left boundary (top to bottom, excluding leaf)
 * 2. Leaf nodes (left to right)
 * 3. Right boundary (bottom to top, excluding leaf)
 *
 * Approach:
 * - Traverse left boundary (excluding leaf)
 * - Traverse all leaf nodes
 * - Traverse right boundary (excluding leaf, in reverse)
 * - Handle edge cases (single node, etc.)
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

// Traverse left boundary (excluding leaf)
void leftBoundary(Node* root, vector<int>& result) {
    if (!root || (!root->left && !root->right)) return;
    result.push_back(root->data);
    if (root->left) leftBoundary(root->left, result);
    else leftBoundary(root->right, result);
}

// Traverse all leaf nodes
void leafNodes(Node* root, vector<int>& result) {
    if (!root) return;
    if (!root->left && !root->right) {
        result.push_back(root->data);
        return;
    }
    leafNodes(root->left, result);
    leafNodes(root->right, result);
}

// Traverse right boundary (excluding leaf, in reverse)
void rightBoundary(Node* root, vector<int>& result) {
    if (!root || (!root->left && !root->right)) return;
    if (root->right) rightBoundary(root->right, result);
    else rightBoundary(root->left, result);
    result.push_back(root->data); // Add after recursion for reverse order
}

vector<int> boundaryTraversal(Node* root) {
    vector<int> result;
    if (!root) return result;
    
    result.push_back(root->data); // Add root
    
    // Left boundary (excluding root and leaf)
    leftBoundary(root->left, result);
    
    // Leaf nodes
    leafNodes(root->left, result);
    leafNodes(root->right, result);
    
    // Right boundary (excluding root and leaf, in reverse)
    rightBoundary(root->right, result);
    
    return result;
}

int main() {
    // Example 1:
    //        1
    //      /   \
    //     2     3
    //    / \   / \
    //   4   5 6   7
    // Boundary: 1 2 4 5 6 7 3
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);
    root1->right->left = new Node(6);
    root1->right->right = new Node(7);

    vector<int> boundary1 = boundaryTraversal(root1);
    cout << "Example 1 - Boundary: ";
    for (int val : boundary1) cout << val << " ";
    cout << "\n";

    // Example 2:
    //        1
    //      /   \
    //     2     3
    //      \
    //       5
    // Boundary: 1 2 5 3
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);
    root2->left->right = new Node(5);

    vector<int> boundary2 = boundaryTraversal(root2);
    cout << "Example 2 - Boundary: ";
    for (int val : boundary2) cout << val << " ";
    cout << "\n";

    // Example 3: Single node
    Node* root3 = new Node(1);
    vector<int> boundary3 = boundaryTraversal(root3);
    cout << "Example 3 (single node) - Boundary: ";
    for (int val : boundary3) cout << val << " ";
    cout << "\n";

    return 0;
}

