/**
 * Problem: Minimum swaps required to convert Binary tree into BST
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Tree modifications previously rearranged pointers or node values directly.
 * - Here, we identify a profound property: A Binary Tree is a valid BST IF AND ONLY IF its Inorder
 *   traversal produces a strictly sorted array!
 * - This reduces a seemingly complex 2D tree topology problem into 1D Cycle Decomposition of Permutations.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Inorder Extraction + Disjoint Cycle Counting:
 *   1. Extract the Inorder traversal of the given binary tree into an array `inorder`.
 *   2. For the tree to be a BST, `inorder` must become sorted.
 *   3. Minimum swaps to sort an array:
 *      - Pair elements with their original indices: `vec[i] = {inorder[i], i}`.
 *      - Sort `vec` by values.
 *      - Model the displacement as a permutation graph of disjoint directed cycles.
 *      - For every cycle of length `L`, exactly `(L - 1)` swaps are necessary and sufficient
 *        to place all `L` elements into their correct positions!
 *      - Total minimum swaps = `sum(cycle_length - 1)` for all cycles.
 * 
 * TIME COMPLEXITY:
 * - O(N log N): Inorder extraction is O(N); sorting pairs takes O(N log N); cycle traversal is O(N).
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for inorder array and visited cycle tracking.
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Inorder traversal of tree represented as 1-based or 0-based array (left = 2*i + 1, right = 2*i + 2)
void getInorder(const std::vector<int>& tree, int index, int n, std::vector<int>& inorder) {
    if (index >= n) return;
    getInorder(tree, 2 * index + 1, n, inorder);
    inorder.push_back(tree[index]);
    getInorder(tree, 2 * index + 2, n, inorder);
}

int minSwapsToSort(std::vector<int>& arr, int n) {
    std::vector<std::pair<int, int>> pairs(n);
    for (int i = 0; i < n; i++) {
        pairs[i] = {arr[i], i};
    }

    std::sort(pairs.begin(), pairs.end());

    std::vector<bool> visited(n, false);
    int totalSwaps = 0;

    for (int i = 0; i < n; i++) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Each permutation cycle of size L requires exactly (L - 1) swaps to place all elements in order.
        if (visited[i] || pairs[i].second == i) {
            continue;
        }

        int cycleSize = 0;
        int j = i;
        while (!visited[j]) {
            visited[j] = true;
            j = pairs[j].second;
            cycleSize++;
        }

        if (cycleSize > 1) {
            totalSwaps += (cycleSize - 1);
        }
    }

    return totalSwaps;
}

int minSwapsToBST(const std::vector<int>& tree, int n) {
    std::vector<int> inorder;
    getInorder(tree, 0, n, inorder);
    return minSwapsToSort(inorder, n);
}

int main() {
    // Binary tree array: root at 0, left at 2*i+1, right at 2*i+2
    //        5
    //      /   \
    //     6     7
    //    / \   / \
    //   8   9 10 11
    std::vector<int> tree = {5, 6, 7, 8, 9, 10, 11};
    int n = tree.size();

    std::cout << "Minimum swaps to convert tree into BST: " << minSwapsToBST(tree, n) << "\n"; // 3

    return 0;
}
