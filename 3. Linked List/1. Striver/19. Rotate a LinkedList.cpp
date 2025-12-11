/*
 * Problem: Rotate List (LeetCode 61)
 * 
 * Given the head of a linked list, rotate the list to the right by k places.
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [4,5,1,2,3]
 * Explanation: Rotate right by 2 places
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

// ========== METHOD 1: Connect Tail to Head and Break (Optimal) ==========
// Time Complexity: O(n), Space Complexity: O(1)
Node* rotateRight(Node* head, int k) {
    if (!head || !head->next || k == 0) return head;
    
    // Step 1: Find length and tail
    int length = 1;
    Node* tail = head;
    while (tail->next) {
        tail = tail->next;
        length++;
    }
    
    // Step 2: Normalize k (handle k > length)
    k = k % length;
    if (k == 0) return head;  // No rotation needed
    
    // Step 3: Make list circular
    tail->next = head;
    
    // Step 4: Find the new tail (length - k - 1 steps from head)
    Node* newTail = head;
    for (int i = 0; i < length - k - 1; i++) {
        newTail = newTail->next;
    }
    
    // Step 5: Break the cycle and return new head
    Node* newHead = newTail->next;
    newTail->next = nullptr;
    
    return newHead;
}


// ========== METHOD 2: Reverse Approach ==========
// Time Complexity: O(n), Space Complexity: O(1)
Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;
    
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    return prev;
}

Node* rotateRightReverse(Node* head, int k) {
    if (!head || !head->next || k == 0) return head;
    
    // Step 1: Calculate length and normalize k
    int length = getLength(head);
    k = k % length;
    if (k == 0) return head;
    
    // Step 2: Reverse the entire list
    head = reverseList(head);
    
    // Step 3: Reverse first k nodes
    Node* curr = head;
    Node* prev = nullptr;
    for (int i = 0; i < k; i++) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    // Step 4: Reverse remaining nodes
    Node* remainingHead = reverseList(curr);
    
    // Step 5: Connect the two parts
    head->next = remainingHead;
    
    // prev is the new head
    return prev;
}

int main() {
    // Test case 1: [1,2,3,4,5], k = 2 -> [4,5,1,2,3]
    vector<int> arr1 = {1, 2, 3, 4, 5};
    Node* head1 = arrayToLinkedList(arr1);
    
    cout << "\nTest case 1:" << endl;
    cout << "Original: ";
    printLinkedList(head1);
    head1 = rotateRight(head1, 2);
    cout << "After rotating right by 2: ";
    printLinkedList(head1);
    cout << "Expected: 4 5 1 2 3" << endl;
    
    return 0;
}

