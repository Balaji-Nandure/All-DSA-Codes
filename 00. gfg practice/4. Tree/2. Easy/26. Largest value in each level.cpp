/*
GeeksforGeeks: Largest value in each level
Difficulty: Easy

Problem:
Given a binary tree, find the largest value in each level.
Return a vector containing the largest value in each level.

Return:
vector<int> representing the largest values at each level.

Example:
Input :
        4
       / \
      9   2
     / \   \
    3   5   7 

Output : 4 9 7
Explanation : 
There are three levels in the tree:
1. {4}, max = 4
2. {9, 2}, max = 9
3. {3, 5, 7}, max = 7

Core Idea:
Use a standard Level Order Traversal (BFS) with a queue.
At the beginning of each outer loop iteration, the size of the queue precisely tells us how many nodes exist on the current level.
We process exactly that number of nodes in an inner loop, dynamically keeping track of the maximum value seen in that level.
After the inner loop completes, simply push the level maximum to the answer array.

Approach:
1. Base Case: If `root` is null, securely return an empty `vector<int>`.
2. Initialize an `ans` array and a `queue<Node*> q`.
3. Push `root` into `q`.
4. While `q` is not empty:
   a. Track `level_size = q.size()`.
   b. Initialize `level_max = INT_MIN`.
   c. Loop exactly `level_size` times:
      i. Pop a node `curr` from the front of the queue.
      ii. Update `level_max = max(level_max, curr->data)`.
      iii. Push its left and right children to `q` (if they exist).
   d. Push `level_max` into `ans`.
5. Return `ans`.

Time Complexity: O(N) since every node is processed exactly once.
Space Complexity: O(W) where W is the maximum width of the tree.

(N = number of nodes)

GFG Link:
https://www.geeksforgeeks.org/problems/largest-value-in-each-level/1
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

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
    vector<int> largestValues(Node* root) {
        vector<int> ans;
        if (!root) {
            return ans;
        }
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int level_size = q.size();
            int level_max = INT_MIN;
            
            // Process all nodes logically present at the current depth
            for (int i = 0; i < level_size; ++i) {
                Node* curr = q.front();
                q.pop();
                
                level_max = max(level_max, curr->data);
                
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            
            ans.push_back(level_max);
        }
        
        return ans;
    }
};

/*
Dry Run:
        4
       / \
      9   2
     / \   \
    3   5   7 

queue = [4]
level_size = 1, max = INT_MIN
- pop 4: max = max(MIN, 4) = 4, push 9, 2
ans = [4]

queue = [9, 2]
level_size = 2, max = INT_MIN
- pop 9: max = max(MIN, 9) = 9, push 3, 5
- pop 2: max = max(9, 2) = 9, push 7
ans = [4, 9]

queue = [3, 5, 7]
level_size = 3, max = INT_MIN
- pop 3: max = max(MIN, 3) = 3
- pop 5: max = max(3, 5) = 5
- pop 7: max = max(5, 7) = 7
ans = [4, 9, 7]

queue = [] -> loop terminates
Return [4, 9, 7]
*/
