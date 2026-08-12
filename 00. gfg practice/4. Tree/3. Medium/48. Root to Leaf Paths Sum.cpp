/*
    Problem Name: Root to Leaf Paths Sum
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree where each node contains a single digit (0–9).
    Every root-to-leaf path represents a number formed by concatenating the digits along the path.
    Starting from the root, each next digit is appended to the current number:
    `currentNumber = currentNumber * 10 + node->data`.
    Return the sum of all the numbers formed by every root-to-leaf path.

    Examples:
    Input:
              6
            /   \
           3     5
          / \     \
         2   5     4
            / \
           7   4

    Output: 13997
    Explanation: The 4 root-to-leaf paths form numbers:
    - Path 6->3->2       = 632
    - Path 6->3->5->7    = 6357
    - Path 6->3->5->4    = 6354
    - Path 6->5->4       = 654
    Sum = 632 + 6357 + 6354 + 654 = 13997.

    Input:
              1
            /   \
           0     0
          / \
         3   0
    Output: 203 (103 + 100)

    Constraints:
    1 <= number of nodes <= 31
    0 <= node->data <= 9

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node once in DFS.
    Space Complexity: O(H), where H is the height of the tree, for the recursion call stack.

    Love Babbar Style Approach:
    Root-to-Leaf Path Accumulation DFS:

    1. INTUITION:
       - As we traverse down from the root to any leaf, we construct the number step-by-step:
         `current_num = current_num * 10 + root->data`
       - When we reach a LEAF node (`!root->left && !root->right`):
         * The complete number for this root-to-leaf path is formed!
         * Return `current_num`.
       - For internal nodes:
         * Recursively get path sums from `root->left` and `root->right`.
         * Return `left_path_sum + right_path_sum`.

    2. ALGORITHM:
       - `solve(root, num)`:
         * `if (!root) return 0;`
         * `num = num * 10 + root->data;`
         * `if (!root->left && !root->right) return num;`
         * `return solve(root->left, num) + solve(root->right, num);`
       - `treePathsSum(root)`:
         * `return solve(root, 0);`

    Dry Run:
            1
          /   \
         0     9
        /
       3

    - solve(1, num=0): num = 0 * 10 + 1 = 1
      - Left: solve(0, num=1): num = 1 * 10 + 0 = 10
        - Left: solve(3, num=10): num = 10 * 10 + 3 = 103 (Leaf!) -> returns 103
        - Right: NULL -> returns 0
        - returns 103
      - Right: solve(9, num=1): num = 1 * 10 + 9 = 19 (Leaf!) -> returns 19
      - returns 103 + 19 = 122

    Total path sum = 122 ✓
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
    long long solve(Node* root, long long num) {
        if (!root) return 0;

        // Append current node's digit
        num = num * 10 + root->data;

        // If leaf node, return the completed path number
        if (!root->left && !root->right)
            return num;

        // Sum of all root-to-leaf paths in left and right subtrees
        return solve(root->left, num) + solve(root->right, num);
    }

public:
    // GFG Signature
    long long treePathsSum(Node *root) {
        return solve(root, 0);
    }
};

int main() {
    Solution ob;

    // Example 1:
    //            6
    //          /   \
    //         3     5
    //        / \     \
    //       2   5     4
    //          / \
    //         7   4
    // Paths: 632, 6357, 6354, 654 -> Expected Sum: 13997
    Node* root1 = new Node(6);
    root1->left = new Node(3);
    root1->right = new Node(5);
    root1->left->left = new Node(2);
    root1->left->right = new Node(5);
    root1->right->right = new Node(4);
    root1->left->right->left = new Node(7);
    root1->left->right->right = new Node(4);

    cout << "Example 1 Paths Sum: " << ob.treePathsSum(root1) << "\n";

    // Example 2:
    //          1
    //        /   \
    //       0     0
    //      / \
    //     3   0
    // Paths: 103, 100, 10 -> Expected Sum: 213 (103 + 100 + 10)
    Node* root2 = new Node(1);
    root2->left = new Node(0);
    root2->right = new Node(0);
    root2->left->left = new Node(3);
    root2->left->right = new Node(0);

    cout << "Example 2 Paths Sum: " << ob.treePathsSum(root2) << "\n";

    return 0;
}
