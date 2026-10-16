/**
 * Problem: Design a Stack with Find Middle and Delete Middle in O(1) Time
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A standard stack only allows access to the top element in O(1). Accessing or deleting an interior
 *   element like the middle requires O(N) operations via auxiliary stacks.
 * - Here, we must achieve BOTH findMiddle() AND deleteMiddle() in strict O(1) time alongside standard push/pop.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Why not an Array? Deleting the middle element in an array forces an O(N) shift of subsequent elements.
 * - Why not a Singly Linked List? Deleting a node requires knowledge of its predecessor, which cannot be moved
 *   backward in O(1).
 * - Doubly Linked List (DLL) + Mid Pointer:
 *   - DLL allows O(1) node deletion by rewiring `mid->prev->next` and `mid->next->prev`.
 *   - Maintaining a `mid` pointer and shifting it forward when count becomes odd/even during push,
 *     and backward during pop, achieves O(1) operations for ALL methods!
 * 
 * TIME COMPLEXITY:
 * - push(x): O(1)
 * - pop(): O(1)
 * - findMiddle(): O(1)
 * - deleteMiddle(): O(1)
 * 
 * SPACE COMPLEXITY:
 * - O(N) for DLL nodes.
 */

#include <iostream>

struct DLLNode {
    int data;
    DLLNode* prev;
    DLLNode* next;
    DLLNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class MidStack {
private:
    DLLNode* head; // Points to top of the stack
    DLLNode* mid;  // Points to middle node
    int count;

public:
    MidStack() : head(nullptr), mid(nullptr), count(0) {}

    ~MidStack() {
        while (head) {
            DLLNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(int x) {
        DLLNode* node = new DLLNode(x);
        node->next = head;
        if (head) {
            head->prev = node;
        }
        head = node;
        count++;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // When size transitions from 1 to 2, mid points to head or next.
        // Mid shifts to predecessor (closer to head) on odd count.
        if (count == 1) {
            mid = head;
        } else if (count % 2 != 0) {
            mid = mid->prev;
        }
    }

    int pop() {
        if (count == 0) {
            std::cout << "Stack Underflow!\n";
            return -1;
        }
        DLLNode* temp = head;
        int val = temp->data;
        head = head->next;
        if (head) head->prev = nullptr;
        count--;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // On even count after deletion, mid shifts down towards bottom (mid->next).
        if (count % 2 == 0) {
            mid = mid ? mid->next : nullptr;
        }

        delete temp;
        return val;
    }

    int findMiddle() const {
        if (count == 0) return -1;
        return mid->data;
    }

    int deleteMiddle() {
        if (count == 0) return -1;
        DLLNode* toDelete = mid;
        int val = toDelete->data;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // O(1) deletion by rewiring both adjacent pointers around mid.
        if (toDelete->prev) toDelete->prev->next = toDelete->next;
        if (toDelete->next) toDelete->next->prev = toDelete->prev;
        if (toDelete == head) head = toDelete->next;

        count--;
        if (count % 2 == 0) {
            mid = toDelete->next;
        } else {
            mid = toDelete->prev;
        }

        delete toDelete;
        return val;
    }

    int size() const {
        return count;
    }
};

int main() {
    MidStack ms;
    ms.push(11);
    ms.push(22);
    ms.push(33);
    ms.push(44);
    ms.push(55);

    std::cout << "Middle element: " << ms.findMiddle() << "\n"; // 33
    std::cout << "Deleted middle: " << ms.deleteMiddle() << "\n"; // 33
    std::cout << "New middle: " << ms.findMiddle() << "\n"; // 44 or 22 depending on rounding
    std::cout << "Popped top: " << ms.pop() << "\n"; // 55
    std::cout << "Middle after pop: " << ms.findMiddle() << "\n"; // 22

    return 0;
}
