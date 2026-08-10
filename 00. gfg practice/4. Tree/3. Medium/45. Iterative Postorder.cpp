/*
    Problem Name: Iterative Postorder
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary tree, find the postorder traversal (Left -> Right -> Root) of the tree
    WITHOUT using recursion (iteratively).

    Examples:
    Input:
               1
             /   \
            2     3
          /  \
         4    5

    Output: [4, 5, 2, 3, 1]

    Constraints:
    1 <= Number of nodes <= 10^5
    1 <= Data of a node <= 10^5

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. Every node is pushed/popped from stacks once.
    Space Complexity: O(N), auxiliary space for the two stacks.

    Love Babbar Style Approach:
    Two-Stack Iterative Strategy (Reverse Preorder Trick):

    1. INTUITION:
       - Standard Postorder order is: `[LEFT, RIGHT, ROOT]`.
       - What if we modify Preorder traversal (`[ROOT, LEFT, RIGHT]`) to push `LEFT` first, then `RIGHT`?
         * Modified traversal visits: `[ROOT, RIGHT, LEFT]`.
       - Notice that reversing `[ROOT, RIGHT, LEFT]` gives EXACTLY `[LEFT, RIGHT, ROOT]` (Postorder)!
       - A second stack `s2` acts as a LIFO buffer that REVERSES the `[ROOT, RIGHT, LEFT]` order
         into the final `[LEFT, RIGHT, ROOT]` order!

    2. ALGORITHM:
       - `if (!root) return ans;`
       - Initialize two stacks `s1` and `s2`.
       - Push `root` into `s1`.
       - While `s1` is not empty:
         * `cur = s1.top(); s1.pop();`
         * Push `cur` into `s2`.
         * `if (cur->left) s1.push(cur->left);`
         * `if (cur->right) s1.push(cur->right);`
       - While `s2` is not empty:
         * Push `s2.top()->data` into `ans`.
         * `s2.pop();`
       - Return `ans`.

    Dry Run:
           1
         /   \
        2     3
      /  \
     4    5

    - s1=[1]
    - Pop 1 -> s2=[1]. Push 1's left(2) & right(3) to s1: s1=[2, 3]
    - Pop 3 -> s2=[1, 3]. 3 has no children. s1=[2]
    - Pop 2 -> s2=[1, 3, 2]. Push 2's left(4) & right(5) to s1: s1=[4, 5]
    - Pop 5 -> s2=[1, 3, 2, 5]. 5 has no children. s1=[4]
    - Pop 4 -> s2=[1, 3, 2, 5, 4]. s1 is empty.

    Pop all elements from s2 into ans:
    ans = [4, 5, 2, 3, 1] ✓
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
    // GFG Signature - Two Stack Iterative Postorder
    vector<int> postOrder(Node* root) {
        vector<int> ans;
        if (!root) return ans;

        stack<Node*> s1, s2;
        s1.push(root);

        // Step 1: Traverse in Root -> Right -> Left order using s1, store order in s2
        while (!s1.empty()) {
            Node* cur = s1.top();
            s1.pop();
            s2.push(cur);

            // Push left child first, then right child to s1
            if (cur->left) s1.push(cur->left);
            if (cur->right) s1.push(cur->right);
        }

        // Step 2: Pop from s2 to get Left -> Right -> Root (Postorder)
        while (!s2.empty()) {
            ans.push_back(s2.top()->data);
            s2.pop();
        }

        return ans;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //            1
    //          /   \
    //         2     3
    //       /  \
    //      4    5
    // Expected Output: 4 5 2 3 1
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);

    vector<int> post1 = ob.postOrder(root1);
    cout << "Example 1 Postorder: ";
    for (int val : post1) cout << val << " ";
    cout << "\n";

    // Example 2:
    //          8
    //       /     \
    //      1       5
    //       \     / \
    //        7   10  6
    Node* root2 = new Node(8);
    root2->left = new Node(1);
    root2->right = new Node(5);
    root2->left->right = new Node(7);
    root2->right->left = new Node(10);
    root2->right->right = new Node(6);

    vector<int> post2 = ob.postOrder(root2);
    cout << "Example 2 Postorder: ";
    for (int val : post2) cout << val << " ";
    cout << "\n";

    return 0;
}
