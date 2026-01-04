/*
Problem:
Clone a Linked List with Random Pointer

Each node of a linked list contains:
- data
- next pointer
- random pointer (can point to any node or NULL)

Create a DEEP COPY of the list:
- New nodes must be created
- next and random pointers must mirror the original list
- Original list must remain unchanged

Examples:
Input:
1 -> 2 -> 3
randoms: 1->3, 2->1, 3->2

Output:
Cloned list with identical next & random structure


-----------------------------------
Approach (Expected / Optimal – O(1) Extra Space, 3-Pass Method):
-----------------------------------
This is the STANDARD and BEST solution.

Step 1: Insert cloned nodes in between original nodes
Original:  A -> B -> C
After step: A -> A' -> B -> B' -> C -> C'

Step 2: Set random pointers of cloned nodes
If original A.random = X
Then A'.random = X->next   (because X->next is X')

Step 3: Separate original and cloned lists
Restore original list and extract cloned list

Why this works:
- No extra hash map needed
- Original structure is temporarily used
- Clean O(1) auxiliary space solution

Time Complexity:
O(n)

Space Complexity:
O(1) auxiliary
(output list space not counted)


GeeksforGeeks:
https://www.geeksforgeeks.org/clone-linked-list-next-random-pointer/

LeetCode:
https://leetcode.com/problems/copy-list-with-random-pointer/
*/


// Definition for node with random pointer
struct Node {
    int data;
    Node* next;
    Node* random;

    Node(int x) {
        data = x;
        next = NULL;
        random = NULL;
    }
};

// approach 1; // Optimal
Node* cloneLinkedList(Node* head) {

    if (head == NULL) return NULL;

    Node* curr = head;

    // -------------------------------
    // Step 1: Insert cloned nodes
    // -------------------------------
    while (curr != NULL) {
        Node* clone = new Node(curr->data);
        clone->next = curr->next;
        curr->next = clone;
        curr = clone->next;
    }

    // -------------------------------
    // Step 2: Set random pointers
    // -------------------------------
    curr = head;
    while (curr != NULL) {
        if (curr->random != NULL) {
            curr->next->random = curr->random->next;
        }
        curr = curr->next->next;
    }

    // -------------------------------
    // Step 3: Separate the lists
    // -------------------------------
    curr = head;
    Node* cloneHead = head->next;

    while (curr != NULL) {
        Node* clone = curr->next;
        curr->next = clone->next;

        if (clone->next != NULL) {
            clone->next = clone->next->next;
        }

        curr = curr->next;
    }

    return cloneHead;
}


// Approach 2: Using hashmap to maintain old node -> new node mapping
Node* copyRandomList(Node* head) {
    // If the original list is empty, return NULL.
    if(!head) return NULL;
    unordered_map<Node *, Node *> mp; // Map from original node to its clone
    Node *curr = head;
    // First pass: Create cloned nodes and store them in the map.
    while(curr){
        mp[curr] = new Node(curr->val); // Create a new copy for each node.
        curr = curr->next;
    }
    curr = head;
    // Second pass: Assign next and random pointers to the cloned nodes.
    while(curr){
        mp[curr]->next = mp[curr->next];       // Set the 'next' pointer.
        mp[curr]->random = mp[curr->random];   // Set the 'random' pointer.
        curr = curr->next;
    }
    // Return the head of the cloned list
    return mp[head];
}