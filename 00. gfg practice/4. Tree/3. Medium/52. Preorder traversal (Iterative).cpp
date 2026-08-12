/*
    Problem Name: Preorder traversal (Iterative)
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a Binary Tree, find the preorder traversal (Root -> Left -> Right) of the tree
    WITHOUT using recursion (iteratively).

    Follow Up: Solve with O(1) auxiliary space (Morris Preorder Traversal).

    Examples:
    Input: root = [1, 2, 3, 4, 5]
    Output: [1, 2, 4, 5, 3]
    Explanation:
             1
           /   \
          2     3
        /  \
       4    5
    Preorder: 1, 2, 4, 5, 3.

    Input: root = [8, 1, 5, N, 7, 10, 6, N, 10, 6]
    Output: [8, 1, 7, 10, 5, 10, 6, 6]

    Constraints:
    1 <= Number of nodes <= 10^5
    0 <= node->data <= 10^5

    ----------------------------------------------------------------------------------------
    APPROACH 1: Standard Iterative Stack [O(N) Time, O(N) Space]
    ----------------------------------------------------------------------------------------
    INTUITION:
    - Preorder order is [Root -> Left -> Right].
    - Using a `stack<Node*> s`:
      * Pop `cur`, process `ans.push_back(cur->data)`.
      * Push `cur->right` FIRST, then `cur->left` SECOND.
      * Since stack is LIFO, `cur->left` will be popped and processed BEFORE `cur->right`!

    ----------------------------------------------------------------------------------------
    APPROACH 2: Morris Preorder Traversal [O(N) Time, O(1) Space]
    ----------------------------------------------------------------------------------------
    INTUITION:
    - Avoids stack by temporarily threading leaf pointers back to ancestors.
    - If `curr->left == NULL`: visit `curr->data`, move `curr = curr->right`.
    - If `curr->left != NULL`:
      * Find predecessor `prev` = rightmost node in `curr`'s left subtree.
      * If `prev->right == NULL`: create thread `prev->right = curr`, visit `curr->data` (PREORDER!), move `curr = curr->left`.
      * If `prev->right == curr`: break thread `prev->right = NULL`, move `curr = curr->right`.
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

// =========================================================================
// APPROACH 1: Standard Iterative Stack (O(N) Space)
// =========================================================================
class SolutionStack {
public:
    vector<int> preOrder(Node* root) {
        vector<int> ans;
        if (!root) return ans;

        stack<Node*> s;
        s.push(root);

        while (!s.empty()) {
            Node* cur = s.top();
            s.pop();

            // Visit root node
            ans.push_back(cur->data);

            // Push right child first so left child is popped and processed first
            if (cur->right) s.push(cur->right);
            if (cur->left) s.push(cur->left);
        }

        return ans;
    }
};

// =========================================================================
// APPROACH 2: Morris Preorder Traversal (O(1) Auxiliary Space Follow-Up)
// =========================================================================
class SolutionMorris {
public:
    vector<int> preOrder(Node* root) {
        vector<int> ans;
        Node* curr = root;

        while (curr != NULL) {
            if (curr->left == NULL) {
                // Visit root and move right
                ans.push_back(curr->data);
                curr = curr->right;
            } else {
                // Find inorder predecessor (rightmost node of left subtree)
                Node* prev = curr->left;
                while (prev->right != NULL && prev->right != curr) {
                    prev = prev->right;
                }

                if (prev->right == NULL) {
                    // Visit root BEFORE going left (Preorder property!)
                    ans.push_back(curr->data);
                    // Create temporary thread
                    prev->right = curr;
                    curr = curr->left;
                } else {
                    // Remove thread and move right
                    prev->right = NULL;
                    curr = curr->right;
                }
            }
        }

        return ans;
    }
};

int main() {
    // Example 1:
    //            1
    //          /   \
    //         2     3
    //       /  \
    //      4    5
    // Expected Output: 1 2 4 5 3
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);

    // Test Approach 1: Stack Solution
    SolutionStack obStack;
    vector<int> resStack = obStack.preOrder(root1);
    cout << "Stack Approach Output : ";
    for (int val : resStack) cout << val << " ";
    cout << "\n";

    // Test Approach 2: Morris Solution (O(1) Space)
    SolutionMorris obMorris;
    vector<int> resMorris = obMorris.preOrder(root1);
    cout << "Morris O(1) Space Output: ";
    for (int val : resMorris) cout << val << " ";
    cout << "\n";

    return 0;
}
