/*
    Problem Name: Common Nodes in Two BSTs
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the roots r1 and r2 of two Binary Search Trees (BST), find all nodes that are
    present in both trees (the intersection of the two BSTs).
    Return the common node values in sorted order.

    Examples:
    Input: r1 = [5, 1, 10, 0, 4, 7, N, N, N, N, N, N, 9], r2 = [10, 7, 20, 4, 9, N, N]
    Output: [4, 7, 9, 10]

    Input: r1 = [10, 2, 11, 1, 3, N, N], r2 = [2, 1, 3]
    Output: [1, 2, 3]

    Constraints:
    1 <= no. of nodes in r1, r2 <= 10^5
    0 <= node->data <= 10^9

    Expected Complexities:
    Time Complexity: O(N1 + N2), where N1 and N2 are the number of nodes in r1 and r2.
    Space Complexity: O(H1 + H2), using iterative two-stack inorder traversal.

    Love Babbar Style Approach:
    Iterative Two-Stack Inorder Traversal (Simultaneous / Controlled Inorder):

    1. INTUITION:
       - Since both trees are BSTs, an INORDER traversal yields values in SORTED order.
       - Instead of storing full array representations in memory, we simulate inorder traversal of
         BOTH trees SIMULTANEOUSLY using two stacks `s1` and `s2`!
       - At any moment, the top of `s1` and `s2` hold the current smallest unvisited node
         from tree 1 and tree 2 respectively.

    2. ALGORITHM:
       - Maintain two stacks `s1` and `s2`.
       - Outer loop `while (true)`:
         * Push all left nodes of `r1` into `s1` while `r1 != NULL`.
         * Push all left nodes of `r2` into `s2` while `r2 != NULL`.
         * If either stack is empty, we cannot compare pairs anymore -> break.
         * Peek `n1 = s1.top()` and `n2 = s2.top()`.
         * If `n1->data == n2->data`:
           - Match found! Add `n1->data` to `ans`.
           - Pop both `s1` and `s2`.
           - Move `r1 = n1->right` and `r2 = n2->right`.
         * Else if `n1->data < n2->data`:
           - `n1` is smaller, so pop `s1`.
           - Move `r1 = n1->right` and set `r2 = nullptr` (so tree 2 stack top stays intact!).
         * Else (`n1->data > n2->data`):
           - `n2` is smaller, so pop `s2`.
           - Move `r2 = n2->right` and set `r1 = nullptr` (so tree 1 stack top stays intact!).

    Dry Run:
    r1 Inorder: [0, 1, 4, 5, 7, 9, 10]
    r2 Inorder: [4, 7, 9, 10, 20]

    - s1.top() = 0, s2.top() = 4  -> 0 < 4  => pop s1, r1 = 0->right, r2 = nullptr
    - s1.top() = 1, s2.top() = 4  -> 1 < 4  => pop s1, r1 = 1->right, r2 = nullptr
    - s1.top() = 4, s2.top() = 4  -> MATCH! => push 4 to ans, pop both, r1 = 4->right, r2 = 4->right
    - s1.top() = 5, s2.top() = 7  -> 5 < 7  => pop s1, r1 = 5->right, r2 = nullptr
    - s1.top() = 7, s2.top() = 7  -> MATCH! => push 7 to ans, pop both, r1 = 7->right, r2 = 7->right
    - s1.top() = 9, s2.top() = 9  -> MATCH! => push 9 to ans, pop both, r1 = 9->right, r2 = 9->right
    - s1.top() = 10, s2.top() = 10 -> MATCH! => push 10 to ans, pop both, r1 = 10->right, r2 = 10->right

    Result: [4, 7, 9, 10] ✓
*/

#include <iostream>
#include <vector>
#include <stack>

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
public:
    // GFG Signature - Controlled Two-Stack Inorder Traversal
    vector<int> findCommon(Node *r1, Node *r2) {
        vector<int> ans;

        stack<Node*> s1, s2;

        while (true) {

            while (r1) {
                s1.push(r1);
                r1 = r1->left;
            }

            while (r2) {
                s2.push(r2);
                r2 = r2->left;
            }

            if (s1.empty() || s2.empty())
                break;

            Node* n1 = s1.top();
            Node* n2 = s2.top();

            if (n1->data == n2->data) {
                ans.push_back(n1->data);

                s1.pop();
                s2.pop();

                r1 = n1->right;
                r2 = n2->right;
            }
            else if (n1->data < n2->data) {
                s1.pop();
                r1 = n1->right;
                r2 = nullptr;
            }
            else {
                s2.pop();
                r2 = n2->right;
                r1 = nullptr;
            }
        }

        return ans;
    }
};

int main() {
    Solution ob;

    // Example 1:
    // Tree 1:
    //         5
    //       /   \
    //      1     10
    //     / \   /
    //    0   4 7
    //           \
    //            9
    Node* r1 = new Node(5);
    r1->left = new Node(1);
    r1->right = new Node(10);
    r1->left->left = new Node(0);
    r1->left->right = new Node(4);
    r1->right->left = new Node(7);
    r1->right->left->right = new Node(9);

    // Tree 2:
    //         10
    //        /  \
    //       7    20
    //      / \
    //     4   9
    Node* r2 = new Node(10);
    r2->left = new Node(7);
    r2->right = new Node(20);
    r2->left->left = new Node(4);
    r2->left->right = new Node(9);

    vector<int> common1 = ob.findCommon(r1, r2);

    cout << "Example 1 Common Nodes: ";
    for (int val : common1) {
        cout << val << " ";
    }
    cout << "\n";
    // Expected: 4 7 9 10

    // Example 2:
    // r1: root=10, left=2 (left=1, right=3), right=11
    // r2: root=2, left=1, right=3
    Node* r1_ex2 = new Node(10);
    r1_ex2->left = new Node(2);
    r1_ex2->right = new Node(11);
    r1_ex2->left->left = new Node(1);
    r1_ex2->left->right = new Node(3);

    Node* r2_ex2 = new Node(2);
    r2_ex2->left = new Node(1);
    r2_ex2->right = new Node(3);

    vector<int> common2 = ob.findCommon(r1_ex2, r2_ex2);

    cout << "Example 2 Common Nodes: ";
    for (int val : common2) {
        cout << val << " ";
    }
    cout << "\n";
    // Expected: 1 2 3

    return 0;
}
