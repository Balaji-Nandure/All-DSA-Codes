/*
GeeksforGeeks: Pairwise swap elements of a linked list
Difficulty: Easy

Problem:
Given a singly linked list. The task is to swap elements in the linked list pairwise. 
For example, if the input list is 1 2 3 4, the resulting list after swaps will be 2 1 4 3.
Note: You need to swap the nodes, not only the data. If only data is swapped then the driver code will print -1.

Example 1:
Input: LinkedList: 1->2->2->4->5->6->7->8
Output: 2->1->4->2->6->5->8->7
Explanation: After swapping each pair considering (1,2), (2, 4), (5, 6).. so on as pairs, we get 2, 1, 4, 2, 6, 5, 8, 7 as a new linked list.

Example 2:
Input: LinkedList: 1->3->4->7->9->10->1
Output: 3->1->7->4->10->9->1
Explanation: After swapping each pair considering (1,3), (4, 7), (9, 10).. so on as pairs, we get 3, 1, 7, 4, 10, 9, 1 as a new linked list.

Core Idea:
To pairwise swap nodes in a linked list, we need to iterate through the list and at each step, grab a pair of nodes. 
We then adjust the pointers to swap them. Since the `head` will change (the second node becomes the new head), 
it's easier to use a `dummy` node that points to the head. This helps in uniformly handling the first pair and subsequent pairs without special cases.

Approach:
1. If the list is empty or has only one node, return the `head` as no swap is needed.
2. Create a `dummy` node and set `dummy->next = head`.
3. Use a `prev` pointer initialized to `dummy` and a `curr` pointer initialized to `head`.
4. Loop while `curr` and `curr->next` are not NULL:
   a. Identify the two nodes to be swapped: `first = curr`, `second = curr->next`.
   b. Identify the start of the next pair: `nextPair = curr->next->next`.
   c. Adjust pointers to swap: 
      - `prev->next = second` (prev node points to the second node)
      - `second->next = first` (second node points to the first node)
      - `first->next = nextPair` (first node points to the first node of the next pair)
   d. Update `prev` to `first` and `curr` to `nextPair` for the next iteration.
5. Return the new head which is `dummy->next`, and delete the `dummy` node to avoid memory leaks.

Time Complexity: O(N) where N is the number of nodes in the linked list. We traverse the list exactly once.
Space Complexity: O(1) as we only use a few extra pointers for the manipulation.

GFG Link:
https://www.geeksforgeeks.org/problems/pairwise-swap-elements-of-a-linked-list-by-swapping-data/1
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
    Node* pairWiseSwap(Node* head) {
        if (!head || !head->next) {
            return head;
        }

        Node* dummy = new Node(0);
        dummy->next = head;
        Node* prev = dummy;
        Node* curr = head;

        while (curr != NULL && curr->next != NULL) {
            Node* second = curr->next;
            Node* nextPair = curr->next->next;

            // Swapping the nodes
            prev->next = second;
            second->next = curr;
            curr->next = nextPair;

            // Updating pointers for the next pair
            prev = curr;
            curr = nextPair;
        }

        Node* newHead = dummy->next;
        delete dummy;
        return newHead;
    }
};

/*
Dry Run — Example 1:
Input: LinkedList: 1->2->2->4->5->6->7->8

Initial state:
dummy -> 1 -> 2 -> 2 -> 4 -> 5 -> 6 -> 7 -> 8
prev = dummy
curr = 1

Iteration 1:
second = 2 (first occurrence), nextPair = 2 (second occurrence)
Swap:
prev->next = 2
second->next = 1
1->next = 2
List becomes: dummy -> 2 -> 1 -> 2 -> 4 -> ...
prev = 1
curr = 2 (second occurrence)

Iteration 2:
curr = 2, second = 4, nextPair = 5
Swap:
prev->next = 4
second->next = 2
2->next = 5
List becomes: dummy -> 2 -> 1 -> 4 -> 2 -> 5 -> 6 -> ...
prev = 2
curr = 5

This process continues for the remaining pairs (5,6) and (7,8).
Resulting list: 2 -> 1 -> 4 -> 2 -> 6 -> 5 -> 8 -> 7
Final Output: 2->1->4->2->6->5->8->7
*/
