/*
 * Problem: Remove Nth Node From End of List
 *
 * LeetCode 19: Remove Nth Node From End of List
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/nth-node-from-end-in-linked-list/1
 *
 * Given the head of a linked list, remove the nth node from the end of the list 
 * and return its head.
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5], n = 2
 * Output: [1,2,3,5]
 * Explanation: Remove the 2nd node from the end (node with value 4)
 * 
 * Example 2:
 * Input: head = [1], n = 1
 * Output: []
 * 
 * Example 3:
 * Input: head = [1,2], n = 1
 * Output: [1]
 * 
 * Constraints:
 * - The number of nodes in the list is sz
 * - 1 <= sz <= 30
 * - 0 <= Node.val <= 100
 * - 1 <= n <= sz
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

// Method 1: Two-pointer approach (Most Efficient)
// Time Complexity: O(n), Space Complexity: O(1)
Node* removeNthFromEnd(Node* head, int n) {
    // Create a dummy node to handle edge case of deleting head
    Node* dummy = new Node(0);
    dummy->next = head;
    
    // Two pointers: fast and slow
    Node* fast = dummy;
    Node* slow = dummy;
    
    // Move fast pointer n+1 steps ahead
    // This ensures slow will be at (n+1)th node from end when fast reaches null
    for (int i = 0; i <= n; i++) {
        fast = fast->next;
    }
    
    // Move both pointers until fast reaches the end
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    
    // Now slow->next is the node to delete
    Node* nodeToDelete = slow->next;
    slow->next = slow->next->next;
    delete nodeToDelete;
    
    // Get the new head
    Node* newHead = dummy->next;
    delete dummy;
    
    return newHead;
}

int main() {
    // Test case 1: [1,2,3,4,5], n = 2 -> [1,2,3,5]
    vector<int> arr1 = {1, 2, 3, 4, 5};
    Node* head1 = arrayToLinkedList(arr1);
    
    cout << "Test case 1:" << endl;
    cout << "Original: ";
    printLinkedList(head1);
    
    head1 = removeNthFromEnd(head1, 2);
    cout << "After removing 2nd from end: ";
    printLinkedList(head1);
    cout << "Expected: 1 2 3 5" << endl;
    cout << endl;
    
    // Test case 2: [1], n = 1 -> []
    vector<int> arr2 = {1};
    Node* head2 = arrayToLinkedList(arr2);
    
    cout << "Test case 2:" << endl;
    cout << "Original: ";
    printLinkedList(head2);
    
    head2 = removeNthFromEnd(head2, 1);
    cout << "After removing 1st from end: ";
    if (head2) {
        printLinkedList(head2);
    } else {
        cout << "[] (empty list)" << endl;
    }
    cout << "Expected: []" << endl;
    cout << endl;
    
    // Test case 3: [1,2], n = 1 -> [1]
    vector<int> arr3 = {1, 2};
    Node* head3 = arrayToLinkedList(arr3);
    
    cout << "Test case 3:" << endl;
    cout << "Original: ";
    printLinkedList(head3);
    
    head3 = removeNthFromEnd(head3, 1);
    cout << "After removing 1st from end: ";
    printLinkedList(head3);
    cout << "Expected: 1" << endl;
    cout << endl;
    
    // Test case 4: [1,2], n = 2 -> [2]
    vector<int> arr4 = {1, 2};
    Node* head4 = arrayToLinkedList(arr4);
    
    cout << "Test case 4:" << endl;
    cout << "Original: ";
    printLinkedList(head4);
    
    head4 = removeNthFromEnd(head4, 2);
    cout << "After removing 2nd from end: ";
    printLinkedList(head4);
    cout << "Expected: 2" << endl;
    cout << endl;
    
    // Test case 5: [1,2,3,4,5], n = 5 -> [2,3,4,5]
    vector<int> arr5 = {1, 2, 3, 4, 5};
    Node* head5 = arrayToLinkedList(arr5);
    
    cout << "Test case 5:" << endl;
    cout << "Original: ";
    printLinkedList(head5);
    
    head5 = removeNthFromEnd(head5, 5);
    cout << "After removing 5th from end: ";
    printLinkedList(head5);
    cout << "Expected: 2 3 4 5" << endl;
    cout << endl;
    
    // Test case 6: [1,2,3,4,5], n = 1 -> [1,2,3,4]
    vector<int> arr6 = {1, 2, 3, 4, 5};
    Node* head6 = arrayToLinkedList(arr6);
    
    cout << "Test case 6:" << endl;
    cout << "Original: ";
    printLinkedList(head6);
    
    head6 = removeNthFromEnd(head6, 1);
    cout << "After removing 1st from end: ";
    printLinkedList(head6);
    cout << "Expected: 1 2 3 4" << endl;
    
    return 0;
}

