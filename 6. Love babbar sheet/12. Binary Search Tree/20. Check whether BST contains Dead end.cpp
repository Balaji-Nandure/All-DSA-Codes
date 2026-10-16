/**
 * Problem: Check whether BST contains Dead End
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A leaf node in a normal tree can always accept new child nodes.
 * - Here, since keys must be positive integers (`val >= 1`) with NO duplicates, a leaf node `x` becomes a DEAD END
 *   if its ancestral constraints force any potential children to lie in a range where NO integer is available
 *   (i.e. lower bound == upper bound).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Ancestral Range Narrowing:
 *   - Carry allowable insertion interval `[minVal, maxVal]` down the tree:
 *     - Root starts with `[1, INT_MAX]`.
 *     - Branching left constrains upper bound: `[minVal, root->data - 1]`.
 *     - Branching right constrains lower bound: `[root->data + 1, maxVal]`.
 *   - At any leaf node (`!root->left && !root->right`):
 *     - If `minVal == maxVal`:
 *       - The only integer that could fit in this range is `minVal`, which is already taken by the leaf itself!
 *       - Neither a left child (`< root->data`) nor a right child (`> root->data`) can ever be inserted without
 *         violating integer bounds or BST ordering.
 *       - A Dead End is identified -> return true!
 * 
 * TIME COMPLEXITY:
 * - O(N): Traverses each node at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion depth bounded by tree height.
 */

#include <iostream>
#include <climits>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

bool checkDeadEnd(Node* root, int minVal, int maxVal) {
    if (!root) return false;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // If a leaf's allowable insertion interval collapses to minVal == maxVal, no integer child can ever be added.
    if (!root->left && !root->right) {
        if (minVal == maxVal) {
            return true;
        }
    }

    return checkDeadEnd(root->left, minVal, root->data - 1) ||
           checkDeadEnd(root->right, root->data + 1, maxVal);
}

bool isDeadEnd(Node* root) {
    return checkDeadEnd(root, 1, INT_MAX);
}

int main() {
    // BST with dead end at node 9:
    //          8
    //        /   \
    //       5     9
    //      / \
    //     2   7
    //    /
    //   1 (dead end: range [1, 1], since 0 is forbidden!)
    Node* root = new Node(8);
    root->left = new Node(5);
    root->right = new Node(9);
    root->left->left = new Node(2);
    root->left->right = new Node(7);
    root->left->left->left = new Node(1);

    std::cout << "BST contains dead end: " 
              << (isDeadEnd(root) ? "Yes" : "No") << "\n"; // Yes (at node 1 and 9)

    return 0;
}
