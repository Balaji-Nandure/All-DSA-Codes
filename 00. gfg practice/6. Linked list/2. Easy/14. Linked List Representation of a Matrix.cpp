/*
GeeksforGeeks: Linked List Representation of a Matrix
Difficulty: Easy

Problem:
Given a Matrix mat of n*n size. Your task is constructing a 2D linked list representation of the given matrix.
Each node of the 2D linked list contains data, a right pointer, and a down pointer.

Example 1:
Input: mat[][] = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
Output: 2D Linked list representation.
Explanation: 
1 -> 2 -> 3
|    |    |
4 -> 5 -> 6
|    |    |
7 -> 8 -> 9

Example 2:
Input: mat[][] = [[23, 28], [23, 28]]
Output: 2D Linked list representation.

Core Idea:
A 2D linked list requires us to map every matrix element `mat[i][j]` to a `Node`. 
Each `Node` at `(i, j)` must point to the `Node` at `(i, j+1)` via its `right` pointer and to the `Node` at `(i+1, j)` via its `down` pointer.
To easily establish these links without multiple complex traversals, we can first create a 2D array (or vector) of `Node*` and instantiate a node for every `mat[i][j]`. 
After all nodes are created, we can iterate through this 2D array and set the `right` and `down` pointers by simply checking boundary conditions.

Approach:
1. Get the size of the matrix `n` (since it's an n*n matrix).
2. Create a 2D vector `nodeMatrix` of size `n x n` to store pointers to the newly created nodes.
3. First Pass: Iterate through `i` from 0 to `n-1` and `j` from 0 to `n-1`, creating a new `Node` for each `mat[i][j]` and storing it in `nodeMatrix[i][j]`.
4. Second Pass: Iterate through the grid again. For each node at `[i][j]`:
   a. If `j + 1 < n`, set `nodeMatrix[i][j]->right = nodeMatrix[i][j+1]`.
   b. If `i + 1 < n`, set `nodeMatrix[i][j]->down = nodeMatrix[i+1][j]`.
5. Return the top-left node `nodeMatrix[0][0]` as the head of the 2D linked list.

Time Complexity: O(N^2) where N is the dimension of the matrix. We process each of the N^2 elements a constant number of times.
Space Complexity: O(N^2) to store the 2D array of pointers. This is well within limits as N <= 15.

GFG Link:
https://www.geeksforgeeks.org/problems/linked-list-matrix/1
*/

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* right;
    Node* down;
    
    Node(int x) {
        data = x;
        right = NULL;
        down = NULL;
    }
};

class Solution {
public:
    Node* constructLinkedMatrix(vector<vector<int>>& mat) {
        int n = mat.size();
        if (n == 0) return NULL;
        
        vector<vector<Node*>> nodeMatrix(n, vector<Node*>(n, NULL));
        
        // Step 1: Create all nodes
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                nodeMatrix[i][j] = new Node(mat[i][j]);
            }
        }
        
        // Step 2: Establish right and down links
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j + 1 < n) {
                    nodeMatrix[i][j]->right = nodeMatrix[i][j + 1];
                }
                if (i + 1 < n) {
                    nodeMatrix[i][j]->down = nodeMatrix[i + 1][j];
                }
            }
        }
        
        return nodeMatrix[0][0];
    }
};

/*
Dry Run — Example 1:
Input: mat[][] = [[1, 2], [3, 4]]
n = 2

Step 1 (Create nodes):
nodeMatrix = [
    [Node(1), Node(2)],
    [Node(3), Node(4)]
]

Step 2 (Establish links):
- i=0, j=0 (Node 1): 
  - j+1 < 2 is TRUE -> 1->right = Node(2)
  - i+1 < 2 is TRUE -> 1->down = Node(3)
  
- i=0, j=1 (Node 2): 
  - j+1 < 2 is FALSE. right remains NULL.
  - i+1 < 2 is TRUE -> 2->down = Node(4)
  
- i=1, j=0 (Node 3):
  - j+1 < 2 is TRUE -> 3->right = Node(4)
  - i+1 < 2 is FALSE. down remains NULL.
  
- i=1, j=1 (Node 4):
  - j+1 < 2 is FALSE. right remains NULL.
  - i+1 < 2 is FALSE. down remains NULL.

Step 3 (Return):
Return nodeMatrix[0][0] which is Node(1).

Final Output Structure:
1 -> 2
|    |
3 -> 4
*/
