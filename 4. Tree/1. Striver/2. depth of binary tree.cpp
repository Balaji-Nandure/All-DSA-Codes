/*
 * Problem: Maximum Depth / Height of a Binary Tree
 *
 * LeetCode 104: Maximum Depth of Binary Tree
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/height-of-binary-tree/1
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

/*
 * Problem: Maximum Depth of Binary Tree
 *
 * LeetCode 104: Maximum Depth of Binary Tree
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/height-of-binary-tree/1
 *
 * Find the maximum depth (height) of binary tree.
 * Depth = number of nodes on longest path from root to leaf.
 *
 * Time: O(n) - visit each node once
 * Space: O(h) for recursive, O(w) for iterative (where h=height, w=width)
 */

// Method 1: Recursive DFS
int maxDepth(Node* root) {
    // Base case: empty tree has depth 0
    if (!root) return 0;
    // Depth = 1 (current node) + max depth of left and right subtrees
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// Method 2: Iterative BFS (Level order)
int maxDepthBFS(Node* root) {
    if (!root) return 0;
    queue<Node*> q;
    q.push(root);
    int depth = 0;
    // Process level by level
    while (!q.empty()) {
        int sz = (int)q.size(); // Number of nodes in current level
        depth++; // Increment depth for each level
        // Process all nodes in current level
        while (sz--) {
            Node* node = q.front();
            q.pop();
            // Add children for next level
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
