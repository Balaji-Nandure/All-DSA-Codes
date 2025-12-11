/*
 * Problem: Reverse Nodes in k-Group (LeetCode 25)
 * 
 * Given the head of a linked list, reverse the nodes of the list k at a time, 
 * and return the modified list.
 * 
 * k is a positive integer and is less than or equal to the length of the linked list. 
 * If the number of nodes is not a multiple of k then left-out nodes, in the end, 
 * should remain as it is.
 * 
 * You may not alter the values in the list's nodes, only nodes themselves may be changed.
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [2,1,4,3,5]
 * Explanation: Reverse first 2 nodes, then next 2 nodes, leaving last node as is
 
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

// Helper function to get length of linked list
int getLength(Node* head) {
    int length = 0;
    Node* curr = head;
    while (curr) {
        length++;
        curr = curr->next;
    }
    return length;
}

// ========== METHOD 1: Iterative Approach (Optimal) ==========
// Time Complexity: O(n), Space Complexity: O(1)
Node* reverseKGroup(Node* head, int k) {
    if (!head || k == 1) return head;
    
    // Check if we have at least k nodes
    Node* temp = head;
    int count = 0;
    while (temp && count < k) {
        temp = temp->next;
        count++;
    }
    
    // If we have k nodes, reverse them
    if (count == k) {
        // Reverse first k nodes
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;
        
        // Reverse k nodes
        for (int i = 0; i < k; i++) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        
        // Recursively reverse next k groups
        // After reversal, head is now the tail of reversed group
        head->next = reverseKGroup(curr, k);
        
        // prev is the new head of reversed group
        return prev;
    }
    
    // If less than k nodes, return as is
    return head;
}

int main() {
    cout << "========== METHOD 1: Recursive Approach ==========" << endl;
    
    // Test case 1: [1,2,3,4,5], k = 2 -> [2,1,4,3,5]
    vector<int> arr1 = {1, 2, 3, 4, 5};
    Node* head1 = arrayToLinkedList(arr1);
    
    cout << "\nTest case 1:" << endl;
    cout << "Original: ";
    printLinkedList(head1);
    head1 = reverseKGroup(head1, 2);
    cout << "After reversing in groups of 2: ";
    printLinkedList(head1);
    cout << "Expected: 2 1 4 3 5" << endl;
    
    return 0;
}

