/*
    Problem Name: Linked List to Binary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the head of a Linked List, construct the complete binary tree from the given
    Linked List and return the root of the tree.
    Note: A complete binary tree is represented in array/linked list form where if the root
    node is at index `i`, its left child is at `2*i+1` and right child is at `2*i+2`.

    Examples:
    Input: head : 1 -> 2 -> 3 -> 4 -> 5
    Output: Level Order Traversal: 1 2 3 4 5
    Explanation:
              1
            /   \
           2     3
          / \
         4   5

    Input: head: 5 -> 4 -> 3 -> 2 -> 1
    Output: Level Order Traversal: 5 4 3 2 1

    Constraints:
    1 <= number of nodes <= 10^6
    1 <= node->data <= 10^4

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes in the linked list. Each node is processed once.
    Space Complexity: O(N), for the level-order queue storing tree nodes.

    Love Babbar Style Approach:
    Queue-Based Level Order Construction:

    1. INTUITION:
       - Since elements in the linked list represent the tree in LEVEL ORDER sequence:
         * 1st element -> Root node.
         * 2nd & 3rd elements -> Left & Right children of Root.
         * 4th & 5th elements -> Left & Right children of 2nd node, etc.
       - A FIFO `queue<TreeNode*>` allows us to process parent nodes in the exact sequence
         their children appear in the linked list!

    2. ALGORITHM:
       - If `head == NULL`, return `NULL`.
       - Create `root = new TreeNode(head->data)`.
       - Push `root` into `queue<TreeNode*> q`.
       - Advance `head = head->next`.
       - While (`head != NULL`):
         * Pop parent node `parent = q.front(); q.pop();`
         * Create `left = new TreeNode(head->data)`.
         * Link `parent->left = left; q.push(left);`
         * Advance `head = head->next`.
         * If `head != NULL`:
           - Create `right = new TreeNode(head->data)`.
           - Link `parent->right = right; q.push(right);`
           - Advance `head = head->next`.
       - Return `root`.

    Dry Run:
    head: 1 -> 2 -> 3 -> 4 -> 5

    - Create root=1, push 1 to q. q=[1], head=2
    - Loop iteration 1:
      - parent = 1 (popped). q=[]
      - left = 2. 1->left = 2. push 2 to q. q=[2], head=3
      - right = 3. 1->right = 3. push 3 to q. q=[2, 3], head=4
    - Loop iteration 2:
      - parent = 2 (popped). q=[3]
      - left = 4. 2->left = 4. push 4 to q. q=[3, 4], head=5
      - right = 5. 2->right = 5. push 5 to q. q=[3, 4, 5], head=NULL
    - Loop ends (head is NULL).

    Resulting Tree is a Complete Binary Tree! ✓
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Definition for Singly Linked List Node.
struct Node {
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = NULL;
    }
};

// Definition for Binary Tree Node.
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        data = val;
        left = right = NULL;
    }
};

class Solution {
public:
    // GFG Signature
    TreeNode *convert(Node *head) {
        if (head == NULL)
            return NULL;

        TreeNode* root = new TreeNode(head->data);
        queue<TreeNode*> q;
        q.push(root);

        head = head->next;

        while (head) {
            TreeNode* parent = q.front();
            q.pop();

            // Left child
            TreeNode* left = new TreeNode(head->data);
            parent->left = left;
            q.push(left);

            head = head->next;

            // Right child
            if (head) {
                TreeNode* right = new TreeNode(head->data);
                parent->right = right;
                q.push(right);

                head = head->next;
            }
        }

        return root;
    }
};

// Helper function to print Level Order Traversal of Binary Tree
void printLevelOrder(TreeNode* root) {
    if (root == NULL) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        cout << curr->data << " ";

        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

int main() {
    Solution ob;

    // Example 1: Linked list 1 -> 2 -> 3 -> 4 -> 5
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(5);

    TreeNode* root1 = ob.convert(head1);

    cout << "Example 1 Level Order Output: ";
    printLevelOrder(root1);
    cout << "\n"; // Expected: 1 2 3 4 5

    // Example 2: Linked list 5 -> 4 -> 3 -> 2 -> 1
    Node* head2 = new Node(5);
    head2->next = new Node(4);
    head2->next->next = new Node(3);
    head2->next->next->next = new Node(2);
    head2->next->next->next->next = new Node(1);

    TreeNode* root2 = ob.convert(head2);

    cout << "Example 2 Level Order Output: ";
    printLevelOrder(root2);
    cout << "\n"; // Expected: 5 4 3 2 1

    return 0;
}
