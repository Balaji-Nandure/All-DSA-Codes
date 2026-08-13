/*
    Problem Name: Sum of nodes within k distance from target
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree, a target node value, and an integer k, return the sum of
    all node values that are within a distance of k from the target node.
    - Distance between two nodes = number of edges in the shortest path connecting them.
    - Target node itself is included in the sum (distance 0).

    Examples:
    Input: k = 1, target = 3, root[] = [1, 2, 3, 4, N, 5, 7]
    Output: 16
    Explanation:
            1
          /   \
         2     3
        /     / \
       4     5   7
    Nodes within distance 1 from node 3 are:
    - Distance 0: 3
    - Distance 1: 5 (left child), 7 (right child), 1 (parent)
    Sum = 3 + 5 + 7 + 1 = 16.

    Input: k = 2, target = 40, root[] = [1, 2, 3, 4, N, 5, 7, 8, 19, N, N, 20, 11, 30, N, 40, 50]
    Output: 113

    Constraints:
    1 <= n <= 10^3
    1 <= data in nodes, target <= 10^5
    1 <= k <= 20
    All node values are unique.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. BFS parent mapping + BFS traversal.
    Space Complexity: O(N), for hash maps (parent map & visited map) and BFS queues.

    Love Babbar Style Approach:
    Parent Mapping + Multi-directional BFS (Graph Conversion):

    1. INTUITION:
       - A binary tree only has downward pointers (`left` and `right`), making it impossible to move
         UPWARDS towards parent nodes directly.
       - By mapping each node to its parent (`unordered_map<Node*, Node*> parentMap`), we effectively
         convert the binary tree into an UNDIRECTED GRAPH.
       - From the `targetNode`, we perform a standard Breadth-First Search (BFS) in all 3 directions:
         1. Left child (`curr->left`)
         2. Right child (`curr->right`)
         3. Parent node (`parentMap[curr]`)
       - Sum up all unvisited nodes encountered level-by-level up to radius `k`.

    2. ALGORITHM:
       - Step 1: Use BFS to populate `parentMap` and locate `targetNode` pointer.
       - Step 2: Initialize `queue<Node*> q`, `unordered_map<Node*, bool> visited`, `sum = 0`, `currDist = 0`.
       - Step 3: Push `targetNode` to `q` and mark `visited[targetNode] = true`.
       - Step 4: While (`!q.empty()` && `currDist <= k`):
         * Level size `sz = q.size()`.
         * For `i = 0` to `sz - 1`:
           - Pop `curr = q.front()`.
           - `sum += curr->data`.
           - Push unvisited neighbours: `curr->left`, `curr->right`, `parentMap[curr]`.
         * `currDist++`.
       - Return `sum`.

    Dry Run:
    target = 3, k = 1, root = 1
    - parentMap[3] = 1, parentMap[5] = 3, parentMap[7] = 3
    - q = [3], visited = {3}, sum = 0, currDist = 0

    - currDist = 0: pop 3 -> sum = 3.
      Push neighbours: 5, 7, 1.
      q = [5, 7, 1], visited = {3, 5, 7, 1}.

    - currDist = 1:
      pop 5 -> sum = 3 + 5 = 8
      pop 7 -> sum = 8 + 7 = 15
      pop 1 -> sum = 15 + 1 = 16.

    - currDist = 2 > k (1) -> Loop ends.
    Result: 16 ✓
*/

#include <iostream>
#include <vector>
#include <unordered_map>
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
private:
    // Helper function to map parent pointers and locate the target node
    Node* mapParentsAndFindTarget(Node* root, int target, unordered_map<Node*, Node*>& parentMap) {
        queue<Node*> q;
        q.push(root);
        parentMap[root] = NULL;

        Node* targetNode = NULL;

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            if (curr->data == target) {
                targetNode = curr;
            }

            if (curr->left) {
                parentMap[curr->left] = curr;
                q.push(curr->left);
            }

            if (curr->right) {
                parentMap[curr->right] = curr;
                q.push(curr->right);
            }
        }

        return targetNode;
    }

public:
    // GFG Signature
    int sum_at_k(Node* root, int target, int k) {
        if (!root) return 0;

        // Step 1: Map parent nodes and find target node pointer
        unordered_map<Node*, Node*> parentMap;
        Node* targetNode = mapParentsAndFindTarget(root, target, parentMap);

        if (!targetNode) return 0; // Target node not found

        // Step 2: BFS from target node up to distance k
        queue<Node*> q;
        unordered_map<Node*, bool> visited;

        q.push(targetNode);
        visited[targetNode] = true;

        int totalSum = 0;
        int currDist = 0;

        while (!q.empty() && currDist <= k) {
            int sz = q.size();

            for (int i = 0; i < sz; i++) {
                Node* curr = q.front();
                q.pop();

                // Add current node's data to total sum
                totalSum += curr->data;

                // Push unvisited left child
                if (curr->left && !visited[curr->left]) {
                    visited[curr->left] = true;
                    q.push(curr->left);
                }

                // Push unvisited right child
                if (curr->right && !visited[curr->right]) {
                    visited[curr->right] = true;
                    q.push(curr->right);
                }

                // Push unvisited parent node
                Node* parentNode = parentMap[curr];
                if (parentNode && !visited[parentNode]) {
                    visited[parentNode] = true;
                    q.push(parentNode);
                }
            }

            currDist++;
        }

        return totalSum;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //            1
    //          /   \
    //         2     3
    //        /     / \
    //       4     5   7
    // target = 3, k = 1  --> Expected Output: 16 (3 + 5 + 7 + 1)
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->right->left = new Node(5);
    root1->right->right = new Node(7);

    cout << "Example 1 Sum at dist k=1 from target=3: " << ob.sum_at_k(root1, 3, 1) << "\n";

    // Example 2:
    // target = 3, k = 2  --> Expected Output: 22 (16 + 2 (from 1->2))
    cout << "Example 2 Sum at dist k=2 from target=3: " << ob.sum_at_k(root1, 3, 2) << "\n";

    return 0;
}
