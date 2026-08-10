/*
    Problem Name: Ancestors in Binary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a Binary Tree and an integer target, find all the ancestors of the given target.

    Note:
    - A node y is an ancestor of x if it lies on the path from x to the root (excluding x itself).
    - Root is ancestor of all other nodes, and root has no ancestors.
    - If target is not present or target is root, return an empty list.
    - Output format: from immediate parent up to the root node (bottom-up along the ancestor path).

    Examples:
    Input: root[] = [1, 2, 3, 4, 5, 6, 8, 7, N, N, N, N, N, N], target = 7
    Output: [4, 2, 1]
    Explanation: The path from 7 to root goes through 4, 2, and 1.

    Input: root[] = [1, 2, 3], target = 1
    Output: []
    Explanation: Since 1 is the root node, it has no ancestors.

    Constraints:
    1 <= no. of nodes <= 10^3
    1 <= data of node <= 10^4

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node at most once.
    Space Complexity: O(H), where H is the height of the tree, for the recursion stack and output vector.

    Love Babbar Style Approach:
    Boolean Return Backtracking DFS:

    1. INTUITION:
       - We perform a DFS search for the `target` node.
       - The recursive function `solve(root, target, ans)` returns `true` if `target` is found
         in the subtree rooted at `root`, and `false` otherwise.
       - As the recursion UNWINDS (backtracks) from the target node towards the root:
         * If either left or right subtree returned `true`, it means `root` is on the path from
           `target` to root!
         * We push `root->data` into `ans` and return `true` to pass the signal up to `root`'s parent.

    2. ALGORITHM:
       - `solve(root, target, ans)`:
         * Base Case 1: `if (root == NULL)` return `false`.
         * Base Case 2: `if (root->data == target)` return `true` (found target, don't include target itself as ancestor).
         * If `solve(root->left, target, ans) || solve(root->right, target, ans)`:
           - `ans.push_back(root->data)`
           - return `true`
         * return `false`.

    Dry Run:
              1
            /   \
           2     3
          / \
         4   5
        /
       7

    target = 7

    - solve(1): calls solve(2)
      - solve(2): calls solve(4)
        - solve(4): calls solve(7)
          - solve(7): root->data == 7 -> returns true!
        - solve(4) receives true -> ans.push_back(4), returns true!
      - solve(2) receives true -> ans.push_back(2), returns true!
    - solve(1) receives true -> ans.push_back(1), returns true!

    Resulting ans: [4, 2, 1] ✓
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
    bool solve(Node* root, int target, vector<int>& ans) {
        if (root == NULL)
            return false;

        if (root->data == target)
            return true;

        if (solve(root->left, target, ans) || solve(root->right, target, ans)) {
            ans.push_back(root->data);
            return true;
        }

        return false;
    }

public:
    // GFG Signature
    vector<int> Ancestors(struct Node *root, int target) {
        vector<int> ans;
        solve(root, target, ans);
        return ans;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //            1
    //          /   \
    //         2     3
    //        / \   / \
    //       4   5 6   8
    //      /
    //     7
    // target = 7  --> Expected Output: [4, 2, 1]

    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);
    root1->right->left = new Node(6);
    root1->right->right = new Node(8);
    root1->left->left->left = new Node(7);

    int target1 = 7;
    vector<int> anc1 = ob.Ancestors(root1, target1);

    cout << "Example 1 Ancestors of 7: ";
    for (int val : anc1) {
        cout << val << " ";
    }
    cout << "\n"; // Output: 4 2 1

    // Example 2: Target is root (1)
    int target2 = 1;
    vector<int> anc2 = ob.Ancestors(root1, target2);

    cout << "Example 2 Ancestors of 1 (Root): ";
    if (anc2.empty()) {
        cout << "[] (No ancestors)";
    } else {
        for (int val : anc2) cout << val << " ";
    }
    cout << "\n"; // Output: []

    return 0;
}
