/*
    Problem Name: K Sum Paths
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree and an integer k, find the number of downward-only
    paths where the sum of node values equals k.
    A path can start and end at ANY node, but must always move downward (parent to child).
    Note: Node values can be NEGATIVE, so we can't prune early!

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node exactly once.
    Space Complexity: O(N), for the prefix sum HashMap and the recursion stack.

    Love Babbar Style Approach:
    The Brute Force would be: for every node, run a DFS downward and count paths summing to k.
    That's O(N^2). We can do MUCH better!

    The KEY insight — think of it like "Subarray Sum Equals K" but on a TREE!
    We use the PREFIX SUM trick:

    As we go from root to any node, we track `currentSum` = sum of all values on this root-to-node path.
    We maintain a HashMap `prefixCount` (prefixSum -> how many times this sum appeared on the current path).

    The MAGIC: If at any ancestor on the current path, the prefix sum was `currentSum - k`,
    then the path FROM that ancestor's child TO the current node sums to exactly k!

    So at every node: count += prefixCount[currentSum - k]

    CRITICAL: After processing a node's subtrees, we BACKTRACK by decrementing its prefix sum
    in the map. This ensures sibling branches don't wrongly use each other's prefix sums!

    Algorithm:
    1. Initialize prefixCount = {0 : 1} (the "empty path" with sum 0 counts once, to handle
       paths that start from the root itself!)
    2. DFS: at each node,
       a) currentSum += node->data
       b) count += prefixCount[currentSum - k]
       c) prefixCount[currentSum]++
       d) Recurse left and right
       e) BACKTRACK: prefixCount[currentSum]--  <-- This is the KEY step!
    3. Return count.

    Dry Run:
    Tree:       1
               / \
              2   3
    k = 3

    prefixCount = {0: 1}, count = 0

    - Visit Node(1): currentSum = 1
        - prefixCount[1 - 3] = prefixCount[-2] = 0  --> count stays 0
        - prefixCount[1]++ --> prefixCount = {0:1, 1:1}

        - Visit Node(2): currentSum = 3
            - prefixCount[3 - 3] = prefixCount[0] = 1  --> count = 1 ✓  (path: 1→2)
            - prefixCount[3]++ --> prefixCount = {0:1, 1:1, 3:1}
            - Visit NULL, Visit NULL
            - BACKTRACK: prefixCount[3]-- --> prefixCount = {0:1, 1:1, 3:0}

        - Visit Node(3): currentSum = 4
            - prefixCount[4 - 3] = prefixCount[1] = 1  --> count = 2 ✓  (path: 3 alone!)
              WHY? Because prefix sum '1' means the path from root(1) covers sum 1.
              So from root's child onwards to current node = sum 4 - 1 = 3 = k!
            - prefixCount[4]++ --> prefixCount = {0:1, 1:1, 3:0, 4:1}
            - Visit NULL, Visit NULL
            - BACKTRACK: prefixCount[4]-- --> prefixCount = {0:1, 1:1, 3:0, 4:0}

        - BACKTRACK: prefixCount[1]-- --> prefixCount = {0:1, 1:0, ...}

    Final count = 2 ✓  (Paths: [1→2] and [3])
*/

#include <iostream>
#include <unordered_map>

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
    void solve(Node* root, int k, long long currentSum, int& count, unordered_map<long long, int>& prefixCount) {
        // Base Case: Fallen off the tree — nothing to process
        if (root == NULL) return;

        // 1. Add current node's value to the running prefix sum
        currentSum += root->data;

        // 2. THE MAGIC: If (currentSum - k) exists as a prefix sum on this path,
        //    those paths from that point to NOW sum exactly to k. Count them all!
        count += prefixCount[currentSum - k];

        // 3. Record this prefix sum — we're about to go deeper
        prefixCount[currentSum]++;

        // 4. Recurse into both subtrees
        solve(root->left,  k, currentSum, count, prefixCount);
        solve(root->right, k, currentSum, count, prefixCount);

        // 5. BACKTRACK: Remove this node's prefix sum before returning to parent.
        //    CRUCIAL! Without this, sibling branches would incorrectly use our path's sums.
        prefixCount[currentSum]--;
    }

public:
    // GFG Signature
    int sumK(Node* root, int k) {
        unordered_map<long long, int> prefixCount;

        // Seed: an empty path has sum 0. This handles paths starting from the root.
        prefixCount[0] = 1;

        int count = 0;
        solve(root, k, 0, count, prefixCount);

        return count;
    }
};

int main() {
    // Example 1:
    //           8
    //          / \
    //         4   5
    //        / \   \
    //       3   2   2
    //      / \   \
    //     3  -2   1
    // k = 7  --> Expected: 3
    // Paths: [4→3], [4→2→1], [5→2]

    Node* root1 = new Node(8);
    root1->left              = new Node(4);
    root1->right             = new Node(5);
    root1->left->left        = new Node(3);
    root1->left->right       = new Node(2);
    root1->right->right      = new Node(2);
    root1->left->left->left  = new Node(3);
    root1->left->left->right = new Node(-2);
    root1->left->right->right = new Node(1);

    Solution ob;
    // Output: 3
    cout << "K Sum Paths (Example 1): " << ob.sumK(root1, 7) << "\n";

    // Example 2:
    //     1
    //    / \
    //   2   3
    // k = 3  --> Expected: 2
    // Paths: [1→2], [3]

    Node* root2 = new Node(1);
    root2->left  = new Node(2);
    root2->right = new Node(3);

    // Output: 2
    cout << "K Sum Paths (Example 2): " << ob.sumK(root2, 3) << "\n";

    return 0;
}
