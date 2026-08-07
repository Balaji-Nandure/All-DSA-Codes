/*
    Problem Name: Closest in BST
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a BST and an integer K, find the least absolute difference between any
    node value in the BST and K.

    Expected Complexities:
    Time Complexity: O(H), where H is the height of the BST.
                     O(log N) for balanced BST, O(N) for skewed.
    Space Complexity: O(1), pure iterative — no recursion stack!

    Love Babbar Style Approach:
    This is similar to "searching" in a BST, but instead of finding an exact match,
    we track the CLOSEST value seen so far!

    At every node, we do TWO things:
    1. UPDATE: Check if |node->data - K| is smaller than our current best → update minDiff.
    2. NAVIGATE: Use BST property to decide which side to go:
       - If K < node->data → go LEFT  (answer might be closer on the smaller side)
       - If K > node->data → go RIGHT (answer might be closer on the larger side)
       - If K == node->data → PERFECT MATCH! Difference is 0 — can't do better!

    WHY does this work? At every step, we're moving TOWARDS K using the BST ordering.
    Even though we skip one subtree each time, the values in the skipped subtree are
    guaranteed to be FARTHER from K (because BST!), so we never miss the optimal answer.

    Dry Run:
    BST:        10
               /  \
              2    11
             / \
            1   5
               / \
              3   6
               \
                4
    K = 13

    - Node(10): |10-13| = 3 → minDiff = 3. K > 10 → go RIGHT
    - Node(11): |11-13| = 2 → minDiff = 2. K > 11 → go RIGHT
    - NULL → STOP
    - Answer: 2 ✓ (closest node is 11)

    Dry Run 2:
    BST:      8
             / \
            1   9
             \   \
              4  10
             /
            3
    K = 9

    - Node(8): |8-9| = 1 → minDiff = 1. K > 8 → go RIGHT
    - Node(9): |9-9| = 0 → minDiff = 0. K == 9 → PERFECT MATCH! STOP
    - Answer: 0 ✓
*/

#include <iostream>
#include <algorithm>
#include <climits>
#include <cmath>

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
public:
    // GFG Signature
    int minDiff(Node* root, int K) {
        int minDifference = INT_MAX;

        Node* curr = root;

        while (curr != NULL) {
            // 1. UPDATE: Check if current node is closer to K than our best so far
            int diff = abs(curr->data - K);
            minDifference = min(minDifference, diff);

            // 2. PERFECT MATCH: Can't do better than 0 — stop immediately!
            if (curr->data == K) {
                return 0;
            }

            // 3. NAVIGATE: Use BST ordering to move towards K
            if (K < curr->data) {
                curr = curr->left;   // K is smaller → go LEFT
            } else {
                curr = curr->right;  // K is larger → go RIGHT
            }
        }

        return minDifference;
    }
};

int main() {
    // Example 1:
    //         10
    //        /  \
    //       2    11
    //      / \
    //     1   5
    //        / \
    //       3   6
    //        \
    //         4
    // K = 13  --> Expected: 2 (closest node is 11, |11-13| = 2)

    Node* root1 = new Node(10);
    root1->left              = new Node(2);
    root1->right             = new Node(11);
    root1->left->left        = new Node(1);
    root1->left->right       = new Node(5);
    root1->left->right->left  = new Node(3);
    root1->left->right->right = new Node(6);
    root1->left->right->left->right = new Node(4);

    Solution ob;
    // Output: 2
    cout << "Min Diff (Example 1, K=13): " << ob.minDiff(root1, 13) << "\n";

    // Example 2:
    //       8
    //      / \
    //     1   9
    //      \   \
    //       4  10
    //      /
    //     3
    // K = 9  --> Expected: 0 (exact match!)

    Node* root2 = new Node(8);
    root2->left         = new Node(1);
    root2->right        = new Node(9);
    root2->left->right  = new Node(4);
    root2->right->right = new Node(10);
    root2->left->right->left = new Node(3);

    // Output: 0
    cout << "Min Diff (Example 2, K=9): " << ob.minDiff(root2, 9) << "\n";

    // Example 3: K not in tree, between two nodes
    // Using root2, K = 5 --> Closest is 4, |4-5| = 1
    // Output: 1
    cout << "Min Diff (Example 3, K=5): " << ob.minDiff(root2, 5) << "\n";

    return 0;
}
