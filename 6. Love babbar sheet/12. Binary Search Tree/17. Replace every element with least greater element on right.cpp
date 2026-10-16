/**
 * Problem: Replace every element with least greater element on its right
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - "Next Greater Element" in Stacks looked for the FIRST larger element sequentially to the right.
 * - Here, we look for the LEAST (smallest) element among ALL elements to the right that is strictly greater
 *   than `arr[i]`, regardless of its index position.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Reverse Traversal with BST Inorder Successor Insertion:
 *   - Traverse array from right to left (from index N-1 down to 0).
 *   - Maintain a dynamic Binary Search Tree (or Self-Balancing BST / `std::set`).
 *   - For each element `arr[i]`:
 *     - Insert `arr[i]` into the BST:
 *       - Whenever we branch LEFT (`arr[i] < curr->data`), `curr` becomes a candidate for the least greater element!
 *       - Whenever we branch RIGHT, continue without updating candidate.
 *     - The final candidate recorded when insertion terminates is the exact Inorder Successor!
 *     - If no left branch was taken, no greater element exists on the right -> `-1`.
 * 
 * TIME COMPLEXITY:
 * - O(N log N): N insertions into a balanced BST / set.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for the BST nodes / set.
 */

#include <iostream>
#include <vector>
#include <set>

// Custom BST Node Implementation
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

BSTNode* insertBST(BSTNode* root, int val, BSTNode*& succ) {
    if (!root) {
        return new BSTNode(val);
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // When branching left, current node is strictly greater than val and acts as candidate successor.
    if (val < root->data) {
        succ = root;
        root->left = insertBST(root->left, val, succ);
    } else {
        root->right = insertBST(root->right, val, succ);
    }

    return root;
}

std::vector<int> findLeastGreater(const std::vector<int>& arr, int n) {
    std::vector<int> res(n);
    BSTNode* root = nullptr;

    // Traverse from right to left
    for (int i = n - 1; i >= 0; i--) {
        BSTNode* succ = nullptr;
        root = insertBST(root, arr[i], succ);
        res[i] = succ ? succ->data : -1;
    }

    return res;
}

// Equivalent modern STL approach using std::set
std::vector<int> findLeastGreaterSTL(const std::vector<int>& arr, int n) {
    std::vector<int> res(n);
    std::set<int> s;

    for (int i = n - 1; i >= 0; i--) {
        auto it = s.upper_bound(arr[i]);
        res[i] = (it != s.end()) ? *it : -1;
        s.insert(arr[i]);
    }

    return res;
}

int main() {
    std::vector<int> arr = {8, 58, 71, 18, 31, 32, 63, 92, 43, 3, 91, 93, 25, 80, 28};
    int n = arr.size();

    std::vector<int> res = findLeastGreater(arr, n);
    std::cout << "Least Greater Elements on right:\n";
    for (int x : res) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    // 18 63 80 25 32 43 80 93 80 25 93 -1 28 -1 -1

    return 0;
}
