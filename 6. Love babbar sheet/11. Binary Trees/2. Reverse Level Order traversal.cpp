/**
 * Problem: Reverse Level Order Traversal of Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Standard level order outputs root first down to leaves (top to bottom).
 * - Here, we must output nodes starting from the deepest level upwards to the root,
 *   while maintaining the left-to-right horizontal order of nodes within each individual level.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Queue + Stack Synergy:
 *   - Why right child first in queue?
 *     - If we enqueue the right child BEFORE the left child, the right child will be dequeued and
 *       pushed onto the stack first.
 *     - Since a stack is LIFO, when we subsequently pop from the stack to produce the final output,
 *       the left child pops before the right child!
 *     - Simultaneously, the bottom-most leaves (pushed last to the stack) pop out first, producing
 *       the exact reverse level-order sequence with zero post-processing overhead!
 * 
 * TIME COMPLEXITY:
 * - O(N): Every node is pushed and popped from queue and stack once.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for queue and stack.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

std::vector<int> reverseLevelOrder(Node* root) {
    std::vector<int> result;
    if (!root) return result;

    std::queue<Node*> q;
    std::stack<Node*> st;

    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        st.push(curr);

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Enqueue RIGHT child first, then LEFT child so that LIFO stack popping outputs left before right!
        if (curr->right) q.push(curr->right);
        if (curr->left) q.push(curr->left);
    }

    // Unload stack to obtain bottom-up order
    while (!st.empty()) {
        result.push_back(st.top()->data);
        st.pop();
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

    std::vector<int> res = reverseLevelOrder(root);
    std::cout << "Reverse level order traversal: ";
    for (int x : res) std::cout << x << " ";
    std::cout << "\n"; // 4 5 2 3 1

    return 0;
}
