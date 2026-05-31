/*
GeeksforGeeks: Deletion at the end of a Linked List
Difficulty: Easy

Problem:
Given a Linked List, delete the tail (i.e., the last node) of the Linked List and return the new head of the modified Linked List.

Example 1:
Input: Linked List: 1 -> 2 -> 3 -> 4 -> 5
Output: 1 -> 2 -> 3 -> 4
Explanation: After deleting tail from the given linked list, we'll be left with just 1 -> 2 -> 3 -> 4.

Example 2:
Input: Linked List: 3 -> 12 -> 8
Output: 3 -> 12
Explanation: After deleting tail from the given linked list, we'll be left with just 3 -> 12.

Core Idea:
To delete the last node (tail) of a singly linked list, we need to find the second-to-last node. Once we reach it, we can disconnect the last node by setting the `next` pointer of the second-to-last node to `NULL` and then delete the detached last node. We also need to handle the edge cases where the list is empty or has only one node.

Approach:
1. If the linked list is empty (`head == NULL`), there is nothing to delete, so return `NULL`.
2. If the linked list has only one node (`head->next == NULL`), delete the head and return `NULL` because the list becomes empty.
3. For lists with more than one node, initialize a pointer `curr` to `head`.
4. Traverse the list until `curr->next->next == NULL`. This loop stops when `curr` points to the second-to-last node.
5. The node to be deleted is `curr->next`. Store it in a temporary pointer `temp`.
6. Set `curr->next = NULL` to make the second-to-last node the new tail.
7. Delete `temp` to free memory.
8. Return the original `head`.

Time Complexity: O(N) where N is the number of nodes. We traverse the list to find the second-to-last node.
Space Complexity: O(1) as we only use a few extra pointers.

GFG Link:
https://www.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1 
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
    Node* deleteTail(Node* head) {
        // Base case 1: Empty list
        if (head == NULL) {
            return NULL;
        }
        
        // Base case 2: List with only one node
        if (head->next == NULL) {
            delete head;
            return NULL;
        }
        
        // General case: List with more than one node
        Node* curr = head;
        
        // Traverse to the second-to-last node
        while (curr->next->next != NULL) {
            curr = curr->next;
        }
        
        // The last node is curr->next
        Node* tailNode = curr->next;
        
        // Disconnect the last node
        curr->next = NULL;
        
        // Free the memory
        delete tailNode;
        
        return head;
    }
};

/*
Dry Run — Example 1:
Input: Linked List: 1 -> 2 -> 3 -> 4 -> 5

Initial State:
head -> 1 -> 2 -> 3 -> 4 -> 5 -> NULL

Step 1: Check base cases
The list has more than one node, so we proceed.

Step 2: Traverse to the second-to-last node
curr = head (1)
- curr->next->next is node 3 (not NULL), move curr to 2
- curr->next->next is node 4 (not NULL), move curr to 3
- curr->next->next is node 5 (not NULL), move curr to 4
- curr->next->next is NULL (node 4's next is node 5, node 5's next is NULL).
Loop terminates.
curr points to node 4.

Step 3: Delete the tail
tailNode = curr->next (points to node 5)
curr->next = NULL (node 4 now points to NULL, making it the new tail)
delete tailNode (node 5 is deleted)

Final Output: 1 -> 2 -> 3 -> 4 -> NULL
Return: head
*/
