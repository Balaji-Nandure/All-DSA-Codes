/*
Problem:
Partitioning a Linked List Around a Given Value (Stable Order)

Given the head of a singly linked list and an integer x,
rearrange the list such that:
1. All nodes with value < x come first
2. Then all nodes with value == x
3. Finally all nodes with value > x

Important:
- The ORIGINAL RELATIVE ORDER of nodes in each partition
  must be preserved (stable partition).
- Do NOT change node values, only rearrange links.

Examples:
Input  : 1 -> 4 -> 3 -> 2 -> 5 -> 2 -> 3,  x = 3
Output : 1 -> 2 -> 2 -> 3 -> 3 -> 4 -> 5

Input  : 10 -> 4 -> 20 -> 10 -> 3,  x = 3
Output : 3 -> 10 -> 4 -> 20 -> 10


-----------------------------------
Approach (Expected / Optimal – Three Dummy Lists):
-----------------------------------
1. Create three dummy lists to preserve order:
   - less    → nodes with value < x
   - equal   → nodes with value == x
   - greater → nodes with value > x
2. Traverse the original list once:
   - Append each node to the appropriate list
3. Connect the three lists in order:
   less → equal → greater
4. Ensure last node points to NULL.
5. Return the new head.

Why this works:
- Each list preserves original order by appending at the tail.
- No extra traversal required.
- No data modification, only pointer reassignment.

Time Complexity:
O(n)

Space Complexity:
O(1) extra space
(only constant dummy nodes; nodes are reused)


GeeksforGeeks:
https://www.geeksforgeeks.org/partitioning-a-linked-list-around-a-given-value/

LeetCode:
https://leetcode.com/problems/partition-list/
*/


// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};


Node* partition(Node* head, int x) {
    // Dummy head for nodes less than x
    Node* lessHead = new Node(0); 
    
    // Dummy head for nodes equal to x
    Node* equalHead = new Node(0); 
    
    // Dummy head for nodes greater than or equal to x
    Node* greaterHead = new Node(0);

    Node* less = lessHead;
    Node* equal = equalHead;
    Node* greater = greaterHead;

    Node* curr = head;

    while (curr != NULL) {
        if (curr->data < x) {
            less->next = curr;
            less = less->next;
        } else if (curr->data == x) {
            equal->next = curr;
            equal = equal->next;
        } else {
            greater->next = curr;
            greater = greater->next;
        }
        curr = curr->next;
    }

    // Connect the partitions together
    greater->next = NULL;  
    
    // Connect equal to greater
    equal->next = greaterHead->next; 
    
    // Connect less to equal
    less->next = equalHead->next;  
    
    // New head of the rearranged list
    Node* newHead = lessHead->next; 

    // Clean up dummy nodes
    delete lessHead;
    delete equalHead;
    delete greaterHead;

    return newHead;
}