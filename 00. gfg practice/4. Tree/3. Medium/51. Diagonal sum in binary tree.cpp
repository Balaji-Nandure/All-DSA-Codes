/*
    Problem Name: Diagonal sum in binary tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Consider lines passing diagonally between nodes in a binary tree.
    The diagonal sum is the sum of all node data lying on each diagonal line.
    Return all diagonal sums starting from diagonal 0 to the last diagonal.

    Diagonal Distance Rules:
    - Root starts at diagonal distance `d = 0`.
    - Going RIGHT child: diagonal distance remains the SAME (`d`).
    - Going LEFT child: diagonal distance INCREMENTED by 1 (`d + 1`).

    Examples:
    Input:
           4
         /   \
        1     3
               \
                3
    Output: [7, 4]
    Explanation:
    - Diagonal 0: Nodes 4, 3, 3 -> Sum = 4 + 3 = 7.
    - Diagonal 1: Node 1        -> Sum = 4.

    Constraints:
    1 <= n <= 10^5
    0 <= data of each node <= 10^4

    Expected Complexities:
    Time Complexity: O(N), using unordered_map with maxD bounds tracking.
    Space Complexity: O(N), for the hash map and recursion stack.

    Love Babbar Style Approach:
    Diagonal Distance (D) Tracking via DFS + Unordered Map + Max Diagonal Bounds (`maxD`):

    1. INTUITION:
       - Using `unordered_map<int, int>` gives O(1) average time per node insertion/lookup.
       - Since `unordered_map` does not store keys in sorted order, we track the maximum
         diagonal distance `maxD` during DFS.
       - After DFS finishes, we iterate `for (int i = 0; i <= maxD; i++)` and push `mp[i]` into `ans`.

    2. ALGORITHM:
       - Helper `solve(root, d, mp, maxD)`:
         * Base Case: `if (!root) return;`
         * Accumulate node data: `mp[d] += root->data;`
         * Update maximum diagonal bound: `maxD = max(maxD, d);`
         * Recurse left with `d + 1`: `solve(root->left, d + 1, mp, maxD);`
         * Recurse right with `d`: `solve(root->right, d, mp, maxD);`
       - In `diagonalSum(root)`:
         * `unordered_map<int, int> mp;`
         * `int maxD = 0;`
         * `solve(root, 0, mp, maxD);`
         * `vector<int> ans;`
         * For `i = 0; i <= maxD; i++`: `ans.push_back(mp[i]);`
         * Return `ans`.

    Dry Run:
            4 (d=0)
          /   \
         1     3 (d=0)
          \
           3 (d=1)

    - solve(4, d=0): mp[0] += 4, maxD = 0
      - Left: solve(1, d=1): mp[1] += 1, maxD = 1
        - Right: solve(3, d=1): mp[1] += 3, maxD = 1
      - Right: solve(3, d=0): mp[0] += 3, maxD = 1

    Loop i from 0 to 1:
    - i = 0 : mp[0] = 4 + 3 = 7
    - i = 1 : mp[1] = 1 + 3 = 4

    Result: [7, 4] ✓
*/

#include <iostream>
#include <vector>
#include <unordered_map>
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
    void solve(Node* root, int d, unordered_map<int, int>& mp, int& maxD) {
        if (!root) return;

        mp[d] += root->data;
        maxD = max(maxD, d);

        solve(root->left, d + 1, mp, maxD);
        solve(root->right, d, mp, maxD);
    }

public:
    // GFG Signature - Unordered Map O(N) Approach
    vector<int> diagonalSum(Node* root) {
        unordered_map<int, int> mp;
        int maxD = 0;

        solve(root, 0, mp, maxD);

        vector<int> ans;
        for (int i = 0; i <= maxD; i++)
            ans.push_back(mp[i]);

        return ans;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //        4
    //      /   \
    //     1     3
    //            \
    //             3
    // Expected Output: 7 4
    Node* root1 = new Node(4);
    root1->left = new Node(1);
    root1->right = new Node(3);
    root1->right->right = new Node(3);

    vector<int> diag1 = ob.diagonalSum(root1);
    cout << "Example 1 Diagonal Sums: ";
    for (int sum : diag1) cout << sum << " ";
    cout << "\n";

    // Example 2:
    //           8
    //        /     \
    //       3       10
    //      / \        \
    //     1   6        14
    //        / \      /
    //       4   7    13
    // Diagonals:
    // d=0: 8 + 10 + 14 = 32
    // d=1: 3 + 6 + 7 + 13 = 29
    // d=2: 1 + 4 = 5
    Node* root2 = new Node(8);
    root2->left = new Node(3);
    root2->right = new Node(10);
    root2->left->left = new Node(1);
    root2->left->right = new Node(6);
    root2->right->right = new Node(14);
    root2->left->right->left = new Node(4);
    root2->left->right->right = new Node(7);
    root2->right->right->left = new Node(13);

    vector<int> diag2 = ob.diagonalSum(root2);
    cout << "Example 2 Diagonal Sums: ";
    for (int sum : diag2) cout << sum << " ";
    cout << "\n";

    return 0;
}
