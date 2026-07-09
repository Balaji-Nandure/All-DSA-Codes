/*
    Problem Name: Maximum path sum
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree, find the maximum path sum. The path may start
    and end at ANY node in the tree (not necessarily root-to-leaf).
    Note: Node values can be NEGATIVE!

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node exactly once.
    Space Complexity: O(H), where H is the height of the tree, for the recursion stack.

    Love Babbar Style Approach:
    This is the CLASSIC "Maximum Path Sum" problem — one of the trickiest tree problems!

    The KEY insight — at every node, there are TWO different things to think about:

    Thing 1 — "What's the best path that PASSES THROUGH this node (bending here)?"
        This path uses the node as a "turning point" — it goes:
        leftSubtree → currentNode → rightSubtree
        Sum = leftMax + node->data + rightMax
        This is a CANDIDATE for the global answer, so we check it against `maxSum`.

    Thing 2 — "What can I OFFER to my parent?"
        A path can only go UP to the parent through ONE side (left OR right), not both!
        If a path bends at this node (uses both sides), it CAN'T extend further upward.
        So we return: node->data + max(leftMax, rightMax) — the BEST single-sided path.

    CRITICAL TRICK: If a subtree contributes a NEGATIVE sum, we DON'T take it!
        We clamp leftMax and rightMax to 0 using max(0, ...).
        WHY? A negative contribution only makes our path WORSE — better to not include it.

    Algorithm:
    1. Recursively get leftMax = max(0, solve(left))  — best gain from left (or 0 if negative)
    2. Recursively get rightMax = max(0, solve(right)) — best gain from right (or 0 if negative)
    3. Update global maxSum = max(maxSum, leftMax + node->data + rightMax)  — path THROUGH node
    4. RETURN node->data + max(leftMax, rightMax)  — best single-sided path to OFFER to parent

    Dry Run:
    Tree:        10
                /  \
               2    10
              / \     \
             20   1   -25
                     /   \
                    3     4
    
    - solve(-25): left=max(0,3)=3, right=max(0,4)=4
                  maxSum = max(INT_MIN, 3+(-25)+4) = max(INT_MIN, -18) → -18
                  return -25 + max(3,4) = -21 → parent gets max(0, -21) = 0

    - solve(10, right child): left=max(0,0)=0, right=max(0,0)=0
                              Actually right child of 10 is -25, which returns -21
                              rightMax = max(0, -21) = 0
                              maxSum = max(-18, 0+10+0) = 10
                              return 10 + max(0,0) = 10

    - solve(20): leaf → leftMax=0, rightMax=0
                 maxSum = max(10, 0+20+0) = 20
                 return 20

    - solve(1):  leaf → maxSum = max(20, 0+1+0) = 20
                 return 1

    - solve(2):  leftMax=max(0,20)=20, rightMax=max(0,1)=1
                 maxSum = max(20, 20+2+1) = max(20, 23) = 23
                 return 2 + max(20,1) = 22

    - solve(10, root): leftMax=max(0,22)=22, rightMax=max(0,10)=10
                       maxSum = max(23, 22+10+10) = max(23, 42) = 42 ← ANSWER!
                       return 10 + max(22,10) = 32

    Final Answer: 42 ✓  (Path: 20→2→10→10)
*/

#include <iostream>
#include <climits>
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
    // Returns the max sum of a single-sided path starting from this node going downward.
    // Also updates global maxSum whenever a "bending" path through this node beats it.
    int solve(Node* root, int& maxSum) {
        // Base Case: NULL contributes 0 (no gain, no loss)
        if (root == NULL) return 0;

        // 1. Get the BEST gain from left and right subtrees
        //    CLAMP to 0: if a subtree is negative, DON'T include it — it only hurts us!
        int leftMax  = max(0, solve(root->left,  maxSum));
        int rightMax = max(0, solve(root->right, maxSum));

        // 2. The path that BENDS at this node (uses both sides):
        //    leftMax + currentNode + rightMax
        //    This is a CANDIDATE for the global maximum path sum!
        int pathThroughNode = leftMax + root->data + rightMax;
        maxSum = max(maxSum, pathThroughNode);

        // 3. OFFER to parent: can only go UP through ONE side (no bending allowed upward)
        //    Pick the better side + current node's value
        return root->data + max(leftMax, rightMax);
    }

public:
    // GFG Signature
    int findMaxSum(Node* root) {
        int maxSum = INT_MIN;  // Start with smallest possible — handles all-negative trees!

        solve(root, maxSum);

        return maxSum;
    }
};

int main() {
    // Example 1:
    //          10
    //         /  \
    //        2    10
    //       / \     \
    //      20   1   -25
    //               /  \
    //              3    4
    // Expected: 42  (path: 20→2→10→10)

    Node* root1 = new Node(10);
    root1->left              = new Node(2);
    root1->right             = new Node(10);
    root1->left->left        = new Node(20);
    root1->left->right       = new Node(1);
    root1->right->right      = new Node(-25);
    root1->right->right->left  = new Node(3);
    root1->right->right->right = new Node(4);

    Solution ob;
    // Output: 42
    cout << "Max Path Sum (Example 1): " << ob.findMaxSum(root1) << "\n";

    // Example 2:
    //      -17
    //      /  \
    //     11   4
    //    / \  /
    //   20 -2 10
    // Expected: 31  (path: 20→11→(-17)→... no wait, let's see)
    // Actually path: 20→11 = 31 (just take 20 + 11, don't go through -17)
    // OR: 20→11→(-17)→4→10 = 28? No, 31 > 28.
    // So: path 20→11 = 31 ✓

    Node* root2 = new Node(-17);
    root2->left         = new Node(11);
    root2->right        = new Node(4);
    root2->left->left   = new Node(20);
    root2->left->right  = new Node(-2);
    root2->right->left  = new Node(10);

    // Output: 31
    cout << "Max Path Sum (Example 2): " << ob.findMaxSum(root2) << "\n";

    return 0;
}
