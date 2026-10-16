/**
 * Problem: Top View of a Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Left and Right views segmented nodes by horizontal depth levels (Y-axis).
 * - Top View segments nodes by VERTICAL LINES (Horizontal Distance, X-axis), selecting the uppermost node on each line.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Level Order BFS + Horizontal Distance Tracking:
 *   - Define horizontal distance (hd):
 *     - Root has `hd = 0`.
 *     - Left child has `hd = parent->hd - 1`.
 *     - Right child has `hd = parent->hd + 1`.
 *   - Why BFS over DFS?
 *     - BFS visits nodes strictly level-by-level (top to bottom).
 *     - Thus, the FIRST time we encounter any horizontal distance `hd`, that node is guaranteed to be
 *       the TOPMOST node on that vertical line!
 *   - Store in `std::map<int, int> topNode` to automatically sort from leftmost `hd` to rightmost `hd`.
 * 
 * TIME COMPLEXITY:
 * - O(N log N) using `std::map` (or O(N) using min/max tracking with an array).
 * 
 * SPACE COMPLEXITY:
 * - O(N) for BFS queue and map.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <map>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

std::vector<int> topView(Node* root) {
    std::vector<int> res;
    if (!root) return res;

    // Map: hd -> node's data (sorted by hd)
    std::map<int, int> topNode;

    // Queue: {node, hd}
    std::queue<std::pair<Node*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        auto [curr, hd] = q.front();
        q.pop();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Only insert if no node has been registered at this horizontal distance yet (BFS ensures top-most).
        if (topNode.find(hd) == topNode.end()) {
            topNode[hd] = curr->data;
        }

        if (curr->left) q.push({curr->left, hd - 1});
        if (curr->right) q.push({curr->right, hd + 1});
    }

    for (const auto& [hd, val] : topNode) {
        res.push_back(val);
    }

    return res;
}

int main() {
    //        1
    //      /   \
    //     2     3
    //      \   /
    //       4 5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(4);
    root->right->left = new Node(5);

    std::vector<int> ans = topView(root);
    std::cout << "Top view of tree: ";
    for (int x : ans) std::cout << x << " ";
    std::cout << "\n"; // 2 1 3

    return 0;
}
