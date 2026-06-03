/*
GeeksforGeeks: Levelorder traversal of a BST
Difficulty: Easy

Problem:
Levelorder traversal means traversing through the tree level by level, from left to right.
Given a BST, find its level-order traversal. 

Examples:
Input:
      5
    /   \
   2     7
   \      \
    3      8
Output: 5 2 7 3 8
Explanation: Move top to down and then left to right and keep printing elements.

Input:
    30
   /
 10
   \ 
   20
Output: 30 10 20

Core Idea:
Level order traversal is fundamentally a Breadth-First Search (BFS) on the tree.
We can use a Queue data structure to achieve this. We start by enqueuing the root node. 
Then, we loop until the queue is empty: we dequeue the front node, add its value to our result list, and enqueue its left and right children (if they exist).
Because a queue follows the First-In-First-Out (FIFO) principle, nodes are processed exactly in the order they were discovered, which naturally processes them level by level, from left to right.

Approach:
1. Create a `vector<int> result` to store the traversal and a `queue<Node*> q`.
2. If `root` is `nullptr`, return the empty `result`.
3. Push `root` into `q`.
4. Loop while `q` is not empty:
   - Get the front element: `Node* curr = q.front();`
   - Remove it from the queue: `q.pop();`
   - Store its value: `result.push_back(curr->data);`
   - If it has a left child, enqueue it: `if (curr->left) q.push(curr->left);`
   - If it has a right child, enqueue it: `if (curr->right) q.push(curr->right);`
5. Return the `result` vector.

Time Complexity: O(N), where N is the number of nodes. We enqueue and dequeue each node exactly once.
Space Complexity: O(N) to store nodes in the queue. In the worst case (a perfectly balanced tree), the last level will have approximately N/2 nodes, so the queue will hold O(N) nodes simultaneously.

GFG Link: https://www.geeksforgeeks.org/problems/levelorder-traversal-of-a-bst/1
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
    // Function to return the level order traversal of a tree.
    vector<int> levelOrder(Node* root) {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            
            result.push_back(curr->data);
            
            // Enqueue left child
            if (curr->left != nullptr) {
                q.push(curr->left);
            }
            
            // Enqueue right child
            if (curr->right != nullptr) {
                q.push(curr->right);
            }
        }
        
        return result;
    }
};

/*
Dry Run — Example 1:
Input:
      5
    /   \
   2     7
   \      \
    3      8

1. Initialization:
   q = [Node(5)]
   result = []

2. Iteration 1:
   - curr = Node(5), q.pop(), q = []
   - result = [5]
   - curr->left (2) exists, q.push(Node(2)) -> q = [Node(2)]
   - curr->right (7) exists, q.push(Node(7)) -> q = [Node(2), Node(7)]

3. Iteration 2:
   - curr = Node(2), q.pop(), q = [Node(7)]
   - result = [5, 2]
   - curr->left is null.
   - curr->right (3) exists, q.push(Node(3)) -> q = [Node(7), Node(3)]

4. Iteration 3:
   - curr = Node(7), q.pop(), q = [Node(3)]
   - result = [5, 2, 7]
   - curr->left is null.
   - curr->right (8) exists, q.push(Node(8)) -> q = [Node(3), Node(8)]

5. Iteration 4:
   - curr = Node(3), q.pop(), q = [Node(8)]
   - result = [5, 2, 7, 3]
   - curr->left is null, curr->right is null.

6. Iteration 5:
   - curr = Node(8), q.pop(), q = []
   - result = [5, 2, 7, 3, 8]
   - curr->left is null, curr->right is null.

7. Queue is empty. Loop breaks.

8. Return result.

Output: [5, 2, 7, 3, 8]
*/
