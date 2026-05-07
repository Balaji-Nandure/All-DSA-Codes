/*
Problem: Check if two Nodes are Cousins

Issue in Previous Code:
We were only checking children nodes.

Failing Case:
        5
         \
          6
         /
        2
         \
          4
         / \
        1   3

a = 1
b = 1

A node cannot be cousin with itself.

So first handle:
if(a == b) return false;

--------------------------------------------------

Correct BFS Approach:

For every node store:
1. current node
2. parent node

Then when we find a and b:
- compare levels
- compare parents

If:
same level && different parents
=> cousins

--------------------------------------------------

Time Complexity: O(N)
Space Complexity: O(N)

GFG:
https://www.geeksforgeeks.org/problems/check-if-two-nodes-are-cousins/1

LeetCode Similar:
https://leetcode.com/problems/cousins-in-binary-tree/

--------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node *left, *right;
    Node(int x) : data(x), left(NULL), right(NULL) {}
};

class Solution {
public:

    bool isCousins(Node* root, int a, int b) {

        // Same node can never be cousins
        if(a == b)
            return false;

        if(root == NULL)
            return false;

        // queue stores:
        // {node, parent}
        queue<pair<Node*, Node*>> q;

        q.push({root, NULL});

        while(!q.empty()) {

            int size = q.size();

            Node* parentA = NULL;
            Node* parentB = NULL;

            // Process one level
            for(int i = 0; i < size; i++) {

                auto frontNode = q.front();
                q.pop();

                Node* curr   = frontNode.first;
                Node* parent = frontNode.second;

                // Found node a
                if(curr->data == a)
                    parentA = parent;

                // Found node b
                if(curr->data == b)
                    parentB = parent;

                // Push children
                if(curr->left)
                    q.push({curr->left, curr});

                if(curr->right)
                    q.push({curr->right, curr});
            }

            // Both found at same level
            if(parentA && parentB) {

                // Parents must be different
                return parentA != parentB;
            }

            // Only one found
            if(parentA || parentB)
                return false;
        }

        return false;
    }
};

/*
Dry Run:

        1
      /   \
     2     3
    /       \
   5         4

a = 5
b = 4

Level 0:
1

Level 1:
2, 3

Level 2:
5(parent=2), 4(parent=3)

Same level
Different parents

Answer = true

--------------------------------------------------

Important Edge Cases:
1. a == b
2. One node missing
3. Sibling nodes
4. Root node involved

--------------------------------------------------

Why This Works Better?
Because we directly track:
- LEVEL using BFS
- PARENT using queue pair

This is the cleanest interview solution.
*/
