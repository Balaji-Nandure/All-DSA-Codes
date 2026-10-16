/**
 * Problem: Diagonal Traversal of a Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Vertical / Top / Bottom views grouped nodes where Left = `x - 1` and Right = `x + 1`.
 * - Diagonal Traversal groups nodes along parallel downward-sloping diagonals from top-left to bottom-right:
 *   - Moving to the RIGHT child stays in the SAME diagonal (`d = d`).
 *   - Moving to the LEFT child moves down to the NEXT diagonal (`d = d + 1`).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Right-Spine Iterative Queue Traversal:
 *   - Push root into a queue.
 *   - While queue is not empty:
 *     - Pop `curr`.
 *     - While `curr != nullptr`:
 *       - Record `curr->data`.
 *       - If `curr->left` exists, enqueue `curr->left` (it starts the next diagonal).
 *       - Advance along the current diagonal by transitioning to the right child: `curr = curr->right`.
 *   - This processes entire diagonals continuously in O(N) time with minimal queue space.
 * 
 * TIME COMPLEXITY:
 * - O(N): Each node is pushed into queue and visited exactly once.
 * 
 * SPACE COMPLEXITY:
 * - O(N) for queue (stores left children of diagonals).
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

std::vector<int> diagonal(Node* root) {
    std::vector<int> result;
    if (!root) return result;

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Traverse entire right spine on current diagonal, enqueueing left children for the next diagonal.
        while (curr != nullptr) {
            result.push_back(curr->data);

            if (curr->left) {
                q.push(curr->left); // Belongs to next diagonal
            }

            curr = curr->right; // Stays on same diagonal
        }
    }

    return result;
}

int main() {
    //         8
    //       /   \
    //      3     10
    //     / \      \
    //    1   6      14
    //       / \     /
    //      4   7   13
    Node* root = new Node(8);
    root->left = new Node(3);
    root->right = new Node(10);
    root->left->left = new Node(1);
    root->left->right = new Node(6);
    root->right->right = new Node(14);
    root->left->right->left = new Node(4);
    root->left->right->right = new Node(7);
    root->right->right->left = new Node(13);

    std::vector<int> diag = diagonal(root);
    std::cout << "Diagonal traversal: ";
    for (int x : diag) std::cout << x << " ";
    std::cout << "\n"; // 8 10 14 3 6 7 13 1 4

    return 0;
}
