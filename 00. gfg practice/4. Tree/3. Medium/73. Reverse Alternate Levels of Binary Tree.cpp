/*
    Problem Name: Reverse Alternate Levels of Binary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree, reverse the values of nodes at every alternate level
    from left to right, while keeping the tree structure unchanged. Only node values are modified.
    - Level 0 (Root) is even -> values unchanged.
    - Levels 1, 3, 5, ... are odd -> values are reversed from left to right.

    Examples:
    Input: root[] = [1, 2, 3, 42, 51, 63, 72]
    Output:
    - Level 0: [1]
    - Level 1: [3, 2] (Reversed 2 and 3)
    - Level 2: [42, 51, 63, 72] (Unchanged)

    Input: root[] = [1, 2, N, 3, 4, 5, N, N, 6]
    Output:
    - Level 1 contains only node 2 -> reversing it has no effect.
    - Level 3 values are reversed from left to right.

    Constraints:
    1 <= number of nodes <= 10^5
    1 <= nodes->data <= 10^5

    Expected Complexities:
    Time Complexity: O(N), single pass level order traversal.
    Space Complexity: O(N), for the level order queue and level vector.

    Love Babbar Style Approach:
    BFS Level Order Traversal with Two-Pointer Level Value Swapping:

    1. INTUITION:
       - Perform a level-by-level Breadth-First Search (BFS) using a queue.
       - Track the current `level` index (starting at 0 for root).
       - For each level:
         * Collect pointers to all nodes at that level into a vector `levelNodes`.
         * Enqueue left and right children for the next level.
         * If `level % 2 == 1` (odd level):
           - Use two pointers (`l = 0`, `r = sz - 1`) to swap node values:
             `swap(levelNodes[l]->data, levelNodes[r]->data)`
       - Increment `level++`.

    2. ALGORITHM:
       - `if (!root) return;`
       - Initialize `queue<Node*> q`, `int level = 0`.
       - `q.push(root);`
       - While (`!q.empty()`):
         * `int sz = q.size();`
         * `vector<Node*> levelNodes;`
         * For `i = 0` to `sz - 1`:
           - `Node* curr = q.front(); q.pop();`
           - `levelNodes.push_back(curr);`
           - `if (curr->left) q.push(curr->left);`
           - `if (curr->right) q.push(curr->right);`
         * If (`level % 2 == 1`):
           - `int l = 0, r = sz - 1;`
           - While (`l < r`):
             `swap(levelNodes[l]->data, levelNodes[r]->data);`
             `l++; r--;`
         * `level++;`

    Dry Run:
    root = [1, 2, 3, 42, 51, 63, 72]
    - Level 0 (even): levelNodes = [1]. No swap. q = [2, 3].
    - Level 1 (odd):  levelNodes = [2, 3]. Swap 2->data & 3->data -> values become [3, 2]. q = [42, 51, 63, 72].
    - Level 2 (even): levelNodes = [42, 51, 63, 72]. No swap.
    Values at Level 1 are successfully reversed ✓
*/

#include <iostream>
#include <vector>
#include <queue>
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
public:
    // GFG Signature - Reverse Alternate Levels
    void reverseAlternate(Node *root) {
        if (!root) return;

        queue<Node*> q;
        q.push(root);

        int level = 0;

        while (!q.empty()) {
            int sz = q.size();
            vector<Node*> levelNodes;

            for (int i = 0; i < sz; i++) {
                Node* curr = q.front();
                q.pop();

                levelNodes.push_back(curr);

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }

            // Reverse node values at odd levels (1, 3, 5...)
            if (level % 2 == 1) {
                int l = 0, r = sz - 1;
                while (l < r) {
                    swap(levelNodes[l]->data, levelNodes[r]->data);
                    l++;
                    r--;
                }
            }

            level++;
        }
    }
};

// Helper function to print level order traversal
void printLevelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            Node* curr = q.front();
            q.pop();
            cout << curr->data << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << "| ";
    }
    cout << "\n";
}

int main() {
    Solution ob;

    // Example 1:
    //            1
    //          /   \
    //         2     3
    //        / \   / \
    //       42 51 63 72
    // Expected Output Level 1 reversed: 1 | 3 2 | 42 51 63 72 |
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(42);
    root1->left->right = new Node(51);
    root1->right->left = new Node(63);
    root1->right->right = new Node(72);

    cout << "Before Reversal: ";
    printLevelOrder(root1);

    ob.reverseAlternate(root1);

    cout << "After Reversal:  ";
    printLevelOrder(root1);

    return 0;
}
