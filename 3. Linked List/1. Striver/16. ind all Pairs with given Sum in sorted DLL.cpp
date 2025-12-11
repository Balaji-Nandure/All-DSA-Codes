/*
 * Problem: Find all Pairs with given Sum in sorted Doubly Linked List
 * 
 * Given a sorted doubly linked list of positive distinct elements, the task is 
 * to find pairs in the doubly linked list whose sum is equal to given value target.
 * 
 * Example 1:
 * Input: DLL: 1 <-> 2 <-> 4 <-> 5 <-> 6 <-> 8 <-> 9
 *        target = 7
 * Output: (1,6), (2,5)
 * 
 * Example 2:
 * Input: DLL: 1 <-> 2 <-> 3 <-> 4 <-> 5
 *        target = 5
 * Output: (1,4), (2,3)
 * 
 * Example 3:
 * Input: DLL: 1 <-> 5 <-> 6
 *        target = 10
 * Output: (5,5) or no pairs if duplicates not allowed
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

// Helper function to get tail of DLL
DNode* getTail(DNode* head) {
    if (!head) return nullptr;
    DNode* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    return curr;
}

// ========== METHOD 1: Two-Pointer Approach (Optimal) ==========
// Time Complexity: O(n), Space Complexity: O(1)
vector<pair<int, int>> findPairs(DNode* head, int target) {
    vector<pair<int, int>> pairs;
    
    if (!head || !head->next) return pairs;
    
    // Initialize two pointers: left at head, right at tail
    DNode* left = head;
    DNode* right = getTail(head);
    
    // Use two-pointer technique similar to sorted array
    while (left && right && left != right && left->prev != right) {
        int sum = left->data + right->data;
        
        if (sum == target) {
            pairs.push_back({left->data, right->data});
            left = left->next;
            right = right->prev;
        } else if (sum < target) {
            // Sum is less, move left pointer forward
            left = left->next;
        } else {
            // Sum is greater, move right pointer backward
            right = right->prev;
        }
    }
    
    return pairs;
}

// Helper function to print pairs
void printPairs(const vector<pair<int, int>>& pairs) {
    if (pairs.empty()) {
        cout << "No pairs found" << endl;
        return;
    }
    
    cout << "Pairs found: ";
    for (int i = 0; i < (int)pairs.size(); i++) {
        cout << "(" << pairs[i].first << "," << pairs[i].second << ")";
        if (i < (int)pairs.size() - 1) cout << ", ";
    }
    cout << endl;
}

int main() {
    cout << "========== METHOD 1: Two-Pointer Approach ==========" << endl;
    
    // Test case 1: [1,2,4,5,6,8,9], target = 7 -> (1,6), (2,5)
    vector<int> arr1 = {1, 2, 4, 5, 6, 8, 9};
    DNode* head1 = arrayToDoublyLinkedList(arr1);
    
    cout << "\nTest case 1:" << endl;
    cout << "DLL: ";
    printDoublyLinkedList(head1);
    cout << "Target sum: 7" << endl;
    vector<pair<int, int>> pairs1 = findPairs(head1, 7);
    printPairs(pairs1);
    cout << "Expected: (1,6), (2,5)" << endl;
    
    return 0;
}

