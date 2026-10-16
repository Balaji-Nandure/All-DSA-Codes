/**
 * Problem: Preorder Traversal (Recursive and Iterative)
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In Inorder, root was processed between left and right subtrees.
 * - In Preorder, the ROOT is visited FIRST, before any of its subtrees: Root -> Left -> Right.
 * - In iterative preorder, stack order must be inverted: pushing right child before left child.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Recursive:
 *   - Visit `root->data`, then recurse `preorder(root->left)`, then `preorder(root->right)`.
 * - Iterative Stack:
 *   - Push root onto stack.
 *   - While stack is not empty:
 *     - Pop `curr` and visit `curr->data`.
 *     - If `curr->right` exists, push `curr->right`.
 *     - If `curr->left` exists, push `curr->left`.
 *     - Why right before left? Because stack is LIFO: pushing right first ensures that the left child
 *       sits at the top of the stack and is processed immediately next!
 * 
 * TIME COMPLEXITY:
 * - O(N): Every node is visited once.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Stack memory proportional to height of tree.
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
void preorderRecursiveHelper(Node* root, std::vector<int>& res) {
    if (!root) return;
    res.push_back(root->data);
    preorderRecursiveHelper(root->left, res);
    preorderRecursiveHelper(root->right, res);
}

std::vector<int> preorderRecursive(Node* root) {
    std::vector<int> res;
    preorderRecursiveHelper(root, res);
    return res;
}

// 2. Iterative Approach using Stack
std::vector<int> preorderIterative(Node* root) {
    std::vector<int> res;
    if (!root) return res;

    std::stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* curr = st.top();
        st.pop();

        res.push_back(curr->data);

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Push RIGHT child first so that the LEFT child remains on top of LIFO stack to be visited next.
        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);
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

    std::vector<int> rec = preorderRecursive(root);
    std::cout << "Preorder (Recursive): ";
    for (int x : rec) std::cout << x << " ";
    std::cout << "\n"; // 1 2 4 5 3

    std::vector<int> it = preorderIterative(root);
    std::cout << "Preorder (Iterative): ";
    for (int x : it) std::cout << x << " ";
    std::cout << "\n"; // 1 2 4 5 3

    return 0;
}
