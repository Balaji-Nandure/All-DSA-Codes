/*
    Problem Name: Sum of nodes on the longest path
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary tree, find the sum of nodes on the longest path from root to any leaf.
    If two or more paths have the SAME length, pick the one with the MAXIMUM sum.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node exactly once.
    Space Complexity: O(H), where H is the height of the tree, for the recursion stack.

    Love Babbar Style Approach:
    Simple DFS where we carry two things down the tree:
    1. `currentLength` — how many nodes we've visited so far on this path.
    2. `currentSum`    — running total of node values on this path.

    We maintain two global trackers:
    - `maxLength` — longest path seen so far.
    - `maxSum`    — the best sum for that longest path.

    At every LEAF node, we check:
    - If currentLength > maxLength → NEW longest path found! Update BOTH maxLength and maxSum.
    - If currentLength == maxLength AND currentSum > maxSum → SAME length but BETTER sum!
      Update maxSum only.

    That's it! No need to store paths, no need for backtracking — just carry values down
    and update at leaves.

    Dry Run:
    Tree:         4
                /   \
               2     5
              / \   / \
             7   1 2   3
                /
               6
    
    Leaf paths (root to leaf):
    - 4→2→7         : length=3, sum=13
    - 4→2→1→6       : length=4, sum=13  ← LONGEST path!
    - 4→5→2         : length=3, sum=11
    - 4→5→3         : length=3, sum=12

    DFS traversal:
    - Start: maxLength=0, maxSum=0
    - Reach leaf(7):  len=3, sum=13. 3 > 0 → maxLength=3, maxSum=13
    - Reach leaf(6):  len=4, sum=13. 4 > 3 → maxLength=4, maxSum=13  ← New longest!
    - Reach leaf(2):  len=3, sum=11. 3 < 4 → skip
    - Reach leaf(3):  len=3, sum=12. 3 < 4 → skip
    - Answer: maxSum = 13 ✓

    Dry Run 2:
    Tree:     1
             / \
            2   3
           / \ / \
          4  5 6  7

    Leaf paths:
    - 1→2→4 : length=3, sum=7
    - 1→2→5 : length=3, sum=8
    - 1→3→6 : length=3, sum=10
    - 1→3→7 : length=3, sum=11 ← SAME length but MAX sum!

    - Reach leaf(4): len=3, sum=7.  3 > 0  → maxLen=3, maxSum=7
    - Reach leaf(5): len=3, sum=8.  3 == 3 AND 8 > 7  → maxSum=8
    - Reach leaf(6): len=3, sum=10. 3 == 3 AND 10 > 8 → maxSum=10
    - Reach leaf(7): len=3, sum=11. 3 == 3 AND 11 > 10 → maxSum=11
    - Answer: maxSum = 11 ✓
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
    void solve(Node* root, int currentLength, int currentSum, int& maxLength, int& maxSum) {
        // Base Case: Fell off the tree — nothing to process
        if (root == NULL) return;

        // 1. Include the current node in the path
        currentLength++;
        currentSum += root->data;

        // 2. If it's a LEAF node, check if this path is the best we've seen
        if (root->left == NULL && root->right == NULL) {
            if (currentLength > maxLength) {
                // NEW longest path found — this one wins unconditionally!
                maxLength = currentLength;
                maxSum    = currentSum;
            } else if (currentLength == maxLength && currentSum > maxSum) {
                // SAME length but BETTER sum — update sum only
                maxSum = currentSum;
            }
            return;
        }

        // 3. Not a leaf — keep going deeper into both children
        solve(root->left,  currentLength, currentSum, maxLength, maxSum);
        solve(root->right, currentLength, currentSum, maxLength, maxSum);
    }

public:
    // GFG Signature
    int sumOfLongRootToLeafPath(Node* root) {
        int maxLength = 0;
        int maxSum    = 0;

        solve(root, 0, 0, maxLength, maxSum);

        return maxSum;
    }
};

int main() {
    // Example 1:
    //           4
    //         /   \
    //        2     5
    //       / \   / \
    //      7   1 2   3
    //         /
    //        6
    // Expected: 13  (path 4→2→1→6, length=4, sum=13)

    Node* root1 = new Node(4);
    root1->left              = new Node(2);
    root1->right             = new Node(5);
    root1->left->left        = new Node(7);
    root1->left->right       = new Node(1);
    root1->right->left       = new Node(2);
    root1->right->right      = new Node(3);
    root1->left->right->left = new Node(6);

    Solution ob;
    // Output: 13
    cout << "Sum of longest path (Example 1): " << ob.sumOfLongRootToLeafPath(root1) << "\n";

    // Example 2:
    //       1
    //      / \
    //     2   3
    //    / \ / \
    //   4  5 6  7
    // Expected: 11  (path 1→3→7, all paths have length 3, max sum is 11)

    Node* root2 = new Node(1);
    root2->left         = new Node(2);
    root2->right        = new Node(3);
    root2->left->left   = new Node(4);
    root2->left->right  = new Node(5);
    root2->right->left  = new Node(6);
    root2->right->right = new Node(7);

    // Output: 11
    cout << "Sum of longest path (Example 2): " << ob.sumOfLongRootToLeafPath(root2) << "\n";

    // Example 3:
    //        10
    //       /  \
    //      5    15
    //     / \     \
    //    3   7    20
    //   /
    //  1
    // Expected: 19  (path 10→5→3→1, length=4, sum=19)

    Node* root3 = new Node(10);
    root3->left              = new Node(5);
    root3->right             = new Node(15);
    root3->left->left        = new Node(3);
    root3->left->right       = new Node(7);
    root3->right->right      = new Node(20);
    root3->left->left->left  = new Node(1);

    // Output: 19
    cout << "Sum of longest path (Example 3): " << ob.sumOfLongRootToLeafPath(root3) << "\n";

    return 0;
}
