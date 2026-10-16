/**
 * Problem: Merge Two BSTs
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Merge 2 sorted arrays", we merged contiguous flat arrays.
 * - Here, we merge two separate 2D hierarchical Binary Search Trees into a single sorted sequence
 *   (and optionally construct a unified balanced BST).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Two-Pointer Inorder Merge:
 *   1. Extract Inorder traversal of BST 1 into `in1` (automatically sorted in O(M) time).
 *   2. Extract Inorder traversal of BST 2 into `in2` (automatically sorted in O(N) time).
 *   3. Merge `in1` and `in2` into a single combined sorted array `merged` using the two-pointer technique in O(M + N) time.
 *   4. (Optional): Construct a new perfectly balanced BST from `merged` in O(M + N) using binary divide-and-conquer.
 * 
 * TIME COMPLEXITY:
 * - O(M + N): Traversing both trees takes O(M + N); two-pointer merge takes O(M + N).
 * 
 * SPACE COMPLEXITY:
 * - O(M + N) auxiliary space for sorted vectors.
 */

#include <iostream>
#include <vector>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void inorder(Node* root, std::vector<int>& res) {
    if (!root) return;
    inorder(root->left, res);
    res.push_back(root->data);
    inorder(root->right, res);
}

std::vector<int> merge(Node* root1, Node* root2) {
    std::vector<int> in1, in2;
    inorder(root1, in1);
    inorder(root2, in2);

    // Merge two sorted arrays using two pointers
    std::vector<int> merged;
    int i = 0, j = 0;
    int n1 = in1.size(), n2 = in2.size();

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Standard two-pointer merge merges the two independent Inorder streams in linear O(M + N) time.
    while (i < n1 && j < n2) {
        if (in1[i] <= in2[j]) {
            merged.push_back(in1[i++]);
        } else {
            merged.push_back(in2[j++]);
        }
    }

    while (i < n1) merged.push_back(in1[i++]);
    while (j < n2) merged.push_back(in2[j++]);

    return merged;
}

int main() {
    // BST 1:
    //      5
    //     / \
    //    3   6
    //   / \
    //  2   4
    Node* root1 = new Node(5);
    root1->left = new Node(3);
    root1->right = new Node(6);
    root1->left->left = new Node(2);
    root1->left->right = new Node(4);

    // BST 2:
    //      2
    //     / \
    //    1   3
    //         \
    //          7
    //         /
    //        6
    Node* root2 = new Node(2);
    root2->left = new Node(1);
    root2->right = new Node(3);
    root2->right->right = new Node(7);
    root2->right->right->left = new Node(6);

    std::vector<int> merged = merge(root1, root2);
    std::cout << "Merged BST elements in sorted order: ";
    for (int x : merged) std::cout << x << " ";
    std::cout << "\n"; // 1 2 2 3 3 4 5 6 6 7

    return 0;
}
