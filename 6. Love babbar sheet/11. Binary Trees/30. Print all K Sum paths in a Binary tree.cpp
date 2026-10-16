/**
 * Problem: Print all "K" Sum Paths in a Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Sum of Nodes on Longest path from root to leaf node", paths were strictly root-to-leaf.
 * - Here, paths can start at ANY arbitrary ancestor node and end at ANY descendant node,
 *   as long as the direction of movement is strictly downward (parent to child).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Path Vector Backtracking (Suffix Sum Verification):
 *   - Maintain a running vector `path` representing the current branch from the root down to node `curr`.
 *   - At each visited node:
 *     1. Append `curr->data` to `path`.
 *     2. Recursively explore left and right children.
 *     3. Suffix Sum Check:
 *        - Iterate backwards from the end of `path` towards index 0, accumulating sum.
 *        - Whenever `subSum == K`, the slice from index `j` to `path.size() - 1` constitutes a valid K-sum path!
 *     4. Backtrack: Remove `curr->data` from `path` before returning to parent.
 * 
 * TIME COMPLEXITY:
 * - O(N * H): At each of the N nodes, checking backwards takes at most O(H) steps.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Auxiliary vector `path` has size bounded by tree height H.
 */

#include <iostream>
#include <vector>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void printVector(const std::vector<int>& path, int start, int end) {
    for (int i = start; i <= end; i++) {
        std::cout << path[i] << " ";
    }
    std::cout << "\n";
}

void printKPathUtil(Node* root, std::vector<int>& path, int k) {
    if (!root) return;

    // Add current node to path
    path.push_back(root->data);

    // Recurse left and right
    printKPathUtil(root->left, path, k);
    printKPathUtil(root->right, path, k);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Check all subpaths ending at the current node by accumulating suffix sums backwards.
    int sum = 0;
    for (int j = (int)path.size() - 1; j >= 0; j--) {
        sum += path[j];

        if (sum == k) {
            printVector(path, j, (int)path.size() - 1);
        }
    }

    // Backtrack
    path.pop_back();
}

void printKPath(Node* root, int k) {
    std::vector<int> path;
    printKPathUtil(root, path, k);
}

int main() {
    //        1
    //       / \
    //      3  -1
    //     / \  / \
    //    2   1 4  5
    //       / / \  \
    //      1 1   2  6
    Node* root = new Node(1);
    root->left = new Node(3);
    root->right = new Node(-1);
    root->left->left = new Node(2);
    root->left->right = new Node(1);
    root->left->right->left = new Node(1);
    root->right->left = new Node(4);
    root->right->left->left = new Node(1);
    root->right->left->right = new Node(2);
    root->right->right = new Node(5);
    root->right->right->right = new Node(6);

    int k = 5;
    std::cout << "All paths with sum " << k << ":\n";
    printKPath(root, k);

    return 0;
}
