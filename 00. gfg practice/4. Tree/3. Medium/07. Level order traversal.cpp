/*
    Problem Name: Level order traversal
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a Binary Tree, your task is to return its Level Order Traversal.
    A level order traversal is a breadth-first search (BFS) of the tree. 
    It visits nodes level by level, starting from the root, and processes all nodes from left to right within each level before moving to the next.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node exactly once.
    Space Complexity: O(N), where N is the maximum number of nodes at any level, to store them in the queue.

    Love Babbar Style Approach:
    1. This is the absolute most fundamental tree traversal: Breadth-First Search (BFS).
    2. We use a simple `queue` to securely keep track of the nodes to visit.
    3. We push the root node into the queue to start the process.
    4. Loop while the queue is not empty:
       - Pop the front node from the queue (we call it `temp`).
       - Store its data into our `ans` array.
       - If its left child exists, push it into the queue.
       - If its right child exists, push it into the queue.
    5. Because a queue is First-In-First-Out (FIFO), it naturally processes the tree level-by-level, strictly from left to right!

    Dry Run:
    Tree:
           10
         /    \
       20      30
      /  \ 
    40    50

    - q=[10].
    - Pop 10. ans=[10]. Push left(20), right(30). q=[20, 30].
    - Pop 20. ans=[10, 20]. Push left(40), right(50). q=[30, 40, 50].
    - Pop 30. ans=[10, 20, 30]. No children. q=[40, 50].
    - Pop 40. ans=[10, 20, 30, 40]. No children. q=[50].
    - Pop 50. ans=[10, 20, 30, 40, 50]. No children. q=[].
    
    Result matches exactly!
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
    vector<int> levelOrder(Node* root) {
        vector<int> ans;
        
        // Return empty array if the tree is empty
        if (root == NULL) {
            return ans;
        }
        
        // Initialize a queue for BFS
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            // Pop the front node
            Node* temp = q.front();
            q.pop();
            
            // Store the current node's data
            ans.push_back(temp->data);
            
            // If left child exists, queue it up for the next level
            if (temp->left) {
                q.push(temp->left);
            }
            
            // If right child exists, queue it up for the next level
            if (temp->right) {
                q.push(temp->right);
            }
        }
        
        return ans;
    }
};

int main() {
    // Example test case 
    //        10
    //      /    \ 
    //    20      30   
    //   /  \
    // 40    50
    
    Node* root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(40);
    root->left->right = new Node(50);
    
    Solution ob;
    vector<int> res = ob.levelOrder(root);
    
    for (int val : res) {
        cout << val << " ";
    }
    cout << "\n";
    
    return 0;
}
