#include <iostream>
#include <algorithm>

using namespace std;

/**
 * Problem: Largest Independent Set Problem (LISS on Binary Tree)
 * 
 * Given a Binary Tree, find size of the Largest Independent Set (LIS) in it.
 * An Independent Set is a subset of all tree nodes such that no two nodes 
 * in the subset are directly connected by an edge.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is TREE DYNAMIC PROGRAMMING (Tree DP).
 * - Unlike linear arrays where adjacency was i vs i-1, on a tree adjacency is parent-child.
 * - Selecting a node directly forbids selecting its immediate children, but permits selecting 
 *   its grandchildren.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Optimal Bottom-Up Tree DP in O(N) Time and O(H) Space:
 *   For every node `root`, compute a pair:
 *     pair<int, int> solve(Node* root) = {include_root, exclude_root}
 *   
 *   Base Case:
 *     If root == nullptr: return {0, 0}.
 *   
 *   Recursive Step:
 *     auto left  = solve(root->left);
 *     auto right = solve(root->right);
 *     
 *     1. If root is INCLUDED:
 *        Neither left child nor right child can be included!
 *        They MUST take their `exclude` values:
 *        include_root = 1 + left.exclude + right.exclude.
 *     
 *     2. If root is EXCLUDED:
 *        Left child and right child can be EITHER included OR excluded (take max of each):
 *        exclude_root = max(left.include, left.exclude) + max(right.include, right.exclude).
 *   
 *   Result at root:
 *     max(result.include, result.exclude).
 *   
 *   Why this is optimal:
 *     Single post-order traversal visits each node once in O(N) time with zero hash map overhead!
 */

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
    // Returns pair<include_sum, exclude_sum> for subtree rooted at node
    pair<int, int> postorderDP(Node* root) {
        if (!root) return {0, 0};

        pair<int, int> left = postorderDP(root->left);
        pair<int, int> right = postorderDP(root->right);

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Case 1: If current root is included, its children MUST be excluded
        int include_root = 1 + left.second + right.second;

        // Case 2: If current root is excluded, children can independently choose best (included or excluded)
        int exclude_root = max(left.first, left.second) + max(right.first, right.second);

        return {include_root, exclude_root};
    }

public:
    int LISS(Node* root) {
        pair<int, int> res = postorderDP(root);
        // *** CRUCIAL LINE: Pick maximum between including and excluding tree root ***
        return max(res.first, res.second);
    }
};

int main() {
    Solution sol;
    // Construct sample tree:
    //         10
    //        /  \
    //       20   30
    //      /  \    \
    //     40  50   60
    Node* root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(40);
    root->left->right = new Node(50);
    root->right->right = new Node(60);

    cout << "Size of Largest Independent Set: " << sol.LISS(root) << "\n";
    // Independent Set: {10, 40, 50, 60} (size 4) or {20, 30} (size 2).
    // Maximum size = 4. Expected: 4.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single post-order traversal visiting all N nodes exactly once.
 * - Space Complexity: O(H) recursion call stack depth where H is the height of the tree.
 */
