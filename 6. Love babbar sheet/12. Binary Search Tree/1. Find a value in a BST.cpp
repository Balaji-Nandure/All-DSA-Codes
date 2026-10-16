/**
 * Problem: Find a value in a BST (Search in BST)
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In a general Binary Tree, searching a key requires traversing potentially all N nodes (O(N) time).
 * - A Binary Search Tree (BST) enforces the BST Invariant:
 *     All nodes in `root->left` have keys < `root->data`.
 *     All nodes in `root->right` have keys > `root->data`.
 * - This allows pruning half of the search space at each comparison, achieving O(H) logarithmic search.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Binary Elimination Search:
 *   - Compare target `val` with `root->data`:
 *     - If `root->data == val`: Key found, return `root`.
 *     - If `val < root->data`: Key can only exist in the LEFT subtree, recurse/loop left.
 *     - If `val > root->data`: Key can only exist in the RIGHT subtree, recurse/loop right.
 *   - Iterative approach achieves O(1) auxiliary space without recursion stack overhead.
 * 
 * TIME COMPLEXITY:
 * - O(H): Where H is tree height (O(log N) for balanced BST, O(N) worst case for skewed BST).
 * 
 * SPACE COMPLEXITY:
 * - O(1) iterative space.
 */

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* searchBST(Node* root, int val) {
    Node* curr = root;

    while (curr != nullptr) {
        if (curr->data == val) {
            return curr;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // BST invariant eliminates the opposite half of the tree at every branching decision.
        if (val < curr->data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    return nullptr; // Not found
}

int main() {
    //        4
    //       / \
    //      2   7
    //     / \
    //    1   3
    Node* root = new Node(4);
    root->left = new Node(2);
    root->right = new Node(7);
    root->left->left = new Node(1);
    root->left->right = new Node(3);

    Node* res = searchBST(root, 2);
    std::cout << "Search 2: " << (res ? "Found" : "Not Found") << "\n"; // Found

    res = searchBST(root, 5);
    std::cout << "Search 5: " << (res ? "Found" : "Not Found") << "\n"; // Not Found

    return 0;
}
