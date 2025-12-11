/*
 * Problem: Intersection of Two Linked Lists (LeetCode 160)
 * 
 * Given the heads of two singly linked-lists headA and headB, return the node 
 * at which the two lists intersect. If the two linked lists have no intersection 
 * at all, return null.
 * 
 * The two linked lists begin to intersect at node c1.
 * 
 * Example 1:
 * List A: [4,1,8,4,5]
 * List B: [5,6,1,8,4,5]
 * Intersection at node with value 8
 * 
 * Example 2:
 * List A: [1,9,1,2,4]
 * List B: [3,2,4]
 * Intersection at node with value 2
 * 
 * Example 3:
 * List A: [2,6,4]
 * List B: [1,5]
 * No intersection, return null
 * 
 * Constraints:
 * - The number of nodes of listA is in the m
 * - The number of nodes of listB is in the n
 * - 1 <= m, n <= 3 * 10^4
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

// ========== METHOD 1: Two-Pointer with Length Difference (Optimal) ==========
// Time Complexity: O(m + n), Space Complexity: O(1)
Node* getIntersectionNode(Node* headA, Node* headB) {
    if (!headA || !headB) return nullptr;
    
    // Step 1: Find lengths of both lists
    int lenA = getLength(headA);
    int lenB = getLength(headB);
    
    // Step 2: Move the longer list pointer ahead by the difference
    Node* currA = headA;
    Node* currB = headB;
    
    if (lenA > lenB) {
        for (int i = 0; i < lenA - lenB; i++) {
            currA = currA->next;
        }
    } else {
        for (int i = 0; i < lenB - lenA; i++) {
            currB = currB->next;
        }
    }
    
    // Step 3: Move both pointers together until they meet
    while (currA && currB) {
        if (currA == currB) {
            return currA;  // Found intersection
        }
        currA = currA->next;
        currB = currB->next;
    }
    
    return nullptr;  // No intersection
}

// Hashmap approach fixed: Avoid duplicate function, rename for clarity, and avoid shadowing main logic
Node* getIntersectionNodeHashmap(Node* headA, Node* headB) {
    if (!headA || !headB) return nullptr;

    unordered_map<Node*, bool> seen;
    Node* curr = headA;
    while (curr) {
        seen[curr] = true;
        curr = curr->next;
    }
    curr = headB;
    while (curr) {
        if (seen.count(curr)) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

int main() {
    
    // Test case 1: Lists intersect at node with value 8
    // List A: [4,1,8,4,5]
    // List B: [5,6,1,8,4,5]
    // Create intersection manually
    Node* common1 = new Node(8);
    common1->next = new Node(4);
    common1->next->next = new Node(5);
    
    Node* headA1 = new Node(4);
    headA1->next = new Node(1);
    headA1->next->next = common1;
    
    Node* headB1 = new Node(5);
    headB1->next = new Node(6);
    headB1->next->next = new Node(1);
    headB1->next->next->next = common1;
    
    cout << "\nTest case 1:" << endl;
    cout << "List A: 4 1 8 4 5" << endl;
    cout << "List B: 5 6 1 8 4 5" << endl;
    Node* intersection1 = getIntersectionNode(headA1, headB1);
    if (intersection1) {
        cout << "Intersection found at node with value: " << intersection1->data << endl;
    } else {
        cout << "No intersection found" << endl;
    }
    cout << "Expected: 8" << endl;
    
    return 0;
}

