/*
    Problem Name: ZigZag Tree Traversal
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree. You have to find the zig-zag level order traversal of the binary tree.
    Note: In zig zag traversal we traverse the nodes from left to right for odd-numbered levels, and from right to left for even-numbered levels.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes in the tree. We traverse every node exactly once using a simple queue.
    Space Complexity: O(N), used by the queue and the temporary array for each level.

    Love Babbar Style Approach:
    1. This problem is just a minor twist on standard Level Order Traversal (BFS).
    2. We maintain a boolean flag `leftToRight` initially set to `true`.
    3. We use a queue to process the tree level by level. For each level:
       - We first check `int size = q.size();` to know exactly how many nodes are in the current level.
       - We create a temporary array `row` of size `size` to cleanly store the values of this specific level.
       - For each node popped from the queue, we uniquely calculate its correct index in the `row` array using a simple mathematical check:
         * If `leftToRight` is true, we insert it normally at index `i`.
         * If `leftToRight` is false, we insert it in reverse at index `size - 1 - i`.
       - Push the left and right children (if any) to the queue for the next level.
    4. After completely processing the level, we simply flip the boolean flag (`leftToRight = !leftToRight`).
    5. Finally, append the values of `row` into our main `ans` array.

    Dry Run:
    Tree:
           1
         /   \
        2     3
       / \   / \
      4   5 6   7

    Level 1: q=[1], size=1, leftToRight=true
             Pop 1. index=0. row=[1]. push 2, 3.
             ans = [1]. flag becomes false.
    Level 2: q=[2, 3], size=2, leftToRight=false
             Pop 2 (i=0). index = 2 - 1 - 0 = 1. row=[_, 2]. push 4, 5.
             Pop 3 (i=1). index = 2 - 1 - 1 = 0. row=[3, 2]. push 6, 7.
             ans = [1, 3, 2]. flag becomes true.
    Level 3: q=[4, 5, 6, 7], size=4, leftToRight=true
             Pop 4 (i=0). index=0. row=[4, _, _, _].
             Pop 5 (i=1). index=1. row=[4, 5, _, _].
             ...
             ans = [1, 3, 2, 4, 5, 6, 7].
             
    Result perfectly matches ZigZag!
*/

#include <iostream>
#include <vector>
#include <queue>

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
public:
    vector<int> zigZagTraversal(Node* root) {
        vector<int> ans;
        if (root == NULL) return ans;
        
        queue<Node*> q;
        q.push(root);
        
        bool leftToRight = true;
        
        while (!q.empty()) {
            int size = q.size();
            
            // Temporary array for the current level
            vector<int> row(size);
            
            for (int i = 0; i < size; i++) {
                Node* frontNode = q.front();
                q.pop();
                
                // Magic formula to handle insertion order dynamically!
                int index = leftToRight ? i : (size - 1 - i);
                row[index] = frontNode->data;
                
                // Push children for the next level
                if (frontNode->left) {
                    q.push(frontNode->left);
                }
                if (frontNode->right) {
                    q.push(frontNode->right);
                }
            }
            
            // Flip the direction for the next level
            leftToRight = !leftToRight;
            
            // Append the correctly ordered level to our final answer
            for (int val : row) {
                ans.push_back(val);
            }
        }
        
        return ans;
    }
};

int main() {
    // Example test case 
    //        1
    //      /   \
    //     2     3
    //    / \   / \
    //   4   5 6   7
    
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    
    Solution ob;
    vector<int> res = ob.zigZagTraversal(root);
    
    for (int x : res) {
        cout << x << " ";
    }
    cout << "\n";
    
    return 0;
}
