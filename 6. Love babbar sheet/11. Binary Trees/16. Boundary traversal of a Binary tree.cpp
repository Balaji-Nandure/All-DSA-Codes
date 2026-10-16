/**
 * Problem: Boundary Traversal of a Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Views (Left, Right, Top, Bottom) only picked one visible node per horizon or line.
 * - Boundary traversal traces the entire PERIMETER of the binary tree in an anti-clockwise direction:
 *   Left Boundary -> Leaves (left-to-right) -> Right Boundary (bottom-to-top).
 * - Nodes must never be duplicated (leaves are strictly excluded from left/right boundary collections).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Three-Phase Modular Traversal:
 *   1. Root Node: Add if not a leaf.
 *   2. Left Boundary:
 *      - Start from `root->left`.
 *      - If not a leaf, add to result.
 *      - Prefer `curr->left`; if null, fall back to `curr->right`.
 *   3. Leaf Nodes:
 *      - Standard DFS traversal covering all subtrees; add any node where `!node->left && !node->right`.
 *   4. Right Boundary (in reverse):
 *      - Start from `root->right`.
 *      - If not a leaf, push onto a temporary stack.
 *      - Prefer `curr->right`; if null, fall back to `curr->left`.
 *      - Unload stack to append bottom-to-top.
 * 
 * TIME COMPLEXITY:
 * - O(N): Each node is visited at most twice (boundary paths + leaf DFS).
 * 
 * SPACE COMPLEXITY:
 * - O(H): Stack/recursion space bounded by tree height.
 */

#include <iostream>
#include <vector>
#include <stack>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

bool isLeaf(Node* node) {
    return node && !node->left && !node->right;
}

void addLeftBoundary(Node* root, std::vector<int>& res) {
    Node* curr = root->left;
    while (curr) {
        if (!isLeaf(curr)) res.push_back(curr->data);
        if (curr->left) curr = curr->left;
        else curr = curr->right;
    }
}

void addLeaves(Node* root, std::vector<int>& res) {
    if (!root) return;
    if (isLeaf(root)) {
        res.push_back(root->data);
        return;
    }
    addLeaves(root->left, res);
    addLeaves(root->right, res);
}

void addRightBoundary(Node* root, std::vector<int>& res) {
    Node* curr = root->right;
    std::stack<int> st;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Collect non-leaf right boundary nodes into a stack so they can be unloaded in reverse (bottom-to-top).
    while (curr) {
        if (!isLeaf(curr)) st.push(curr->data);
        if (curr->right) curr = curr->right;
        else curr = curr->left;
    }

    while (!st.empty()) {
        res.push_back(st.top());
        st.pop();
    }
}

std::vector<int> boundary(Node* root) {
    std::vector<int> res;
    if (!root) return res;

    if (!isLeaf(root)) res.push_back(root->data);

    addLeftBoundary(root, res);
    addLeaves(root, res);
    addRightBoundary(root, res);

    return res;
}

int main() {
    //        1
    //      /   \
    //     2     3
    //    / \   / \
    //   4   5 6   7
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    std::vector<int> b = boundary(root);
    std::cout << "Boundary traversal: ";
    for (int x : b) std::cout << x << " ";
    std::cout << "\n"; // 1 2 4 5 6 7 3

    return 0;
}
