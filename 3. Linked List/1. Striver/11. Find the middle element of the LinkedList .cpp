/*
 * Problem: Middle of the Linked List (LeetCode 876)
 * 
 * Given the head of a singly linked list, return the middle node of the linked list.
 * If there are two middle nodes, return the second middle node.
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5]
 * Output: [3,4,5]
 * Explanation: The middle node of the list is node 3
 * 
 * Example 2:
 * Input: head = [1,2,3,4,5,6]
 * Output: [4,5,6]
 * Explanation: Since the list has two middle nodes with values 3 and 4, 
 * we return the second one.
 * 
 * Constraints:
 * - The number of nodes in the list is in the range [1, 100]
 * - 1 <= Node.val <= 100
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

// ========== METHOD 1: Two-Pointer (Slow and Fast) - Optimal ==========
// Time Complexity: O(n), Space Complexity: O(1)
Node* middleNode(Node* head) {
    if (!head) return nullptr;
    
    Node* slow = head;
    Node* fast = head;
    
    // Move fast pointer 2 steps and slow pointer 1 step
    // When fast reaches end, slow will be at middle
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

// ========== METHOD 2: Find Length First ==========
// Time Complexity: O(n), Space Complexity: O(1)
Node* middleNodeByLength(Node* head) {
    if (!head) return nullptr;
    
    // Step 1: Find the length
    int length = 0;
    Node* curr = head;
    while (curr) {
        length++;
        curr = curr->next;
    }
    
    // Step 2: Traverse to middle
    int middle = length / 2;
    curr = head;
    for (int i = 0; i < middle; i++) {
        curr = curr->next;
    }
    
    return curr;
}

int main() {
    cout << "========== METHOD 1: Two-Pointer (Slow and Fast) ==========" << endl;
    
    // Test case 1: [1,2,3,4,5] -> middle is 3
    vector<int> arr1 = {1, 2, 3, 4, 5};
    Node* head1 = arrayToLinkedList(arr1);
    
    cout << "\nTest case 1:" << endl;
    cout << "List: ";
    printLinkedList(head1);
    Node* middle1 = middleNode(head1);
    cout << "Middle node value: " << middle1->data << endl;
    cout << "From middle onwards: ";
    printLinkedList(middle1);
    cout << "Expected: 3" << endl;
    
    return 0;
}

