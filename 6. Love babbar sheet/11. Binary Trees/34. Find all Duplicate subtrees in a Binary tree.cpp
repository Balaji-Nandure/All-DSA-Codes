/**
 * Problem: Find All Duplicate Subtrees in a Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In Problem 24 ("Check if duplicate subtree of size >= 2 exists"), we only returned a boolean flag.
 * - Here, we must RETURN THE ROOT POINTER of each duplicate subtree category, ensuring each distinct duplicate
 *   pattern is included in the output exactly ONCE.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Subtree Serialization + Exact-Count Deduplication:
 *   - Serialize each subtree into a canonical unique string:
 *     `s = to_string(root->data) + "," + serialize(left) + "," + serialize(right)`.
 *   - Null children are encoded as `"#"`.
 *   - Track frequency in `unordered_map<string, int> countMap`:
 *     - Increment `countMap[s]++`.
 *     - If `countMap[s] == 2`: Add `root` to `result`!
 *       (Checking strictly for `== 2` ensures that if a duplicate appears 3, 4, or more times, its root
 *        is captured in the result exactly once!).
 * 
 * TIME COMPLEXITY:
 * - O(N): Traverses each node once, building subtree signatures.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for storing serialization strings in hash map.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

std::string serialize(Node* root, std::unordered_map<std::string, int>& countMap, std::vector<Node*>& duplicates) {
    if (!root) return "#";

    std::string left = serialize(root->left, countMap, duplicates);
    std::string right = serialize(root->right, countMap, duplicates);

    std::string s = std::to_string(root->data) + "," + left + "," + right;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Add to result when count becomes EXACTLY 2 to avoid duplicate entries for triplets/quadruplets.
    countMap[s]++;
    if (countMap[s] == 2) {
        duplicates.push_back(root);
    }

    return s;
}

std::vector<Node*> printAllDups(Node* root) {
    std::unordered_map<std::string, int> countMap;
    std::vector<Node*> duplicates;
    serialize(root, countMap, duplicates);
    return duplicates;
}

int main() {
    //        1
    //       / \
    //      2   3
    //     /   / \
    //    4   2   4
    //       /
    //      4
    // Duplicate subtrees: Node 4 (leaf) and Subtree 2->4
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->right->left = new Node(2);
    root->right->right = new Node(4);
    root->right->left->left = new Node(4);

    std::vector<Node*> dups = printAllDups(root);
    std::cout << "Roots of duplicate subtrees: ";
    for (Node* node : dups) {
        std::cout << node->data << " ";
    }
    std::cout << "\n"; // 4 2

    return 0;
}
