/*
    Problem Name: Duplicate Subtree Check
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree, determine whether the tree contains any duplicate
    subtree of size 2 or more (not just a single leaf). Two subtrees are duplicates if
    they have the same structure and identical node values.
    Return true if a duplicate subtree exists, otherwise false.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node once and
                     hash map operations are O(1) amortized.
    Space Complexity: O(N), for the hash map storing serialized subtree strings.

    Love Babbar Style Approach:
    The KEY insight — SERIALIZE each subtree into a unique string, and use a HashMap
    to detect duplicates!

    If we do a POSTORDER traversal (Left-Right-Node), at each node we can build a string
    that represents the ENTIRE subtree rooted there. If two subtrees produce the SAME
    string, they're structurally identical with the same values → DUPLICATE!

    How to serialize a subtree:
        serialize(node) = serialize(left) + "," + serialize(right) + "," + node->data
        serialize(NULL) = "#"  (a special marker for empty nodes)

    WHY commas? Without delimiters, "1,2" and "12" would be ambiguous!
    WHY "#" for NULL? It distinguishes different structures — e.g., a node with only a
    left child vs only a right child.

    WHY Postorder? Because by the time we process a node, its children are already
    serialized, so we can BUILD the full subtree string bottom-up.

    IMPORTANT: We skip single-leaf subtrees (size 1) by only checking for duplicates
    when the node has at LEAST one child.

    Dry Run:
    Tree:        1
                / \
               2   3
              / \    \
             4   5    2
                     / \
                    4   5

    Postorder serialization:
    - Node(4, left leaf):  "#,#,4"
    - Node(5, left leaf):  "#,#,5"
    - Node(2, left):       "#,#,4,#,#,5,2"  ← subtree (2,4,5)
    - Node(4, right leaf): "#,#,4"
    - Node(5, right leaf): "#,#,5"
    - Node(2, right):      "#,#,4,#,#,5,2"  ← subtree (2,4,5) SAME STRING!
    - DUPLICATE FOUND at "#,#,4,#,#,5,2" → return true ✓

    Note: "#,#,4" and "#,#,5" also appear twice (leaf nodes 4 and 5), but we SKIP
    single-leaf subtrees since they have size 1. We only flag subtrees of size ≥ 2.
*/

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// Definition for a binary tree node.
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

class Solution {
private:
    // Returns the serialized string of the subtree rooted at this node.
    // Updates `found` to true if a duplicate subtree of size >= 2 is detected.
    string solve(Node* root, unordered_map<string, int>& subtreeCount, bool& found) {
        // Base Case: NULL node is represented as "#"
        if (root == NULL) return "#";

        // 1. POSTORDER: Serialize left and right subtrees first
        string leftStr  = solve(root->left,  subtreeCount, found);
        string rightStr = solve(root->right, subtreeCount, found);

        // 2. Build THIS subtree's unique serialized string
        string currStr = leftStr + "," + rightStr + "," + to_string(root->data);

        // 3. Only check for duplicates if subtree size >= 2 (at least one child exists)
        //    A leaf node has serialization "#,#,val" — we skip those!
        if (root->left != NULL || root->right != NULL) {
            subtreeCount[currStr]++;

            // If this exact serialization has been seen BEFORE → DUPLICATE!
            if (subtreeCount[currStr] == 2) {
                found = true;
            }
        }

        return currStr;
    }

public:
    // GFG Signature
    bool dupSub(Node* root) {
        unordered_map<string, int> subtreeCount;
        bool found = false;

        solve(root, subtreeCount, found);

        return found;
    }
};

int main() {
    // Example 1:
    //     1
    //    / \
    //   2   3
    // Expected: false (no duplicate subtrees of size >= 2)

    Node* root1 = new Node(1);
    root1->left  = new Node(2);
    root1->right = new Node(3);

    Solution ob;
    // Output: false
    cout << "Duplicate Subtree (Example 1): " << (ob.dupSub(root1) ? "true" : "false") << "\n";

    // Example 2:
    //          1
    //         / \
    //        2   3
    //       / \    \
    //      4   5    2
    //              / \
    //             4   5
    // Expected: true (subtree rooted at node 2 with children 4,5 appears TWICE!)

    Node* root2 = new Node(1);
    root2->left              = new Node(2);
    root2->right             = new Node(3);
    root2->left->left        = new Node(4);
    root2->left->right       = new Node(5);
    root2->right->right      = new Node(2);
    root2->right->right->left  = new Node(4);
    root2->right->right->right = new Node(5);

    // Output: true
    cout << "Duplicate Subtree (Example 2): " << (ob.dupSub(root2) ? "true" : "false") << "\n";

    return 0;
}
