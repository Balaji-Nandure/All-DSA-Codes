/*
    Problem Name: Vertical Tree Traversal
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a Binary Tree, find the vertical traversal of the tree starting from the leftmost level to the rightmost level.
    If there are multiple nodes passing through a vertical line, then they should be printed as they appear in level order traversal.

    Expected Complexities:
    Time Complexity: O(N) - We optimize standard map insertion to O(N) using unordered_map + manual min/max tracking!
    Space Complexity: O(N) - For the queue and hash map.

    Love Babbar Style Approach:
    1. We logically assign a Horizontal Distance (hd) to every node. Root is at `hd = 0`. Left child goes to `hd - 1`. Right child goes to `hd + 1`.
    2. Because nodes on the exact same vertical line must be printed in level-order, we absolutely MUST use Breadth-First Search (BFS) Level Order Traversal!
    3. We use a queue containing pairs of `(Node*, hd)`.
    4. We use an `unordered_map<int, vector<int>> nodes` to cleanly map each `hd` column to all the nodes that fall on it.
    5. We could use a standard `map` to automatically sort the `hd` keys, but `map` insertion is `O(log N)`. 
       Instead, we can easily achieve strict `O(N)` time complexity by simply keeping track of the `min_hd` and `max_hd` manually during our BFS, exactly like we did for the Top View problem!
    6. Finally, we just run a simple `for` loop from `min_hd` to `max_hd` and dump all the grouped nodes into our final `ans` array from left to right.

    Dry Run:
    Tree:
           1 (hd=0)
         /   \
  (hd=-1)2     3 (hd=1)
       /  \      \
(-2) 4     5(0)   6 (2)

    - Queue: [{1, 0}]. min_hd=0, max_hd=0
    - Pop {1, 0}: nodes[0] = [1]. Push {2, -1}, {3, 1}.
    - Pop {2, -1}: nodes[-1] = [2]. min_hd=-1. Push {4, -2}, {5, 0}.
    - Pop {3, 1}: nodes[1] = [3]. max_hd=1. Push {6, 2}.
    - Pop {4, -2}: nodes[-2] = [4]. min_hd=-2.
    - Pop {5, 0}: nodes[0] = [1, 5].
    - Pop {6, 2}: nodes[2] = [6]. max_hd=2.
    
    Loop from min_hd (-2) to max_hd (2):
    i = -2 -> [4]
    i = -1 -> [2]
    i =  0 -> [1, 5]
    i =  1 -> [3]
    i =  2 -> [6]
    
    Final Ans = [4, 2, 1, 5, 3, 6]. Matches perfectly!
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
    // Function to find the vertical order traversal of Binary Tree.
    vector<int> verticalOrder(Node *root) {
        vector<int> ans;
        if (root == NULL) return ans;
        
        // Map to store lists of nodes for every horizontal distance (hd)
        unordered_map<int, vector<int>> nodes;
        
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
            
            // Add the current node's data to the list for its specific horizontal column
            nodes[hd].push_back(frontNode->data);
            
            // Push left and right children with their respective hd offsets
            if (frontNode->left) {
                q.push({frontNode->left, hd - 1});
            }
            if (frontNode->right) {
                q.push({frontNode->right, hd + 1});
            }
        }
        
        // Extract the final vertical traversal strictly from leftmost to rightmost column
        for (int i = min_hd; i <= max_hd; i++) {
            for (int val : nodes[i]) {
                ans.push_back(val);
            }
        }
        
        return ans;
    }
};

int main() {
    // Example test case 
    //           1
    //         /   \
    //       2       3
    //     /   \       \
    //    4     5       6
    
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    
    root->right->right = new Node(6);
    
    Solution ob;
    vector<int> res = ob.verticalOrder(root);
    
    for (int x : res) {
        cout << x << " ";
    }
    cout << "\n";
    
    return 0;
}
