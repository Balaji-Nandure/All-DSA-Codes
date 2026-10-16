/**
 * Problem: Construct Binary Tree from Inorder and Preorder Traversal
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Construct Binary Tree from String with Bracket Representation", parentheses explicitly marked subtree boundaries.
 * - Here, we synthesize two flat 1D projections (Inorder and Preorder) to uniquely reconstruct the 2D tree topology.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Hash Map Lookup + Divide-and-Conquer:
 *   - Preorder Property: The very first element in `preorder` is always the ROOT of the current tree/subtree.
 *   - Inorder Property: Searching for this root in `inorder` cleanly divides the remaining elements:
 *     - All elements strictly to its left belong to the LEFT subtree.
 *     - All elements strictly to its right belong to the RIGHT subtree.
 *   - By pre-indexing `inorder` elements into a Hash Map `inMap[val] -> index`, locating the root takes O(1) time.
 *   - Recursively build:
 *     1. `root->left = build(inStart, rootIndex - 1)`
 *     2. `root->right = build(rootIndex + 1, inEnd)`
 * 
 * TIME COMPLEXITY:
 * - O(N): Hash map builds in O(N); each node is constructed in O(1).
 * 
 * SPACE COMPLEXITY:
 * - O(N) for hash map and tree nodes.
 */

#include <iostream>
#include <vector>
#include <unordered_map>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* buildTreeHelper(const std::vector<int>& preorder, int& preIndex, int inStart, int inEnd,
                     const std::unordered_map<int, int>& inMap) {
    if (inStart > inEnd) return nullptr;

    // The current element in preorder is the root of the current subtree
    int rootVal = preorder[preIndex++];
    Node* root = new Node(rootVal);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Locate root in inorder: everything to the left is left subtree; everything to the right is right subtree.
    int mid = inMap.at(rootVal);

    root->left = buildTreeHelper(preorder, preIndex, inStart, mid - 1, inMap);
    root->right = buildTreeHelper(preorder, preIndex, mid + 1, inEnd, inMap);

    return root;
}

Node* buildTree(const std::vector<int>& inorder, const std::vector<int>& preorder, int n) {
    std::unordered_map<int, int> inMap;
    for (int i = 0; i < n; i++) {
        inMap[inorder[i]] = i;
    }
    int preIndex = 0;
    return buildTreeHelper(preorder, preIndex, 0, n - 1, inMap);
}

void printPostorder(Node* root) {
    if (!root) return;
    printPostorder(root->left);
    printPostorder(root->right);
    std::cout << root->data << " ";
}

int main() {
    std::vector<int> inorder = {3, 1, 4, 0, 5, 2};
    std::vector<int> preorder = {0, 1, 3, 4, 2, 5};
    int n = inorder.size();

    Node* root = buildTree(inorder, preorder, n);
    std::cout << "Postorder of constructed tree: ";
    printPostorder(root); // 3 4 1 5 2 0
    std::cout << "\n";

    return 0;
}
