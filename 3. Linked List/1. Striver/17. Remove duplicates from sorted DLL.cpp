/*
 * Problem: Remove duplicates from sorted Doubly Linked List
 * 
 * Given a sorted doubly linked list containing n nodes. The problem is to remove 
 * duplicate nodes from the given list.
 * 
 * Example 1:
 * Input: DLL: 1 <-> 1 <-> 1 <-> 2 <-> 3 <-> 3 <-> 4
 * Output: 1 <-> 2 <-> 3 <-> 4
 * 
 * Example 2:
 * Input: DLL: 1 <-> 2 <-> 2 <-> 2 <-> 3
 * Output: 1 <-> 2 <-> 3
 * 
 * Example 3:
 * Input: DLL: 1 <-> 2 <-> 3 <-> 4
 * Output: 1 <-> 2 <-> 3 <-> 4 (no duplicates)
 * 
 * Constraints:
 * - 1 <= number of nodes <= 10^5
 * - 0 <= Node->data <= 10^5
 * - The list is sorted in non-decreasing order
 */

#include <bits/stdc++.h>
using namespace std;

// Node class represents a node in a doubly linked list
class DNode {
public:
    int data;
    DNode* next;
    DNode* prev;

    // Constructor with data, next, prev
    DNode(int data, DNode* next = nullptr, DNode* prev = nullptr) {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

// Convert array to doubly linked list
DNode* arrayToDoublyLinkedList(const vector<int>& arr) {
    if (arr.size() == 0) return nullptr;
    DNode* head = new DNode(arr[0]);
    DNode* curr = head;
    for (int i = 1; i < arr.size(); ++i) {
        DNode* newNode = new DNode(arr[i]);
        curr->next = newNode;
        newNode->prev = curr;
        curr = newNode;
    }
    return head;
}

// Print doubly linked list forwards
void printDoublyLinkedList(DNode* head) {
    DNode* curr = head;
    while (curr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

// ========== METHOD 1: Remove Duplicates (Optimal) ==========
// Time Complexity: O(n), Space Complexity: O(1)
DNode* removeDuplicates(DNode* head) {
    if (!head || !head->next) return head;
    
    DNode* curr = head;
    
    while (curr && curr->next) {
        // If current node and next node have same value
        if (curr->data == curr->next->data) {
            DNode* duplicate = curr->next;
            
            // Update pointers to skip duplicate
            curr->next = duplicate->next;
            
            // Update prev pointer of next node (if exists)
            if (duplicate->next) {
                duplicate->next->prev = curr;
            }
            
            // Delete duplicate node
            delete duplicate;
        } else {
            // Move to next node only if no duplicate found
            curr = curr->next;
        }
    }
    
    return head;
}


int main() {
    cout << "========== METHOD 1: Remove Duplicates ==========" << endl;
    
    // Test case 1: [1,1,1,2,3,3,4] -> [1,2,3,4]
    vector<int> arr1 = {1, 1, 1, 2, 3, 3, 4};
    DNode* head1 = arrayToDoublyLinkedList(arr1);
    
    cout << "\nTest case 1:" << endl;
    cout << "Original DLL: ";
    printDoublyLinkedList(head1);
    head1 = removeDuplicates(head1);
    cout << "After removing duplicates: ";
    printDoublyLinkedList(head1);
    cout << "Expected: 1 2 3 4" << endl;
    
    return 0;
}

