/*
GeeksforGeeks: Exchange the Leaf Nodes
Difficulty: Easy

Problem:
Given a binary tree, you have to swap leaf nodes in the given binary tree pairwise 
starting from left to right.

Example 1:
Input: 
          1
       /     \
      2       3
       \    /    \
        5  6      7
Output: [2, 6, 1, 5, 3, 7] (Inorder traversal)
Explanation: 
The leaf nodes from left to right are: 5, 6, 7.
We swap them pairwise:
- Swap 5 and 6.
- 7 has no pair, so it remains unchanged.
The new leaves are: 6, 5, 7.
The modified tree is:
        1
     /     \
    2       3
     \    /   \
      6  5     7
Inorder traversal of this modified tree is [2, 6, 1, 5, 3, 7].

Example 2:
Input: 
          2
       /     \
      6       3
            /    \
           9      7
Output: [9, 2, 6, 3, 7]
Explanation: 
Leaves from left to right: 6, 9, 7.
Pairwise swap: swap 6 and 9.
New leaves: 9, 6, 7.
The inorder traversal of the modified tree is [9, 2, 6, 3, 7].

Core Idea:
Since we just need to swap the values of the leaf nodes from left to right, we 
can easily perform a standard Depth-First Search (DFS) which naturally visits leaves 
in left-to-right order. 
To swap them pairwise, we can keep track of a `firstLeaf` pointer. 
- The first time we see a leaf, we just remember it by setting `firstLeaf = curr`.
- The second time we see a leaf, we swap its value with `firstLeaf->data`, and then 
  reset `firstLeaf = NULL` to get ready for the next pair!

Approach:
1. Create a recursive helper function `solve(Node* root, Node*& firstLeaf)`.
2. Base case: If `root` is NULL, return.
3. If `root` is a leaf (`!root->left && !root->right`):
   a. If `firstLeaf == NULL`, we store `root` in `firstLeaf`.
   b. Else, we swap `firstLeaf->data` and `root->data`, and reset `firstLeaf = NULL`.
4. If `root` is not a leaf, recurse on `root->left` then `root->right`.
5. In the main function, initialize `Node* firstLeaf = NULL` and call `solve(root, firstLeaf)`.

Time Complexity : O(N) — Every node is visited exactly once.
Space Complexity: O(H) — Recursion stack depth equals the height of the tree.

(N = number of nodes, H = height of the tree)

GFG Link:
https://www.geeksforgeeks.org/problems/exchange-the-leaf-nodes1613/1
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node
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
private:
    void solve(Node* root, Node*& firstLeaf) {
        if (!root) {
            return;
        }
        
        // If the current node is a leaf
        if (!root->left && !root->right) {
            if (firstLeaf == NULL) {
                // This is the first leaf of the current pair
                firstLeaf = root;
            } else {
                // This is the second leaf of the current pair, so we swap!
                swap(firstLeaf->data, root->data);
                
                // Reset for the next pair
                firstLeaf = NULL;
            }
            return;
        }
        
        // Traverse left and right to find leaves from left to right
        solve(root->left, firstLeaf);
        solve(root->right, firstLeaf);
    }
    
public:
    void pairwiseSwap(Node *root) {
        // We pass firstLeaf by reference to avoid using global variables
        Node* firstLeaf = NULL;
        solve(root, firstLeaf);
    }
};

/*
Dry Run — Example 1:
          1
       /     \
      2       3
       \    /    \
        5  6      7

pairwiseSwap(1):
  - firstLeaf = NULL
  - solve(1):
    --> solve(2):
        --> solve(NULL)
        --> solve(5) -> Leaf!
            - firstLeaf is NULL. So firstLeaf = 5.
    --> solve(3):
        --> solve(6) -> Leaf!
            - firstLeaf is NOT NULL (it points to 5).
            - swap(5->data, 6->data). Tree leaves are now 6, 5.
            - firstLeaf = NULL.
        --> solve(7) -> Leaf!
            - firstLeaf is NULL. So firstLeaf = 7.

Traversal ends.
The nodes with original values 5 and 6 have been swapped. Node 7 is unchanged.
Final Inorder traversal: [2, 6, 1, 5, 3, 7] ✓
*/
