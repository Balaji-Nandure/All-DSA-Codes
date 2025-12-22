/*
 * Problem: Reverse Linked List (LeetCode 206)
 * 
 * Given the head of a singly linked list, reverse the list, and return the reversed list.
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5]
 * Output: [5,4,3,2,1]
 * 
 * Example 2:
 * Input: head = [1,2]
 * Output: [2,1]
 * 
 * Example 3:
 * Input: head = []
 * Output: []
 * 
 * Constraints:
 * - The number of nodes in the list is the range [0, 5000]
 * - -5000 <= Node.val <= 5000
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


/*
 * Problem: Reverse Linked List
 *
 * LeetCode 206: Reverse Linked List
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/reverse-a-linked-list/1
 *
 * Reverse a singly linked list.
 * Example: [1,2,3,4,5] -> [5,4,3,2,1]
 *
 * Time: O(n) - single pass
 * Space: O(1) for iterative, O(n) for recursive
 */

// Method 1: Iterative (Three-pointer approach)
Node* reverseIterative(Node* head) {
    Node* prev = nullptr; // Previous node (starts as null)
    Node* curr = head; // Current node
    Node* next = nullptr; // Next node (temporary)
    
    while (curr) {
        // Save next node before reversing link
        next = curr->next;
        // Reverse the link: point current to previous
        curr->next = prev;
        // Move pointers forward
        prev = curr; // prev becomes current
        curr = next; // curr becomes next
    }
    
    // prev is now the new head (last node of original list)
    return prev;
}

// Method 2: Tail Recursive (Space optimized recursion)
Node* reverseTailRecursive(Node* curr, Node* prev) {
    // Base case: reached end of list
    if (!curr) {
        return prev; // prev is new head
    }
    
    // Save next node
    Node* next = curr->next;
    // Reverse current link
    curr->next = prev;
    // Recurse with next node and current as previous
    return reverseTailRecursive(next, curr);
}

Node* reverseTailRec(Node* head) {
    return reverseTailRecursive(head, nullptr);
}

int main() {
    
    // Test case 1: [1,2,3,4,5] -> [5,4,3,2,1]
    vector<int> arr1 = {1, 2, 3, 4, 5};
    Node* head1 = arrayToLinkedList(arr1);
    
    cout << "\nTest case 1:" << endl;
    cout << "Original: ";
    printLinkedList(head1);
    
    head1 = reverseIterative(head1);
    cout << "Reversed (iterative): ";
    printLinkedList(head1);
    cout << "Expected: 5 4 3 2 1" << endl;
    
    // Test case 2: [1,2] -> [2,1]
    vector<int> arr2 = {1, 2};
    Node* head2 = arrayToLinkedList(arr2);
    
    cout << "\nTest case 2:" << endl;
    cout << "Original: ";
    printLinkedList(head2);
    
    head2 = reverseIterative(head2);
    cout << "Reversed (iterative): ";
    printLinkedList(head2);
    cout << "Expected: 2 1" << endl;
    
    // Test case 3: [1] -> [1]
    vector<int> arr3 = {1};
    Node* head3 = arrayToLinkedList(arr3);
    
    cout << "\nTest case 3:" << endl;
    cout << "Original: ";
    printLinkedList(head3);
    
    head3 = reverseIterative(head3);
    cout << "Reversed (iterative): ";
    printLinkedList(head3);
    cout << "Expected: 1" << endl;
     
    return 0;
}

