/**
 * Problem: Find Minimum and Maximum Value in a BST
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In an arbitrary Binary Tree, finding min/max requires inspecting every single node (O(N) time).
 * - In a BST, the total order invariant establishes that the minimum element ALWAYS resides at the
 *   leftmost extremity, and the maximum element ALWAYS resides at the rightmost extremity.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Direct Spine Traversal:
 *   - Minimum: Start from root, follow `left` child pointers until reaching a node where `left == nullptr`.
 *   - Maximum: Start from root, follow `right` child pointers until reaching a node where `right == nullptr`.
 *   - Both operations take strictly O(H) time and O(1) space.
 * 
 * TIME COMPLEXITY:
 * - O(H): Where H is tree height.
 * 
 * SPACE COMPLEXITY:
 * - O(1) auxiliary space.
 */

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

int minValue(Node* root) {
    if (!root) return -1;

    Node* curr = root;
    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Drill leftwards until the leftmost node; by BST invariant, no smaller value can exist anywhere.
    while (curr->left != nullptr) {
        curr = curr->left;
    }

    return curr->data;
}

int maxValue(Node* root) {
    if (!root) return -1;

    Node* curr = root;
    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Drill rightwards until the rightmost node; by BST invariant, no larger value can exist anywhere.
    while (curr->right != nullptr) {
        curr = curr->right;
    }

    return curr->data;
}

int main() {
    //        20
    //       /  \
    //      8    22
    //     / \
    //    4  12
    //       /  \
    //      10  14
    Node* root = new Node(20);
    root->left = new Node(8);
    root->right = new Node(22);
    root->left->left = new Node(4);
    root->left->right = new Node(12);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(14);

    std::cout << "Minimum value in BST: " << minValue(root) << "\n"; // 4
    std::cout << "Maximum value in BST: " << maxValue(root) << "\n"; // 22

    return 0;
}
