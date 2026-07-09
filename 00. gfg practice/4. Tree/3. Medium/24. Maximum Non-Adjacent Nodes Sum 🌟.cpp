/*
    Problem Name: Maximum Non-Adjacent Nodes Sum
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary tree, select a subset of nodes such that the sum is MAXIMIZED,
    with the condition that no two selected nodes are directly connected (parent-child).
    This is the "House Robber III" problem on trees!

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. Each node visited exactly once.
    Space Complexity: O(H), where H is the height of the tree, for the recursion stack.

    Love Babbar Style Approach:
    At every node, we have exactly TWO choices:

    Choice 1 — INCLUDE this node:
        If we include this node, we CANNOT include its children (they're directly connected).
        But we CAN include its grandchildren!
        Sum = node->data + grandchildren sums (children's "exclude" values)

    Choice 2 — EXCLUDE this node:
        If we skip this node, we're FREE to include or exclude its children — pick the
        best option for each child!
        Sum = max(include, exclude) for left child + max(include, exclude) for right child

    The TRICK: Return a PAIR {include, exclude} from each recursive call!
        - include = node->data + left.exclude + right.exclude
        - exclude = max(left.include, left.exclude) + max(right.include, right.exclude)

    Final answer = max(root.include, root.exclude)

    WHY does this avoid the classic O(2^N) blowup?
    Because each node is processed ONCE, and we carry both states (include/exclude)
    in a single pass — no repeated subproblems, no memoization needed!

    Dry Run:
    Tree:       1
               / \
              2   3
             /   / \
            4   5   6

    - solve(4): leaf → include=4, exclude=0 → return {4, 0}
    - solve(2): left={4,0}, right={0,0}
        include = 2 + 0 + 0 = 2     (include 2, so exclude children: left.exc=0, right.exc=0)
        exclude = max(4,0) + max(0,0) = 4  (skip 2, best of each child)
        → return {2, 4}

    - solve(5): leaf → return {5, 0}
    - solve(6): leaf → return {6, 0}
    - solve(3): left={5,0}, right={6,0}
        include = 3 + 0 + 0 = 3     (include 3, exclude both children)
        exclude = max(5,0) + max(6,0) = 11  (skip 3, take both children!)
        → return {3, 11}

    - solve(1): left={2,4}, right={3,11}
        include = 1 + 4 + 11 = 16   (include 1, so exclude children: left.exc=4, right.exc=11)
        exclude = max(2,4) + max(3,11) = 4 + 11 = 15  (skip 1, best of each child)
        → return {16, 15}

    Answer = max(16, 15) = 16 ✓
    Selected nodes: 1, 4, 5, 6 → sum = 1+4+5+6 = 16 ✓
*/

#include <iostream>
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
    // Returns {include, exclude} pair for the subtree rooted at this node.
    // include = max sum if we INCLUDE this node
    // exclude = max sum if we EXCLUDE this node
    pair<int, int> solve(Node* root) {
        // Base Case: NULL node contributes nothing
        if (root == NULL) return {0, 0};

        // 1. Get include/exclude pairs from both children
        pair<int, int> leftPair  = solve(root->left);
        pair<int, int> rightPair = solve(root->right);

        // 2. INCLUDE this node:
        //    We take this node's value, but MUST exclude both children
        int include = root->data + leftPair.second + rightPair.second;

        // 3. EXCLUDE this node:
        //    For each child, we're FREE to pick whichever gives the better sum
        int exclude = max(leftPair.first,  leftPair.second)
                    + max(rightPair.first, rightPair.second);

        return {include, exclude};
    }

public:
    // GFG Signature
    int getMaxSum(Node* root) {
        pair<int, int> result = solve(root);

        // The answer is whichever choice gives the bigger sum at the root
        return max(result.first, result.second);
    }
};

int main() {
    // Example 1:
    //     11
    //    /  \
    //   1    2
    // Expected: 11 (just take the root, skip children 1+2=3 < 11)

    Node* root1 = new Node(11);
    root1->left  = new Node(1);
    root1->right = new Node(2);

    Solution ob;
    // Output: 11
    cout << "Max Non-Adjacent Sum (Example 1): " << ob.getMaxSum(root1) << "\n";

    // Example 2:
    //       1
    //      / \
    //     2   3
    //    /   / \
    //   4   5   6
    // Expected: 16 (nodes 1, 4, 5, 6 → 1+4+5+6 = 16)

    Node* root2 = new Node(1);
    root2->left        = new Node(2);
    root2->right       = new Node(3);
    root2->left->left  = new Node(4);
    root2->right->left = new Node(5);
    root2->right->right = new Node(6);

    // Output: 16
    cout << "Max Non-Adjacent Sum (Example 2): " << ob.getMaxSum(root2) << "\n";

    return 0;
}
