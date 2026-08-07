/*
    Problem Name: Node and Ancestor Max Diff
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree, find the maximum value you can get by subtracting
    the value of node B from the value of node A (i.e. A->data - B->data), where A and B
    are two nodes of the binary tree and A is an ancestor of B.

    Examples:
    Input: root = [5, 2, 1]
    Output: 4
    Explanation: The maximum difference is 4 (5 - 1 = 4, where 5 is ancestor of 1).

    Input: root = [1, 2, 3, N, N, N, 7]
    Output: -1
    Explanation: The maximum difference is -1 (1 - 2 = -1, where 1 is ancestor of 2).

    Constraints:
    2 <= Number of edges <= 10^4
    0 <= Data of a node <= 10^5

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node once in Postorder traversal.
    Space Complexity: O(H), where H is the height of the tree, for the recursion call stack.

    Love Babbar Style Approach:
    Bottom-Up Postorder Traversal (Subtree Minimum Tracking):

    1. INTUITION:
       - To maximize `(Ancestor Value - Descendant Value)`, for a given ancestor node `A`,
         we want to find the MINIMUM node value in `A`'s subtree (descendants).
       - If we process the tree from bottom to top (Postorder: Left, Right, Node):
         * Each child returns the MINIMUM node value found in its subtree.
         * Current node `A` calculates `diff = A->data - min(leftSubtreeMin, rightSubtreeMin)`.
         * We update global max result `ans = max(ans, diff)`.
         * Current node `A` then returns `min(A->data, minDescendant)` up to its parent.

    2. ALGORITHM:
       - Base Case: If `root == NULL`, return `INT_MAX`.
       - If `root` is a leaf node (`!root->left && !root->right`), it has no descendants.
         Return `root->data` to its parent.
       - Recursively get `leftMin` from left subtree and `rightMin` from right subtree.
       - Find `minDescendant = min(leftMin, rightMin)`.
       - Update `ans = max(ans, root->data - minDescendant)`.
       - Return `min(root->data, minDescendant)` so parent node knows the minimum value in this entire subtree.

    Dry Run:
            5
           /
          2
         /
        1

    - solve(1): Leaf node -> returns 1.
    - solve(2): leftMin = 1, rightMin = INT_MAX -> minDescendant = 1.
                ans = max(INT_MIN, 2 - 1) = 1.
                returns min(2, 1) = 1.
    - solve(5): leftMin = 1, rightMin = INT_MAX -> minDescendant = 1.
                ans = max(1, 5 - 1) = 4.
                returns min(5, 1) = 1.

    Output: 4 ✓
*/

#include <iostream>
#include <algorithm>
#include <climits>

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
    int solve(Node* root, int& maxDiffResult) {
        if (root == NULL) return INT_MAX;

        // Base case: Leaf node cannot be an ancestor of any node
        if (root->left == NULL && root->right == NULL) {
            return root->data;
        }

        // Recursively find minimum value in left and right subtrees
        int leftMin = solve(root->left, maxDiffResult);
        int rightMin = solve(root->right, maxDiffResult);

        // Find overall minimum value among all descendants
        int minDescendant = min(leftMin, rightMin);

        // Update maximum difference (Ancestor - Descendant)
        maxDiffResult = max(maxDiffResult, root->data - minDescendant);

        // Return minimum value in the current subtree (including root)
        return min(root->data, minDescendant);
    }

public:
    // GFG Signature
    int maxDiff(Node* root) {
        int maxDiffResult = INT_MIN;
        solve(root, maxDiffResult);
        return maxDiffResult;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //        5
    //       /
    //      2
    //     /
    //    1
    // Expected Output: 4 (5 - 1 = 4)
    Node* root1 = new Node(5);
    root1->left = new Node(2);
    root1->left->left = new Node(1);

    cout << "Example 1 Max Diff: " << ob.maxDiff(root1) << "\n";

    // Example 2:
    //      1
    //     / \
    //    2   3
    //         \
    //          7
    // Expected Output: -1 (1 - 2 = -1)
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);
    root2->right->right = new Node(7);

    cout << "Example 2 Max Diff: " << ob.maxDiff(root2) << "\n";

    return 0;
}
