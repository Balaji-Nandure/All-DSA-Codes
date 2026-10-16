/**
 * Problem: Implement Stack from Scratch
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Previously, we relied on STL `std::stack` or recursion call stacks to handle LIFO behaviour.
 * - Here, we build the fundamental Last-In-First-Out (LIFO) primitive data structure from bare metal using both
 *   dynamic arrays and linked lists, tracking capacity, overflow, underflow, and pointer/index mechanics.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Array-based stack: Provides contiguous memory locality and true O(1) cache-friendly push/pop/peek operations.
 * - Linked-List based stack: Offers dynamic sizing without capacity limits or reallocation overhead.
 * - Array implementation is standard for competitive programming due to zero heap allocation during execution.
 * 
 * TIME COMPLEXITY:
 * - push(x): O(1) amortized / worst-case O(1) with fixed array
 * - pop(): O(1)
 * - top(): O(1)
 * - isEmpty(): O(1)
 * 
 * SPACE COMPLEXITY:
 * - O(N) where N is maximum capacity / elements stored.
 */

#include <iostream>
#include <vector>
#include <stdexcept>

class ArrayStack {
private:
    int* arr;
    int topIndex;
    int capacity;

public:
    ArrayStack(int size = 1000) {
        capacity = size;
        arr = new int[capacity];
        topIndex = -1; // Empty state
    }

    ~ArrayStack() {
        delete[] arr;
    }

    void push(int x) {
        if (topIndex >= capacity - 1) {
            std::cout << "Stack Overflow!\n";
            return;
        }
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Increment topIndex first, then assign element into the newly reserved slot.
        arr[++topIndex] = x;
    }

    int pop() {
        if (isEmpty()) {
            std::cout << "Stack Underflow!\n";
            return -1;
        }
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Return element at topIndex and decrement pointer in one atomic step.
        return arr[topIndex--];
    }

    int top() const {
        if (isEmpty()) {
            std::cout << "Stack is Empty!\n";
            return -1;
        }
        return arr[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    int size() const {
        return topIndex + 1;
    }
};

// Linked List Node Implementation
struct StackNode {
    int data;
    StackNode* next;
    StackNode(int val) : data(val), next(nullptr) {}
};

class LinkedListStack {
private:
    StackNode* head;
    int count;

public:
    LinkedListStack() : head(nullptr), count(0) {}

    ~LinkedListStack() {
        while (head) {
            StackNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(int x) {
        StackNode* node = new StackNode(x);
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // New node points to existing head, head becomes new node (O(1) insertion at head).
        node->next = head;
        head = node;
        count++;
    }

    int pop() {
        if (isEmpty()) {
            std::cout << "Stack Underflow!\n";
            return -1;
        }
        StackNode* temp = head;
        int val = temp->data;
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Move head forward before deallocating old top node.
        head = head->next;
        delete temp;
        count--;
        return val;
    }

    int top() const {
        if (isEmpty()) return -1;
        return head->data;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int size() const {
        return count;
    }
};

int main() {
    ArrayStack s(5);
    s.push(10);
    s.push(20);
    s.push(30);
    std::cout << "Top element: " << s.top() << "\n"; // 30
    std::cout << "Popped: " << s.pop() << "\n";       // 30
    std::cout << "Top after pop: " << s.top() << "\n"; // 20
    std::cout << "Size: " << s.size() << "\n";         // 2

    return 0;
}
