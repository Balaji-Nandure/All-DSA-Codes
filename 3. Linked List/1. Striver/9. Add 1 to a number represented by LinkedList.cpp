/*
 * Problem: Add 1 to a number represented as linked list
 * 
 * A number N is represented in Linked List such that each digit corresponds 
 * to a node in linked list. You need to add 1 to it.
 * 
 * Example 1:
 * Input: head = [1,2,3]
 * Output: [1,2,4]
 * Explanation: 123 + 1 = 124
 * 
 * Example 2:
 * Input: head = [9,9,9]
 * Output: [1,0,0,0]
 * Explanation: 999 + 1 = 1000
 * 
 * Example 3:
 * Input: head = [4,5,6]
 * Output: [4,5,7]
 * Explanation: 456 + 1 = 457
 * 
 * Constraints:
 * - 1 <= length of the linked list <= 10^5
 * - 0 <= Node->data <= 9
 * - The number represented by the linked list does not contain leading zeros
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

// Helper function to reverse a linked list
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

// ========== METHOD 1: Reverse, Add, Reverse Back ==========
// Time Complexity: O(n), Space Complexity: O(1)
Node* addOneReverse(Node* head) {
    if (!head) return new Node(1);
    
    // Step 1: Reverse the list
    head = reverseList(head);
    
    // Step 2: Add 1
    Node* curr = head;
    int carry = 1;  // Start with 1 to add
    
    // && is used to check if the current node is not null and the carry is greater than 0
    while (curr && carry > 0) {
        int sum = curr->data + carry;
        curr->data = sum % 10;
        carry = sum / 10;
        curr = curr->next;
    }
    
    // Step 3: Reverse back
    head = reverseList(head);

    if(carry > 0){
        Node* newHead = new Node(carry);
        newHead->next = head;
        return newHead;
    }
    
    return head;
}

// ========== METHOD 2: Recursive Approach ==========
// Time Complexity: O(n), Space Complexity: O(n) due to recursion
int addOneRecursive(Node* head) {
    if (!head) return 1;  // Return 1 to add
    
    int carry = addOneRecursive(head->next);
    
    int sum = head->data + carry;
    head->data = sum % 10;
    
    return sum / 10;  // Return carry
}

Node* addOneRecursiveWrapper(Node* head) {
    int carry = addOneRecursive(head);
    
    // If there's a carry left, create a new head node
    if (carry > 0) {
        Node* newHead = new Node(carry);
        newHead->next = head;
        return newHead;
    }
    
    return head;
}

// ========== METHOD 3: Find Rightmost Non-9 Digit ==========
// Time Complexity: O(n), Space Complexity: O(1)
Node* addOneOptimal(Node* head) {
    if (!head) return new Node(1);
    
    // Step 1: Find the rightmost non-9 digit
    Node* lastNonNine = nullptr;
    Node* curr = head;
    
    // Traverse to find the rightmost non-9 node
    while (curr) {
        if (curr->data != 9) {
            lastNonNine = curr;
        }
        curr = curr->next;
    }
    
    // Step 2: If all digits are 9, we need a new head
    if (!lastNonNine) {
        // All digits are 9, create new head with 1
        Node* newHead = new Node(1);
        newHead->next = head;
        
        // Set all nodes to 0
        curr = head;
        while (curr) {
            curr->data = 0;
            curr = curr->next;
        }
        
        return newHead;
    }
    
    // Step 3: Increment the rightmost non-9 digit
    lastNonNine->data++;
    
    // Step 4: Set all digits after it to 0
    curr = lastNonNine->next;
    while (curr) {
        curr->data = 0;
        curr = curr->next;
    }
    
    return head;
}

// ========== METHOD 4: Using Stack ==========
// Time Complexity: O(n), Space Complexity: O(n)
Node* addOneStack(Node* head) {
    if (!head) return new Node(1);
    
    stack<Node*> st;
    Node* curr = head;
    
    // Push all nodes onto stack
    while (curr) {
        st.push(curr);
        curr = curr->next;
    }
    
    int carry = 1;
    
    // Pop and add 1
    while (!st.empty() && carry > 0) {
        Node* node = st.top();
        st.pop();
        
        int sum = node->data + carry;
        node->data = sum % 10;
        carry = sum / 10;
    }
    
    // If carry remains, create new head
    if (carry > 0) {
        Node* newHead = new Node(carry);
        newHead->next = head;
        return newHead;
    }
    
    return head;
}

int main() {
    cout << "========== METHOD 1: Reverse, Add, Reverse ==========" << endl;
    
    // Test case 1: [1,2,3] -> [1,2,4]
    vector<int> arr1 = {1, 2, 3};
    Node* head1 = arrayToLinkedList(arr1);
    
    cout << "\nTest case 1:" << endl;
    cout << "Original: ";
    printLinkedList(head1);
    head1 = addOneReverse(head1);
    cout << "After adding 1: ";
    printLinkedList(head1);
    cout << "Expected: 1 2 4" << endl;
    
    // Test case 2: [9,9,9] -> [1,0,0,0]
    vector<int> arr2 = {9, 9, 9};
    Node* head2 = arrayToLinkedList(arr2);
    
    cout << "\nTest case 2:" << endl;
    cout << "Original: ";
    printLinkedList(head2);
    head2 = addOneReverse(head2);
    cout << "After adding 1: ";
    printLinkedList(head2);
    cout << "Expected: 1 0 0 0" << endl;
    
    // Test case 3: [4,5,6] -> [4,5,7]
    vector<int> arr3 = {4, 5, 6};
    Node* head3 = arrayToLinkedList(arr3);
    
    cout << "\nTest case 3:" << endl;
    cout << "Original: ";
    printLinkedList(head3);
    head3 = addOneReverse(head3);
    cout << "After adding 1: ";
    printLinkedList(head3);
    cout << "Expected: 4 5 7" << endl;
    
    cout << "\n========== METHOD 2: Recursive ==========" << endl;
    
    // Test case 4: [1,9,9] -> [2,0,0]
    vector<int> arr4 = {1, 9, 9};
    Node* head4 = arrayToLinkedList(arr4);
    
    cout << "\nTest case 4:" << endl;
    cout << "Original: ";
    printLinkedList(head4);
    head4 = addOneRecursiveWrapper(head4);
    cout << "After adding 1 (recursive): ";
    printLinkedList(head4);
    cout << "Expected: 2 0 0" << endl;
    
    cout << "\n========== METHOD 3: Optimal (Find Rightmost Non-9) ==========" << endl;
    
    // Test case 5: [9,9,9] -> [1,0,0,0]
    vector<int> arr5 = {9, 9, 9};
    Node* head5 = arrayToLinkedList(arr5);
    
    cout << "\nTest case 5:" << endl;
    cout << "Original: ";
    printLinkedList(head5);
    head5 = addOneOptimal(head5);
    cout << "After adding 1 (optimal): ";
    printLinkedList(head5);
    cout << "Expected: 1 0 0 0" << endl;
    
    // Test case 6: [1,2,9] -> [1,3,0]
    vector<int> arr6 = {1, 2, 9};
    Node* head6 = arrayToLinkedList(arr6);
    
    cout << "\nTest case 6:" << endl;
    cout << "Original: ";
    printLinkedList(head6);
    head6 = addOneOptimal(head6);
    cout << "After adding 1 (optimal): ";
    printLinkedList(head6);
    cout << "Expected: 1 3 0" << endl;
    
    // Test case 7: [9] -> [1,0]
    vector<int> arr7 = {9};
    Node* head7 = arrayToLinkedList(arr7);
    
    cout << "\nTest case 7:" << endl;
    cout << "Original: ";
    printLinkedList(head7);
    head7 = addOneOptimal(head7);
    cout << "After adding 1 (optimal): ";
    printLinkedList(head7);
    cout << "Expected: 1 0" << endl;
    
    return 0;
}

