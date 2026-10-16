/**
 * Problem: Clone an Undirected Graph
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In cloning a linked list or binary tree, the structure is acyclic and branching is strictly hierarchical.
 * - In an arbitrary undirected graph, cycles exist and multiple nodes can point to the same neighbor.
 * - Without cycle tracking, a naive deep copy will enter an infinite loop creating duplicate nodes indefinitely.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Hash Map + DFS / BFS Deep Copy:
 *   - Maintain an `unordered_map<Node*, Node*> visited` that records `originalNode -> clonedNode`.
 *   - When visiting a node:
 *     1. If already in map, return the existing cloned reference.
 *     2. If not, instantiate a new `Node(originalNode->val)` and store in map BEFORE recursing on neighbors.
 *     3. Iterate through `neighbors` of the original node, recursively clone each, and append to the clone's `neighbors`.
 * 
 * TIME COMPLEXITY:
 * - O(V + E): Each vertex and edge is visited exactly once.
 * 
 * SPACE COMPLEXITY:
 * - O(V): For the hash map and call stack / BFS queue.
 */

#include <iostream>
#include <vector>
#include <unordered_map>

class Node {
public:
    int val;
    std::vector<Node*> neighbors;
    Node() : val(0), neighbors() {}
    Node(int _val) : val(_val), neighbors() {}
    Node(int _val, std::vector<Node*> _neighbors) : val(_val), neighbors(_neighbors) {}
};

class Solution {
    std::unordered_map<Node*, Node*> cloneMap;

public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        // If the node has already been copied, return the existing cloned instance
        if (cloneMap.find(node) != cloneMap.end()) {
            return cloneMap[node];
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Map the original node to the clone BEFORE traversing neighbors to prevent infinite recursion on cycles.
        Node* clone = new Node(node->val);
        cloneMap[node] = clone;

        for (Node* neighbor : node->neighbors) {
            clone->neighbors.push_back(cloneGraph(neighbor));
        }

        return clone;
    }
};

int main() {
    // Construct sample graph: 1 -- 2, 2 -- 3, 3 -- 4, 4 -- 1
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);

    n1->neighbors = {n2, n4};
    n2->neighbors = {n1, n3};
    n3->neighbors = {n2, n4};
    n4->neighbors = {n1, n3};

    Solution sol;
    Node* cloned = sol.cloneGraph(n1);

    std::cout << "Original Node 1 address: " << n1 << ", Cloned Node 1 address: " << cloned << "\n";
    std::cout << "Cloned Node 1 val: " << cloned->val << "\n";
    std::cout << "Cloned Node 1 neighbor count: " << cloned->neighbors.size() << "\n";

    return 0;
}
