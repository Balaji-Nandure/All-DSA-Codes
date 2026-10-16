/**
 * Problem: Convert Binary Tree into Doubly Linked List (In-Place)
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Previous problems transformed binary tree nodes or created new external linear structures.
 * - Here, we perform an IN-PLACE POINTER REWIRING: repurposing existing `left` pointers as DLL `prev`
 *   and `right` pointers as DLL `next`, preserving Inorder sequence with zero memory reallocation.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Inorder Traversal with Previous Pointer Tracking:
 *   - The order of nodes in DLL must match the Inorder traversal of the tree (Left -> Root -> Right).
 *   - Maintain:
 *     - `head`: Points to the first node in Inorder traversal (leftmost leaf).
 *     - `prev`: Points to the node visited immediately before the current node in Inorder.
 *   - At each node `curr`:
 *     - If `prev == nullptr`: `curr` is the very first node -> `head = curr`.
 *     - Else: Establish bidirectional links:
 *       `curr->left = prev;` (left acts as prev)
 *       `prev->right = curr;` (right acts as next)
 *     - Advance `prev = curr`.
 * 
 * TIME COMPLEXITY:
 * - O(N): Traverses each node once.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion stack depth proportional to tree height (zero extra nodes created).
 */

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void bToDLLUtil(Node* root, Node*& head, Node*& prev) {
    if (!root) return;

    // Recurse left
    bToDLLUtil(root->left, head, prev);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Wire previous Inorder node's right to curr, and curr's left to previous Inorder node.
    if (prev == nullptr) {
        head = root; // First node visited is the DLL head
    } else {
        root->left = prev;
        prev->right = root;
    }
    prev = root;

    // Recurse right
    bToDLLUtil(root->right, head, prev);
}

Node* bToDLL(Node* root) {
    Node* head = nullptr;
    Node* prev = nullptr;
    bToDLLUtil(root, head, prev);
    return head;
}

void printDLL(Node* head) {
    Node* curr = head;
    while (curr) {
        std::cout << curr->data << " ";
        curr = curr->right;
    }
    std::cout << "\n";
}

int main() {
    //      10
    //     /  \
    //    12   15
    //   /  \  /
    //  25  30 36
    Node* root = new Node(10);
    root->left = new Node(12);
    root->right = new Node(15);
    root->left->left = new Node(25);
    root->left->right = new Node(30);
    root->right->left = new Node(36);

    Node* dllHead = bToDLL(root);
    std::cout << "DLL Inorder sequence: ";
    printDLL(dllHead); // 25 12 30 10 36 15

    return 0;
}
