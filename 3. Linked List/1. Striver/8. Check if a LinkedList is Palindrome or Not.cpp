/*
 * Problem: Palindrome Linked List (LeetCode 234)
 * 
 * Given the head of a singly linked list, return true if it is a palindrome 
 * or false otherwise.
 * 
 * Example 1:
 * Input: head = [1,2,2,1]
 * Output: true
 * Explanation: The list reads the same forwards and backwards
 * 
 * Example 2:
 * Input: head = [1,2]
 * Output: false
 * 
 * Constraints:
 * - The number of nodes in the list is in the range [1, 10^5]
 * - 0 <= Node.val <= 9
 * 
 * Follow up: Could you solve it in O(n) time and O(1) space?
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

// ========== METHOD 1: Reverse Second Half (Optimal) ==========
// Time Complexity: O(n), Space Complexity: O(1)
bool isPalindrome(Node* head) {
    if (!head || !head->next) return true;
    
    // Step 1: Find the middle of the list using slow and fast pointers
    Node* slow = head;
    Node* fast = head;
    
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Step 2: Reverse the second half
    Node* secondHalf = reverseList(slow->next);
    Node* firstHalf = head;
    
    // Step 3: Compare first half with reversed second half
    while (secondHalf) {
        if (firstHalf->data != secondHalf->data) {
            // Restore the list (optional, but good practice)
            reverseList(secondHalf);
            return false;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }
    
    // Restore the list (optional)
    reverseList(slow->next);
    
    return true;
}

// ========== METHOD 2: Using Stack ==========
// Time Complexity: O(n), Space Complexity: O(n)
bool isPalindromeStack(Node* head) {
    if (!head || !head->next) return true;
    
    stack<int> st;
    Node* slow = head;
    Node* fast = head;
    
    // Push first half onto stack
    while (fast && fast->next) {
        st.push(slow->data);
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // If odd number of nodes, skip the middle node
    if (fast) {
        slow = slow->next;
    }
    
    // Compare second half with stack
    while (slow) {
        if (st.top() != slow->data) {
            return false;
        }
        st.pop();
        slow = slow->next;
    }
    
    return true;
}

// ========== METHOD 3: Convert to Array ==========
// Time Complexity: O(n), Space Complexity: O(n)
bool isPalindromeArray(Node* head) {
    vector<int> arr;
    Node* curr = head;
    
    while (curr) {
        arr.push_back(curr->data);
        curr = curr->next;
    }
    
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        if (arr[left] != arr[right]) {
            return false;
        }
        left++;
        right--;
    }
    
    return true;
}

int main() {
    cout << "========== METHOD 1: Reverse Second Half ==========" << endl;
    
    // Test case 1: [1,2,2,1] -> true
    vector<int> arr1 = {1, 2, 2, 1};
    Node* head1 = arrayToLinkedList(arr1);
    
    cout << "\nTest case 1:" << endl;
    cout << "List: ";
    printLinkedList(head1);
    cout << "Is Palindrome: " << (isPalindrome(head1) ? "true" : "false") << endl;
    cout << "Expected: true" << endl;
    
    return 0;
}

