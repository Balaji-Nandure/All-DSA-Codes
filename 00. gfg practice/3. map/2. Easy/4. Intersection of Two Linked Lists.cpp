/*
Problem: Intersection of Two Linked Lists

Given two linked lists head1 and head2, find the intersection of two linked lists. Each of the two linked lists contains distinct node values.
Note: The order of nodes in this list should be the same as the order in which those particular nodes appear in input head1 and return null if no common element is present.

Constraints:
1 <= no. of nodes in head1, head2 <= 10^4
1 <= node->data <= 10^5

--------------------------------------------------

Pattern:
Hash Set + Linked List Traversal

--------------------------------------------------

Key Observation:
- We need to find elements that exist in both linked lists.
- Since the order in the output must match the exact order in `head1`, we must process `head1` chronologically to build our answer.
- To quickly check if an element from `head1` exists in `head2`, we can pre-store all elements of `head2` in a hash set. This provides O(1) average lookup time.

--------------------------------------------------

Approach:
1. Initialize an `unordered_set<int> elements` to store the node values of `head2`.
2. Traverse `head2` from start to end and insert every node's data into the set.
3. Create a `dummy` node to cleanly construct the resultant intersected linked list. Maintain a `tail` pointer to append matching nodes.
4. Traverse `head1` from start to end:
    a. Check if the current node's data exists in our hash set.
    b. If it does, create a new node with this data, append it to `tail->next`, and advance `tail`.
5. Return the actual head of the intersected list, which is `dummy->next`. (Don't forget to delete the dummy node to avoid memory leaks).

--------------------------------------------------

Time Complexity: O(N + M) where N and M are the sizes of the two linked lists. We traverse both lists once and set operations take O(1) on average.
Space Complexity: O(M) to store the elements of `head2` in the hash set.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/intersection-of-two-linked-list/1
*/

#include <iostream>
#include <unordered_set>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Solution {
public:
    Node* findIntersection(Node* head1, Node* head2) {
        unordered_set<int> elements;
        Node* curr = head2;
        
        // Store all elements of the second list in a hash set
        while (curr != nullptr) {
            elements.insert(curr->data);
            curr = curr->next;
        }
        
        Node* dummy = new Node(0);
        Node* tail = dummy;
        
        curr = head1;
        // Traverse the first list and preserve order
        while (curr != nullptr) {
            if (elements.find(curr->data) != elements.end()) {
                tail->next = new Node(curr->data);
                tail = tail->next;
            }
            curr = curr->next;
        }
        
        Node* ans = dummy->next;
        delete dummy; // Free the dummy node memory
        
        return ans;
    }
};
