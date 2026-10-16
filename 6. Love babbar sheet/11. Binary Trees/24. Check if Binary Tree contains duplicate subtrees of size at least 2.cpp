/**
 * Problem: Check if Binary Tree contains duplicate subtrees of size >= 2
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Tree comparisons previously compared two trees globally against each other.
 * - Here, we perform an INTRA-TREE pattern recognition: detecting if any two disconnected subtrees
 *   within the SAME tree share an identical topological structure and node values (excluding trivial single-node leaves).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Subtree Serialization with Hash Map:
 *   - Each subtree can be uniquely characterized by its post-order serialization string:
 *     `str = to_string(root->data) + "," + serialize(left) + "," + serialize(right)`.
 *   - Null children are encoded as `"$"`.
 *   - Leaf nodes produce a 3-character string like `"X,$,$"`. Trivial single leaves are excluded.
 *   - For any non-leaf subtree:
 *     - If `str` is already present in `unordered_map<string, int> subtrees`, a duplicate subtree exists!
 *     - Increment frequency in hash map and flag duplicate detection.
 * 
 * TIME COMPLEXITY:
 * - O(N): Traverses each node once, serializing subtrees.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for storing subtree serialization strings in the map.
 */

#include <iostream>
#include <string>
#include <unordered_map>

struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

std::string serializeSubtrees(Node* root, std::unordered_map<std::string, int>& subtrees, bool& hasDuplicate) {
    if (!root) return "$";

    std::string left = serializeSubtrees(root->left, subtrees, hasDuplicate);
    std::string right = serializeSubtrees(root->right, subtrees, hasDuplicate);

    // Current subtree serialization
    std::string s = "";
    s += root->data;
    s += "," + left;
    s += "," + right;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Only check subtrees of size >= 2 (exclude single leaf nodes whose left and right are both "$").
    if (left != "$" || right != "$") {
        subtrees[s]++;
        if (subtrees[s] >= 2) {
            hasDuplicate = true;
        }
    }

    return s;
}

bool dupSub(Node* root) {
    std::unordered_map<std::string, int> subtrees;
    bool hasDuplicate = false;
    serializeSubtrees(root, subtrees, hasDuplicate);
    return hasDuplicate;
}

int main() {
    // Tree containing duplicate subtree D -> (E, F):
    //        A
    //      /   \
    //     B     C
    //    / \     \
    //   D   E     B
    //            / \
    //           D   E
    Node* root = new Node('A');
    root->left = new Node('B');
    root->right = new Node('C');
    root->left->left = new Node('D');
    root->left->right = new Node('E');
    root->right->right = new Node('B');
    root->right->right->left = new Node('D');
    root->right->right->right = new Node('E');

    std::cout << "Contains duplicate subtree of size >= 2: " 
              << (dupSub(root) ? "Yes" : "No") << "\n"; // Yes

    return 0;
}
