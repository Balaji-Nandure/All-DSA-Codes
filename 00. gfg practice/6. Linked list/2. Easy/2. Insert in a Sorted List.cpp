/*
GeeksforGeeks: Insert in a Sorted List
Difficulty: Easy

Problem:
Given a linked list sorted in ascending order and an integer called key, insert data in the linked list such that the list remains sorted.

Example 1:
Input: LinkedList: 25->36->47->58->69->80, key: 19
Output: 19->25->36->47->58->69->80
Explanation: After inserting 19 the sorted linked list will look like the one in the output.

Example 2:
Input: LinkedList: 50->100, key: 75
Output: 50->75->100
Explanation: After inserting 75 the sorted linked list will look like the one in the output.

Core Idea:
Since the linked list is sorted, we need to find the correct position for the `key`. We iterate through the list. We have three cases:
1. The list is empty. We just return a new node with the `key`.
2. The `key` is smaller than or equal to the head's data. We insert the new node before the head and make it the new head.
3. The `key` should be inserted somewhere in the middle or at the end. We traverse the list with a pointer `curr`. As long as `curr->next` is not NULL and `curr->next->data < key`, we move `curr = curr->next`. We then insert the new node after `curr`.

Approach:
1. Create a `newNode` with data `key`.
2. Check if `head == NULL` or `head->data >= key`. If so, set `newNode->next = head` and return `newNode` as the new head.
3. Initialize `curr = head`.
4. While `curr->next != NULL` and `curr->next->data < key`, update `curr = curr->next`.
5. Set `newNode->next = curr->next`.
6. Set `curr->next = newNode`.
7. Return `head`.

Time Complexity: O(N) where N is the number of nodes. We might need to traverse the entire list in the worst case.
Space Complexity: O(1) as we only use a few pointers.

GFG Link:
https://www.geeksforgeeks.org/problems/insert-in-a-sorted-list/1
*/

#include <iostream>

using namespace std;

/*
Structure of the linked list node is as
*/
struct Node {
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
public:
    // Should return head of the modified linked list
    Node* sortedInsert(Node* head, int key) {
        Node* newNode = new Node(key);
        
        // Case 1: Empty list or key is smaller than head's data
        if (head == NULL || head->data >= key) {
            newNode->next = head;
            return newNode;
        }
        
        // Case 2: Insert somewhere in the middle or at the end
        Node* curr = head;
        while (curr->next != NULL && curr->next->data < key) {
            curr = curr->next;
        }
        
        newNode->next = curr->next;
        curr->next = newNode;
        
        return head;
    }
};

/*
Dry Run — Example 1:
Input: LinkedList: 25->36->47->58->69->80, key: 19

Initial state:
head -> [25] -> [36] -> [47] -> [58] -> [69] -> [80] -> NULL
key = 19

Step 1:
newNode = new Node(19)
head->data (25) >= key (19) is TRUE.

Step 2:
newNode->next = head
newNode->next points to [25]
return newNode

Final Output Linked List:
[19] -> [25] -> [36] -> [47] -> [58] -> [69] -> [80] -> NULL

Dry Run — Example 2:
Input: LinkedList: 50->100, key: 75

Initial state:
head -> [50] -> [100] -> NULL
key = 75

Step 1:
newNode = new Node(75)
head->data (50) >= key (75) is FALSE.

Step 2:
curr = head (points to [50])
Loop condition: curr->next != NULL (TRUE) && curr->next->data (100) < key (75) (FALSE)
Loop terminates immediately.

Step 3:
newNode->next = curr->next; (newNode->next points to [100])
curr->next = newNode; (curr->next points to [75])

Final Output Linked List:
[50] -> [75] -> [100] -> NULL
*/
