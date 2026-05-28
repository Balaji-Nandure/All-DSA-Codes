/*
Problem: Reverse Level Order Traversal

Given a binary tree, find its reverse level order traversal. ie- the traversal must begin from the last level.

Constraints:
1 <= n <= 10^5
1 <= node->data <= 10^5

--------------------------------------------------

Pattern:
Tree Traversal (Modified BFS)

--------------------------------------------------

Key Observation:
- A standard Level Order Traversal (BFS) processes nodes level by level from top to bottom, and strictly left to right within each level.
- If we naively collect all nodes in a standard BFS and reverse the entire array, the nodes within each level will consequently also be reversed (becoming right to left). 
- To cleverly prevent this and preserve the "left to right" order within the reversed levels, we can subtly mathematically tweak our BFS queue logic:
    1. Enqueue the RIGHT child before the LEFT child.
    2. This effectively collects nodes from top to bottom, but backwards (right to left).
    3. When we finally reverse the entire collected array at the end, both the levels AND the internal right-to-left orders are beautifully flipped, gracefully yielding perfectly ordered bottom-to-top, left-to-right nodes!

--------------------------------------------------

Approach:
1. Initialize an empty `vector<int> res` to securely store the values, and a `queue<Node*> q` for standard BFS.
2. Push the `root` node into `q`.
3. While `q` is definitively not empty:
    a. Pop the front node.
    b. Push its `data` into `res`.
    c. Explicitly push its RIGHT child to `q` first (if it exists).
    d. Explicitly push its LEFT child to `q` second (if it exists).
4. After the BFS queue is entirely exhausted, natively reverse the `res` array using `std::reverse(res.begin(), res.end())`.
5. Return the finalized `res`.

--------------------------------------------------

Time Complexity: O(N) as we seamlessly visit every single node in the tree exactly once via the queue, and then precisely reverse the array of size N in O(N) time.
Space Complexity: O(N) for the BFS queue, which at worst safely holds N/2 nodes (at the very bottom leaf level of a perfectly balanced tree), plus natively O(N) for securely storing the result array.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/reverse-level-order-traversal/1
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Definition for a binary tree node
struct Node
{
    int data;
    Node* left;
    Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
};

class Solution {
public:
    vector<int> reverseLevelOrder(Node *root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            
            res.push_back(curr->data);
            
            // Crucial step: Push RIGHT child first, then LEFT child
            if (curr->right != nullptr) {
                q.push(curr->right);
            }
            if (curr->left != nullptr) {
                q.push(curr->left);
            }
        }
        
        // Reverse the collected array to achieve the final bottom-up, left-right order
        reverse(res.begin(), res.end());
        
        return res;
    }
};
