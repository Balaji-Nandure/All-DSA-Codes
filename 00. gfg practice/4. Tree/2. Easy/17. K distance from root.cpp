/*
GeeksforGeeks: K distance from root
Difficulty: Easy

Problem:
Given a binary tree having n nodes and an integer k, return all nodes that are at distance k from the root (root is considered at distance 0 from itself). Nodes should be returned from left to right.

Return:
vector<int> containing all nodes at distance k.

Example:
Input: k = 3
        1
       / \
      2   3
     /     \
    4       5
Output: [4, 5] (Assuming 4 and 5 are at distance 2, if there were children at distance 3, they would be returned).

Core Idea:
Use DFS to traverse the tree while keeping track of the current distance from the root.
When the current distance equals k, we've found a valid node.
Since we traverse the left child before the right child, the nodes will naturally be correctly appended in left-to-right order.

Approach:
1. Create a helper function `solve(root, current_distance, k, ans)`.
2. Base case: If `root` is null, simply return.
3. If `current_distance == k`, push `root->data` to `ans` and return (no need to go deeper since we strictly want distance k).
4. Recursively call `solve` for left and right children with `current_distance + 1`.
5. Return the populated `ans` array.

Time Complexity: O(N)
Space Complexity: O(H)

(H = tree height)

GFG Link:
https://www.geeksforgeeks.org/problems/k-distance-from-root/1
*/

#include <iostream>
#include <vector>

using namespace std;

// Definition for a binary tree node
struct Node {
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
    void solve(Node* root, int current_distance, int k, vector<int>& ans) {
        if (!root) {
            return;
        }
        
        // Target distance reached
        if (current_distance == k) {
            ans.push_back(root->data);
            return; // No need to traverse deeper
        }
        
        // Traverse left then right to strictly maintain left-to-right order
        solve(root->left, current_distance + 1, k, ans);
        solve(root->right, current_distance + 1, k, ans);
    }

    vector<int> Kdistance(Node *root, int k) {
        vector<int> ans;
        solve(root, 0, k, ans);
        return ans;
    }
};

/*
Dry Run:

        1
       / \
      2   3
     /     \
    4       5

k = 2

solve(1, 0):
  solve(2, 1):
    solve(4, 2):
      k reached! ans = [4]
  solve(3, 1):
    solve(5, 2):
      k reached! ans = [4, 5]

Answer = [4, 5]
*/
