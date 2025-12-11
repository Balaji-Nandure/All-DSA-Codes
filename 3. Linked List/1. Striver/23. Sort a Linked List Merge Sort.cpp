/*
 * Problem: Sort List (LeetCode 148)
 * 
 * Given the head of a linked list, return the list after sorting it in 
 * ascending order.
 * 
 * Example 1:
 * Input: head = [4,2,1,3]
 * Output: [1,2,3,4]
 * 
 * 
 */

#include <bits/stdc++.h>
using namespace std;

// Node class represents a node in the linked list
class Node {
public:
    int data;     // Data value
    Node* next;   // Pointer to next node

    // Constructor with data and next
    Node(int data, Node* next) {
        this->data = data;
        this->next = next;
    }

    // Constructor with only data
    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

// Helper function to convert array to linked list
Node* arrayToLinkedList(const vector<int>& arr) {
    if (arr.size() == 0) return nullptr;
    Node* head = new Node(arr[0]);
    Node* curr = head;
    for (int i = 1; i < arr.size(); ++i) {
        curr->next = new Node(arr[i]);
        curr = curr->next;
    }
    return head;
}

// Helper function to print linked list
void printLinkedList(Node* head) {
    Node* curr = head;
    while(curr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

// Helper function to merge two sorted linked lists
Node* mergeTwoLists(Node* list1, Node* list2) {
    Node* dummy = new Node(0);
    Node* tail = dummy;
    
    while (list1 && list2) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    
    if (list1) tail->next = list1;
    if (list2) tail->next = list2;
    
    Node* result = dummy->next;
    delete dummy;
    return result;
}

// Helper function to find the middle node of linked list
Node* findMiddle(Node* head) {
    if (!head) return nullptr;
    
    Node* slow = head;
    Node* fast = head->next;  // Start fast one step ahead to get first middle in even length
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

// ========== METHOD 1: Merge Sort (Optimal) ==========
// Time Complexity: O(n log n), Space Complexity: O(log n) for recursion stack
Node* sortList(Node* head) {
    // Base case: empty list or single node
    if (!head || !head->next) {
        return head;
    }
    
    // Step 1: Find the middle node
    Node* mid = findMiddle(head);
    Node* right = mid->next;
    mid->next = nullptr;  // Split the list
    
    // Step 2: Recursively sort both halves
    Node* left = sortList(head);
    right = sortList(right);
    
    // Step 3: Merge the sorted halves
    return mergeTwoLists(left, right);
}
