/*
    Problem Name: Count SubTrees with Sum
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a root of a binary tree and an integer x, count the number of subtrees whose sum
    of all node values is equal to x.

    Examples:
    Input: root = [5, -10, 3, 9, 8, -4, 7], x = 7
    Output: 2
    Explanation: Subtrees with sum 7 are:
    - Subtree rooted at -10: (-10 + 9 + 8 = 7)
    - Subtree rooted at 7: (7)
    Total count = 2.

    Input: root = [1, 2, 3], x = 5
    Output: 0
    Explanation: No subtree has a sum equal to 5.

    Constraints:
    1 <= no. of nodes in root <= 10^5
    -10^5 <= node->data <= 10^5

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node once in Postorder traversal.
    Space Complexity: O(H), where H is the height of the tree, for the recursion call stack.

    Love Babbar Style Approach:
    Bottom-Up Postorder Traversal (Subtree Sum Calculation):

    1. INTUITION:
       - To know the total sum of a subtree rooted at node `root`:
         `subtree_sum = root->data + left_subtree_sum + right_subtree_sum`
       - By executing a bottom-up Postorder traversal (Left -> Right -> Root):
         * Left child returns `left_subtree_sum`.
         * Right child returns `right_subtree_sum`.
         * Current node calculates its total `subtree_sum`.
         * If `subtree_sum == x`, increment our answer `count`.
         * Current node returns `subtree_sum` to its parent.

    2. ALGORITHM:
       - Helper `solve(root, x, count)`:
         * Base Case: `if (root == NULL)` return `0`.
         * `int leftSum = solve(root->left, x, count);`
         * `int rightSum = solve(root->right, x, count);`
         * `int currSum = root->data + leftSum + rightSum;`
         * `if (currSum == x) count++;`
         * Return `currSum`.
       - In `countSubtreesWithSumX(root, X)`:
         * `int count = 0;`
         * `solve(root, X, count);`
         * Return `count`.

    Dry Run:
             5
           /   \
        -10     3
        / \    / \
       9   8  -4  7
    x = 7

    - solve(9)  -> sum = 9
    - solve(8)  -> sum = 8
    - solve(-10)-> sum = -10 + 9 + 8 = 7 == x -> count = 1
    - solve(-4) -> sum = -4
    - solve(7)  -> sum = 7 == x -> count = 2
    - solve(3)  -> sum = 3 + (-4) + 7 = 6
    - solve(5)  -> sum = 5 + 7 + 6 = 18

    Result: count = 2 ✓
*/

#include <iostream>

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
    int solve(Node* root, int x, int& count) {
        if (root == NULL) return 0;

        // Bottom-up postorder traversal to calculate left and right subtree sums
        int leftSum = solve(root->left, x, count);
        int rightSum = solve(root->right, x, count);

        int currSum = root->data + leftSum + rightSum;

        // If current subtree sum equals target x, increment count
        if (currSum == x) {
            count++;
        }

        return currSum;
    }

public:
    // GFG Signature
    int countSubtreesWithSumX(Node* root, int X) {
        int count = 0;
        solve(root, X, count);
        return count;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //             5
    //           /   \
    //        -10     3
    //        / \    / \
    //       9   8  -4  7
    // x = 7  --> Expected Output: 2
    Node* root1 = new Node(5);
    root1->left = new Node(-10);
    root1->right = new Node(3);
    root1->left->left = new Node(9);
    root1->left->right = new Node(8);
    root1->right->left = new Node(-4);
    root1->right->right = new Node(7);

    cout << "Example 1 Subtrees with Sum 7: " << ob.countSubtreesWithSumX(root1, 7) << "\n";

    // Example 2:
    //      1
    //     / \
    //    2   3
    // x = 5  --> Expected Output: 0
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);

    cout << "Example 2 Subtrees with Sum 5: " << ob.countSubtreesWithSumX(root2, 5) << "\n";

    return 0;
}
