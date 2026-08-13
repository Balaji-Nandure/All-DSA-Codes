/*
    Problem Name: Max Sum Leaf to Root Path
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree, find the maximum sum path from any leaf node to the root.

    Examples:
    Input: root[] = [1, 2, 3, 4, 5, N, 8, N, 2, N, N, 6, 7]
    Output: 19
    Explanation: The 4 leaf-to-root paths are:
    - 2 -> 4 -> 2 -> 1 (sum = 9)
    - 5 -> 2 -> 1       (sum = 8)
    - 6 -> 8 -> 3 -> 1 (sum = 18)
    - 7 -> 8 -> 3 -> 1 (sum = 19)
    The maximum sum path is 19.

    Input: root[] = [1, -2, 3, N, 5, N, 8]
    Output: 12
    Explanation: The 2 leaf-to-root paths are:
    - 5 -> -2 -> 1 (sum = 4)
    - 8 -> 3 -> 1  (sum = 12)
    Maximum sum path is 12.

    Constraints:
    1 <= Number of nodes <= 10^5
    -10^6 <= max sum path <= 10^6

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. DFS visits each node once.
    Space Complexity: O(H), where H is the height of the tree, for the recursion stack.

    Love Babbar Style Approach:
    Bottom-Up Postorder DFS (Leaf-to-Root Sum Propagation):

    1. INTUITION:
       - The maximum leaf-to-root path starting at node `root` is:
         `max_path = root->data + max(left_leaf_to_root_sum, right_leaf_to_root_sum)`
       - Base Case:
         * If `root` is a LEAF node (`!root->left && !root->right`), return `root->data`.
         * If a node only has one child (e.g. left exists but right is NULL), we must ONLY consider
           paths ending at valid leaves. We set non-existent child sums to `INT_MIN` so `max()`
           selects the valid child branch!

    2. ALGORITHM:
       - `maxPathSum(root)`:
         * `if (!root) return 0;`
         * `if (!root->left && !root->right) return root->data;`
         * `int leftSum = root->left ? maxPathSum(root->left) : INT_MIN;`
         * `int rightSum = root->right ? maxPathSum(root->right) : INT_MIN;`
         * `return root->data + max(leftSum, rightSum);`

    Dry Run:
             1
           /   \
         -2     3
           \     \
            5     8

    - Leaf 5 returns 5 -> node -2 returns -2 + 5 = 3
    - Leaf 8 returns 8 -> node 3 returns 3 + 8 = 11
    - Root 1 returns 1 + max(3, 11) = 1 + 11 = 12.

    Output: 12 ✓
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
public:
    // GFG Signature - Bottom-up Postorder DFS
    int maxPathSum(Node* root) {
        if (!root) return 0;

        // Base case: If leaf node, return its value
        if (!root->left && !root->right)
            return root->data;

        // Recursively compute max leaf-to-root sum for left and right subtrees
        int leftSum = root->left ? maxPathSum(root->left) : INT_MIN;
        int rightSum = root->right ? maxPathSum(root->right) : INT_MIN;

        // Current node's data plus max path from any leaf in its subtrees
        return root->data + max(leftSum, rightSum);
    }
};

int main() {
    Solution ob;

    // Example 1:
    //            1
    //          /   \
    //        -2     3
    //          \     \
    //           5     8
    // Expected Output: 12 (8 -> 3 -> 1)
    Node* root1 = new Node(1);
    root1->left = new Node(-2);
    root1->right = new Node(3);
    root1->left->right = new Node(5);
    root1->right->right = new Node(8);

    cout << "Example 1 Max Path Sum: " << ob.maxPathSum(root1) << "\n";

    // Example 2:
    //               1
    //             /   \
    //            2     3
    //           / \     \
    //          4   5     8
    //         / \
    //        6   7
    // Expected Output: 19 (7 -> 8 -> 3 -> 1? Wait, 7 -> 4 -> 2 -> 1 = 14; 8 -> 3 -> 1 = 12)
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);
    root2->left->left = new Node(4);
    root2->left->right = new Node(5);
    root2->right->right = new Node(8);
    root2->left->left->left = new Node(6);
    root2->left->left->right = new Node(7);

    cout << "Example 2 Max Path Sum: " << ob.maxPathSum(root2) << "\n";

    return 0;
}
