/**
 * Problem: Populate Inorder Successor for all nodes
 * Category: Binary Search Tree / Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Find inorder successor and predecessor in a BST", we queried the successor of a SINGLE key in O(H).
 * - Here, every node has an explicit `next` pointer (like a threaded tree), and we must populate the Inorder
 *   successor for ALL N nodes in a single O(N) sweep.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Reverse Inorder Traversal (Right -> Root -> Left):
 *   - In forward Inorder (Left -> Root -> Right), when visiting `root`, its successor in the right subtree
 *     has NOT been visited yet.
 *   - In REVERSE Inorder (Right -> Root -> Left):
 *     - The Inorder successor of `root` has ALREADY BEEN VISITED in the preceding step!
 *     - We maintain a pointer `succ = nullptr`.
 *     - 1. Recurse right: `populate(root->right)`.
 *     - 2. Connect current node to successor: `root->next = succ`.
 *     - 3. Update successor to be the current node: `succ = root`.
 *     - 4. Recurse left: `populate(root->left)`.
 *   - Beautiful, optimal O(N) single-pass with zero extra memory!
 * 
 * TIME COMPLEXITY:
 * - O(N): Visits every node once.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion depth bounded by tree height.
 */

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* next; // Pointer to Inorder Successor
    Node(int val) : data(val), left(nullptr), right(nullptr), next(nullptr) {}
};

void populateNext(Node* root, Node*& succ) {
    if (!root) return;

    // First visit right subtree
    populateNext(root->right, succ);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // In reverse inorder, 'succ' holds the previously visited node which is the exact Inorder successor of root!
    root->next = succ;
    succ = root; // Update successor for nodes visited in the left subtree

    // Then visit left subtree
    populateNext(root->left, succ);
}

void populate(Node* root) {
    Node* succ = nullptr;
    populateNext(root, succ);
}

int main() {
    //        10
    //       /  \
    //      8   12
    //     /
    //    3
    // Inorder: 3 -> 8 -> 10 -> 12 -> null
    Node* root = new Node(10);
    root->left = new Node(8);
    root->right = new Node(12);
    root->left->left = new Node(3);

    populate(root);

    // Verify chain following next pointers starting from leftmost node (3)
    Node* curr = root->left->left;
    std::cout << "Inorder chain via next pointers: ";
    while (curr) {
        std::cout << curr->data << " -> ";
        curr = curr->next;
    }
    std::cout << "null\n"; // 3 -> 8 -> 10 -> 12 -> null

    return 0;
}
