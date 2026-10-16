/**
 * Problem: Postorder Traversal (Recursive and Iterative)
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Preorder visits root first; Inorder visits root in the middle.
 * - Postorder visits the ROOT LAST: Left -> Right -> Root.
 * - In iterative postorder, a node must only be processed AFTER both of its subtrees have been completely traversed.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Method 1: Two Stacks (Most Intuitive Iterative Postorder):
 *   - Notice that modified preorder produces: Root -> Right -> Left.
 *   - Pushing this sequence into a second stack `s2` reverses it into: Left -> Right -> Root (Postorder)!
 *   - Algorithm:
 *     - Push root to `s1`.
 *     - While `s1` not empty:
 *       - Pop `curr` from `s1`, push `curr` to `s2`.
 *       - Push `curr->left` to `s1`, then push `curr->right` to `s1`.
 *     - Pop all elements from `s2`.
 * - Method 2: Single Stack:
 *   - Uses a `lastVisited` pointer to know whether we are returning from right child or visiting it.
 * 
 * TIME COMPLEXITY:
 * - O(N): Every node is visited once.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for stacks / recursion stack.
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
void postorderRecursiveHelper(Node* root, std::vector<int>& res) {
    if (!root) return;
    postorderRecursiveHelper(root->left, res);
    postorderRecursiveHelper(root->right, res);
    res.push_back(root->data);
}

std::vector<int> postorderRecursive(Node* root) {
    std::vector<int> res;
    postorderRecursiveHelper(root, res);
    return res;
}

// 2. Iterative Approach using Two Stacks
std::vector<int> postorderTwoStacks(Node* root) {
    std::vector<int> res;
    if (!root) return res;

    std::stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* curr = s1.top();
        s1.pop();
        s2.push(curr);

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Push left first then right to s1, so right is processed first into s2 (Root -> Right -> Left in s2).
        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }

    // Unloading s2 reverses (Root -> Right -> Left) into (Left -> Right -> Root)
    while (!s2.empty()) {
        res.push_back(s2.top()->data);
        s2.pop();
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

    std::vector<int> rec = postorderRecursive(root);
    std::cout << "Postorder (Recursive): ";
    for (int x : rec) std::cout << x << " ";
    std::cout << "\n"; // 4 5 2 3 1

    std::vector<int> it = postorderTwoStacks(root);
    std::cout << "Postorder (Iterative 2-Stack): ";
    for (int x : it) std::cout << x << " ";
    std::cout << "\n"; // 4 5 2 3 1

    return 0;
}
