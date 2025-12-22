/*
 * Problem: Boundary Traversal in Binary Tree
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/boundary-traversal-of-binary-tree/1
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

/*
 * Problem: Boundary Traversal of Binary Tree
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/boundary-traversal-of-binary-tree/1
 *
 * Print boundary nodes in anti-clockwise: left boundary -> leaves -> right boundary (reverse).
 *
 * Time: O(n) - visit each node once
 * Space: O(h) - recursion stack
 */

// Traverse left boundary (top to bottom, excluding leaf)
void leftBoundary(Node* root, vector<int>& result) {
    // Base case: null or leaf node (skip)
    if (!root || (!root->left && !root->right)) return;
    // Add current node
    result.push_back(root->data);
    // Prefer left child, else right child
    if (root->left) leftBoundary(root->left, result);
    else leftBoundary(root->right, result);
}

// Traverse all leaf nodes (left to right)
void leafNodes(Node* root, vector<int>& result) {
    if (!root) return;
    // Leaf node: add to result
    if (!root->left && !root->right) {
        result.push_back(root->data);
        return;
    }
    // Recurse left then right (inorder for leaves)
    leafNodes(root->left, result);
    leafNodes(root->right, result);
}

// Traverse right boundary (bottom to top, excluding leaf)
void rightBoundary(Node* root, vector<int>& result) {
    // Base case: null or leaf node (skip)
    if (!root || (!root->left && !root->right)) return;
    // Recurse first (prefer right, else left)
    if (root->right) rightBoundary(root->right, result);
    else rightBoundary(root->left, result);
    // Add after recursion for reverse order (bottom to top)
    result.push_back(root->data);
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

