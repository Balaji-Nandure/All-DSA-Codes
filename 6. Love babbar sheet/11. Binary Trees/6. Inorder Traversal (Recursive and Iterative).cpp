/**
 * Problem: Inorder Traversal (Recursive and Iterative)
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Level order visited nodes breadth-first.
 * - Inorder traversal visits Depth-First in Left -> Root -> Right order.
 * - In Binary Search Trees, Inorder produces elements in strictly ascending sorted order.
 * - We implement both standard recursion and iterative stack simulation (plus Morris Traversal for O(1) space).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Recursive:
 *   - `inorder(root->left)`, process `root->data`, `inorder(root->right)`.
 * - Iterative Stack:
 *   - Why? Avoids recursion call-stack overflow on deeply skewed trees (e.g. depth 10^5).
 *   - Drill as far left as possible, pushing every node onto a stack.
 *   - When null is reached, pop top node, record its value, and transition to its right child (`curr = curr->right`).
 * 
 * TIME COMPLEXITY:
 * - O(N): Each node is visited once.
 * 
 * SPACE COMPLEXITY:
 * - O(H) for both recursion call stack and iterative stack.
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

// 1. Recursive Approach
void inorderRecursiveHelper(Node* root, std::vector<int>& res) {
    if (!root) return;
    inorderRecursiveHelper(root->left, res);
    res.push_back(root->data);
    inorderRecursiveHelper(root->right, res);
}

std::vector<int> inorderRecursive(Node* root) {
    std::vector<int> res;
    inorderRecursiveHelper(root, res);
    return res;
}

// 2. Iterative Approach using Stack
std::vector<int> inorderIterative(Node* root) {
    std::vector<int> res;
    std::stack<Node*> st;
    Node* curr = root;

    while (curr != nullptr || !st.empty()) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Drill down to the leftmost unvisited node, pushing all ancestors onto the stack.
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }

        // Pop the leftmost node, visit it, then explore its right subtree
        curr = st.top();
        st.pop();
        res.push_back(curr->data);

        curr = curr->right;
    }

    return res;
}

int main() {
    //      1
    //    /   \
    //   2     3
    //  / \
    // 4   5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    std::vector<int> rec = inorderRecursive(root);
    std::cout << "Inorder (Recursive): ";
    for (int x : rec) std::cout << x << " ";
    std::cout << "\n"; // 4 2 5 1 3

    std::vector<int> it = inorderIterative(root);
    std::cout << "Inorder (Iterative): ";
    for (int x : it) std::cout << x << " ";
    std::cout << "\n"; // 4 2 5 1 3

    return 0;
}
