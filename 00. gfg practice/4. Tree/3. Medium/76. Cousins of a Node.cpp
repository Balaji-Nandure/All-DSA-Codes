/*
    Problem Name: Cousins of a Node
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree and a target node pointer `node`, return all cousins (not siblings)
    of the given node in the order of their appearance in level order traversal.
    - Cousins are nodes at the same level in the tree having DIFFERENT parents.
    - Siblings (nodes sharing the same parent) are NOT cousins.
    - If no cousins exist, return [-1].

    Examples:
    Input: root[] = [1, 2, 3, 4, 5, 6, 7], target = Node(5)
    Output: [6, 7]
    Explanation:
            1
          /   \
         2     3
        / \   / \
       4   5 6   7
    Node 5 is at level 2. Node 4 is sibling of 5 (same parent 2).
    Nodes 6 and 7 have parent 3 (different parent), so they are cousins.

    Input: root[] = [9, 5, N], target = Node(5)
    Output: [-1]
    Explanation:
        9
       /
      5
    No other nodes exist at level 1. So output is [-1].

    Constraints:
    1 <= n <= 10^5

    Expected Complexities:
    Time Complexity: O(N), single pass BFS level order traversal.
    Space Complexity: O(N), for the BFS queue.

    Love Babbar Style Approach:
    BFS Level-Order Parent Identification:

    1. INTUITION:
       - To find cousins of a `target` node:
         * We traverse the tree level-by-level using BFS.
         * When processing level `L`, we inspect the children of each node `curr`.
         * If a node `curr` is the PARENT of `target` (`curr->left == target || curr->right == target`):
           - `target` is at the next level `L + 1`.
           - Both `curr->left` and `curr->right` are either `target` or its sibling, so we DISCARD them.
           - We set a flag `targetFoundAtNextLevel = true`.
         * For all OTHER nodes `curr` at level `L`:
           - Their children lie at level `L + 1` and have a DIFFERENT parent than `target`.
           - Thus, their children ARE the cousins of `target`! We collect their values into `nextLevelCousins`.
         * As soon as level `L` finishes processing and `targetFoundAtNextLevel == true`:
           - If `nextLevelCousins` is non-empty, return `nextLevelCousins`.
           - Else return `{-1}`.

    2. ALGORITHM:
       - `if (!root || root == node_to_find) return {-1};`
       - Initialize `queue<Node*> q`.
       - `q.push(root);`
       - While (`!q.empty()`):
         * `int sz = q.size();`
         * `bool found = false;`
         * `vector<int> cousins;`
         * For `i = 0` to `sz - 1`:
           - `Node* curr = q.front(); q.pop();`
           - If (`curr->left == node_to_find || curr->right == node_to_find`):
             `found = true;`
           - Else:
             `if (curr->left) { cousins.push_back(curr->left->data); q.push(curr->left); }`
             `if (curr->right) { cousins.push_back(curr->right->data); q.push(curr->right); }`
         * If (`found`):
           - `if (cousins.empty()) return {-1};`
           - Return `cousins;`
       - Return `{-1}`.

    Dry Run:
    root = [1, 2, 3, 4, 5, 6, 7], target = Node(5)
    - Level 0: q = [1]. curr = 1. Children: 2, 3. q = [2, 3].
    - Level 1: q = [2, 3].
      * curr = 2: 2->right == target(5) -> found = true. Do not push 4 or 5 to cousins.
      * curr = 3: push 6 and 7 to cousins = [6, 7].
    - Level 1 ends. found == true. cousins = [6, 7].
    Returns [6, 7] ✓
*/

#include <iostream>
#include <vector>
#include <queue>

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
    // GFG Signature - BFS Cousin Identification
    vector<int> printCousins(Node* root, Node* node_to_find) {
        if (!root || root == node_to_find) {
            return {-1};
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int sz = q.size();
            bool targetFoundAtNextLevel = false;
            vector<int> cousins;

            for (int i = 0; i < sz; i++) {
                Node* curr = q.front();
                q.pop();

                // If current node is parent of node_to_find, skip its children (sibling & target)
                if (curr->left == node_to_find || curr->right == node_to_find) {
                    targetFoundAtNextLevel = true;
                } else {
                    // Push children of other parents to cousins list
                    if (curr->left) {
                        cousins.push_back(curr->left->data);
                        q.push(curr->left);
                    }
                    if (curr->right) {
                        cousins.push_back(curr->right->data);
                        q.push(curr->right);
                    }
                }
            }

            // If target node was found at the next level, return the collected cousins
            if (targetFoundAtNextLevel) {
                if (cousins.empty()) {
                    return {-1};
                }
                return cousins;
            }
        }

        return {-1};
    }
};

int main() {
    Solution ob;

    // Example 1:
    //            1
    //          /   \
    //         2     3
    //        / \   / \
    //       4   5 6   7
    // target = Node(5)  --> Expected Output: [6, 7]
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);
    root1->right->left = new Node(6);
    root1->right->right = new Node(7);

    Node* target1 = root1->left->right; // Node 5

    vector<int> res1 = ob.printCousins(root1, target1);
    cout << "Example 1 Cousins of Node 5: [ ";
    for (int val : res1) cout << val << " ";
    cout << "]\n";

    // Example 2:
    //        9
    //       /
    //      5
    // target = Node(5)  --> Expected Output: [-1]
    Node* root2 = new Node(9);
    root2->left = new Node(5);

    Node* target2 = root2->left; // Node 5

    vector<int> res2 = ob.printCousins(root2, target2);
    cout << "Example 2 Cousins of Node 5: [ ";
    for (int val : res2) cout << val << " ";
    cout << "]\n";

    return 0;
}
