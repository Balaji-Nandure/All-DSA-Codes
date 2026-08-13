/*
    Problem Name: Largest Subtree Sum
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary tree, find the subtree with the maximum sum of node values in the tree and return its sum.

    Examples:
    Input: root[] = [10, 8, 2, 3, 5, N, N]
    Output: 28
    Explanation:
            10
           /  \
          8    2
         / \
        3   5
    Since all node values are positive, the largest subtree sum is the sum of the whole tree (28).

    Input: root[] = [1, -2, 3, 4, 5, -6, 2]
    Output: 7
    Explanation:
             1
           /   \
         -2     3
        /  \   / \
       4    5 -6  2
    Subtree rooted at node -2 has sum = -2 + 4 + 5 = 7.
    Whole tree sum = 1 + (-2) + 3 + 4 + 5 + (-6) + 2 = 7.
    Maximum subtree sum = 7.

    Constraints:
    1 <= n <= 10^5
    -10^3 <= node->data <= 10^3

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. Bottom-up postorder DFS visits each node once.
    Space Complexity: O(H), where H is the height of the tree, for the recursion call stack.

    Love Babbar Style Approach:
    Bottom-Up Postorder DFS (Subtree Sum Accumulation):

    1. INTUITION:
       - The total sum of a subtree rooted at node `root` is:
         `currSum = root->data + left_subtree_sum + right_subtree_sum`
       - By traversing the tree in Postorder (Left -> Right -> Root):
         * `left_subtree_sum` is computed first from the left child.
         * `right_subtree_sum` is computed next from the right child.
         * `currSum` is computed at the current root.
       - We update our overall `maxSum = max(maxSum, currSum)` at every node.
       - Pass `maxSum` by reference (`int& maxSum`) to avoid global or class-level state variables.

    2. ALGORITHM:
       - Helper `solve(root, maxSum)`:
         * Base Case: `if (root == NULL) return 0;`
         * `int leftSum = solve(root->left, maxSum);`
         * `int rightSum = solve(root->right, maxSum);`
         * `int currSum = root->data + leftSum + rightSum;`
         * `maxSum = max(maxSum, currSum);`
         * Return `currSum;`
       - Main `findLargestSubtreeSum(root)`:
         * `if (!root) return 0;`
         * `int maxSum = INT_MIN;`
         * `solve(root, maxSum);`
         * Return `maxSum;`

    Dry Run:
             1
           /   \
         -2     3
        /  \   / \
       4    5 -6  2

    - solve(4): returns 4, maxSum = 4
    - solve(5): returns 5, maxSum = 5
    - solve(-2): sum = -2 + 4 + 5 = 7, maxSum = max(5, 7) = 7
    - solve(-6): returns -6, maxSum = 7
    - solve(2): returns 2, maxSum = 7
    - solve(3): sum = 3 + (-6) + 2 = -1, maxSum = 7
    - solve(1): sum = 1 + 7 + (-1) = 7, maxSum = 7

    Result: 7 ✓
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
    // Bottom-up postorder traversal calculating subtree sum and updating maxSum by reference
    int solve(Node* root, int& maxSum) {
        if (root == NULL) return 0;

        int leftSum = solve(root->left, maxSum);
        int rightSum = solve(root->right, maxSum);

        int currSum = root->data + leftSum + rightSum;

        // Track the maximum subtree sum found so far
        maxSum = max(maxSum, currSum);

        return currSum;
    }

public:
    // GFG Signature
    int findLargestSubtreeSum(Node* root) {
        if (!root) return 0;

        int maxSum = INT_MIN;
        solve(root, maxSum);

        return maxSum;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //        10
    //       /  \
    //      8    2
    //     / \
    //    3   5
    // Expected Output: 28
    Node* root1 = new Node(10);
    root1->left = new Node(8);
    root1->right = new Node(2);
    root1->left->left = new Node(3);
    root1->left->right = new Node(5);

    cout << "Example 1 Largest Subtree Sum: " << ob.findLargestSubtreeSum(root1) << "\n";

    // Example 2:
    //         1
    //       /   \
    //     -2     3
    //    /  \   / \
    //   4    5 -6  2
    // Expected Output: 7
    Node* root2 = new Node(1);
    root2->left = new Node(-2);
    root2->right = new Node(3);
    root2->left->left = new Node(4);
    root2->left->right = new Node(5);
    root2->right->left = new Node(-6);
    root2->right->right = new Node(2);

    cout << "Example 2 Largest Subtree Sum: " << ob.findLargestSubtreeSum(root2) << "\n";

    return 0;
}
