/*
    Problem Name: Construct Binary Tree from Parent Array
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an array parent[] where each index `i` represents a node with value `i` and `parent[i]`
    gives the parent's index (-1 indicates the root).
    Construct the binary tree and return the root node.
    Note: If two nodes share the same parent, the one appearing first in the array becomes the left child.

    Examples:
    Input: parent[] = [-1, 0, 0, 1, 1, 3, 5]
    Output: Level order: 0 1 2 3 4 N N 5 N N N 6
    Explanation:
              0
            /   \
           1     2
          / \
         3   4
        /
       5
      /
     6

    Input: parent[] = [2, 0, -1]
    Output: Level order: 2 0 N 1
    Explanation:
              2
             /
            0
           /
          1

    Constraints:
    1 <= parent.size() <= 10^3

    Expected Complexities:
    Time Complexity: O(N), two linear passes over the parent array.
    Space Complexity: O(N), for storing node pointers in a vector.

    Love Babbar Style Approach:
    Node Pointer Mapping (Lookup Array Approach):

    1. INTUITION:
       - Since node values range from `0` to `n - 1`, we can create a `vector<Node*> nodes(n)`
         where `nodes[i]` stores the created `Node*` for value `i`.
       - In Pass 1: Instantiate all `n` nodes (`nodes[i] = new Node(i)`).
       - In Pass 2: Iterate through `parent[]`:
         * If `parent[i] == -1`, `nodes[i]` is the ROOT of the tree.
         * Otherwise, fetch `par = nodes[parent[i]]`:
           - If `par->left == NULL`, attach `par->left = nodes[i]`.
           - Else, attach `par->right = nodes[i]`.

    2. ALGORITHM:
       - `int n = parent.size();`
       - `vector<Node*> nodes(n);`
       - Loop `i` from `0` to `n-1`: `nodes[i] = new Node(i);`
       - Loop `i` from `0` to `n-1`:
         * `if (parent[i] == -1)` `root = nodes[i];`
         * `else`:
           - `Node* par = nodes[parent[i]];`
           - `if (par->left == NULL) par->left = nodes[i];`
           - `else par->right = nodes[i];`
       - Return `root`.

    Dry Run:
    parent[] = [2, 0, -1], n = 3
    - nodes: [Node(0), Node(1), Node(2)]

    - i = 0: parent[0] = 2 -> par = Node(2). Node(2)->left = Node(0).
    - i = 1: parent[1] = 0 -> par = Node(0). Node(0)->left = Node(1).
    - i = 2: parent[2] = -1 -> root = Node(2).

    Tree: 2 -> left=0 -> left=1. Root = 2 ✓
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
    // GFG Signature
    Node *createTree(vector<int> parent) {
        int n = parent.size();

        // Step 1: Create all nodes for values 0 to n-1
        vector<Node*> nodes(n);
        for (int i = 0; i < n; i++)
            nodes[i] = new Node(i);

        Node* root = NULL;

        // Step 2: Establish parent-child pointer connections
        for (int i = 0; i < n; i++) {
            if (parent[i] == -1) {
                root = nodes[i];
            } else {
                Node* par = nodes[parent[i]];

                if (par->left == NULL)
                    par->left = nodes[i];
                else
                    par->right = nodes[i];
            }
        }

        return root;
    }
};

// Helper function to print Level Order Traversal of Binary Tree
void printLevelOrder(Node* root) {
    if (root == NULL) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (curr != NULL) {
            cout << curr->data << " ";
            q.push(curr->left);
            q.push(curr->right);
        } else {
            cout << "N ";
        }
    }
    cout << "\n";
}

int main() {
    Solution ob;

    // Example 1:
    // parent[] = [-1, 0, 0, 1, 1, 3, 5]
    vector<int> parent1 = {-1, 0, 0, 1, 1, 3, 5};
    Node* root1 = ob.createTree(parent1);

    cout << "Example 1 Level Order Output: ";
    printLevelOrder(root1);

    // Example 2:
    // parent[] = [2, 0, -1]
    vector<int> parent2 = {2, 0, -1};
    Node* root2 = ob.createTree(parent2);

    cout << "Example 2 Level Order Output: ";
    printLevelOrder(root2);

    return 0;
}
