/*
GeeksforGeeks: Nodes at Odd Levels
Difficulty: Easy

Problem:
Given a binary tree, find all the nodes at odd levels. Return in sorted order. 
The root is considered at level 1.

Example 1:
Input: root = [1, 2, 3, 4, 5, N, 6, N, N, 7, 8, 9]
          1
       /     \
      2       3
    /   \       \
   4     5       6
        /  \     /
       7    8   9
Output:  [1, 4, 5, 6]
Explanation: The odd levels are 1 and 3. The nodes at level 1 is 1. 
The nodes at level 3 are 4, 5, 6. Sorted order: 1, 4, 5, 6.

Example 2:
Input: root = [1, 2, 3, 4, 5, 8, 7]
          1
       /     \
     2        3
   /   \    /   \
  4     5  8     7
Output: [1, 4, 5, 7, 8]
Explanation: The odd levels are 1 and 3. Node at level 1 is 1. 
Nodes at level 3 are 4, 5, 8, 7. 
Combined: 1, 4, 5, 8, 7. Sorted: 1, 4, 5, 7, 8.

Core Idea:
This is a straightforward traversal problem combined with sorting. 
Since the problem asks for all nodes exactly at odd levels, we can just use 
Depth-First Search (DFS) while keeping track of the current depth `level`.
Whenever `level % 2 != 0`, we add the node's data to our result array.
Since the problem explicitly demands the output to be in **sorted order**, we 
can collect all the odd-level nodes in O(N) time and then sort the resulting 
array at the end.

Approach:
1. Create a helper function `dfs(root, level, res)`:
   a. Base Case: If `root` is NULL, return.
   b. Check if `level % 2 != 0` (i.e., it's an odd level). If so, push `root->data` 
      into `res`.
   c. Recursively call `dfs` for `root->left` and `root->right`, passing `level + 1`.
2. In the main function, call `dfs(root, 1, res)`. (Root is level 1).
3. Use `std::sort` on the resulting vector.
4. Return the sorted vector.

Time Complexity : O(N log N) — O(N) to traverse the tree + O(K log K) to sort K odd-level nodes (where K <= N).
Space Complexity: O(N) — For the result array and recursion stack.

GFG Link:
https://www.geeksforgeeks.org/problems/nodes-at-odd-levels/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

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
    void dfs(Node* root, int level, vector<int>& res) {
        if (!root) {
            return;
        }
        
        // Root is considered at level 1, which is odd
        if (level % 2 != 0) {
            res.push_back(root->data);
        }
        
        // Traverse left and right children, increasing the level
        dfs(root->left, level + 1, res);
        dfs(root->right, level + 1, res);
    }
    
public:
    vector<int> nodesAtOddLevels(Node *root) {
        vector<int> res;
        
        // Start DFS from root at level 1
        dfs(root, 1, res);
        
        // Sort the result vector in ascending order as requested
        sort(res.begin(), res.end());
        
        return res;
    }
};

/*
Dry Run — Example 2:
          1 (L1)
       /     \
     2        3 (L2)
   /   \    /   \
  4     5  8     7 (L3)

dfs(1, 1): 1 % 2 != 0 -> res = [1]. 
  - dfs(2, 2): 2 % 2 == 0 -> ignore.
    - dfs(4, 3): 3 % 2 != 0 -> res = [1, 4]. dfs(NULL), dfs(NULL)
    - dfs(5, 3): 3 % 2 != 0 -> res = [1, 4, 5]. dfs(NULL), dfs(NULL)
  - dfs(3, 2): 2 % 2 == 0 -> ignore.
    - dfs(8, 3): 3 % 2 != 0 -> res = [1, 4, 5, 8]. dfs(NULL), dfs(NULL)
    - dfs(7, 3): 3 % 2 != 0 -> res = [1, 4, 5, 8, 7]. dfs(NULL), dfs(NULL)

Traversal completes.
res = [1, 4, 5, 8, 7]
Sorting res -> [1, 4, 5, 7, 8]

Return [1, 4, 5, 7, 8]. ✓
*/
