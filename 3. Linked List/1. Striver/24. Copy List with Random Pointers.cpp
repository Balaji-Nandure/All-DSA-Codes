/*
 * Problem: Copy List with Random Pointer (LeetCode 138)
 * 
 * A linked list of length n is given such that each node contains an additional 
 * random pointer, which could point to any node in the list, or null.
 * 
 * Construct a deep copy of the list. The deep copy should consist of exactly n 
 * brand new nodes, where each new node has its value set to the value of its 
 * corresponding original node. Both the next and random pointer of the new nodes 
 * should point to new nodes in the copied list such that the pointers in the 
 * original list and copied list represent the same list state. None of the 
 * pointers in the new list should point to nodes in the original list.
 * 
 * Example 1:
 * Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
 * Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
 * 
 * Constraints:
 * - 0 <= n <= 1000
 * - -10^4 <= Node.val <= 10^4
 * - Node.random is null or is pointing to some node in the linked list
 */

#include <bits/stdc++.h>
using namespace std;

// Node class represents a node in the linked list with random pointer
class Node {
public:
    int val;           // Data value
    Node* next;        // Pointer to next node
    Node* random;      // Pointer to random node

    // Constructor
    Node(int val) {
        this->val = val;
        this->next = nullptr;
        this->random = nullptr;
    }
};

/*
 * Problem: Copy List with Random Pointer
 *
 * LeetCode 138: Copy List with Random Pointer
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/clone-a-linked-list-with-next-and-random-pointer/1
 *
 * Create a deep copy of linked list with random pointers.
 * Each node has next and random pointers that need to be copied.
 *
 * Time: O(n) - two passes
 * Space: O(n) for hashmap, O(1) for interleaving method
 */

// Method 1: Using HashMap (Optimal for clarity)
Node* copyRandomList(Node* head) {
    if (!head) return nullptr;
    
    // Map original nodes to their copies
    unordered_map<Node*, Node*> nodeMap;
    
    // First pass: Create all new nodes and map original to copy
    Node* curr = head;
    while (curr) {
        nodeMap[curr] = new Node(curr->val);
        curr = curr->next;
    }
    
    // Second pass: Set next and random pointers using the map
    curr = head;
    while (curr) {
        Node* copy = nodeMap[curr];
        
        // Set next pointer (map original->next to copy->next)
        if (curr->next) {
            copy->next = nodeMap[curr->next];
        }
        
        // Set random pointer (map original->random to copy->random)
        if (curr->random) {
            copy->random = nodeMap[curr->random];
        }
        
        curr = curr->next;
    }
    
    return nodeMap[head]; // Return head of copied list
}

// Method 2: Interleaving Nodes (Optimal Space - O(1))
// Insert copy nodes between original nodes, set pointers, then separate
Node* copyRandomListInterleaving(Node* head) {
    if (!head) return nullptr;
    
    // Step 1: Create interleaved list: original -> copy -> original -> copy ...
    Node* curr = head;
    while (curr) {
        Node* copy = new Node(curr->val);
        copy->next = curr->next; // Copy points to next original
        curr->next = copy; // Original points to copy
        curr = copy->next; // Move to next original
    }
    
    // Step 2: Set random pointers for copies
    // copy->random = original->random->next (the copy of original->random)
    curr = head;
    while (curr) {
        if (curr->random) {
            curr->next->random = curr->random->next; // Copy's random = copy of original's random
        }
        curr = curr->next->next; // Skip copy, move to next original
    }
    
    // Step 3: Separate original and copy lists
    Node* original = head;
    Node* copyHead = head->next; // Save head of copy list
    Node* copy = copyHead;
    
    while (original) {
        original->next = original->next->next; // Restore original links
        if (copy->next) {
            copy->next = copy->next->next; // Connect copy links
        }
        original = original->next;
        copy = copy->next;
    }
    
    return copyHead;
}
