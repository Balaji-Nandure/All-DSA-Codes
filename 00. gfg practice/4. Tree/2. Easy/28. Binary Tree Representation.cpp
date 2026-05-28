/*
GeeksforGeeks: Binary Tree Representation
Difficulty: Easy

Problem:
Given an array nodes[] of size n, where each element represents the value of a node in the 
level-order traversal of a complete binary tree, construct the complete binary tree and 
return its root node.

Example 1:
Input: nodes[] = [1, 2, 3, 4, 5, 6, 7]
Output: 
        1
      /   \
     2     3
    / \   / \
   4   5 6   7

Explanation: We start from the root and fill the tree level by level. First 1 becomes the 
root, then 2 and 3 become its children, and then 4, 5, 6, 7 fill the next level from left to right.

Example 2:
Input: nodes[] = [10, 20, 30, 40, 50]
Output:
        10
      /    \
     20    30
    /  \
   40  50

Core Idea:
A complete binary tree can be constructed from its level-order traversal using a Queue, 
similar to how we traverse it. We start with the root, push it to a queue, and then 
iteratively pop nodes and attach their left and right children from the array.

Alternatively, since it's a complete binary tree, for any node at index `i`, its left 
child is at index `2*i + 1` and right child is at index `2*i + 2`. A recursive approach 
using this property is extremely concise.

Approach 1: Iterative (Queue)
1. Initialize the root with nodes[0] and push it to a queue.
2. Maintain a pointer `i` starting from 1.
3. While the queue is not empty and `i < n`:
   a. Pop a node `curr` from the queue.
   b. If `i < n`, create the left child with nodes[i], attach to `curr->left`, push to queue, and increment `i`.
   c. If `i < n`, create the right child with nodes[i], attach to `curr->right`, push to queue, and increment `i`.

Approach 2: Recursive (using complete binary tree property)
- construct(i) creates a node for nodes[i].
- Its left child is construct(2*i + 1).
- Its right child is construct(2*i + 2).

*Note: The signature in GFG for this problem is often `void create_tree(node* root0, vector<int> &vec)`.
The below implementation handles that exact signature using the queue approach.

Time Complexity : O(N) — every node is processed once.
Space Complexity: O(N) — for the queue in the worst case (the last level has N/2 nodes).

GFG Link:
https://www.geeksforgeeks.org/problems/binary-tree-representation/1
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Definition for a binary tree node
// Note: GFG sometimes uses lowercase `node` for this problem
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = NULL;
    }
};

class Solution {
public:
    Node* buildTree(vector<int>& nodes) {
        if (nodes.empty()) return NULL;
        
        Node* root = new Node(nodes[0]);
        queue<Node*> q;
        q.push(root);
        
        int i = 1;
        while (i < nodes.size() && !q.empty()) {
            Node* curr = q.front();
            q.pop();
            
            // Construct and attach left child
            if (i < nodes.size()) {
                curr->left = new Node(nodes[i++]);
                q.push(curr->left);
            }
            
            // Construct and attach right child
            if (i < nodes.size()) {
                curr->right = new Node(nodes[i++]);
                q.push(curr->right);
            }
        }
        
        return root;
    }
    
    /*
    // Alternative Recursive Approach
    Node* buildTreeRecursive(const vector<int>& nodes, int i = 0) {
        if (i >= nodes.size()) return NULL;
        
        Node* root = new Node(nodes[i]);
        root->left = buildTreeRecursive(nodes, 2 * i + 1);
        root->right = buildTreeRecursive(nodes, 2 * i + 2);
        
        return root;
    }
    */
};

/*
Dry Run — Example 2:
nodes[] = [10, 20, 30, 40, 50]

Initial:
root->data = 10
queue = [node(10)]
i = 1

Iteration 1:
curr = node(10), queue = []
- i=1 < 5: curr->left = node(20), queue = [node(20)], i=2
- i=2 < 5: curr->right = node(30), queue = [node(20), node(30)], i=3

Iteration 2:
curr = node(20), queue = [node(30)]
- i=3 < 5: curr->left = node(40), queue = [node(30), node(40)], i=4
- i=4 < 5: curr->right = node(50), queue = [node(30), node(40), node(50)], i=5

Iteration 3:
curr = node(30), queue = [node(40), node(50)]
- i=5 == 5: no left child
- i=5 == 5: no right child

Loop terminates since i == 5.
Tree constructed successfully!
*/
