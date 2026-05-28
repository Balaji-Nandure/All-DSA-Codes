/*
Problem: Postorder Traversal

Given the root of a Binary Tree, your task is to return its Postorder Traversal.
Note: A postorder traversal first visits the left child (including its entire subtree), then visits the right child (including its entire subtree), and finally visits the node itself.

Constraints:
1 <= number of nodes <= 3*10^4
0 <= node->data <= 10^5

--------------------------------------------------

Pattern:
Tree Traversal (DFS)

--------------------------------------------------

Key Observation:
- Postorder traversal strictly follows the classic traversal order: Left -> Right -> Root.
- This specific ordering is incredibly useful for bottom-up operations that require evaluating children entirely *before* evaluating their parents, such as safely deleting an entire tree from memory or mathematically evaluating a post-fix expression tree.
- We can gracefully accomplish this natively using a simple, robust recursive Depth-First Search strategy.

--------------------------------------------------

Approach:
1. Initialize an empty `vector<int> res` to meticulously securely collect our traversal output.
2. Create a standard recursive `dfs` helper function that actively takes the current `node` and a reference to `res`.
3. Base case: If the current `node` is `nullptr`, immediately safely return (bottom out of the recursion stack).
4. Recursively natively traverse the entirely of the left subtree: `dfs(node->left, res)`.
5. Recursively natively traverse the entirely of the right subtree: `dfs(node->right, res)`.
6. Finally, explicitly process the current parent node by gracefully pushing its data into our list: `res.push_back(node->data)`.
7. Return the neatly fully populated `res` array from the main generic wrapper function.

--------------------------------------------------

Time Complexity: O(N) since we strictly physically visit every single node in the entire tree exactly once.
Space Complexity: O(N) overall natively. O(H) for the internal recursion stack where H is the maximum height of the tree (which smoothly degrades to linearly O(N) in the absolute worst-case perfectly skewed tree), plus O(N) to explicitly securely natively store the final requested answers array.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/postorder-traversal/1
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
private:
    void dfs(Node* root, vector<int>& res) {
        if (root == nullptr) {
            return;
        }
        
        // 1. Visit the entirely of the left subtree first
        dfs(root->left, res);
        
        // 2. Visit the entirely of the right subtree next
        dfs(root->right, res);
        
        // 3. Process the current root node absolutely last
        res.push_back(root->data);
    }

public:
    vector<int> postOrder(Node* root) {
        vector<int> res;
        dfs(root, res);
        return res;
    }
};
