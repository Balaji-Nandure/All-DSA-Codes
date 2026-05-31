/*
GeeksforGeeks: Array to Linked List
Difficulty: Easy

Problem:
You are given an array arr[] of integers. You have to construct a singly linked list from the elements of the arr[] and return the head of the linked list.

Example 1:
Input: arr[] = [1, 2, 3, 4, 5]
Output: 1 -> 2 -> 3 -> 4 -> 5 
Explanation: Linked list for the given array will be 1->2->3->4->5.

Example 2:
Input: arr[] = [10, 11, 12, 13, 14]
Output: 10 -> 11 -> 12 -> 13 -> 14
Explanation: Linked list for the given array will be 10->11->12->13->14.

Core Idea:
To convert an array into a linked list, we first create the head node using the first element of the array. Then, we use a pointer (say `curr`) to keep track of the last node in the linked list we have built so far. We iterate through the remaining elements of the array, creating a new node for each element, appending it to `curr->next`, and then moving `curr` to this new node.

Approach:
1. Handle the edge case: If the array is empty (though constraints say size >= 1), return NULL.
2. Initialize `head` with a new node containing `arr[0]`.
3. Initialize a pointer `curr = head`.
4. Loop through the array starting from index 1.
5. In each iteration, create a `newNode` with `arr[i]`.
6. Set `curr->next = newNode` and update `curr = newNode`.
7. Return `head`.

Time Complexity: O(N) where N is the size of the array. We visit each element exactly once.
Space Complexity: O(N) to store the newly created linked list. The auxiliary space is O(1).

GFG Link:
https://www.geeksforgeeks.org/problems/array-to-linked-list/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    int data;
    Node* next;
  
    // Default constructor
    Node() {
        data = 0;
        next = NULL;
    }
  
    // Parameterised Constructor
    Node(int data) {
        this->data = data;
        this->next = NULL;
    }
};

class Solution {
public:
    Node* constructLL(vector<int>& arr) {
        if (arr.empty()) return NULL;
        
        Node* head = new Node(arr[0]);
        Node* curr = head;
        
        for (int i = 1; i < arr.size(); i++) {
            Node* newNode = new Node(arr[i]);
            curr->next = newNode;
            curr = newNode;
        }
        
        return head;
    }
};

/*
Dry Run — Example 1:
Input: arr[] = [1, 2, 3, 4, 5]

Initial state:
arr size = 5
head = new Node(1)
curr = head

Step 1 (i = 1):
arr[1] = 2
newNode = new Node(2)
curr->next = newNode  (1 -> 2)
curr = newNode (curr points to 2)

Step 2 (i = 2):
arr[2] = 3
newNode = new Node(3)
curr->next = newNode  (2 -> 3)
curr = newNode (curr points to 3)

Step 3 (i = 3):
arr[3] = 4
newNode = new Node(4)
curr->next = newNode  (3 -> 4)
curr = newNode (curr points to 4)

Step 4 (i = 4):
arr[4] = 5
newNode = new Node(5)
curr->next = newNode  (4 -> 5)
curr = newNode (curr points to 5)

Loop terminates as i becomes 5.
Return head.

Final Linked List:
1 -> 2 -> 3 -> 4 -> 5 -> NULL
*/
