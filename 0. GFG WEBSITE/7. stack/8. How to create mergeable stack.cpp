/*
Problem:
How to Create a Mergeable Stack

Design a stack data structure supporting the following operations:
- push(Stack s, x)  : Add element x to stack s
- pop(Stack s)      : Remove and return the top element from stack s
- merge(Stack s1, Stack s2) : Merge contents of s2 into s1

After merge:
- Stack s1 contains all its elements followed by elements of s2
- Stack s2 becomes empty

Rules:
- merge operation must run in O(1) time
- Stack must follow LIFO order

Example:
s1: 3 -> 2 -> 1
s2: 6 -> 5 -> 4

After merge(s1, s2):
s1: 3 -> 2 -> 1 -> 6 -> 5 -> 4
s2: empty

Approach:
- Implement stack using a singly linked list
- Maintain both head (top) and tail pointers
- push and pop work on head
- merge is done by pointer linking using tail

GeeksforGeeks:
https://www.geeksforgeeks.org/mergeable-stack/

LeetCode:
No direct equivalent problem.

Time Complexity:
push  → O(1)
pop   → O(1)
merge → O(1)

Space Complexity:
O(N)
*/

struct Node {
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Stack {
private:
    Node* head;
    Node* tail;

public:
    Stack() {
        head = NULL;
        tail = NULL;
    }

    void push(int x) {
        Node* node = new Node(x);
        node->next = head;
        head = node;
        if (tail == NULL) tail = node;
    }

    int pop() {
        if (head == NULL) return -1;

        int val = head->data;
        Node* temp = head;
        head = head->next;
        if (head == NULL) tail = NULL;
        delete temp;
        return val;
    }

    void merge(Stack& s2) {
        if (s2.head == NULL) return;

        if (head == NULL) {
            head = s2.head;
            tail = s2.tail;
        } else {
            tail->next = s2.head;
            tail = s2.tail;
        }

        s2.head = NULL;
        s2.tail = NULL;
    }
};
