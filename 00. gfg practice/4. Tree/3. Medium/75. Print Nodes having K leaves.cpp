/*
    Problem Name: Print Nodes having K leaves
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree and an integer k, find all nodes whose subtree contains
    exactly k leaf nodes.
    - Return the node values in the order they appear in Postorder traversal.
    - Leaf nodes themselves are not considered to have subtrees below them.
    - If no such node exists, return [-1].

    Examples:
    Input: root[] = [0, 1, 2], k = 1
    Output: [-1]
    Explanation:
          0
        /   \
       1     2
    Nodes 1 and 2 are leaf nodes. Node 0 has 2 leaves. No node has 1 leaf in its subtree.

    Input: root[] = [0, 1, 2, N, N, 4, N, 5, 9], k = 2
    Output: [4, 2]
    Explanation:
          0
        /   \
       1     2
            /
           4
          / \
         5   9
    - Subtree rooted at 4 has 2 leaves (5, 9).
    - Subtree rooted at 2 has 2 leaves (5, 9).
    Postorder traversal order: [4, 2].

    Constraints:
    1 <= n, k <= 2 * 10^4
    0 <= node->data <= 10^4

    Expected Complexities:
    Time Complexity: O(N), postorder DFS visits each node once.
    Space Complexity: O(H), for recursion call stack.

    Love Babbar Style Approach:
    Bottom-Up Postorder DFS (Leaf Count Accumulation):

    1. INTUITION:
       - To count the number of leaves in the subtree of any node `root`:
         * Leaf node (`!root->left && !root->right`): contributes 1 leaf to its parent, returns 1.
         * Internal node: total leaves = `leftLeaves + rightLeaves`.
       - Using Postorder DFS (Left -> Right -> Root):
         * Compute `leftLeaves` from `root->left`.
         * Compute `rightLeaves` from `root->right`.
         * `totalLeaves = leftLeaves + rightLeaves`.
         * If `totalLeaves == k`, record `root->data` into `ans`.
         * This naturally records nodes in Postorder traversal order!
       - If no node matches (`ans.empty()`), return `{-1}`.

    2. ALGORITHM:
       - `solve(root, k, ans)`:
         * `if (root == NULL) return 0;`
         * `if (!root->left && !root->right) return 1;`
         * `int leftLeaves = solve(root->left, k, ans);`
         * `int rightLeaves = solve(root->right, k, ans);`
         * `int total = leftLeaves + rightLeaves;`
         * `if (total == k) ans.push_back(root->data);`
         * Return `total`.
       - Main `btWithKleaves(root, k)`:
         * `vector<int> ans;`
         * `solve(root, k, ans);`
         * `if (ans.empty()) return {-1};`
         * Return `ans`.

    Dry Run:
    root = [0, 1, 2, N, N, 4, N, 5, 9], k = 2
    - solve(1): leaf -> returns 1
    - solve(5): leaf -> returns 1
    - solve(9): leaf -> returns 1
    - solve(4): left=1, right=1 -> total = 2 == k -> ans = [4], returns 2
    - solve(2): left=2, right=0 -> total = 2 == k -> ans = [4, 2], returns 2
    - solve(0): left=1, right=2 -> total = 3 != k -> returns 3
    Result: [4, 2] ✓
*/

#include <iostream>
#include <vector>

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
    // Helper function to count leaf nodes in subtree and record nodes with k leaves in postorder
    int solve(Node* root, int k, vector<int>& ans) {
        if (root == NULL) return 0;

        // Base Case: Leaf node contributes 1 leaf count
        if (!root->left && !root->right) {
            return 1;
        }

        // Postorder DFS traversal
        int leftLeaves = solve(root->left, k, ans);
        int rightLeaves = solve(root->right, k, ans);

        int totalLeaves = leftLeaves + rightLeaves;

        // If internal node's subtree contains exactly k leaves, record node value
        if (totalLeaves == k) {
            ans.push_back(root->data);
        }

        return totalLeaves;
    }

public:
    // GFG Signature
    vector<int> btWithKleaves(Node *root, int k) {
        vector<int> ans;
        solve(root, k, ans);

        if (ans.empty()) {
            return {-1};
        }

        return ans;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //      0
    //     / \
    //    1   2
    // k = 1  --> Expected Output: [-1]
    Node* root1 = new Node(0);
    root1->left = new Node(1);
    root1->right = new Node(2);

    vector<int> res1 = ob.btWithKleaves(root1, 1);
    cout << "Example 1 Output: [ ";
    for (int val : res1) cout << val << " ";
    cout << "]\n";

    // Example 2:
    //          0
    //        /   \
    //       1     2
    //            /
    //           4
    //          / \
    //         5   9
    // k = 2  --> Expected Output: [4, 2]
    Node* root2 = new Node(0);
    root2->left = new Node(1);
    root2->right = new Node(2);
    root2->right->left = new Node(4);
    root2->right->left->left = new Node(5);
    root2->right->left->right = new Node(9);

    vector<int> res2 = ob.btWithKleaves(root2, 2);
    cout << "Example 2 Output: [ ";
    for (int val : res2) cout << val << " ";
    cout << "]\n";

    return 0;
}
