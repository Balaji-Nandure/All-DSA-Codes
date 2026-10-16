/**
 * Problem: Deletion of a Node in a BST
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Inserting or searching in a BST only visits a path without disrupting pointers.
 * - Deletion is structurally delicate because removing an interior node must preserve the BST invariant
 *   for all descendants of both subtrees.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Three-Case Deletion via Inorder Successor:
 *   - Search for key using BST branching:
 *     - If `key < root->data`: `root->left = deleteNode(root->left, key)`.
 *     - If `key > root->data`: `root->right = deleteNode(root->right, key)`.
 *   - Once the matching node is reached:
 *     - Case 1 (0 children / Leaf): Delete and return `nullptr`.
 *     - Case 2 (1 child): Bypass current node and return the single existing child.
 *     - Case 3 (2 children):
 *       - Find the Inorder Successor (the minimum element in the RIGHT subtree).
 *       - Copy the successor's data into current node.
 *       - Recursively delete the successor node from the right subtree.
 *       - (Alternatively, Inorder Predecessor can be used; both preserve BST invariants).
 * 
 * TIME COMPLEXITY:
 * - O(H): Where H is tree height.
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

Node* minValueNode(Node* node) {
    Node* curr = node;
    while (curr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node with only one child or no child
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Node with two children: replace with Inorder Successor (minimum in right subtree), then delete successor.
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    std::cout << root->data << " ";
    inorder(root->right);
}

int main() {
    //        50
    //       /  \
    //      30   70
    //     /  \  / \
    //    20 40 60 80
    Node* root = new Node(50);
    root->left = new Node(30);
    root->right = new Node(70);
    root->left->left = new Node(20);
    root->left->right = new Node(40);
    root->right->left = new Node(60);
    root->right->right = new Node(80);

    std::cout << "Original BST: ";
    inorder(root); // 20 30 40 50 60 70 80
    std::cout << "\n";

    root = deleteNode(root, 50); // Delete root with 2 children

    std::cout << "After deleting 50: ";
    inorder(root); // 20 30 40 60 70 80
    std::cout << "\n";

    return 0;
}
