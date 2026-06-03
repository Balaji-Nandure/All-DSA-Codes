/*
GeeksforGeeks: Construct BST from Postorder
Difficulty: Easy

Problem:
Given postorder traversal of a Binary Search Tree, you need to construct a BST from postorder traversal. The output will be inorder traversal of the constructed BST.

Examples:
Input: post[] = [1, 7, 5, 50, 40, 10]
Output: [1, 5, 7, 10, 40, 50] (Inorder traversal of the constructed BST)

Input: post[] = [2, 1, 3, 5]
Output: [1, 2, 3, 5]

Core Idea:
In a postorder traversal (Left, Right, Root), the last element of the array is always the root of the tree.
Since it's a BST, we know that all elements in the right subtree are strictly greater than the root, and elements in the left subtree are strictly smaller.
If we iterate through the postorder array from right to left (starting from the last element), we will first encounter the root, then the elements of its right subtree, and finally the elements of its left subtree.
We can use a range-based approach: maintain an allowed range `[minBound, maxBound]` for each node.
If the current element falls within this range, it belongs to the current subtree. We create a node, decrement our index, and recursively build the right subtree (updating the lower bound to `root->data`) and then the left subtree (updating the upper bound to `root->data`). 
It's crucial to build the right subtree *before* the left subtree because we are processing the postorder array in reverse.

Approach:
1. Initialize an index `i = size - 1`.
2. Call a recursive function `buildBST(post, i, minBound, maxBound)`.
3. In `buildBST`:
   - Base case: If `i < 0` or `post[i]` is not within `[minBound, maxBound]`, return `nullptr`.
   - Create a new `Node` with `post[i]`.
   - Decrement `i`.
   - Recursively call `buildBST` for `root->right` with `minBound = root->data` and `maxBound = maxBound`.
   - Recursively call `buildBST` for `root->left` with `minBound = minBound` and `maxBound = root->data`.
   - Return the `root`.

Time Complexity: O(N), where N is the number of nodes. We visit each element of the postorder array exactly once.
Space Complexity: O(H), where H is the height of the BST, due to the recursion stack. In the worst case (skewed tree), it's O(N).

GFG Link: https://www.geeksforgeeks.org/problems/construct-bst-from-post-order/1
*/

#include <iostream>
#include <climits>

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
   Node* buildBST(int post[], int& i, int minBound, int maxBound) {
      // Base case: no elements left or element doesn't belong to current subtree's bounds
      if (i < 0 || post[i] < minBound || post[i] > maxBound) {
         return nullptr;
      }

      // The current element becomes the root of this subtree
      Node* root = new Node(post[i]);
      i--; // Move to the next element from right to left

      // Build right subtree FIRST (since right child comes right before root in postorder)
      root->right = buildBST(post, i, root->data, maxBound);
      
      // Build left subtree SECOND
      root->left = buildBST(post, i, minBound, root->data);

      return root;
   }

public:
   Node* constructTree(int post[], int size) {
      int i = size - 1;
      return buildBST(post, i, INT_MIN, INT_MAX);
   }
};
 
/*
Dry Run — Example 1:
Input: post[] = [1, 7, 5, 50, 40, 10], size = 6

1. constructTree calls buildBST with i = 5, bounds = [INT_MIN, INT_MAX].
   post[5] = 10. Within bounds. root = Node(10), i = 4.
   
2. root(10)->right calls buildBST(i = 4, bounds = [10, INT_MAX]).
   post[4] = 40. Within bounds. root = Node(40), i = 3.
   
3. root(40)->right calls buildBST(i = 3, bounds = [40, INT_MAX]).
   post[3] = 50. Within bounds. root = Node(50), i = 2.
   
4. root(50)->right calls buildBST(i = 2, bounds = [50, INT_MAX]).
   post[2] = 5. NOT within bounds. Returns NULL.
   
5. root(50)->left calls buildBST(i = 2, bounds = [40, 50]).
   post[2] = 5. NOT within bounds. Returns NULL.
   
6. root(40)->left calls buildBST(i = 2, bounds = [10, 40]).
   post[2] = 5. NOT within bounds. Returns NULL.
   
7. root(10)->left calls buildBST(i = 2, bounds = [INT_MIN, 10]).
   post[2] = 5. Within bounds. root = Node(5), i = 1.
   
8. root(5)->right calls buildBST(i = 1, bounds = [5, 10]).
   post[1] = 7. Within bounds. root = Node(7), i = 0.
   
9. root(7)->right calls buildBST(i = 0, bounds = [7, 10]).
   post[0] = 1. NOT within bounds. Returns NULL.
   
10. root(7)->left calls buildBST(i = 0, bounds = [5, 7]).
    post[0] = 1. NOT within bounds. Returns NULL.
    
11. root(5)->left calls buildBST(i = 0, bounds = [INT_MIN, 5]).
    post[0] = 1. Within bounds. root = Node(1), i = -1.
    
12. Returns bubble up. The constructed tree is returned.

    Tree structure:
          10
         /  \
        5    40
       / \     \
      1   7     50
*/
