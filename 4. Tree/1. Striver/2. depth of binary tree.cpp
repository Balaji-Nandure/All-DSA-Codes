/*
 * Problem: Maximum Depth / Height of a Binary Tree
 *
 * Depth (or height) of a binary tree = number of nodes on the longest path
 * from the root down to a leaf node.
 *
 * Methods:
 * - Recursive DFS: O(n) time, O(h) recursion stack
 * - Iterative BFS (level order): O(n) time, O(w) queue
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

// Method 1: Recursive DFS
int maxDepth(Node* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// Method 2: Iterative BFS (Level order)
int maxDepthBFS(Node* root) {
    if (!root) return 0;
    queue<Node*> q;
    q.push(root);
    int depth = 0;
    while (!q.empty()) {
        int sz = (int)q.size();
        depth++;
        while (sz--) {
            Node* node = q.front();
            q.pop();
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return depth;
}

int main() {
    // Example tree (same as your intro file):
    //        1
    //      /   \
    //     2     3
    //      \
    //       5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(5);

    cout << "Depth (DFS): " << maxDepth(root) << "\n";
    cout << "Depth (BFS): " << maxDepthBFS(root) << "\n";

    return 0;
}
