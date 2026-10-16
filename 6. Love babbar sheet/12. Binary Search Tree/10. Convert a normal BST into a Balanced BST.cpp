/**
 * Problem: Convert a Normal BST into a Balanced BST
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A normal BST may degrade into a skewed linear chain with height O(N), degrading search/insert to O(N).
 * - Here, we restructure the tree topology to achieve minimal logarithmic height `O(log N)`
 *   where `|height(left) - height(right)| <= 1` at every node.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Inorder Extraction + Binary Divide-and-Conquer:
 *   1. Traverse the skewed BST in Inorder to collect all nodes into an array `nodes`.
 *      - Because the original tree is already a valid BST, `nodes` is automatically sorted in strictly O(N) time!
 *   2. Build Balanced BST from Sorted Array:
 *      - Find middle element `mid = (start + end) / 2`.
 *      - Make `nodes[mid]` the root of the current subtree.
 *      - Recursively build:
 *        `root->left = buildBalancedTree(nodes, start, mid - 1)`
 *        `root->right = buildBalancedTree(nodes, mid + 1, end)`
 *      - Dividing the remaining elements evenly into two halves guarantees optimal height `ceil(log2(N))`.
 * 
 * TIME COMPLEXITY:
 * - O(N): Inorder extraction is O(N); divide-and-conquer reconstruction is O(N).
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for vector storing Inorder nodes.
 */

#include <iostream>
#include <vector>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void storeInorder(Node* root, std::vector<Node*>& nodes) {
    if (!root) return;
    storeInorder(root->left, nodes);
    nodes.push_back(root);
    storeInorder(root->right, nodes);
}

Node* buildBalancedTree(const std::vector<Node*>& nodes, int start, int end) {
    if (start > end) return nullptr;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Pick the middle element as root, ensuring equal distribution of descendants on both subtrees.
    int mid = start + (end - start) / 2;
    Node* root = nodes[mid];

    root->left = buildBalancedTree(nodes, start, mid - 1);
    root->right = buildBalancedTree(nodes, mid + 1, end);

    return root;
}

Node* buildBalancedBST(Node* root) {
    std::vector<Node*> nodes;
    storeInorder(root, nodes);
    return buildBalancedTree(nodes, 0, (int)nodes.size() - 1);
}

void preOrder(Node* root) {
    if (!root) return;
    std::cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

int main() {
    // Degenerate Skewed BST (Height 4):
    //        4
    //       /
    //      3
    //     /
    //    2
    //   /
    //  1
    Node* root = new Node(4);
    root->left = new Node(3);
    root->left->left = new Node(2);
    root->left->left->left = new Node(1);

    std::cout << "Original skewed BST Preorder: ";
    preOrder(root); // 4 3 2 1
    std::cout << "\n";

    Node* balancedRoot = buildBalancedBST(root);

    std::cout << "Balanced BST Preorder: ";
    preOrder(balancedRoot); // 2 1 3 4 (Height reduced to 3)
    std::cout << "\n";

    return 0;
}
