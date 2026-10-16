/**
 * Problem: Mirror of a Tree (Invert Binary Tree)
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Previous problems queried properties of a static tree (traversals, height, diameter).
 * - Here, we perform an in-place structural transformation: flipping every subtree across its vertical axis
 *   so that left children become right children and vice versa.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Recursive Post-Order Inversion:
 *   - Base Case: If node is null, return.
 *   - Recursively invert the left subtree: `mirror(root->left)`.
 *   - Recursively invert the right subtree: `mirror(root->right)`.
 *   - Swap the left and right child pointers of the current node: `std::swap(root->left, root->right)`.
 *   - Every node's children are flipped, generating the exact reflection of the original binary tree.
 * 
 * TIME COMPLEXITY:
 * - O(N): Every node is visited and has its pointers swapped in O(1).
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion stack space proportional to height of tree.
 */

#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void mirror(Node* root) {
    if (!root) return;

    // Recurse on subtrees
    mirror(root->left);
    mirror(root->right);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Swap left and right child pointers at every node to invert the tree across its vertical axis.
    std::swap(root->left, root->right);
}

void inOrder(Node* root) {
    if (!root) return;
    inOrder(root->left);
    std::cout << root->data << " ";
    inOrder(root->right);
}

int main() {
    // Original Tree:
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

    std::cout << "Original tree Inorder: ";
    inOrder(root); // 4 2 5 1 3
    std::cout << "\n";

    mirror(root);

    std::cout << "Mirrored tree Inorder: ";
    inOrder(root); // 3 1 5 2 4
    std::cout << "\n";

    return 0;
}
