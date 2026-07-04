/*
    Problem Name: Top View of Binary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    You are given the root of a binary tree, and your task is to return its top view. 
    The top view of a binary tree is the set of nodes visible when the tree is viewed from the top.
    Return the nodes from the leftmost node to the rightmost node.
    If multiple nodes overlap at the same horizontal position, only the topmost (closest to the root) node is included.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. Using Level Order Traversal (BFS) processes each node once. By keeping track of the minimum and maximum horizontal distance manually, we easily avoid the O(log N) overhead of a standard std::map, achieving strict O(N) time.
    Space Complexity: O(N), for the BFS queue and the Hash Map holding the top nodes.

    Love Babbar Style Approach:
    1. To get the "Top View", we can logically assign a Horizontal Distance (hd) to each node. 
       - The root is at hd = 0.
       - A left child goes left: (hd - 1).
       - A right child goes right: (hd + 1).
    2. Since we only want the TOP-MOST node at each horizontal distance, we MUST traverse level-by-level using Breadth-First Search (BFS). This heavily guarantees that the very first node we encounter at any specific `hd` is absolutely the highest one in the tree!
    3. We use a simple `queue` holding pairs of `(Node*, hd)`.
    4. We use an `unordered_map<int, int> topNode` to store exactly the first node's data we see at each `hd`. (If an `hd` already exists in the map, we simply ignore the new node because it's lower down and blocked from the top view).
    5. While doing BFS, we smoothly keep track of `min_hd` and `max_hd` so that at the end, we can easily run a simple loop from `min_hd` to `max_hd` and push the values from our map into the `ans` array strictly from left to right.

    Dry Run:
    Tree:
           1 (hd=0)
         /   \
  (hd=-1)2     3 (hd=1)

    - Queue: [{1, 0}]. min_hd=0, max_hd=0
    - Pop {1, 0}: hd=0 not in map! topNode[0] = 1.
      Push left: {2, -1}. Push right: {3, 1}.
    - Pop {2, -1}: hd=-1 not in map! topNode[-1] = 2. min_hd = -1.
    - Pop {3, 1}: hd=1 not in map! topNode[1] = 3. max_hd = 1.
    
    Loop from min_hd (-1) to max_hd (1):
    i = -1 -> topNode[-1] = 2
    i = 0  -> topNode[0]  = 1
    i = 1  -> topNode[1]  = 3
    
    Result = [2, 1, 3]. Matches perfectly!
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

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
    vector<int> topView(Node *root) {
        vector<int> ans;
        if (root == NULL) return ans;
        
        // Map to store exactly the top-most node's data at each horizontal distance (hd)
        unordered_map<int, int> topNode;
        
        // Queue for Level Order Traversal: stores pairs of {Node*, horizontal_distance}
        queue<pair<Node*, int>> q;
        
        // Push the root with an initial horizontal distance of 0
        q.push({root, 0});
        
        int min_hd = 0;
        int max_hd = 0;
        
        while (!q.empty()) {
            pair<Node*, int> temp = q.front();
            q.pop();
            
            Node* frontNode = temp.first;
            int hd = temp.second;
            
            // Maintain the boundaries of our horizontal distances
            min_hd = min(min_hd, hd);
            max_hd = max(max_hd, hd);
            
            // If this horizontal distance is seen for the VERY FIRST TIME, 
            // then this node is perfectly the top-most node for this column!
            if (topNode.find(hd) == topNode.end()) {
                topNode[hd] = frontNode->data;
            }
            
            // Push left and right children with their respective hd offsets
            if (frontNode->left) {
                q.push({frontNode->left, hd - 1});
            }
            
            if (frontNode->right) {
                q.push({frontNode->right, hd + 1});
            }
        }
        
        // Extract the final top view strictly from leftmost to rightmost column
        for (int i = min_hd; i <= max_hd; i++) {
            ans.push_back(topNode[i]);
        }
        
        return ans;
    }
};

int main() {
    // Example test case 
    //      1
    //    /   \
    //   2     3
    
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    
    Solution ob;
    vector<int> res = ob.topView(root);
    
    for (int x : res) {
        cout << x << " ";
    }
    cout << "\n";
    
    return 0;
}
