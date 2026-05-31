/*
GeeksforGeeks: Size of Doubly Linked List
Difficulty: Easy

Problem:
Given a doubly linked list. The task is to find the number of nodes in the doubly linked list.

Example 1:
Input:  1 <-> 2 <-> 3 <-> 4
Output: 4
Explanation: The size of the linked list is 4 which is the number of nodes in it.

Example 2:
Input:  1 <-> 2
Output: 2
Explanation: The size of the linked list is 2 which is the number of nodes in it.

Core Idea:
Finding the size of a Doubly Linked List is essentially the same as finding the size of a Singly Linked List. We simply need to traverse the list from the head node to the end, counting the number of nodes we encounter along the way by following the `next` pointers.

Approach:
1. Initialize a variable `count` to 0.
2. Initialize a pointer `curr` pointing to the `head` of the list.
3. Use a `while` loop that runs as long as `curr` is not `NULL`.
4. Inside the loop, increment the `count` by 1.
5. Move `curr` to the next node by setting `curr = curr->next`.
6. Once the loop finishes (meaning we've reached the end of the list), return the `count`.

Time Complexity: O(N) where N is the number of nodes in the doubly linked list, as we must traverse the entire list.
Space Complexity: O(1) since we only use a counter and a single pointer.

GFG Link:
https://www.geeksforgeeks.org/problems/find-the-size-of-doubly-linked-list/1
*/

#include <iostream>

using namespace std;

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;

    Node(int x) {
        data = x;
        next = NULL;
        prev = NULL;
    }
};

class Solution {
public:
    int findLength(Node* head) {
        int count = 0;
        Node* curr = head;

        // Traverse the doubly linked list
        while (curr != NULL) {
            count++;
            curr = curr->next;
        }

        return count;
    }
};

/*
Dry Run — Example 1:
Input: 1 <-> 2 <-> 3 <-> 4

Initial State:
head -> 1 <-> 2 <-> 3 <-> 4 -> NULL
count = 0
curr = head (points to node with data 1)

Iteration 1:
curr != NULL (curr is node 1)
count++ (count becomes 1)
curr = curr->next (curr becomes node 2)

Iteration 2:
curr != NULL (curr is node 2)
count++ (count becomes 2)
curr = curr->next (curr becomes node 3)

Iteration 3:
curr != NULL (curr is node 3)
count++ (count becomes 3)
curr = curr->next (curr becomes node 4)

Iteration 4:
curr != NULL (curr is node 4)
count++ (count becomes 4)
curr = curr->next (curr becomes NULL)

Iteration 5:
curr != NULL is False (curr is NULL)
Loop terminates.

Return count (which is 4)

Final Output: 4
*/
