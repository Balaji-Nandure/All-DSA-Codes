/*
 * Problem: Add Two Numbers (LeetCode 2)
 * 
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order, and each of their nodes contains a single digit.
 * Add the two numbers and return the sum as a linked list.
 * 
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 * 
 * Example 1:
 * Input: l1 = [2,4,3], l2 = [5,6,4]
 * Output: [7,0,8]
 * Explanation: 342 + 465 = 807
 * 
 * Example 2:
 * Input: l1 = [0], l2 = [0]
 * Output: [0]
 * 
 * Example 3:
 * Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 * Output: [8,9,9,9,0,0,0,1]
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

// Add two numbers represented as linked lists
// The digits are stored in reverse order
Node* addTwoNumbers(Node* l1, Node* l2) {
    // Create a dummy node to simplify the code
    Node* dummy = new Node(0);
    Node* curr = dummy;
    int carry = 0;
    
    // Traverse both lists while they exist or carry is non-zero
    while (l1 || l2 || carry) {
        int sum = carry;
        
        // Add value from l1 if it exists
        if (l1) {
            sum += l1->data;
            l1 = l1->next;
        }
        
        // Add value from l2 if it exists
        if (l2) {
            sum += l2->data;
            l2 = l2->next;
        }
        
        // Calculate digit and carry
        int digit = sum % 10;
        carry = sum / 10;
        
        // Create new node with the digit
        curr->next = new Node(digit);
        curr = curr->next;
    }
    
    // Return the head of the result list (skip dummy node)
    Node* result = dummy->next;
    delete dummy;
    return result;
}

int main() {
    // Test case 1: [2,4,3] + [5,6,4] = [7,0,8]
    // Represents: 342 + 465 = 807
    vector<int> arr1 = {2, 4, 3};
    vector<int> arr2 = {5, 6, 4};
    Node* l1 = arrayToLinkedList(arr1);
    Node* l2 = arrayToLinkedList(arr2);
    
    cout << "Test case 1:" << endl;
    cout << "l1: ";
    printLinkedList(l1);
    cout << "l2: ";
    printLinkedList(l2);
    
    Node* result1 = addTwoNumbers(l1, l2);
    cout << "Sum: ";
    printLinkedList(result1);
    cout << "Expected: 7 0 8" << endl;
    cout << endl;
    
    // Test case 2: [0] + [0] = [0]
    vector<int> arr3 = {0};
    vector<int> arr4 = {0};
    Node* l3 = arrayToLinkedList(arr3);
    Node* l4 = arrayToLinkedList(arr4);
    
    cout << "Test case 2:" << endl;
    cout << "l1: ";
    printLinkedList(l3);
    cout << "l2: ";
    printLinkedList(l4);
    
    Node* result2 = addTwoNumbers(l3, l4);
    cout << "Sum: ";
    printLinkedList(result2);
    cout << "Expected: 0" << endl;
    cout << endl;
    
    // Test case 3: [9,9,9,9,9,9,9] + [9,9,9,9] = [8,9,9,9,0,0,0,1]
    // Represents: 9999999 + 9999 = 10009998
    vector<int> arr5 = {9, 9, 9, 9, 9, 9, 9};
    vector<int> arr6 = {9, 9, 9, 9};
    Node* l5 = arrayToLinkedList(arr5);
    Node* l6 = arrayToLinkedList(arr6);
    
    cout << "Test case 3:" << endl;
    cout << "l1: ";
    printLinkedList(l5);
    cout << "l2: ";
    printLinkedList(l6);
    
    Node* result3 = addTwoNumbers(l5, l6);
    cout << "Sum: ";
    printLinkedList(result3);
    cout << "Expected: 8 9 9 9 0 0 0 1" << endl;
    cout << endl;
    
    // Test case 4: [1,8] + [0] = [1,8]
    vector<int> arr7 = {1, 8};
    vector<int> arr8 = {0};
    Node* l7 = arrayToLinkedList(arr7);
    Node* l8 = arrayToLinkedList(arr8);
    
    cout << "Test case 4:" << endl;
    cout << "l1: ";
    printLinkedList(l7);
    cout << "l2: ";
    printLinkedList(l8);
    
    Node* result4 = addTwoNumbers(l7, l8);
    cout << "Sum: ";
    printLinkedList(result4);
    cout << "Expected: 1 8" << endl;
    
    return 0;
}
