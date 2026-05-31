/*
GeeksforGeeks: Join Two Linked Lists
Difficulty: Easy

Problem:
Given heads of two singly linked lists, head1 and head2. Append the second list to the end of the first list. After performing this operation, return head of the new list.

Example 1:
Input: head1: 1 -> 2 -> 3, head2: 4 -> 5
Output: 1 -> 2 -> 3 -> 4 -> 5
Explanation: After joining both lists we get 1 -> 2 -> 3 -> 4 -> 5

Core Idea:
To join two linked lists, we need to find the tail (the last node) of the first linked list and point its `next` pointer to the head of the second linked list. 

Approach:
1. If the first linked list is empty (`head1 == NULL`), simply return `head2` as the joined list.
2. Similarly, if `head2 == NULL`, return `head1`.
3. Traverse the first linked list starting from `head1` until you reach the last node (where `curr->next == NULL`).
4. Set the `next` pointer of this last node to `head2`.
5. Return the original `head1` as the new head of the joined list.

Time Complexity: O(N) where N is the number of nodes in the first linked list, as we must traverse it to find its tail.
Space Complexity: O(1) as we only use a single pointer for traversal.

GFG Link:
https://www.geeksforgeeks.org/problems/join-two-linked-lists/1
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
    Node* joinTheLists(Node* head1, Node* head2) {
        // If the first list is empty, the result is the second list
        if (head1 == NULL) {
            return head2;
        }

        // If the second list is empty, the result is the first list
        if (head2 == NULL) {
            return head1;
        }

        Node* curr = head1;

        // Traverse to the last node of the first list
        while (curr->next != NULL) {
            curr = curr->next;
        }

        // Append the second list to the end of the first list
        curr->next = head2;

        return head1;
    }
};

/*
Dry Run — Example 1:
Input: head1: 1 -> 2 -> 3, head2: 4 -> 5

Initial State:
head1 -> 1 -> 2 -> 3 -> NULL
head2 -> 4 -> 5 -> NULL

Step 1: Check base cases
Both head1 and head2 are not NULL. Proceed.

Step 2: Traverse head1 to find its tail
curr = head1 (points to 1)
curr->next (2) is not NULL, move curr to 2
curr->next (3) is not NULL, move curr to 3
curr->next is NULL, loop terminates.
curr now points to node 3 (the tail of the first list).

Step 3: Join the lists
curr->next = head2
node 3's next now points to node 4.
The lists are now linked: 1 -> 2 -> 3 -> 4 -> 5 -> NULL

Final Output: 1 -> 2 -> 3 -> 4 -> 5
Return: head1
*/
