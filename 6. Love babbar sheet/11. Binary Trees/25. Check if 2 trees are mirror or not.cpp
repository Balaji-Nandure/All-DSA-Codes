/**
 * Problem: Check if 2 Trees are Mirror of Each Other
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Mirror of a tree", we mutated a single tree in-place to create its reflection.
 * - Here, we perform a dual-traversal symmetry test to verify if two independent trees (binary or N-ary)
 *   are identical reflections of each other across their central axis.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Part 1: Binary Tree Formulation:
 *   - Two binary trees `T1` and `T2` are mirror images if:
 *     1. Their root values are equal: `T1->data == T2->data`.
 *     2. Left subtree of `T1` is a mirror of Right subtree of `T2`: `isMirror(T1->left, T2->right)`.
 *     3. Right subtree of `T1` is a mirror of Left subtree of `T2`: `isMirror(T1->right, T2->left)`.
 * - Part 2: N-ary Tree Formulation (GFG representation):
 *   - Represented as edge lists for N nodes with E edges.
 *   - For each node `u`, the child sequence in Tree 1 must match the REVERSED child sequence in Tree 2.
 *   - Store Tree 1's children in a stack (`std::stack<int>`) and compare with Tree 2's sequential edges.
 * 
 * TIME COMPLEXITY:
 * - O(N): Visits each node/edge once.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

// Binary Tree Node Structure
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Binary Tree check
bool isMirrorBinary(Node* t1, Node* t2) {
    if (!t1 && !t2) return true;
    if (!t1 || !t2) return false;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Symmetrical cross-comparison: t1's left child matches t2's right child, and vice versa!
    return (t1->data == t2->data) &&
           isMirrorBinary(t1->left, t2->right) &&
           isMirrorBinary(t1->right, t2->left);
}

// N-ary Tree check (edge list representation)
int checkMirrorTreeNary(int n, int e, int A[], int B[]) {
    std::unordered_map<int, std::stack<int>> mp;

    // Push tree 1's children into stack for each parent
    for (int i = 0; i < 2 * e; i += 2) {
        mp[A[i]].push(A[i + 1]);
    }

    // Compare with tree 2's children (LIFO stack pops in reverse order)
    for (int i = 0; i < 2 * e; i += 2) {
        int u = B[i];
        int v = B[i + 1];

        if (mp[u].empty() || mp[u].top() != v) {
            return 0; // Not a mirror
        }
        mp[u].pop();
    }

    return 1;
}

int main() {
    // Binary Tree Example:
    Node* t1 = new Node(1);
    t1->left = new Node(2);
    t1->right = new Node(3);

    Node* t2 = new Node(1);
    t2->left = new Node(3);
    t2->right = new Node(2);

    std::cout << "Binary trees are mirror: " 
              << (isMirrorBinary(t1, t2) ? "Yes" : "No") << "\n"; // Yes

    // N-ary Tree Example:
    int n = 3, e = 2;
    int A[] = {1, 2, 1, 3};
    int B[] = {1, 3, 1, 2};
    std::cout << "N-ary trees are mirror: " 
              << (checkMirrorTreeNary(n, e, A, B) ? "Yes" : "No") << "\n"; // Yes

    return 0;
}
