/*
GeeksforGeeks: Reverse Two Parts of Linked List
Difficulty: Easy

Problem:
Given the head of a linked list and an integer k, reverse the first k nodes and separately reverse the remaining n - k nodes of the linked list.

Example 1:
Input: head: 1 -> 2 -> 3 -> 4 -> 5,  k = 2
Output: 2 -> 1 -> 5 -> 4 -> 3
Explanation: Since k = 2, split the linked list into two parts:
First part: 1 -> 2
Second part: 3 -> 4 -> 5
Reversed first part: 2 -> 1
Reversed second part: 5 -> 4 -> 3
Finally, connect the reversed parts to obtain: 2 -> 1 -> 5 -> 4 -> 3

Example 2:
Input: head: 1 -> 2 -> 4 -> 3,  k = 3
Output: 4 -> 2 -> 1 -> 3
Explanation: Since k = 3, split the linked list into two parts:
First part: 1 -> 2 -> 4
Second part: 3
Reversed first part: 4 -> 2 -> 1
Reversed second part: 3
Finally, connect the reversed parts to obtain: 4 -> 2 -> 1 -> 3

Core Idea:
The problem asks us to reverse the linked list in two specific segments: the first `k` nodes, and the rest. 
We can solve this by splitting the linked list into two separate lists at the `k`-th node. 
Then, we reverse both linked lists independently. 
Finally, we link the tail of the reversed first part (which was originally the head) to the head of the reversed second part.

Approach:
1. Traverse the list to find the `k`-th node.
2. Store the `(k+1)`-th node as the head of the second part (`second_part_head`).
3. Set the `next` pointer of the `k`-th node to `NULL` to disconnect the two parts.
4. Reverse the first part of the list using a standard reverse function. Keep track of the new head.
5. Reverse the second part of the list. Keep track of the new head of the second part.
6. Connect the two parts: The original head of the first part is now its tail. Set its `next` to the new head of the reversed second part.
7. Return the new head of the reversed first part.

Time Complexity: O(N) where N is the number of nodes in the linked list. We traverse the list to split it, and then traverse it again to reverse both parts.
Space Complexity: O(1) since we only use a few extra pointers.

GFG Link:
https://www.geeksforgeeks.org/problems/reverse-two-parts-of-linked-list/1
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
private:
    Node* reverseList(Node* head) {
        Node* prev = NULL;
        Node* curr = head;
        while (curr != NULL) {
            Node* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
    }

public:
    Node* reverseTwoParts(Node* head, int k) {
        if (!head || !head->next || k <= 0) {
            return head;
        }

        Node* curr = head;
        int count = 1;
        
        // Traverse to the k-th node
        while (curr != NULL && count < k) {
            curr = curr->next;
            count++;
        }
        
        // If k is greater than or equal to the size of the list, 
        // the second part is empty, and we just reverse the whole list.
        // However, constraints say 1 <= k < size of linked list.
        if (curr == NULL || curr->next == NULL) {
            return reverseList(head);
        }

        Node* first_part_head = head;
        Node* second_part_head = curr->next;
        
        // Split the list
        curr->next = NULL;

        // Reverse both parts
        Node* new_first_head = reverseList(first_part_head);
        Node* new_second_head = reverseList(second_part_head);

        // Connect the reversed parts
        // first_part_head is now the tail of the first reversed part
        first_part_head->next = new_second_head;

        return new_first_head;
    }
};

/*
Dry Run — Example 1:
Input: head: 1 -> 2 -> 3 -> 4 -> 5,  k = 2

Initial State:
1 -> 2 -> 3 -> 4 -> 5

Step 1: Traverse to k-th node
count = 1, curr = 1
curr = curr->next (2), count = 2
Loop ends as count is not < k.
curr is now at node 2.

Step 2: Split the list
first_part_head = 1
second_part_head = 3 (curr->next)
curr->next = NULL (node 2's next is NULL)

First part: 1 -> 2 -> NULL
Second part: 3 -> 4 -> 5 -> NULL

Step 3: Reverse the first part
new_first_head = reverseList(1 -> 2)
new_first_head is 2 -> 1 -> NULL

Step 4: Reverse the second part
new_second_head = reverseList(3 -> 4 -> 5)
new_second_head is 5 -> 4 -> 3 -> NULL

Step 5: Connect the two parts
The original first_part_head was 1, which is now the tail of the reversed first part.
first_part_head->next = new_second_head
node 1's next points to node 5.

Final List: 2 -> 1 -> 5 -> 4 -> 3 -> NULL
Return: new_first_head (2)
*/
