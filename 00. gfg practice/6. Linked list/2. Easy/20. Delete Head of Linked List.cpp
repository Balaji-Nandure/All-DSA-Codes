/*
GeeksforGeeks: Delete Head of Linked List
Difficulty: Easy

Problem:
Given a Linked List, delete the head of the Linked List and return the new head of the modified Linked List.
Note: Set the original head to NULL.

Example 1:
Input: Linked List: 1 -> 2 -> 3 -> 1 -> 7
Output: 2 -> 3 -> 1 -> 7
Explanation: After deleting head from the given linked list, we'll be left with just 2 -> 3 -> 1 -> 7.

Example 2:
Input: Linked List: 4 -> 5 -> 7 -> 8 -> 99 -> 100
Output: 5 -> 7 -> 8 -> 99 -> 100
Explanation: After deleting head from the given linked list, we'll be left with just 5 -> 7 -> 8 -> 99 -> 100.

Core Idea:
To delete the head of a singly linked list, we just need to make the second node the new head of the list. We keep a reference to the original head, update the head pointer to `head->next`, and then safely delete the original head to prevent memory leaks.

Approach:
1. If the linked list is empty (`head == NULL`), return `NULL`.
2. Store the current `head` in a temporary pointer `temp`.
3. Update the `head` pointer to point to the next node (`head = head->next`).
4. Delete the `temp` node to free up memory (as per C++ best practices).
5. Return the new `head`.

Time Complexity: O(1) as we only change a few pointers and delete one node.
Space Complexity: O(1) since no extra space is used.

GFG Link:
https://www.geeksforgeeks.org/problems/delete-head-of-linked-list/1
*/

#include <iostream>

using namespace std;

struct Node {
    int data;
    struct Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
public:
    Node* deleteHead(Node* head) {
        // Base case: If the list is empty
        if (head == NULL) {
            return NULL;
        }
        
        // Store the original head
        Node* temp = head;
        
        // Update head to the next node
        head = head->next;
        
        // Free the memory of the original head
        delete temp;
        
        return head;
    }
};

/*
Dry Run — Example 1:
Input: Linked List: 1 -> 2 -> 3 -> 1 -> 7

Initial State:
head -> 1 -> 2 -> 3 -> 1 -> 7 -> NULL

Step 1: Base case check
head is not NULL, so we proceed.

Step 2: Store original head
temp = head (points to node with data 1)

Step 3: Update head
head = head->next (points to node with data 2)
List state:
temp -> 1 -> 2
head -> 2 -> 3 -> 1 -> 7 -> NULL

Step 4: Delete original head
delete temp (node with data 1 is removed from memory)

Step 5: Return new head
Return head (points to node with data 2)

Final Output: 2 -> 3 -> 1 -> 7
*/
