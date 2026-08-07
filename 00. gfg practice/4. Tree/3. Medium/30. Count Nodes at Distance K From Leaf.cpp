/*
    Problem Name: Count Nodes at Distance K From Leaf
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary tree with n nodes and a non-negative integer k, count the number of special nodes.
    A node is considered special if there exists at least one leaf in its subtree such that
    the distance between the node and the leaf is exactly k.
    Any such node should be counted ONLY ONCE even if it is at distance k from multiple leaves.

    Examples:
    Input: root[] = [1, 2, 3, 4, 5, 6, 7, N, N, N, N, N, 8], k = 2
    Output: 2
    Explanation:
    Special nodes are:
    - Node 1: distance 2 from leaves 4, 5, and 7.
    - Node 3: distance 2 from leaf 8.
    Total unique special nodes = 2.

    Constraints:
    1 <= n <= 10^5
    1 <= k <= n
    1 <= root->data <= 10^5

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node once during DFS.
    Space Complexity: O(H), where H is the height of the tree, for the path vector and recursion stack.

    Love Babbar Style Approach:
    Path Array + DFS Backtracking:

    1. INTUITION:
       - As we traverse down from the root to any leaf node, we keep track of all ancestors
         on the current path in a `path` vector.
       - When we reach a LEAF node (node with no left or right child):
         * The ancestor node at distance `k` above this leaf will be located at index:
           `path.size() - 1 - k` (if valid index >= 0).
       - To avoid counting the same ancestor node multiple times (when multiple leaves share
         the same ancestor at distance k), we store unique special nodes in an `unordered_set`
         or set a boolean flag on visited path nodes.

    2. ALGORITHM:
       - Maintain a `path` vector to store nodes along the path from root to current node.
       - Maintain an `unordered_set<Node*>` (or vector of count) to store unique special ancestor nodes.
       - At current `node`:
         * Push `node` into `path`.
         * If `node` is a leaf (`!node->left && !node->right`):
           - Check if `path.size() - 1 - k >= 0`.
           - If yes, `path[path.size() - 1 - k]` is a special node! Add it to set.
         * Recursively call for `node->left` and `node->right`.
         * Backtrack: Pop `node` from `path`.

    Dry Run:
              1
           /     \
          2       3
         / \     / \
        4   5   6   7
                     \
                      8
    k = 2

    - Path to Leaf 4: [1, 2, 4] | len=3 | ancestor at len-1-2 = index 0 -> Node 1 (Add Node 1)
    - Path to Leaf 5: [1, 2, 5] | len=3 | index 0 -> Node 1 (Already in set)
    - Path to Leaf 6: [1, 3, 6] | len=3 | index 0 -> Node 1 (Already in set)
    - Path to Leaf 8: [1, 3, 7, 8] | len=4 | len-1-2 = index 1 -> Node 3 (Add Node 3)

    Unique special nodes: {Node 1, Node 3} -> Total Count = 2.
*/

#include <iostream>
#include <vector>
#include <unordered_set>

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
    void solve(Node* root, int k, vector<Node*>& path, unordered_set<Node*>& specialNodes) {
        if (root == NULL) return;

        // Add current node to path
        path.push_back(root);

        // Check if current node is a leaf node
        if (root->left == NULL && root->right == NULL) {
            int n = path.size();
            // Check if an ancestor exists at distance k
            if (n - 1 - k >= 0) {
                specialNodes.insert(path[n - 1 - k]);
            }
        }

        // Traverse left and right subtrees
        solve(root->left, k, path, specialNodes);
        solve(root->right, k, path, specialNodes);

        // Backtrack
        path.pop_back();
    }

public:
    // GFG Signature
    int printKDistantfromLeaf(Node* root, int k) {
        vector<Node*> path;
        unordered_set<Node*> specialNodes;

        solve(root, k, path, specialNodes);

        return specialNodes.size();
    }
};

int main() {
    Solution ob;

    // Example 1:
    //            1
    //         /     \
    //        2       3
    //       / \     / \
    //      4   5   6   7
    //                   \
    //                    8
    // k = 2  --> Expected Output: 2

    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);
    root1->right->left = new Node(6);
    root1->right->right = new Node(7);
    root1->right->right->right = new Node(8);

    int k1 = 2;
    cout << "Example 1 (k = 2) Count: " << ob.printKDistantfromLeaf(root1, k1) << "\n";

    // Example 2:
    //      1
    //     /
    //    2
    //   /
    //  3
    // k = 1  --> Expected Output: 2 (Node 2 for leaf 3, Node 1 for leaf 3? Distance 1 from leaf 3 is node 2, distance 1 from leaf 2? 2 is not a leaf)
    // Leaf = 3. Distance 1 ancestor = 2. Total special nodes = 1.
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->left->left = new Node(3);

    int k2 = 1;
    cout << "Example 2 (k = 1) Count: " << ob.printKDistantfromLeaf(root2, k2) << "\n";

    return 0;
}
