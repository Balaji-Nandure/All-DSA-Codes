/*
    Problem Name: Vertical Width of a Binary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a root of a Binary Tree, find and return the vertical width of the tree.
    The vertical width of a binary tree is defined as the number of distinct vertical
    lines (horizontal distances) that pass through the nodes of the tree.

    Examples:
    Input: root = [1, 2, 3, 4, 5, 6, 7, N, N, N, N, N, 8, N, 9]
    Output: 6
    Explanation: The tree spans across 6 distinct vertical lines (from min_hd to max_hd).

    Input: root = [1, 2, 3]
    Output: 3
    Explanation:
           1 (hd=0)
         /   \
        2     3
     (hd=-1) (hd=+1)
    Min HD = -1, Max HD = +1 -> Width = (+1) - (-1) + 1 = 3.

    Constraints:
    0 <= number of nodes <= 10^4
    1 <= node->data <= 10^5

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node once during DFS.
    Space Complexity: O(H), where H is the height of the tree, for the recursion call stack.

    Love Babbar Style Approach:
    Horizontal Distance (HD) Tracking via DFS:

    1. INTUITION:
       - Think of the root node as being at horizontal line `hd = 0`.
       - Moving to the LEFT child shifts us to `hd - 1`.
       - Moving to the RIGHT child shifts us to `hd + 1`.
       - Since horizontal distances change continuously by steps of 1, every integer line
         between `min_hd` and `max_hd` is guaranteed to contain at least one node.
       - Therefore, the total vertical width is simply: `(max_hd - min_hd + 1)`.

    2. ALGORITHM:
       - If `root == NULL`, return 0.
       - Maintain `min_hd = 0` and `max_hd = 0`.
       - Perform DFS `solve(root, hd, min_hd, max_hd)`:
         * Update `min_hd = min(min_hd, hd)`.
         * Update `max_hd = max(max_hd, hd)`.
         * Recurse for `root->left` with `hd - 1`.
         * Recurse for `root->right` with `hd + 1`.
       - Return `(max_hd - min_hd + 1)`.

    Dry Run:
            1 (hd=0)
          /   \
         2     3
      (hd=-1) (hd=+1)

    - solve(Node 1, hd=0): min_hd=0, max_hd=0
      - Left  -> solve(Node 2, hd=-1): min_hd=-1, max_hd=0
      - Right -> solve(Node 3, hd=+1): min_hd=-1, max_hd=+1

    Vertical Width = max_hd - min_hd + 1 = 1 - (-1) + 1 = 3 ✓
*/

#include <iostream>
#include <algorithm>

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
    void solve(Node* root, int hd, int& min_hd, int& max_hd) {
        if (root == NULL) return;

        // Update minimum and maximum horizontal distance seen so far
        min_hd = min(min_hd, hd);
        max_hd = max(max_hd, hd);

        // Traverse left and right subtrees
        solve(root->left, hd - 1, min_hd, max_hd);
        solve(root->right, hd + 1, min_hd, max_hd);
    }

public:
    // GFG Signature
    int verticalWidth(Node* root) {
        // Base Case: Empty tree has 0 vertical width
        if (root == NULL) return 0;

        int min_hd = 0, max_hd = 0;
        solve(root, 0, min_hd, max_hd);

        return (max_hd - min_hd + 1);
    }
};

int main() {
    Solution ob;

    // Example 1:
    //         1
    //       /   \
    //      2     3
    //     / \   / \
    //    4   5 6   7
    //           \   \
    //            8   9
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);
    root1->right->left = new Node(6);
    root1->right->right = new Node(7);
    root1->right->left->right = new Node(8);
    root1->right->right->right = new Node(9);

    cout << "Example 1 Vertical Width: " << ob.verticalWidth(root1) << "\n"; // Expected: 6

    // Example 2: Simple 3 node tree
    //     1
    //    / \
    //   2   3
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);

    cout << "Example 2 Vertical Width: " << ob.verticalWidth(root2) << "\n"; // Expected: 3

    // Example 3: Empty Tree
    cout << "Example 3 Vertical Width: " << ob.verticalWidth(NULL) << "\n"; // Expected: 0

    return 0;
}
