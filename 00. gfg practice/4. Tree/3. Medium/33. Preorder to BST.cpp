/*
    Problem Name: Preorder to BST
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an array pre[] representing the preorder traversal of a Binary Search Tree,
    construct the corresponding BST and return its root.
    Note: All node values are distinct.

    Examples:
    Input: pre[] = [40, 30, 35, 80, 100]
    Output: [40, 30, 80, N, 35, N, 100]
    Explanation:
               40
             /    \
            30    80
              \     \
              35    100

    Input: pre[] = [10, 5, 1, 7, 40, 50]
    Output: [10, 5, 40, 1, 7, N, 50]

    Constraints:
    1 <= n <= 10^3
    1 <= pre[i] <= 10^4

    Expected Complexities:
    Time Complexity: O(N), where N is the size of pre[]. Each element is processed once.
    Space Complexity: O(H), where H is the height of the BST, for the recursion call stack.

    Love Babbar Style Approach:
    Range-Bound Approach [minVal, maxVal] with Index Passed by Reference:

    1. INTUITION:
       - Preorder traversal processes nodes in order: [Root -> Left Subtree -> Right Subtree].
       - Every node in a BST must satisfy a valid range `[mn, mx]`:
         * Left child range  --> `[mn, root->data]`
         * Right child range --> `[root->data, mx]`
       - Instead of relying on a class/global member variable for `idx`, we pass `idx` BY REFERENCE (`int& idx`).
       - This ensures pure recursive function state while sharing the current index progression across calls!

    2. ALGORITHM:
       - `build(pre, idx, mn, mx)`:
         * Base Case 1: `idx == pre.size()` -> return `NULL`.
         * Base Case 2: `pre[idx] < mn || pre[idx] > mx` -> return `NULL`.
         * Create `root = new Node(pre[idx++])`.
         * `root->left = build(pre, idx, mn, root->data)`.
         * `root->right = build(pre, idx, root->data, mx)`.
         * Return `root`.

    Dry Run:
    pre[] = [40, 30, 35, 80, 100], idx = 0

    - build(idx=0, INT_MIN, INT_MAX): pre[0]=40 valid -> Node(40), idx becomes 1
      - root->left: build(idx=1, INT_MIN, 40): pre[1]=30 valid -> Node(30), idx becomes 2
        - root->left: build(idx=2, INT_MIN, 30): pre[2]=35 out of range (>30) -> NULL
        - root->right: build(idx=2, 30, 40): pre[2]=35 valid -> Node(35), idx becomes 3
          - root->left: build(idx=3, 30, 35): pre[3]=80 out of range -> NULL
          - root->right: build(idx=3, 35, 40): pre[3]=80 out of range -> NULL
      - root->right: build(idx=3, 40, INT_MAX): pre[3]=80 valid -> Node(80), idx becomes 4
        - root->left: build(idx=4, 40, 80): pre[4]=100 out of range -> NULL
        - root->right: build(idx=4, 80, INT_MAX): pre[4]=100 valid -> Node(100), idx becomes 5

    Resulting BST constructed cleanly in O(N) time!
*/

#include <iostream>
#include <vector>
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
private:
    Node* build(vector<int>& pre, int& idx, int mn, int mx) {
        if (idx == pre.size())
            return NULL;

        if (pre[idx] < mn || pre[idx] > mx)
            return NULL;

        Node* root = new Node(pre[idx++]);

        root->left = build(pre, idx, mn, root->data);
        root->right = build(pre, idx, root->data, mx);

        return root;
    }

public:
    // GFG Signature
    Node* Bst(vector<int> &pre) {
        int idx = 0;
        return build(pre, idx, INT_MIN, INT_MAX);
    }
};

// Helper function to print Inorder Traversal (should produce sorted output for valid BST)
void printInorder(Node* root) {
    if (root == NULL) return;
    printInorder(root->left);
    cout << root->data << " ";
    printInorder(root->right);
}

int main() {
    Solution ob;

    // Example 1:
    // Input: pre[] = [40, 30, 35, 80, 100]
    vector<int> pre1 = {40, 30, 35, 80, 100};
    Node* root1 = ob.Bst(pre1);

    cout << "Example 1 (Preorder: 40 30 35 80 100)\n";
    cout << "Root Data       : " << (root1 ? root1->data : -1) << "\n";
    cout << "Inorder Traversal: ";
    printInorder(root1);
    cout << "\n\n";

    // Example 2:
    // Input: pre[] = [10, 5, 1, 7, 40, 50]
    vector<int> pre2 = {10, 5, 1, 7, 40, 50};
    Node* root2 = ob.Bst(pre2);

    cout << "Example 2 (Preorder: 10 5 1 7 40 50)\n";
    cout << "Root Data       : " << (root2 ? root2->data : -1) << "\n";
    cout << "Inorder Traversal: ";
    printInorder(root2);
    cout << "\n";

    return 0;
}
