/**
 * Problem: Convert a Binary Tree into BST preserving structure
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Convert Binary tree into Doubly Linked List", pointers were rewired into a line.
 * - Here, the EXACT PHYSICAL TOPOLOGY / SHAPE of the tree must remain strictly intact;
 *   only the NODE DATA values may be reassigned so that the resulting tree satisfies BST invariants.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Three-Step Inorder Re-assignment:
 *   1. Extract: Traverse the Binary Tree in Inorder and collect all node values into an array `vals`.
 *   2. Sort: Sort `vals` in ascending order (`std::sort`).
 *   3. Re-populate: Traverse the Binary Tree in Inorder a second time, overwriting each node's data
 *      sequentially with elements from the sorted `vals` array (`node->data = vals[index++]`).
 *   - Why this works?
 *     - An Inorder traversal of any BST ALWAYS visits nodes in ascending key order.
 *     - By writing sorted values back into the Inorder traversal sequence, the original tree topology
 *       is 100% preserved while unconditionally guaranteeing that every node satisfies the BST property!
 * 
 * TIME COMPLEXITY:
 * - O(N log N): Two Inorder traversals O(N) + sorting N elements O(N log N).
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space to store node values.
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

void storeInorder(Node* root, std::vector<int>& vals) {
    if (!root) return;
    storeInorder(root->left, vals);
    vals.push_back(root->data);
    storeInorder(root->right, vals);
}

void arrayToBST(Node* root, const std::vector<int>& vals, int& index) {
    if (!root) return;

    arrayToBST(root->left, vals, index);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Overwrite node values along Inorder sequence with sorted values to convert to BST without changing shape.
    root->data = vals[index++];

    arrayToBST(root->right, vals, index);
}

Node* binaryTreeToBST(Node* root) {
    if (!root) return root;

    std::vector<int> vals;
    storeInorder(root, vals);

    std::sort(vals.begin(), vals.end());

    int index = 0;
    arrayToBST(root, vals, index);

    return root;
}

void printInorder(Node* root) {
    if (!root) return;
    printInorder(root->left);
    std::cout << root->data << " ";
    printInorder(root->right);
}

int main() {
    // Non-BST Binary Tree:
    //          10
    //         /  \
    //        2    7
    //       / \
    //      8   4
    Node* root = new Node(10);
    root->left = new Node(2);
    root->right = new Node(7);
    root->left->left = new Node(8);
    root->left->right = new Node(4);

    std::cout << "Original tree Inorder: ";
    printInorder(root); // 8 2 4 10 7
    std::cout << "\n";

    binaryTreeToBST(root);

    std::cout << "Converted BST Inorder (strictly sorted): ";
    printInorder(root); // 2 4 7 8 10
    std::cout << "\n";

    return 0;
}
