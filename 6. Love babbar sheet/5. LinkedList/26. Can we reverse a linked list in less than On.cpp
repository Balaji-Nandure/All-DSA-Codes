/**
 * ============================================================================
 * Problem: Can We Reverse a Linked List in Less Than O(N)?
 * Category: LinkedList / Architecture & Design Patterns
 * 
 * Conceptual Question:
 * Can a linked list be reversed in less than O(N) time (e.g. O(1) or O(log N))?
 * 
 * Detailed Theoretical & Practical Analysis:
 * ----------------------------------------------------------------------------
 * 1. Standard Singly/Doubly Linked List (Physical Reversal):
 *    - Answer: NO.
 *    - Theoretical Proof: A standard linked list is a directed graph where each 
 *      of the N nodes contains a concrete pointer field (`next`) stored at a 
 *      distinct physical memory address.
 *      To invert the graph such that node (i+1) points to node i, all N pointer
 *      variables must be rewritten. Any algorithm that mutates N distinct memory 
 *      words has an information-theoretic lower bound of Omega(N).
 * 
 * 2. XOR Linked List (Mathematical Bitwise Duality):
 *    - Answer: YES! Reversible in O(1) time.
 *    - In an XOR Linked List, each node stores a single pointer field:
 *        `npx = address(prev) ^ address(next)`
 *    - Since XOR is symmetric and commutative:
 *        `address(prev) ^ address(next) == address(next) ^ address(prev)`
 *    - Therefore, the exact same internal representation serves both forward
 *      and reverse traversals!
 *    - To reverse an XOR linked list, we simply SWAP the `head` and `tail` pointers:
 *        `swap(head, tail);`  <--- Takes strictly O(1) time!
 * 
 * 3. Lazy Wrapper Pattern (Deque / Direction Flag):
 *    - Answer: YES! In O(1) time.
 *    - Wrap a Doubly Linked List with a boolean state flag `isReversed`.
 *    - Reversal simply toggles `isReversed = !isReversed` in O(1) time.
 *    - Operations (push, pop, traversal) inspect `isReversed` to determine whether
 *      to follow `next` or `prev`.
 * ============================================================================
 */

#include <iostream>
#include <cstdint>

using namespace std;

// ============================================================================
// Implementation 1: XOR Linked List (O(1) Time Reversal)
// ============================================================================
struct XORNode {
    int data;
    XORNode* npx; // XOR of prev and next addresses
    XORNode(int val) : data(val), npx(nullptr) {}
};

class XORLinkedList {
private:
    XORNode* head;
    XORNode* tail;

    // Helper: Bitwise XOR of two node pointers
    XORNode* XOR(XORNode* a, XORNode* b) {
        return reinterpret_cast<XORNode*>(
            reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b)
        );
    }

public:
    XORLinkedList() : head(nullptr), tail(nullptr) {}

    // Insert node at the end in O(1) time
    void insertEnd(int val) {
        XORNode* newNode = new XORNode(val);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            // newNode->npx = tail ^ nullptr = tail
            newNode->npx = XOR(tail, nullptr);
            // tail->npx = (old_prev) ^ newNode
            tail->npx = XOR(XOR(tail->npx, nullptr), newNode);
            tail = newNode;
        }
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // In an XOR linked list, since (prev ^ next) == (next ^ prev), the internal links
    // are completely direction-agnostic! Reversing the entire list is achieved in O(1)
    // by merely swapping the head and tail pointers.
    void reverseInO1() {
        swap(head, tail);
    }

    // Print list from head to tail in O(N) time
    void printList() {
        XORNode* curr = head;
        XORNode* prev = nullptr;
        XORNode* next = nullptr;

        while (curr != nullptr) {
            cout << curr->data;
            // Decode next address: next = curr->npx ^ prev
            next = XOR(curr->npx, prev);
            if (next != nullptr) cout << " -> ";
            prev = curr;
            curr = next;
        }
        cout << " -> NULL\n";
    }
};

// ============================================================================
// Implementation 2: State-Machine Wrapper List (O(1) Time Reversal)
// ============================================================================
struct DLLNode {
    int data;
    DLLNode* next;
    DLLNode* prev;
    DLLNode(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class ReversibleList {
private:
    DLLNode* head;
    DLLNode* tail;
    bool isReversed;

public:
    ReversibleList() : head(nullptr), tail(nullptr), isReversed(false) {}

    void insertEnd(int val) {
        DLLNode* newNode = new DLLNode(val);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Toggling a boolean flag achieves O(1) logical reversal without modifying any pointers.
    void reverseInO1() {
        isReversed = !isReversed;
    }

    void printList() {
        if (!isReversed) {
            DLLNode* curr = head;
            while (curr) {
                cout << curr->data;
                if (curr->next) cout << " -> ";
                curr = curr->next;
            }
        } else {
            DLLNode* curr = tail;
            while (curr) {
                cout << curr->data;
                if (curr->prev) cout << " -> ";
                curr = curr->prev;
            }
        }
        cout << " -> NULL\n";
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== Demonstration 1: XOR Linked List O(1) Reversal ===\n";
    XORLinkedList xorList;
    xorList.insertEnd(10);
    xorList.insertEnd(20);
    xorList.insertEnd(30);
    xorList.insertEnd(40);

    cout << "Initial XOR List:  ";
    xorList.printList();

    xorList.reverseInO1();
    cout << "Reversed in O(1):  ";
    xorList.printList();

    cout << "\n=== Demonstration 2: Wrapper DLL O(1) Reversal ===\n";
    ReversibleList revList;
    revList.insertEnd(1);
    revList.insertEnd(2);
    revList.insertEnd(3);
    revList.insertEnd(4);

    cout << "Initial DLL:       ";
    revList.printList();

    revList.reverseInO1();
    cout << "Reversed in O(1):  ";
    revList.printList();

    return 0;
}

/**
 * SUMMARY OF INTERVIEW KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Physical Reversal of a standard singly linked list CANNOT be done in < O(N)
 *    because N independent heap pointer words must be overwritten.
 * 2. XOR Linked List solves this physically in O(1) by exploiting the algebraic
 *    involution property of XOR: A ^ B = B ^ A.
 * 3. Lazy Evaluation / Wrapper Pattern solves this logically in O(1) by maintaining
 *    a direction flag and swapping semantics of next and prev.
 */
