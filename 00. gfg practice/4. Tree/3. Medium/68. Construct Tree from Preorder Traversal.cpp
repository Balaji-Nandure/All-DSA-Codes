/*
    Problem Name: Construct Tree from Preorder Traversal
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given two arrays pre[] and preLN[] of size n:
    - pre[] represents the preorder traversal of a Full Binary Tree (every node has 0 or 2 children).
    - preLN[i] stores 'L' if pre[i] is a leaf node and 'N' if a non-leaf (internal) node.
    Construct the binary tree and return its root.

    Examples:
    Input: pre[] = [10, 30, 20, 5, 15], preLN[] = ['N', 'N', 'L', 'L', 'L']
    Output: Tree Root 10
    Explanation:
            10 (N)
           /  \
        30 (N) 15 (L)
        /  \
      20(L) 5(L)

    Input: pre[] = [1, 2, 4, 5, 3, 6, 8, 9, 7], preLN[] = ['N', 'N', 'L', 'L', 'N', 'N', 'L', 'L', 'L']

    Constraints:
    1 <= pre.size() <= 10^5
    1 <= pre[i] <= 10^9
    preLN.size() == pre.size()

    Expected Complexities:
    Time Complexity: O(N), single pass through the preorder arrays.
    Space Complexity: O(N), for recursion call stack.

    Love Babbar Style Approach:
    Preorder Recursion with Index Reference Pointer:

    1. INTUITION:
       - Since `pre[]` is in Preorder traversal (`Root -> Left -> Right`):
         * Node at `index` is ALWAYS created first as `root`.
         * If `preLN[index] == 'N'` (internal node):
           - It MUST have 2 children in a full binary tree.
           - Increment `index++` and recursively construct `root->left`.
           - Increment `index++` and recursively construct `root->right`.
         * If `preLN[index] == 'L'` (leaf node):
           - It has NO children (`left = right = NULL`), so we return `root` immediately.
       - Passing `index` by reference (`int& index`) allows sequential element consumption across call frames.

    2. ALGORITHM:
       - `solve(n, pre, preLN, index)`:
         * `if (index >= n) return NULL;`
         * `Node* root = new Node(pre[index]);`
         * `if (preLN[index] == 'N')`:
           - `index++; root->left = solve(n, pre, preLN, index);`
           - `index++; root->right = solve(n, pre, preLN, index);`
         * Return `root`.

    Dry Run:
    pre[] = [10, 30, 20, 5, 15], preLN[] = ['N', 'N', 'L', 'L', 'L']
    - index 0: root = 10 ('N').
      * index 1: root->left = 30 ('N').
        - index 2: 30->left = 20 ('L'). Returns Node(20).
        - index 3: 30->right = 5 ('L'). Returns Node(5).
        Returns Node(30).
      * index 4: root->right = 15 ('L'). Returns Node(15).
    Returns Node(10) ✓
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
private:
    Node* solve(int n, int pre[], char preLN[], int& index) {
        if (index >= n) return NULL;

        // Step 1: Create root node for current preorder element
        Node* root = new Node(pre[index]);

        // Step 2: If internal node ('N'), recursively construct left and right subtrees
        if (preLN[index] == 'N') {
            index++;
            root->left = solve(n, pre, preLN, index);

            index++;
            root->right = solve(n, pre, preLN, index);
        }

        // If leaf node ('L'), return root with left = right = NULL
        return root;
    }

public:
    // GFG Signature
    Node* constructTree(int n, int pre[], char preLN[]) {
        int index = 0;
        return solve(n, pre, preLN, index);
    }
};

// Helper function to print level order traversal
void printLevelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (curr) {
            cout << curr->data << " ";
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    cout << "\n";
}

int main() {
    Solution ob;

    // Example 1:
    // pre[] = [10, 30, 20, 5, 15], preLN[] = ['N', 'N', 'L', 'L', 'L']
    // Expected Level Order: 10 30 15 20 5
    int n1 = 5;
    int pre1[] = {10, 30, 20, 5, 15};
    char preLN1[] = {'N', 'N', 'L', 'L', 'L'};

    Node* root1 = ob.constructTree(n1, pre1, preLN1);
    cout << "Example 1 Level Order Output: ";
    printLevelOrder(root1);

    // Example 2:
    // pre[] = [1, 2, 4, 5, 3, 6, 8, 9, 7], preLN[] = ['N', 'N', 'L', 'L', 'N', 'N', 'L', 'L', 'L']
    int n2 = 9;
    int pre2[] = {1, 2, 4, 5, 3, 6, 8, 9, 7};
    char preLN2[] = {'N', 'N', 'L', 'L', 'N', 'N', 'L', 'L', 'L'};

    Node* root2 = ob.constructTree(n2, pre2, preLN2);
    cout << "Example 2 Level Order Output: ";
    printLevelOrder(root2);

    return 0;
}
