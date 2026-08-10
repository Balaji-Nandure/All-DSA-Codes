/*
    Problem Name: Vertical Sum
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary tree having n nodes, find the vertical sum of the nodes that are in the same
    vertical line. Return all sums through different vertical lines starting from the left-most
    vertical line to the right-most vertical line.

    Examples:
    Input:
             1
           /   \
          2     3
         / \   / \
        4   5 6   7

    Output: [4, 2, 12, 3, 7]
    Explanation:
    - Line 1 (hd = -2): node 4                  -> sum = 4
    - Line 2 (hd = -1): node 2                  -> sum = 2
    - Line 3 (hd = 0) : nodes 1, 5, 6           -> sum = 1 + 5 + 6 = 12
    - Line 4 (hd = +1): node 3                  -> sum = 3
    - Line 5 (hd = +2): node 7                  -> sum = 7

    Constraints:
    1 <= n <= 10^4
    1 <= Node value <= 10^5

    Expected Complexities:
    Time Complexity: O(N), using unordered_map with min_hd and max_hd bounds tracking.
    Space Complexity: O(N), for the hash map storing vertical line sums and the recursion stack.

    Love Babbar Style Approach:
    Horizontal Distance (HD) Tracking via DFS + Unordered Map + Bounds Tracking:

    1. INTUITION:
       - Using `unordered_map<int, int>` gives O(1) average time per node insertion/lookup.
       - Since `unordered_map` does not store keys in sorted order, we track the minimum
         horizontal distance `min_hd` and maximum horizontal distance `max_hd` during DFS.
       - After DFS finishes, we iterate `for (int i = min_hd; i <= max_hd; i++)` and push `mp[i]` into `ans`.

    2. ALGORITHM:
       - Helper `solve(root, hd, min_hd, max_hd, mp)`:
         * Base Case: `if (root == NULL)` return.
         * Update bounds: `min_hd = min(min_hd, hd); max_hd = max(max_hd, hd);`
         * Accumulate: `mp[hd] += root->data;`
         * Recurse left: `solve(root->left, hd - 1, min_hd, max_hd, mp);`
         * Recurse right: `solve(root->right, hd + 1, min_hd, max_hd, mp);`
       - In `verticalSum(root)`:
         * If `root == NULL` return `{}`.
         * Initialize `unordered_map<int, int> mp`, `min_hd = 0`, `max_hd = 0`.
         * Call `solve(root, 0, min_hd, max_hd, mp)`.
         * Loop `for (int i = min_hd; i <= max_hd; i++)` -> push `mp[i]` to `ans`.
         * Return `ans`.

    Dry Run:
             1 (hd=0)
           /   \
          2     3
     (hd=-1)   (hd=+1)
        / \     / \
       4   5   6   7
   (hd=-2)(hd=0)(hd=0)(hd=+2)

    min_hd = -2, max_hd = 2
    - i = -2 : mp[-2] = 4
    - i = -1 : mp[-1] = 2
    - i =  0 : mp[0]  = 1 + 5 + 6 = 12
    - i =  1 : mp[1]  = 3
    - i =  2 : mp[2]  = 7

    Output vector: [4, 2, 12, 3, 7] ✓
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
    void solve(Node* root, int hd, int& min_hd, int& max_hd, unordered_map<int, int>& mp) {
        if (root == NULL) return;

        // Update range bounds
        min_hd = min(min_hd, hd);
        max_hd = max(max_hd, hd);

        // Accumulate node data into hash map
        mp[hd] += root->data;

        // Recurse left and right subtrees
        solve(root->left, hd - 1, min_hd, max_hd, mp);
        solve(root->right, hd + 1, min_hd, max_hd, mp);
    }

public:
    // GFG Signature - Unordered Map O(N) Approach
    vector<int> verticalSum(Node *root) {
        if (root == NULL) return {};

        unordered_map<int, int> mp;
        int min_hd = 0, max_hd = 0;

        solve(root, 0, min_hd, max_hd, mp);

        vector<int> ans;
        for (int i = min_hd; i <= max_hd; i++) {
            ans.push_back(mp[i]);
        }

        return ans;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //             1
    //           /   \
    //          2     3
    //         / \   / \
    //        4   5 6   7
    // Expected Output: 4 2 12 3 7
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);
    root1->right->left = new Node(6);
    root1->right->right = new Node(7);

    vector<int> res1 = ob.verticalSum(root1);

    cout << "Example 1 Vertical Sums: ";
    for (int sum : res1) cout << sum << " ";
    cout << "\n";

    // Example 2:
    //         1
    //        /
    //       2
    //      /
    //     3
    // Expected Output: 3 2 1
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->left->left = new Node(3);

    vector<int> res2 = ob.verticalSum(root2);

    cout << "Example 2 Vertical Sums: ";
    for (int sum : res2) cout << sum << " ";
    cout << "\n";

    return 0;
}
