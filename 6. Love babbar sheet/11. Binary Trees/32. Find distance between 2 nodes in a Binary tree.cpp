/**
 * Problem: Find distance between 2 nodes in a Binary tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Find LCA in a Binary tree", we identified the common ancestor node.
 * - Here, we quantify the METRIC DISTANCE (number of edges) connecting any two nodes `a` and `b`
 *   which route upwards through their LCA.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - LCA + Depth Sum Reduction:
 *   - The unique simple path between any two nodes `a` and `b` in a tree always ascends from `a` to their
 *     Lowest Common Ancestor (LCA), and descends from the LCA down to `b`.
 *   - Therefore:
 *     `distance(a, b) = distance(LCA, a) + distance(LCA, b)`.
 *   - Steps:
 *     1. Find `ancestor = lca(root, a, b)` in O(N).
 *     2. Find depth of `a` starting from `ancestor`: `d1 = findLevel(ancestor, a, 0)`.
 *     3. Find depth of `b` starting from `ancestor`: `d2 = findLevel(ancestor, b, 0)`.
 *     4. Return `d1 + d2`.
 * 
 * TIME COMPLEXITY:
 * - O(N): Two linear tree traversals (LCA + level finding).
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

Node* findLCA(Node* root, int a, int b) {
    if (!root) return nullptr;
    if (root->data == a || root->data == b) return root;

    Node* left = findLCA(root->left, a, b);
    Node* right = findLCA(root->right, a, b);

    if (left && right) return root;
    return left ? left : right;
}

int findLevel(Node* root, int target, int level) {
    if (!root) return -1;
    if (root->data == target) return level;

    int leftLevel = findLevel(root->left, target, level + 1);
    if (leftLevel != -1) return leftLevel;

    return findLevel(root->right, target, level + 1);
}

int findDist(Node* root, int a, int b) {
    // Step 1: Find Lowest Common Ancestor
    Node* lcaNode = findLCA(root, a, b);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Distance between a and b is the sum of distances from their LCA to each of the two nodes.
    int d1 = findLevel(lcaNode, a, 0);
    int d2 = findLevel(lcaNode, b, 0);

    return d1 + d2;
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

    // Distance between 4 and 5: 4->2->5 = 2 edges
    std::cout << "Distance between 4 and 5: " << findDist(root, 4, 5) << "\n"; // 2

    // Distance between 4 and 3: 4->2->1->3 = 3 edges
    std::cout << "Distance between 4 and 3: " << findDist(root, 4, 3) << "\n"; // 3

    return 0;
}
