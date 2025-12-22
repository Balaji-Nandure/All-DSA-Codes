/*
 * Problem: Odd Even Linked List (LeetCode 328)
 * 
 * Given the head of a singly linked list, group all the nodes with odd indices 
 * together followed by the nodes with even indices, and return the reordered list.
 * 
 * The first node is considered odd, and the second node is even, and so on.
 * 
 * Note that the relative order inside both the even and odd groups should remain 
 * as it was in the input.
 * 
 * You must solve the problem in O(1) extra space complexity and O(n) time complexity.
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5]
 * Output: [1,3,5,2,4]
 * Explanation: 
 * - Odd indices: 1 (index 1), 3 (index 3), 5 (index 5)
 * - Even indices: 2 (index 2), 4 (index 4)
 * 
 * Example 2:
 * Input: head = [2,1,3,5,6,4,7]
 * Output: [2,3,6,7,1,5,4]
 * 
 * Constraints:
 * - The number of nodes in the linked list is in the range [0, 10^4].
 * - -10^6 <= Node.val <= 10^6
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
 * Problem: Odd Even Linked List
 *
 * LeetCode 328: Odd Even Linked List
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/rearrange-a-linked-list/1
 *
 * Group all nodes with odd indices together, followed by nodes with even indices.
 * First node is at index 1 (odd), second at index 2 (even), etc.
 *
 * Example: [1,2,3,4,5] -> [1,3,5,2,4]
 *
 * Time: O(n) - single pass
 * Space: O(1) - in-place rearrangement
 */

// Group odd-indexed nodes followed by even-indexed nodes
Node* oddEvenList(Node* head) {
    // Edge cases: empty list or list with 1 or 2 nodes (already in correct order)
    if (!head || !head->next || !head->next->next) {
        return head;
    }
    
    // Separate odd and even nodes using two pointers
    Node* odd = head;           // Points to odd-indexed nodes (1st, 3rd, 5th, ...)
    Node* even = head->next;    // Points to even-indexed nodes (2nd, 4th, 6th, ...)
    Node* evenHead = even;      // Save head of even list to connect later
    
    // Traverse and separate: connect odd nodes together, even nodes together
    while (even && even->next) {
        // Connect odd nodes: link current odd to next odd
        odd->next = even->next;  // Skip even node, link to next odd
        odd = odd->next; // Move odd pointer forward
        
        // Connect even nodes: link current even to next even
        even->next = odd->next;  // Skip odd node, link to next even
        even = even->next; // Move even pointer forward
    }
    
    // Connect odd list to even list
    odd->next = evenHead;
    
    return head; // Head remains the same (first node is odd)
}


int main() {
    // Test case 1: [1,2,3,4,5] -> [1,3,5,2,4]
    vector<int> arr1 = {1, 2, 3, 4, 5};
    Node* head1 = arrayToLinkedList(arr1);
    
    cout << "Test case 1:" << endl;
    cout << "Original: ";
    printLinkedList(head1);
    
    head1 = oddEvenList(head1);
    cout << "After odd-even: ";
    printLinkedList(head1);
    cout << "Expected: 1 3 5 2 4" << endl;
    cout << endl;
    
    // Test case 2: [2,1,3,5,6,4,7] -> [2,3,6,7,1,5,4]
    vector<int> arr2 = {2, 1, 3, 5, 6, 4, 7};
    Node* head2 = arrayToLinkedList(arr2);
    
    cout << "Test case 2:" << endl;
    cout << "Original: ";
    printLinkedList(head2);
    
    head2 = oddEvenList(head2);
    cout << "After odd-even: ";
    printLinkedList(head2);
    cout << "Expected: 2 3 6 7 1 5 4" << endl;
    cout << endl;
    
    // Test case 3: [1,2] -> [1,2]
    vector<int> arr3 = {1, 2};
    Node* head3 = arrayToLinkedList(arr3);
    
    cout << "Test case 3:" << endl;
    cout << "Original: ";
    printLinkedList(head3);
    
    head3 = oddEvenList(head3);
    cout << "After odd-even: ";
    printLinkedList(head3);
    cout << "Expected: 1 2" << endl;
    cout << endl;
    
    // Test case 4: [1] -> [1]
    vector<int> arr4 = {1};
    Node* head4 = arrayToLinkedList(arr4);
    
    cout << "Test case 4:" << endl;
    cout << "Original: ";
    printLinkedList(head4);
    
    head4 = oddEvenList(head4);
    cout << "After odd-even: ";
    printLinkedList(head4);
    cout << "Expected: 1" << endl;
    cout << endl;
    
    // Test case 5: [1,2,3,4] -> [1,3,2,4]
    vector<int> arr5 = {1, 2, 3, 4};
    Node* head5 = arrayToLinkedList(arr5);
    
    cout << "Test case 5:" << endl;
    cout << "Original: ";
    printLinkedList(head5);
    
    head5 = oddEvenList(head5);
    cout << "After odd-even: ";
    printLinkedList(head5);
    cout << "Expected: 1 3 2 4" << endl;
    
    return 0;
}

