/**
 * Problem: Zig-Zag (Spiral) Traversal of a Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Level order visited all levels in a monotonous left-to-right direction.
 * - Here, the traversal direction alternates across consecutive levels:
 *   Level 1: Left to Right
 *   Level 2: Right to Left
 *   Level 3: Left to Right, and so forth.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Level-by-Level Direct Array Placement:
 *   - Use standard BFS queue to traverse nodes level by level.
 *   - At each level with `sz` nodes:
 *     - Allocate a vector of exact size `sz`.
 *     - If `leftToRight` is true: fill vector from index `0` to `sz - 1`.
 *     - If `leftToRight` is false: fill vector in reverse from index `sz - 1` down to `0`.
 *     - Continue pushing children to queue in regular left-then-right order.
 *   - Toggle `leftToRight = !leftToRight` after each completed level.
 *   - This avoids slow vector reversals or two-stack gymnastics, achieving clean O(N) execution.
 * 
 * TIME COMPLEXITY:
 * - O(N): Every node is visited once and directly placed at its target index.
 * 
 * SPACE COMPLEXITY:
 * - O(W): Queue memory bounded by maximum tree width.
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

std::vector<int> zigZagTraversal(Node* root) {
    std::vector<int> result;
    if (!root) return result;

    std::queue<Node*> q;
    q.push(root);
    bool leftToRight = true;

    while (!q.empty()) {
        int sz = q.size();
        std::vector<int> level(sz);

        for (int i = 0; i < sz; i++) {
            Node* curr = q.front();
            q.pop();

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Alternate index placement between forward (i) and reverse (sz - 1 - i) based on level parity.
            int index = leftToRight ? i : (sz - 1 - i);
            level[index] = curr->data;

            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }

        // Toggle direction
        leftToRight = !leftToRight;

        for (int val : level) {
            result.push_back(val);
        }
    }

    return result;
}

int main() {
    //        1
    //      /   \
    //     2     3
    //    / \   / \
    //   4   5 6   7
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    std::vector<int> res = zigZagTraversal(root);
    std::cout << "Zig-Zag traversal: ";
    for (int x : res) std::cout << x << " ";
    std::cout << "\n"; // 1 3 2 4 5 6 7

    return 0;
}
