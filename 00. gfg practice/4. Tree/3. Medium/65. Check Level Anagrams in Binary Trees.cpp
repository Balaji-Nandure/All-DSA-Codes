/*
    Problem Name: Check Level Anagrams in Binary Trees
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the roots of two binary trees root1 and root2, check whether the nodes at every
    corresponding level of the two trees are anagrams of each other.
    - Two levels are anagrams if they contain the exact same node values with the same frequencies,
      regardless of their ordering.
    - Return true if every corresponding level is an anagram; otherwise return false.

    Examples:
    Input: root1 = [1, 3, 2, N, N, 5, 4], root2 = [1, 2, 3, 4, 5, N, N]
    Output: true
    Explanation:
    - Level 0: [1] vs [1] -> Anagram
    - Level 1: [3, 2] vs [2, 3] -> Anagram
    - Level 2: [5, 4] vs [4, 5] -> Anagram
    All corresponding levels are anagrams -> true.

    Input: root1 = [1, 2, 3, 5, 4], root2 = [1, 2, 4, 5, 3]
    Output: false
    Explanation:
    - Level 0: [1] vs [1] -> Anagram
    - Level 1: [2, 3] vs [2, 4] -> Not Anagram! -> false.

    Constraints:
    1 <= n <= 10^4
    1 <= Node.data <= 10^9

    Expected Complexities:
    Time Complexity: O(N log N), for level-by-level sorting comparison.
    Space Complexity: O(N), for the two BFS level order queues.

    Love Babbar Style Approach:
    Simultaneous BFS Level Order Traversal + Sorted Vector Anagram Check:

    1. INTUITION:
       - To check if two trees have level-by-level anagrams:
         * Traverse both trees SIMULTANEOUSLY using BFS (Level Order).
         * At each level `L`:
           - If `q1.size() != q2.size()`, the two trees have a different number of nodes at level `L` -> Return `false`.
           - Collect all node values at level `L` into `level1` and `level2`.
           - Sort `level1` and `level2`.
           - If `level1 != level2`, the nodes at level `L` are NOT anagrams -> Return `false`.
           - Enqueue valid left and right children for the next level.
         * After the loop, if one queue is not empty while the other is, trees have different heights -> Return `false`.

    2. ALGORITHM:
       - `if (!root1 && !root2) return true;`
       - `if (!root1 || !root2) return false;`
       - `queue<Node*> q1, q2;`
       - `q1.push(root1); q2.push(root2);`
       - While (`!q1.empty()` && `!q2.empty()`):
         * `if (q1.size() != q2.size()) return false;`
         * `int sz = q1.size();`
         * `vector<int> level1, level2;`
         * For `i = 0` to `sz - 1`:
           - `Node* c1 = q1.front(); q1.pop();`
           - `Node* c2 = q2.front(); q2.pop();`
           - `level1.push_back(c1->data);`
           - `level2.push_back(c2->data);`
           - `if (c1->left) q1.push(c1->left);`
           - `if (c1->right) q1.push(c1->right);`
           - `if (c2->left) q2.push(c2->left);`
           - `if (c2->right) q2.push(c2->right);`
         * `sort(level1.begin(), level1.end());`
         * `sort(level2.begin(), level2.end());`
         * `if (level1 != level2) return false;`
       - `if (!q1.empty() || !q2.empty()) return false;`
       - Return `true`.

    Dry Run:
    root1 = [1, 2, 3, 5, 4], root2 = [1, 2, 4, 5, 3]

    - Level 0:
      level1 = [1], level2 = [1] -> equal!
      q1 = [2, 3], q2 = [2, 4]

    - Level 1:
      level1 = [2, 3], level2 = [2, 4]
      Sort: level1 = [2, 3], level2 = [2, 4]
      level1 != level2 -> Returns false ✓
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
    // GFG Signature
    bool areAnagrams(Node *root1, Node *root2) {
        if (!root1 && !root2) return true;
        if (!root1 || !root2) return false;

        queue<Node*> q1, q2;
        q1.push(root1);
        q2.push(root2);

        while (!q1.empty() && !q2.empty()) {
            // Level size mismatch -> Not anagrams
            if (q1.size() != q2.size()) {
                return false;
            }

            int sz = q1.size();
            vector<int> level1, level2;

            for (int i = 0; i < sz; i++) {
                Node* c1 = q1.front(); q1.pop();
                Node* c2 = q2.front(); q2.pop();

                level1.push_back(c1->data);
                level2.push_back(c2->data);

                if (c1->left) q1.push(c1->left);
                if (c1->right) q1.push(c1->right);

                if (c2->left) q2.push(c2->left);
                if (c2->right) q2.push(c2->right);
            }

            // Sort level node values to check anagram property
            sort(level1.begin(), level1.end());
            sort(level2.begin(), level2.end());

            if (level1 != level2) {
                return false;
            }
        }

        // Height mismatch -> Not anagrams
        if (!q1.empty() || !q2.empty()) {
            return false;
        }

        return true;
    }
};

int main() {
    Solution ob;

    // Example 1:
    // root1 = [1, 3, 2, N, N, 5, 4]
    // root2 = [1, 2, 3, 4, 5, N, N]
    // Expected Output: true
    Node* root1 = new Node(1);
    root1->left = new Node(3);
    root1->right = new Node(2);
    root1->right->left = new Node(5);
    root1->right->right = new Node(4);

    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);
    root2->left->left = new Node(4);
    root2->left->right = new Node(5);

    cout << "Example 1 Are Level Anagrams: " << (ob.areAnagrams(root1, root2) ? "true" : "false") << "\n";

    // Example 2:
    // root1 = [1, 2, 3, 5, 4]
    // root2 = [1, 2, 4, 5, 3]
    // Expected Output: false
    Node* root3 = new Node(1);
    root3->left = new Node(2);
    root3->right = new Node(3);
    root3->left->left = new Node(5);
    root3->left->right = new Node(4);

    Node* root4 = new Node(1);
    root4->left = new Node(2);
    root4->right = new Node(4);
    root4->left->left = new Node(5);
    root4->left->right = new Node(3);

    cout << "Example 2 Are Level Anagrams: " << (ob.areAnagrams(root3, root4) ? "true" : "false") << "\n";

    return 0;
}
