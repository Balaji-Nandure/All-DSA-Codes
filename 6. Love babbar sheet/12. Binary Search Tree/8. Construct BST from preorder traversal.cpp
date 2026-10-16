/**
 * Problem: Construct BST from Preorder Traversal
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Construct Binary tree from Inorder and preorder traversal", we required BOTH traversals to reconstruct the tree.
 * - In a BST, the Inorder sequence is implicitly defined (it is simply the sorted keys)!
 * - We can construct the entire BST directly from PREORDER ALONE in optimal O(N) time using an upper-bound parameter.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Upper-Bound Constrained DFS:
 *   - The preorder array processes: Root -> Left Subtree -> Right Subtree.
 *   - Every node in the left subtree must be strictly `< root->data`.
 *   - Every node in the right subtree must be strictly `< bound` (the upper limit inherited from its ancestor).
 *   - Maintain a global/reference index `i = 0`:
 *     - If `i == n` or `preorder[i] > bound`: current element does NOT belong to this subtree, return null.
 *     - Otherwise, consume `preorder[i++]` to form `root`.
 *     - `root->left = build(preorder, i, root->data)` (upper bound is root's value).
 *     - `root->right = build(preorder, i, bound)` (upper bound remains ancestor's bound).
 * 
 * TIME COMPLEXITY:
 * - O(N): Each element of the preorder array is inspected at most twice.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion depth bounded by tree height.
 */

#include <iostream>
#include <vector>
#include <climits>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* bstFromPreorderHelper(const std::vector<int>& preorder, int& i, int bound) {
    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // If the next element exceeds the allowable upper bound for this subtree, return null without advancing i.
    if (i >= (int)preorder.size() || preorder[i] > bound) {
        return nullptr;
    }

    Node* root = new Node(preorder[i++]);

    // Left child must be smaller than current root
    root->left = bstFromPreorderHelper(preorder, i, root->data);

    // Right child must be smaller than parent's upper bound
    root->right = bstFromPreorderHelper(preorder, i, bound);

    return root;
}

Node* bstFromPreorder(const std::vector<int>& preorder) {
    int i = 0;
    return bstFromPreorderHelper(preorder, i, INT_MAX);
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    std::cout << root->data << " ";
    inorder(root->right);
}

int main() {
    std::vector<int> preorder = {10, 5, 1, 7, 40, 50};

    Node* root = bstFromPreorder(preorder);

    std::cout << "Inorder of constructed BST (must be strictly sorted): ";
    inorder(root); // 1 5 7 10 40 50
    std::cout << "\n";

    return 0;
}
