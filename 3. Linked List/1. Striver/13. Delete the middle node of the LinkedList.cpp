/*
 * Problem: Delete the Middle Node of a Linked List (LeetCode 2095)
 * 
 * You are given the head of a linked list. Delete the middle node, and return 
 * the head of the modified linked list.
 * 
 * The middle node of a linked list of size n is the ⌊n / 2⌋th node from the start 
 * using 0-based indexing, where ⌊x⌋ denotes the largest integer less than or equal to x.
 * 
 * Example 1:
 * Input: head = [1,3,4,7,1,2,6]
 * Output: [1,3,4,1,2,6]
 * Explanation: The middle node is 7, which is deleted
 * 
 * Constraints:
 * - The number of nodes in the list is in the range [1, 10^5]
 * - 1 <= Node.val <= 10^5
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
 * Problem: Delete the Middle Node of a Linked List
 *
 * LeetCode 2095: Delete the Middle Node of a Linked List
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/delete-middle-of-linked-list/1
 *
 * Delete the middle node of a linked list. Middle = ⌊n/2⌋ (0-indexed).
 * Example: [1,3,4,7,1,2,6] -> [1,3,4,1,2,6] (deleted 7)
 *
 * Time: O(n) - single pass
 * Space: O(1)
 */

// Method 1: Two-Pointer with Dummy Node (Optimal)
Node* deleteMiddle(Node* head) {
    // Edge case: single node - delete and return null
    if (!head || !head->next) {
        delete head;
        return nullptr;
    }
    
    // Edge case: two nodes - delete second one
    if (!head->next->next) {
        delete head->next;
        head->next = nullptr;
        return head;
    }
    
    // Dummy node simplifies code (handles head deletion case)
    Node* dummy = new Node(0);
    dummy->next = head;
    
    Node* slow = dummy; // Will point to node before middle
    Node* fast = head; // Moves 2 steps
    
    // When fast reaches end, slow is at node before middle
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Delete middle node (slow->next)
    Node* nodeToDelete = slow->next;
    slow->next = slow->next->next; // Bypass middle node
    delete nodeToDelete;
    
    Node* newHead = dummy->next;
    delete dummy;
    return newHead;
}

// ========== METHOD 2: Two-Pointer without Dummy Node ==========
// Time Complexity: O(n), Space Complexity: O(1)
Node* deleteMiddleNoDummy(Node* head) {
    // Edge case: single node
    if (!head || !head->next) {
        delete head;
        return nullptr;
    }
    
    // Edge case: two nodes - delete the second one
    if (!head->next->next) {
        delete head->next;
        head->next = nullptr;
        return head;
    }
    
    // Here is the difference between the two methods:
    Node* slow = head;
    Node* fast = head->next->next;  // Start fast 2 steps ahead
    
    // Move fast pointer 2 steps and slow pointer 1 step
    // When fast reaches end, slow will be at node before middle
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Delete the middle node (slow->next)
    Node* nodeToDelete = slow->next;
    slow->next = slow->next->next;
    delete nodeToDelete;
    
    return head;
}

int main() {
    
    // Test case 1: [1,3,4,7,1,2,6] -> [1,3,4,1,2,6]
    vector<int> arr1 = {1, 3, 4, 7, 1, 2, 6};
    Node* head1 = arrayToLinkedList(arr1);
    
    cout << "\nTest case 1:" << endl;
    cout << "Original: ";
    printLinkedList(head1);
    head1 = deleteMiddle(head1);
    cout << "After deleting middle: ";
    printLinkedList(head1);
    cout << "Expected: 1 3 4 1 2 6" << endl;
    
    return 0;
}

