/*
GeeksforGeeks: Sorted Elements Of BST
Difficulty: Easy

Problem:
You are given the root node of a Binary Search Tree (BST), Return the elements of the tree in sorted order.

Examples:
Input: root = [10, 5, 18, N, N, 12]
Output: [5, 10, 12, 18]
Explanation: The Sorted order of BST is 5, 10, 12, 18.

Input: root = [22, 12, 30, 8, 20]
Output: [8, 12, 20, 22, 30]
Explanation: The Sorted order of BST is 8, 12, 20, 22, 30.

Core Idea:
A fundamental property of a Binary Search Tree (BST) is that an inorder traversal (Left-Root-Right) visits the nodes in strictly ascending, sorted order.
Therefore, to get the sorted elements of a BST, we simply need to perform a standard inorder traversal and collect the node values into an array or list.

Approach:
1. Initialize a `vector<int> result` to hold the sorted values.
2. Create a recursive helper function `inorder(Node* root, vector<int>& result)`:
   - Base Case: If `root` is `nullptr`, just return.
   - Recursive Step 1: Traverse the left subtree (`inorder(root->left, result)`).
   - Process Node: Add `root->data` to `result`.
   - Recursive Step 2: Traverse the right subtree (`inorder(root->right, result)`).
3. In the main function, call `inorder` with the tree root and return the `result` vector.

Time Complexity: O(N), where N is the number of nodes in the BST, since we visit every node exactly once.
Space Complexity: O(H) auxiliary space for the recursion stack, where H is the height of the tree. The result array itself takes O(N) space.

GFG Link: https://www.geeksforgeeks.org/problems/sorted-elements-of-bst/1
*/

#include <iostream>
#include <vector>

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
    void inorder(Node* root, vector<int>& result) {
        if (root == nullptr) {
            return;
        }
        
        inorder(root->left, result);        // Traverse left subtree
        result.push_back(root->data);       // Process current node
        inorder(root->right, result);       // Traverse right subtree
    }

public:
    // Function to return a list of integers denoting the sorted traversal of BST.
    vector<int> sortedElements(Node *root) {
        vector<int> result;
        inorder(root, result);
        return result;
    }
};

/*
Dry Run — Example 1:
Input: root = [10, 5, 18, N, N, 12]
Tree structure:
        10
       /  \
      5    18
          /
        12

1. sortedElements(10): calls inorder(10, result). result = [].

2. inorder(10):
   - calls inorder(10->left) -> inorder(5)

3. inorder(5):
   - calls inorder(5->left) -> inorder(null) -> returns
   - pushes 5. result = [5].
   - calls inorder(5->right) -> inorder(null) -> returns
   - returns to 10

4. inorder(10) resumes:
   - pushes 10. result = [5, 10].
   - calls inorder(10->right) -> inorder(18)

5. inorder(18):
   - calls inorder(18->left) -> inorder(12)

6. inorder(12):
   - calls inorder(12->left) -> inorder(null) -> returns
   - pushes 12. result = [5, 10, 12].
   - calls inorder(12->right) -> inorder(null) -> returns
   - returns to 18

7. inorder(18) resumes:
   - pushes 18. result = [5, 10, 12, 18].
   - calls inorder(18->right) -> inorder(null) -> returns
   - returns to 10

8. inorder(10) completes.

9. sortedElements returns result = [5, 10, 12, 18].

Output: [5, 10, 12, 18]
*/
