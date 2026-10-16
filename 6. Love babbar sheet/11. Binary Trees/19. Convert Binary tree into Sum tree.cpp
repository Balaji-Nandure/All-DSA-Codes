/**
 * Problem: Convert a given Tree to Sum Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Convert Binary tree into Doubly Linked List", pointers were rewired while data values stayed invariant.
 * - Here, the tree's topological pointer structure stays identical, but every node's VALUE is overwritten
 *   with the sum of all nodes in its left and right subtrees in the ORIGINAL tree (leaves become 0).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Bottom-Up Post-Order Transformation:
 *   - Base Case: Null node contributes 0 to its parent's sum.
 *   - At each node:
 *     1. Preserve its original value: `oldVal = node->data`.
 *     2. Recursively transform left and right subtrees, receiving their total original subtree sums:
 *        `leftSum = toSumTree(node->left)`, `rightSum = toSumTree(node->right)`.
 *     3. Overwrite current node's value with `leftSum + rightSum`.
 *     4. Return `node->data + oldVal` to the parent so that the parent receives the sum of this node's
 *        entire original subtree.
 * 
 * TIME COMPLEXITY:
 * - O(N): Traverses each node exactly once.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion stack space bounded by tree height.
 */

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

int toSumTree(Node* node) {
    if (!node) return 0;

    int oldVal = node->data;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Current node becomes the sum of its left and right original subtrees; returns new value + original value to parent.
    node->data = toSumTree(node->left) + toSumTree(node->right);

    return node->data + oldVal;
}

void printInorder(Node* node) {
    if (!node) return;
    printInorder(node->left);
    std::cout << node->data << " ";
    printInorder(node->right);
}

int main() {
    // Original Tree:
    //         10
    //       /    \
    //     -2      6
    //    /   \   / \
    //   8    -4 7   5
    Node* root = new Node(10);
    root->left = new Node(-2);
    root->right = new Node(6);
    root->left->left = new Node(8);
    root->left->right = new Node(-4);
    root->right->left = new Node(7);
    root->right->right = new Node(5);

    std::cout << "Original tree Inorder: ";
    printInorder(root);
    std::cout << "\n";

    toSumTree(root);

    std::cout << "Sum tree Inorder: ";
    printInorder(root); // 0 4 0 20 0 12 0
    std::cout << "\n";

    return 0;
}
