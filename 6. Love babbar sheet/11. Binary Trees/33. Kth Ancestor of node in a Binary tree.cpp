/**
 * Problem: Kth Ancestor of a Node in a Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - LCA found the first meeting point of two paths.
 * - Here, we locate a single target node and climb UPWARDS exactly K steps along its parent lineage.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Bottom-Up Recursive Backtracking:
 *   - Search for the target node `node` using DFS.
 *   - Once found, return that node pointer upwards.
 *   - As recursion unwinds through each successive parent frame:
 *     - Decrement `k--`.
 *     - If `k == 0`, the current frame IS the Kth ancestor!
 *     - Lock `k = INT_MAX` (or very negative) to prevent overwriting by higher ancestors.
 *     - Return `root` as the definitive Kth ancestor.
 * 
 * TIME COMPLEXITY:
 * - O(N): Traverses each node once.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion depth bounded by tree height.
 */

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* kthAncestorUtil(Node* root, int& k, int target, int& ans) {
    if (!root) return nullptr;

    if (root->data == target) {
        return root;
    }

    Node* left = kthAncestorUtil(root->left, k, target, ans);
    Node* right = kthAncestorUtil(root->right, k, target, ans);

    if (left || right) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Decrement k on each upward step; when k reaches 0, current node is the Kth ancestor!
        k--;
        if (k == 0) {
            ans = root->data;
            return nullptr; // Cut off further ancestor counting
        }
        return left ? left : right;
    }

    return nullptr;
}

int kthAncestor(Node* root, int k, int node) {
    int ans = -1;
    kthAncestorUtil(root, k, node, ans);
    return ans;
}

int main() {
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    // 1st ancestor of 4 is 2
    std::cout << "1st ancestor of 4: " << kthAncestor(root, 1, 4) << "\n"; // 2

    // 2nd ancestor of 4 is 1
    std::cout << "2nd ancestor of 4: " << kthAncestor(root, 2, 4) << "\n"; // 1

    // 3rd ancestor of 4 does not exist
    std::cout << "3rd ancestor of 4: " << kthAncestor(root, 3, 4) << "\n"; // -1

    return 0;
}
