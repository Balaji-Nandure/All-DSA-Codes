/**
 * Problem: Tree Isomorphism Problem
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Check if 2 trees are mirror or not", subtrees had to be strictly flipped at EVERY node.
 * - In Tree Isomorphism, children can be swapped at ANY arbitrary subset of nodes (or not swapped at all),
 *   allowing local flips while preserving overall topological equivalence.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Branching Case Recursion:
 *   - Base Cases:
 *     - If both roots are null: return true.
 *     - If exactly one is null: return false.
 *     - If node values differ (`root1->data != root2->data`): return false.
 *   - At each matching node, there are exactly two valid geometric possibilities:
 *     1. Subtrees were NOT swapped:
 *        `isIsomorphic(r1->left, r2->left) && isIsomorphic(r1->right, r2->right)`.
 *     2. Subtrees WERE swapped:
 *        `isIsomorphic(r1->left, r2->right) && isIsomorphic(r1->right, r2->left)`.
 *   - Return `Case 1 || Case 2`.
 * 
 * TIME COMPLEXITY:
 * - O(N): On balanced trees; worst-case O(min(M, N)^2) on heavily branching ambiguous isomorphic trees.
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

bool isIsomorphic(Node* root1, Node* root2) {
    // Base Case 1: Both null
    if (!root1 && !root2) return true;

    // Base Case 2: One null, other non-null
    if (!root1 || !root2) return false;

    // Base Case 3: Values differ
    if (root1->data != root2->data) return false;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Evaluate both possibilities: children preserved as-is OR children flipped at this node!
    bool notFlipped = isIsomorphic(root1->left, root2->left) &&
                      isIsomorphic(root1->right, root2->right);

    bool flipped = isIsomorphic(root1->left, root2->right) &&
                   isIsomorphic(root1->right, root2->left);

    return notFlipped || flipped;
}

int main() {
    // Tree 1:
    //        1
    //      /   \
    //     2     3
    //    /
    //   4
    Node* t1 = new Node(1);
    t1->left = new Node(2);
    t1->right = new Node(3);
    t1->left->left = new Node(4);

    // Tree 2: (children of 1 are swapped: 3 on left, 2 on right)
    //        1
    //      /   \
    //     3     2
    //          /
    //         4
    Node* t2 = new Node(1);
    t2->left = new Node(3);
    t2->right = new Node(2);
    t2->right->left = new Node(4);

    std::cout << "Trees are isomorphic: " << (isIsomorphic(t1, t2) ? "Yes" : "No") << "\n"; // Yes

    return 0;
}
