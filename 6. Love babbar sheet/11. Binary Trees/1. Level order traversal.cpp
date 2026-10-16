/**
 * Problem: Level Order Traversal of Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Linear data structures (arrays, linked lists) have a single unambiguous forward traversal.
 * - Trees are hierarchical non-linear structures branching out at each level.
 * - Here, we perform Breadth-First Search (BFS) on a tree using a FIFO queue to visit nodes
 *   strictly level by level, left to right.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Queue-Based Breadth-First Traversal:
 *   - Enqueue the root node.
 *   - While queue is not empty:
 *     - Dequeue front node `curr`.
 *     - Record `curr->data`.
 *     - If `curr->left` exists, enqueue it.
 *     - If `curr->right` exists, enqueue it.
 *   - FIFO queue order naturally guarantees that all nodes at horizontal depth `d` are processed
 *     before any node at depth `d + 1`.
 * 
 * TIME COMPLEXITY:
 * - O(N): Every node is enqueued and dequeued exactly once.
 * 
 * SPACE COMPLEXITY:
 * - O(W): Where W is maximum width (at most ceil(N/2) nodes in a complete binary tree).
 */

#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

std::vector<int> levelOrder(Node* root) {
    std::vector<int> result;
    if (!root) return result;

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        result.push_back(curr->data);

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Push children in left-to-right order so FIFO processing preserves horizontal layout.
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }

    return result;
}

int main() {
    //      1
    //    /   \
    //   2     3
    //  / \
    // 4   5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    std::vector<int> res = levelOrder(root);
    std::cout << "Level order traversal: ";
    for (int x : res) std::cout << x << " ";
    std::cout << "\n"; // 1 2 3 4 5

    return 0;
}
