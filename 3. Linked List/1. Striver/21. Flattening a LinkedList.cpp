/*
 * Problem: Flattening a Linked List (GeeksforGeeks / Interview Problem)
 * 
 * Given a Linked List of size N, where every node represents a sub-linked-list 
 * and contains two pointers:
 * (i) a next pointer to the next node,
 * (ii) a bottom pointer to a linked list where this node is head.
 * 
 * Each of the sub-linked-list is in sorted order.
 * Flatten the Link List such that all the nodes appear in a single level 
 * while maintaining the sorted order.
 * 
 * Note: The flattened list will be printed using the bottom pointer instead 
 * of next pointer.
 * 
 * Example 1:
 * Input:
 * 5 -> 10 -> 19 -> 28
 * |     |     |     |
 * 7     20    22   35
 * |           |     |
 * 8          50    40
 * |                 |
 * 30               45
 * 
 * Output: 5->7->8->10->19->20->22->28->30->35->40->45->50
 * 
 */

#include <bits/stdc++.h>
using namespace std;

// Node class represents a node in the multi-level linked list
class Node {
public:
    int data;      // Data value
    Node* next;    // Pointer to next node (horizontal)
    Node* bottom;   // Pointer to bottom node (vertical/child)

    // Constructor with data, next, and bottom
    Node(int data, Node* next = nullptr, Node* bottom = nullptr) {
        this->data = data;
        this->next = next;
        this->bottom = bottom;
    }
};

// Helper function to print flattened linked list (using bottom pointer)
void printFlattenedList(Node* head) {
    Node* curr = head;
    while(curr) {
        cout << curr->data;
        if (curr->bottom) {
            cout << " -> ";
        }
        curr = curr->bottom;
    }
    cout << endl;
}

// Helper function to print multi-level structure (for visualization)
void printMultiLevelList(Node* head) {
    Node* curr = head;
    while(curr) {
        cout << curr->data;
        Node* bottom = curr->bottom;
        if (bottom) {
            cout << " -> ";
            while(bottom) {
                cout << bottom->data;
                if (bottom->bottom) cout << " -> ";
                bottom = bottom->bottom;
            }
        }
        cout << " | ";
        curr = curr->next;
    }
    cout << endl;
}

// ========== METHOD 1: Merge One by One (Iterative) ==========
// Time Complexity: O(N * M), Space Complexity: O(1)

Node* mergeIterative(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    
    Node* dummy = new Node(0);
    Node* tail = dummy;
    
    while (a && b) {
        if (a->data <= b->data) {
            tail->bottom = a;
            a = a->bottom;
        } else {
            tail->bottom = b;
            b = b->bottom;
        }
        tail = tail->bottom;
    }
    
    if (a) tail->bottom = a;
    if (b) tail->bottom = b;
    
    Node* result = dummy->bottom;
    delete dummy;
    return result;
}

Node* flattenOneByOne(Node* root) {
    if (!root || !root->next) return root;
    
    Node* result = root;
    Node* curr = root->next;
    
    // Merge each subsequent list with the result
    while (curr) {
        result = mergeIterative(result, curr);
        curr = curr->next;
    }
    
    return result;
}

// Helper function to create a test multi-level linked list
Node* createTestList1() {
    // Create: 5->7->8->30, 10->20, 19->22->50, 28->35->40->45
    Node* node5 = new Node(5);
    node5->bottom = new Node(7);
    node5->bottom->bottom = new Node(8);
    node5->bottom->bottom->bottom = new Node(30);
    
    Node* node10 = new Node(10);
    node10->bottom = new Node(20);
    
    Node* node19 = new Node(19);
    node19->bottom = new Node(22);
    node19->bottom->bottom = new Node(50);
    
    Node* node28 = new Node(28);
    node28->bottom = new Node(35);
    node28->bottom->bottom = new Node(40);
    node28->bottom->bottom->bottom = new Node(45);
    
    node5->next = node10;
    node10->next = node19;
    node19->next = node28;
    
    return node5;
}

int main() {
    cout << "========== METHOD 1: Recursive Merge (Optimal) ==========" << endl;
    
    // Test case 1
    Node* head1 = createTestList1();
    cout << "\nTest case 1:" << endl;
    cout << "Original structure: 5->7->8->30 | 10->20 | 19->22->50 | 28->35->40->45" << endl;
    head1 = flatten(head1);
    cout << "Flattened: ";
    printFlattenedList(head1);
    cout << "Expected: 5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 30 -> 35 -> 40 -> 45 -> 50" << endl;
    
    return 0;
}

