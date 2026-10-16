/**
 * Problem: Check if Binary Tree is Sum Tree or not
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Convert Binary tree into Sum tree", we modified nodes to MAKE it a sum tree.
 * - Here, we perform a read-only VALIDATION: verifying if every non-leaf node satisfies:
 *   `node->data == sum(all nodes in left subtree) + sum(all nodes in right subtree)`.
 * - Leaf nodes and null nodes are valid Sum Trees by definition.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Bottom-Up Post-Order with Fast-Fail Sentinel (-1):
 *   - Base Cases:
 *     - Null node: returns 0.
 *     - Leaf node (`!left && !right`): returns its own value (valid Sum Tree).
 *   - At each non-leaf node:
 *     - Recursively obtain `leftSum` and `rightSum`.
 *     - If either returned `-1`, propagate `-1` immediately.
 *     - If `node->data == leftSum + rightSum`:
 *       - The subtree is a valid Sum Tree!
 *       - Return `node->data + leftSum + rightSum` (which equals `2 * node->data`) to the parent.
 *     - Otherwise: return `-1`.
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

int checkSumTree(Node* root) {
    if (!root) return 0;

    // Leaf nodes are sum trees by definition
    if (!root->left && !root->right) {
        return root->data;
    }

    int leftSum = checkSumTree(root->left);
    if (leftSum == -1) return -1;

    int rightSum = checkSumTree(root->right);
    if (rightSum == -1) return -1;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Verify that current node's value strictly equals the sum of its left and right subtrees.
    if (root->data == leftSum + rightSum) {
        return root->data + leftSum + rightSum; // Total subtree sum = 2 * root->data
    }

    return -1; // Violation detected
}

bool isSumTree(Node* root) {
    return checkSumTree(root) != -1;
}

int main() {
    // Valid Sum Tree:
    //        26
    //       /  \
    //      10   3
    //     /  \   \
    //    4    6   3
    Node* root1 = new Node(26);
    root1->left = new Node(10);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(6);
    root1->right->right = new Node(3);

    std::cout << "Tree 1 is Sum Tree: " << (isSumTree(root1) ? "Yes" : "No") << "\n"; // Yes

    // Invalid Sum Tree:
    Node* root2 = new Node(10);
    root2->left = new Node(5);
    root2->right = new Node(6);

    std::cout << "Tree 2 is Sum Tree: " << (isSumTree(root2) ? "Yes" : "No") << "\n"; // No

    return 0;
}
