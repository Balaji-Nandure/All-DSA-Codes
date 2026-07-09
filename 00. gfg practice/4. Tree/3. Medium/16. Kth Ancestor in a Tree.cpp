/*
    Problem Name: Kth Ancestor in a Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary tree, a target node value, and a positive integer k, find the kth ancestor
    of the target node. The kth ancestor is the node that is exactly k levels above the target.
    Return -1 if no such ancestor exists.
    Note: All node values are DISTINCT and the target node is GUARANTEED to exist.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We do a single DFS pass.
    Space Complexity: O(H), where H is the height of the tree, for the recursion stack.

    Love Babbar Style Approach:
    The KEY insight — instead of finding the path from root to node (and then counting k
    steps backward), we let the RECURSION ITSELF do the counting as it UNWINDS (backtracks)!

    Our helper `solve(root, node, k)` returns an integer that means:
        -1    --> The target node was NOT found in this subtree at all.
         0    --> We JUST found the target node at this current node!
         1    --> We are 1 level above the target.
         2    --> We are 2 levels above the target.
         ...  --> And so on.

    At each step as we backtrack, we increment this "distance counter" by 1.
    The MOMENT the distance counter hits k, the CURRENT NODE is the kth ancestor — SAVE IT!

    But here's the subtle trick: after saving the answer, we must keep returning upward
    without overwriting `ans`. Since `dist` will keep incrementing (k+1, k+2...), and we only
    set `ans` when `dist == k`, this naturally happens only once. 

    Dry Run:
    Tree:       1
               / \
              2   3
             / \
            4   5
    node = 4, k = 2

    - solve(1, 4, 2, ans)
        - solve(2, 4, 2, ans)
            - solve(4, 4, 2, ans): root->data == 4 → return 0  (FOUND!)
            - solve(5, 4, 2, ans): → return -1 (not found)
            - dist = 0 (from left side)
            - dist++ = 1  (node 2 is 1 level above node 4)
            - dist == k?  1 == 2? NO → don't save yet
            - return 1
        - solve(3, 4, 2, ans): → return -1 (not found)
        - dist = 1 (from left side)
        - dist++ = 2  (node 1 is 2 levels above node 4)
        - dist == k?  2 == 2? YES → ans = root->data = 1  ← kth ANCESTOR FOUND!
        - return 2
    - Answer: 1 ✓

    Dry Run 2:
    Tree:  1       node = 2, k = 3
          / \
         3   2
    
    - solve(1, 2, 3): left→-1, right→0 (found node 2), dist=0→1. 1==3? NO → return 1
    - We return 1 to our caller (main), ans is NEVER set → remains -1
    - Answer: -1 ✓ (node 2 only has one ancestor — node 1 — not 3!)
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
    // Returns -1 if node not found, or the distance (levels above) from the target node.
    // Sets `ans` when the distance reaches exactly k.
    int solve(Node* root, int node, int k, int& ans) {
        // Base Case: Fell off the tree — target not found in this path
        if (root == NULL) return -1;

        // TARGET FOUND: We are 0 levels above it (we ARE it!)
        if (root->data == node) return 0;

        // Search in both subtrees
        int leftDist  = solve(root->left,  node, k, ans);
        int rightDist = solve(root->right, node, k, ans);

        // Figure out which side actually found the target
        // (only one side can find it since all values are distinct)
        int dist = -1;
        if (leftDist  != -1) dist = leftDist;
        if (rightDist != -1) dist = rightDist;

        // Node not found in either subtree — propagate -1 upward
        if (dist == -1) return -1;

        // We are one level ABOVE the subtree that found the node
        dist++;

        // JACKPOT: We are exactly k levels above the target — save the answer!
        if (dist == k) {
            ans = root->data;
        }

        // Pass the updated distance upward for further counting
        return dist;
    }

public:
    // GFG Signature
    int kthAncestor(Node* root, int k, int node) {
        int ans = -1;  // Default: assume no kth ancestor exists

        solve(root, node, k, ans);

        // ans is set inside solve() only when the kth ancestor is found
        return ans;
    }
};

int main() {
    // Example 1:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    // node = 4, k = 2  -->  Expected: 1

    Node* root1 = new Node(1);
    root1->left         = new Node(2);
    root1->right        = new Node(3);
    root1->left->left   = new Node(4);
    root1->left->right  = new Node(5);

    Solution ob;
    // Output: 1
    cout << "Kth Ancestor (Example 1): " << ob.kthAncestor(root1, 2, 4) << "\n";

    // Example 2:
    //   1
    //  / \
    // 2   3
    // node = 3, k = 1  -->  Expected: 1

    Node* root2 = new Node(1);
    root2->left  = new Node(2);
    root2->right = new Node(3);

    // Output: 1
    cout << "Kth Ancestor (Example 2): " << ob.kthAncestor(root2, 1, 3) << "\n";

    // Example 3:
    //   1
    //  / \
    // 3   2
    // node = 2, k = 3  -->  Expected: -1 (only 1 ancestor exists)

    Node* root3 = new Node(1);
    root3->left  = new Node(3);
    root3->right = new Node(2);

    // Output: -1
    cout << "Kth Ancestor (Example 3): " << ob.kthAncestor(root3, 3, 2) << "\n";

    return 0;
}
