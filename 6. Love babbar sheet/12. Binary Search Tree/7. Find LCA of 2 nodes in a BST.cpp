/**
 * Problem: Lowest Common Ancestor (LCA) in a Binary Search Tree
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Find LCA in a Binary tree", we had to explore both left and right subtrees in O(N) time.
 * - In a BST, the key values themselves dictate whether both nodes lie on the left, on the right, or split!
 * - This turns LCA into a direct downward descent in O(H) time and O(1) auxiliary space.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - BST Split Point Detection:
 *   - While `curr != nullptr`:
 *     - If both `n1 < curr->data` and `n2 < curr->data`:
 *       - Both targets lie deeper in the left subtree -> move left: `curr = curr->left`.
 *     - If both `n1 > curr->data` and `n2 > curr->data`:
 *       - Both targets lie deeper in the right subtree -> move right: `curr = curr->right`.
 *     - Otherwise:
 *       - The paths to `n1` and `n2` bifurcate here (one is on left, one on right, or `curr` matches one of them).
 *       - Therefore, `curr` is the Lowest Common Ancestor! Return `curr`.
 * 
 * TIME COMPLEXITY:
 * - O(H): Where H is tree height (single downward traversal).
 * 
 * SPACE COMPLEXITY:
 * - O(1) auxiliary space (iterative).
 */

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* LCAinBST(Node* root, int n1, int n2) {
    Node* curr = root;

    while (curr != nullptr) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // If both keys lie on the same side, continue descending; the first node where they diverge is their LCA!
        if (n1 < curr->data && n2 < curr->data) {
            curr = curr->left;
        } else if (n1 > curr->data && n2 > curr->data) {
            curr = curr->right;
        } else {
            return curr; // Split point reached
        }
    }

    return nullptr;
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

    Node* ans = LCAinBST(root, 10, 14);
    std::cout << "LCA of 10 and 14: " << (ans ? ans->data : -1) << "\n"; // 12

    ans = LCAinBST(root, 14, 8);
    std::cout << "LCA of 14 and 8: " << (ans ? ans->data : -1) << "\n"; // 8

    ans = LCAinBST(root, 10, 22);
    std::cout << "LCA of 10 and 22: " << (ans ? ans->data : -1) << "\n"; // 20

    return 0;
}
