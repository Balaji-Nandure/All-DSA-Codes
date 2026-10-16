/**
 * Problem: Bottom View of a Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In Top View, we retained the FIRST node encountered at each horizontal distance `hd` and discarded later ones.
 * - In Bottom View, we do the exact inverse: continually OVERWRITING each vertical line with the latest node,
 *   so that the deepest (bottom-most) node on each vertical line remains at the end.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Level Order BFS with Map Overwrite:
 *   - Queue stores `pair<Node*, int hd>`.
 *   - For each dequeued node:
 *     - Unconditionally overwrite `bottomNode[hd] = curr->data`.
 *     - If `curr->left`: enqueue `{curr->left, hd - 1}`.
 *     - If `curr->right`: enqueue `{curr->right, hd + 1}`.
 *   - Because BFS progresses level by level downwards, lower nodes will naturally overwrite higher ones.
 *   - If two nodes are at the same depth and horizontal distance, standard convention picks the rightmost one
 *     (which BFS naturally does if right child is pushed or processed appropriately).
 * 
 * TIME COMPLEXITY:
 * - O(N log N) using `std::map`.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space.
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

std::vector<int> bottomView(Node* root) {
    std::vector<int> res;
    if (!root) return res;

    // Map: hd -> node's data (sorted by hd)
    std::map<int, int> bottomNode;

    // Queue: {node, hd}
    std::queue<std::pair<Node*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        auto [curr, hd] = q.front();
        q.pop();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Unconditionally update/overwrite so that the deepest node at this horizontal distance stays recorded.
        bottomNode[hd] = curr->data;

        if (curr->left) q.push({curr->left, hd - 1});
        if (curr->right) q.push({curr->right, hd + 1});
    }

    for (const auto& [hd, val] : bottomNode) {
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
    // Both 4 and 5 share hd = 0. In bottom view, 5 (or rightmost) is visible.
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(4);
    root->right->left = new Node(5);

    std::vector<int> ans = bottomView(root);
    std::cout << "Bottom view of tree: ";
    for (int x : ans) std::cout << x << " ";
    std::cout << "\n"; // 2 5 3 (or 2 4 3 depending on traversal order)

    return 0;
}
