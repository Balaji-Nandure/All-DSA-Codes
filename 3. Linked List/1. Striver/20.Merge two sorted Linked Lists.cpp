/*
 * Problem: Merge Two Sorted Lists (LeetCode 21)
 * 
 * You are given the heads of two sorted linked lists list1 and list2.
 * Merge the two lists in a one sorted list. The list should be made by splicing 
 * together the nodes of the first two lists.
 * 
 * Return the head of the merged linked list.
 * 
 * Example 1:
 * Input: list1 = [1,2,4], list2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
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

// ========== METHOD 1: Iterative Approach with Dummy Node (Optimal) ==========
// Time Complexity: O(n + m), Space Complexity: O(1)
Node* mergeTwoLists(Node* list1, Node* list2) {
    // Create a dummy node to simplify edge cases
    Node* dummy = new Node(0);
    Node* tail = dummy;
    
    // Merge while both lists have nodes
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
    
    // Attach remaining nodes from either list
    if (list1) {
        tail->next = list1;
    } else if (list2) {
        tail->next = list2;
    }
    
    // Get the actual head and delete dummy
    Node* result = dummy->next;
    delete dummy;
    return result;
}


int main() {
    
    // Test case 1: [1,2,4] and [1,3,4] -> [1,1,2,3,4,4]
    vector<int> arr1 = {1, 2, 4};
    vector<int> arr2 = {1, 3, 4};
    Node* list1_1 = arrayToLinkedList(arr1);
    Node* list2_1 = arrayToLinkedList(arr2);
    
    cout << "\nTest case 1:" << endl;
    cout << "List 1: ";
    printLinkedList(list1_1);
    cout << "List 2: ";
    printLinkedList(list2_1);
    Node* merged1 = mergeTwoLists(list1_1, list2_1);
    cout << "Merged: ";
    printLinkedList(merged1);
    cout << "Expected: 1 1 2 3 4 4" << endl;
    
    return 0;
}

