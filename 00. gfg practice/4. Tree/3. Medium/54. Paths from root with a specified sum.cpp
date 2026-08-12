/*
    Problem Name: Paths from root with a specified sum
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree and an integer s, find all paths starting from the root
    such that the sum of the node values along each path equals s.

    Note: A path MUST start at the root, but does NOT necessarily have to end at a leaf node.

    Examples:
    Input: s = 8, root = [1, 20, 3, N, N, 4, 15, 6, N, N, N, N, N]
    Output: [[1, 3, 4]]
    Explanation: Sum of path 1 -> 3 -> 4 = 8.

    Input: s = 38, root = [10, 28, 13, N, N, 14, 15]
    Output: [[10, 28], [10, 13, 15]]
    Explanation: Path 10 -> 28 sums to 38, and Path 10 -> 13 -> 15 sums to 38.

    Constraints:
    1 <= n <= 2 * 10^3
    -10^3 <= s <= 10^3
    -10^3 <= Node.value <= 10^3

    Expected Complexities:
    Time Complexity: O(N * H), where N is number of nodes and H is height of tree (for path copying).
    Space Complexity: O(H), for path tracking vector and recursion call stack.

    Love Babbar Style Approach:
    DFS + Backtracking (Pass-by-Reference State):

    1. INTUITION:
       - We start at `root` with `currSum = 0` and an empty `path` vector.
       - As we visit each node:
         * Add `root->data` to `currSum` and push `root->data` into `path`.
         * Check: `if (currSum == sum)`, we found a valid path starting from root! Push `path` into `result`.
         * IMPORTANT: Do NOT return after finding a match! Why? Because child nodes might sum to 0
           or extend the path to form further valid paths!
         * Recurse for `root->left` and `root->right`.
         * Backtrack: Pop `root->data` from `path` before returning to parent.

    2. ALGORITHM:
       - `solve(root, targetSum, currSum, path, result)`:
         * Base Case: `if (root == NULL) return;`
         * `currSum += root->data;`
         * `path.push_back(root->data);`
         * `if (currSum == targetSum) result.push_back(path);`
         * `solve(root->left, targetSum, currSum, path, result);`
         * `solve(root->right, targetSum, currSum, path, result);`
         * Backtrack: `path.pop_back();`

    Dry Run:
             10
           /    \
          28     13
                /  \
               14   15
    s = 38

    - solve(10): currSum=10, path=[10]
      - Left: solve(28): currSum=38, path=[10, 28] -> MATCH! Add [10, 28] to result.
      - Right: solve(13): currSum=23, path=[10, 13]
        - Left: solve(14): currSum=37, path=[10, 13, 14]
        - Right: solve(15): currSum=38, path=[10, 13, 15] -> MATCH! Add [10, 13, 15] to result.

    Result: [[10, 28], [10, 13, 15]] ✓
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
    void solve(Node* root, int targetSum, int currSum, vector<int>& path, vector<vector<int>>& result) {
        if (root == NULL) return;

        // Include current node in path and running sum
        currSum += root->data;
        path.push_back(root->data);

        // Check if current path starting from root sums to targetSum
        if (currSum == targetSum) {
            result.push_back(path);
        }

        // Recurse left and right subtrees
        solve(root->left, targetSum, currSum, path, result);
        solve(root->right, targetSum, currSum, path, result);

        // Backtrack
        path.pop_back();
    }

public:
    // GFG Signature
    vector<vector<int>> printPaths(Node *root, int sum) {
        vector<vector<int>> result;
        vector<int> path;

        solve(root, sum, 0, path, result);

        return result;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //             10
    //           /    \
    //          28     13
    //                /  \
    //               14   15
    // s = 38  --> Expected Output: [[10, 28], [10, 13, 15]]
    Node* root1 = new Node(10);
    root1->left = new Node(28);
    root1->right = new Node(13);
    root1->right->left = new Node(14);
    root1->right->right = new Node(15);

    int s1 = 38;
    vector<vector<int>> paths1 = ob.printPaths(root1, s1);

    cout << "Example 1 Paths (sum = 38):\n";
    for (const auto& path : paths1) {
        cout << "[ ";
        for (int val : path) cout << val << " ";
        cout << "]\n";
    }
    cout << "\n";

    // Example 2:
    //           1
    //         /   \
    //        20    3
    //             / \
    //            4   15
    //           /
    //          6
    // s = 8  --> Expected Output: [[1, 3, 4]]
    Node* root2 = new Node(1);
    root2->left = new Node(20);
    root2->right = new Node(3);
    root2->right->left = new Node(4);
    root2->right->right = new Node(15);
    root2->right->left->left = new Node(6);

    int s2 = 8;
    vector<vector<int>> paths2 = ob.printPaths(root2, s2);

    cout << "Example 2 Paths (sum = 8):\n";
    for (const auto& path : paths2) {
        cout << "[ ";
        for (int val : path) cout << val << " ";
        cout << "]\n";
    }

    return 0;
}
