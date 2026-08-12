/*
    Problem Name: Iterative Inorder
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary tree, find the inorder traversal (Left -> Root -> Right) of the tree
    WITHOUT using recursion (iteratively).

    Examples:
    Input:
               1
             /   \
            2     3
          /  \
         4    5

    Output: [4, 2, 5, 1, 3]

    Constraints:
    1 <= Number of nodes <= 10^5
    1 <= Node data <= 10^5

    ----------------------------------------------------------------------------------------
    APPROACH 1: Iterative Stack Strategy [O(N) Time, O(H) Space]
    ----------------------------------------------------------------------------------------
    INTUITION:
    - Inorder traversal order is [LEFT -> ROOT -> RIGHT].
    - We use a pointer `curr` initialized to `root` and a `stack<Node*> s`.
    - Go as far LEFT as possible, pushing nodes to `s`.
    - When `curr == NULL` (leftmost reached):
      * Pop `curr = s.top()`.
      * Visit `curr` (`ans.push_back(curr->data)`).
      * Move to right subtree: `curr = curr->right`.

    ----------------------------------------------------------------------------------------
    APPROACH 2: Morris Inorder Traversal [O(N) Time, O(1) Space]
    ----------------------------------------------------------------------------------------
    INTUITION:
    - Eliminates stack by temporarily threading leaf pointers back to ancestors.
    - If `curr->left == NULL`: visit `curr->data`, move `curr = curr->right`.
    - If `curr->left != NULL`:
      * Find predecessor `prev` = rightmost node of `curr`'s left subtree.
      * If `prev->right == NULL`: create thread `prev->right = curr`, move `curr = curr->left`.
      * If `prev->right == curr`: break thread `prev->right = NULL`, visit `curr->data` (INORDER!), move `curr = curr->right`.

    Dry Run (Stack Approach):
           1
         /   \
        2     3
      /  \
     4    5

    - Go left: s=[1, 2, 4], curr=NULL
    - Pop 4 -> ans=[4]. curr = 4's right (NULL)
    - Pop 2 -> ans=[4, 2]. curr = 2's right (5)
    - Go left: s=[1, 5], curr=NULL
    - Pop 5 -> ans=[4, 2, 5]. curr = 5's right (NULL)
    - Pop 1 -> ans=[4, 2, 5, 1]. curr = 1's right (3)
    - Go left: s=[3], curr=NULL
    - Pop 3 -> ans=[4, 2, 5, 1, 3]. curr = 3's right (NULL)
    - Done! Output: [4, 2, 5, 1, 3] ✓
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
// APPROACH 1: Iterative Stack Strategy (O(H) Space)
// =========================================================================
class SolutionStack {
public:
    vector<int> inOrder(Node* root) {
        vector<int> ans;
        stack<Node*> s;
        Node* curr = root;

        while (curr != NULL || !s.empty()) {
            // Push all left subtrees onto stack
            while (curr != NULL) {
                s.push(curr);
                curr = curr->left;
            }

            // Pop top node, visit it (Root), and move to right child
            curr = s.top();
            s.pop();

            ans.push_back(curr->data);

            curr = curr->right;
        }

        return ans;
    }
};

// =========================================================================
// APPROACH 2: Morris Inorder Traversal (O(1) Auxiliary Space)
// =========================================================================
class SolutionMorris {
public:
    vector<int> inOrder(Node* root) {
        vector<int> ans;
        Node* curr = root;

        while (curr != NULL) {
            if (curr->left == NULL) {
                // Visit root and move right
                ans.push_back(curr->data);
                curr = curr->right;
            } else {
                // Find inorder predecessor (rightmost node in left subtree)
                Node* prev = curr->left;
                while (prev->right != NULL && prev->right != curr) {
                    prev = prev->right;
                }

                if (prev->right == NULL) {
                    // Create temporary thread
                    prev->right = curr;
                    curr = curr->left;
                } else {
                    // Remove thread, visit root (Inorder property!), and move right
                    prev->right = NULL;
                    ans.push_back(curr->data);
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
    // Expected Output: 4 2 5 1 3
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);

    // Test Approach 1: Stack Solution
    SolutionStack obStack;
    vector<int> resStack = obStack.inOrder(root1);
    cout << "Stack Approach Output : ";
    for (int val : resStack) cout << val << " ";
    cout << "\n";

    // Test Approach 2: Morris Solution (O(1) Space)
    SolutionMorris obMorris;
    vector<int> resMorris = obMorris.inOrder(root1);
    cout << "Morris O(1) Space Output: ";
    for (int val : resMorris) cout << val << " ";
    cout << "\n";

    return 0;
}
