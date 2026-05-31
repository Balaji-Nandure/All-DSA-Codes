/*
GeeksforGeeks: Sum of Last n Nodes of a Linked List
Difficulty: Easy

Problem:
Given the head of a singly linked list and an integer n, compute the sum of the last n nodes of the linked list. If n is greater than or equal to the number of nodes in the linked list, then return total sum.

Example 1:
Input: Linked List: 5->9->6->3->4->10, n = 3
Output: 17
Explanation: The sum of the last three nodes in the linked list is 3 + 4 + 10 = 17.

Example 2:
Input: Linked List: 1->2, n = 2
Output:  3
Explanation: The sum of the last two nodes in the linked list is 2 + 1 = 3.

Core Idea:
To find the sum of the last `n` nodes, we first need to know the total length of the linked list. 
Once we have the total length (say `L`), the number of nodes we need to skip from the beginning is `L - n`.
If `n` is greater than or equal to `L`, we simply don't skip any nodes (`skip = 0`) and sum the entire list.
After skipping the required number of nodes, we traverse the rest of the list and calculate the sum.

Approach:
1. Traverse the list from `head` to calculate its total length `L`.
2. Calculate the number of nodes to skip: `skip = L - n`.
3. If `skip < 0`, set `skip = 0` (this handles the case where n >= L).
4. Re-initialize a pointer `curr = head`.
5. Move `curr` forward by `skip` steps to reach the start of the last `n` nodes.
6. Initialize `sum = 0`.
7. Traverse from `curr` to the end of the list, adding each node's `data` to `sum`.
8. Return the calculated `sum`.

Time Complexity: O(L) where L is the total number of nodes in the linked list. We traverse the list at most twice.
Space Complexity: O(1) as we only use a few variables for counting and summing.

GFG Link:
https://www.geeksforgeeks.org/problems/find-the-sum-of-last-n-nodes-of-the-linked-list/1
*/

#include <iostream>

using namespace std;

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
    int sumOfLastN_Nodes(Node* head, int n) {
        if (head == NULL) return 0;
        
        // Step 1: Find the length of the linked list
        int len = 0;
        Node* curr = head;
        while (curr != NULL) {
            len++;
            curr = curr->next;
        }
        
        // Step 2: Determine how many nodes to skip from the start
        int skip = len - n;
        if (skip < 0) {
            skip = 0;
        }
        
        // Step 3: Skip the nodes
        curr = head;
        while (skip > 0) {
            curr = curr->next;
            skip--;
        }
        
        // Step 4: Calculate the sum of the remaining nodes
        int sum = 0;
        while (curr != NULL) {
            sum += curr->data;
            curr = curr->next;
        }
        
        return sum;
    }
};

/*
Dry Run — Example 1:
Input: Linked List: 5->9->6->3->4->10, n = 3

Initial state:
head -> [5] -> [9] -> [6] -> [3] -> [4] -> [10] -> NULL
n = 3

Step 1 (Find Length):
- Traverse from head to NULL.
- len becomes 6.

Step 2 (Determine Skip):
- skip = len - n = 6 - 3 = 3.

Step 3 (Skip nodes):
- curr = head (points to 5)
- skip = 3. `curr = curr->next` (points to 9), `skip = 2`
- skip = 2. `curr = curr->next` (points to 6), `skip = 1`
- skip = 1. `curr = curr->next` (points to 3), `skip = 0`
- Loop terminates. `curr` is now pointing to 3.

Step 4 (Calculate Sum):
- sum = 0
- curr points to 3. sum += 3 (sum = 3). curr = curr->next.
- curr points to 4. sum += 4 (sum = 7). curr = curr->next.
- curr points to 10. sum += 10 (sum = 17). curr = curr->next.
- curr is NULL. Loop terminates.

Final Output: 17
*/
