/*
 * Problem: Sort a Linked List of 0's, 1's and 2's
 * 
 * Given a linked list of N nodes where nodes can contain values 0s, 1s, and 2s only.
 * The task is to segregate 0s, 1s, and 2s linked list such that all zeros segregate 
 * to head side, 2s at the end of the linked list, and 1s in the middle of 0s and 2s.
 * 
 * This is similar to the Dutch National Flag problem but for linked lists.
 * 
 * Example 1:
 * Input: head = [1,2,2,1,2,0,2,2]
 * Output: [0,1,1,2,2,2,2,2]
 * 
 * Example 2:
 * Input: head = [2,2,0,1]
 * Output: [0,1,2,2]
 * 
 * Constraints:
 * - 1 <= N <= 10^5
 * - Node->data can only be 0, 1, or 2
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

// Method 1: Using separate lists for 0s, 1s, and 2s (Most Efficient)
// Time Complexity: O(n), Space Complexity: O(1)
Node* segregate012(Node* head) {
    if (!head || !head->next) return head;
    
    // Create dummy nodes for three lists
    Node* zeroHead = new Node(-1);
    Node* oneHead = new Node(-1);
    Node* twoHead = new Node(-1);
    
    // Pointers to track the end of each list
    Node* zero = zeroHead;
    Node* one = oneHead;
    Node* two = twoHead;
    
    // Traverse the original list and separate nodes
    Node* curr = head;
    while (curr) {
        if (curr->data == 0) {
            zero->next = curr;
            zero = zero->next;
        } else if (curr->data == 1) {
            one->next = curr;
            one = one->next;
        } else { // curr->data == 2
            two->next = curr;
            two = two->next;
        }
        curr = curr->next;
    }
    
    // Connect the three lists: 0s -> 1s -> 2s
    // Connect 1s to 2s
    two->next = nullptr;
    
    // Connect 0s to 1s
    if (oneHead->next) {
        zero->next = oneHead->next;
        one->next = twoHead->next;
    } else {
        // If no 1s, connect 0s directly to 2s
        zero->next = twoHead->next;
    }
    
    // Get the new head
    Node* newHead = zeroHead->next;
    
    // Delete dummy nodes
    delete zeroHead;
    delete oneHead;
    delete twoHead;
    
    return newHead;
}
 
int main() {
    // Test case 1: [1,2,2,1,2,0,2,2] -> [0,1,1,2,2,2,2,2]
    vector<int> arr1 = {1, 2, 2, 1, 2, 0, 2, 2};
    Node* head1 = arrayToLinkedList(arr1);
    
    cout << "Test case 1:" << endl;
    cout << "Original: ";
    printLinkedList(head1);
    
    head1 = segregate012(head1);
    cout << "After segregation: ";
    printLinkedList(head1);
    cout << "Expected: 0 1 1 2 2 2 2 2" << endl;
    cout << endl;
     
    return 0;
}

