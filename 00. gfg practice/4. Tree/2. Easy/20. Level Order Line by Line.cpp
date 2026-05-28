/*
GeeksforGeeks: Level Order Line by Line
Difficulty: Easy

Problem:
Given the root of a binary tree, return its level order traversal line by line as a 2D array.

Return:
vector<vector<int>> where each inner vector represents a specific level.

Example:
Input: root = [1, 2, 3, 4, 5, 6, 7]
Output: [[1], [2, 3], [4, 5, 6, 7]]

Core Idea:
Use a standard Level Order Traversal (BFS) intelligently with a queue.
At the very beginning of each iteration of the outer loop, the size of the queue tells us exactly how many nodes exist exclusively on the current depth level.
We seamlessly process precisely that many nodes in an inner loop, strategically collect them into a single temporary array, and successfully push that array to our final 2D result list.

Approach:
1. Base Case: If `root` is explicitly null, securely return an empty `vector<vector<int>>`.
2. Initialize the 2D result array `ans` and a generic queue `q`.
3. Push `root` into `q`.
4. While `q` is physically not empty:
   a. Check `level_size = q.size()`.
   b. Dynamically create a temporary `vector<int> current_level`.
   c. Loop exactly `level_size` times:
      i. Pop a structural node from `q`.
      ii. Appensively add its data to `current_level`.
      iii. Securely push its left and right physical children to `q` (if they actively exist).
   d. Gracefully push `current_level` into the overall `ans`.
5. Return the natively populated `ans`.

Time Complexity: O(N) as we identically safely process each node in the tree explicitly once.
Space Complexity: O(W) (where W is the dynamically max width of the tree, which bounds at worst structurally to O(N))

GFG Link:
https://www.geeksforgeeks.org/problems/level-order-traversal-line-by-line/1
*/

#include <iostream>
#include <vector>
#include <queue>

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
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> ans;
        if (!root) {
            return ans;
        }
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int level_size = q.size();
            vector<int> current_level;
            
            // Process exactly the number of physical nodes logically present at the current levelfire
            for (int i = 0; i < level_size; ++i) {
                Node* curr = q.front();
                q.pop();
                
                current_level.push_back(curr->data);
                
                // Queue the next level logically
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            
            // Flawlessly store the finalized level logically
            ans.push_back(current_level);
        }
        
        return ans;
    }
};

/*
Dry Run:
        1
       / \
      2   3

queue = [1]
level_size = 1
i = 0: pop 1, push 2, push 3
current_level = [1]
ans = [[1]]

queue = [2, 3]
level_size = 2
i = 0: pop 2, push nothing
i = 1: pop 3, push nothing
current_level = [2, 3]
ans = [[1], [2, 3]]

queue = [] -> explicitly loop completely terminates
Return [[1], [2, 3]]
*/
