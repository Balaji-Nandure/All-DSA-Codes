/*
GeeksforGeeks: Stack using Linked List
Difficulty: Easy

Problem:
Implement a Stack using a Linked List. The stack has dynamic size and can grow until memory is available.
The Stack must support the following operations:
(i) push(x): Insert an element x at the top of the stack.
(ii) pop(): Remove the element from the top of the stack.
(iii) peek(): Return top element if not empty, else -1.
(iv) isEmpty(): Return true if the stack is empty else return false.
(v) size(): Return the number of elements currently in the stack.

Example 1:
Input: q = 7, queries[][] = [[1, 5], [1, 3], [1, 4], [3], [2], [5], [4]]
Output: [4, 2, false]
Explanation: Queries on queue are as follows:
push(5): Insert 5 at the top of the stack.
push(3): Insert 3 at the top of the stack.
push(4): Insert 4 at the top of the stack.
peek(): Return the top element i.e 4.
pop(): Remove the top element 4 from the stack.
size(): Stack contains 2 elements return 2.
isEmpty(): Stack is not empty return false.

Example 2:
Input: q = 4, queries[][] = [[4], [3], [1, 10], [5]]
Output: [true, -1, 1]
Explanation: Queries on queue are as follows:
isEmpty(): Stack is empty return true.
peek(): Stack is empty return -1.
push(10): Insert 10 at the top of the stack.
size(): Stack contains 1 element return 1.

Core Idea:
A stack follows Last In First Out (LIFO). When using a linked list to implement a stack, we can keep track of the `top` element.
- `push(x)`: Create a new node with data `x`. Point its next to the current `top`. Update `top` to point to this new node. This is O(1).
- `pop()`: If the stack is empty, return -1. Otherwise, remember the top node's data. Move `top` to `top->next`. Delete the old top node and return its data. This is O(1).
- `peek()`: If empty, return -1. Else, return `top->data`. This is O(1).
- `isEmpty()`: Return true if `top` is NULL, false otherwise.
- `size()`: We can maintain a separate variable `count` that increments on push and decrements on pop, making it O(1).

Approach:
1. Define a `StackNode` struct/class containing `data` and a `next` pointer.
2. The `MyStack` class has a `top` pointer (initially NULL) and an integer `count` (initially 0).
3. Implement the operations as described in the Core Idea.

Time Complexity: O(1) for all operations - push, pop, peek, isEmpty, size.
Space Complexity: O(N) where N is the number of elements in the stack, as we use dynamic memory allocation for nodes.

GFG Link:
https://www.geeksforgeeks.org/problems/implement-stack-using-linked-list/1
*/

#include <iostream>

using namespace std;

/* Structure of linked list Node
class Node {
  public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = nullptr;
    }
};
*/

class myStack {
  private:
    Node* top;
    int count;
    
  public:
    myStack() {
        top = nullptr;
        count = 0;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void push(int x) {
        Node* newNode = new Node(x);
        newNode->next = top;
        top = newNode;
        count++;
    }

    void pop() {
        if (top == nullptr) return;
        Node* temp = top;
        top = top->next;
        delete temp;
        count--;
    }

    int peek() {
        if (top == nullptr) return -1;
        return top->data;
    }

    int size() {
        return count;
    }
};

/*
Dry Run — Example 1:
Queries: [[1, 5], [1, 3], [1, 4], [3], [2], [5], [4]]

Initial state:
MyStack: top = NULL, count = 0

Query 1: push(5)
- new node(5)
- node(5)->next = NULL
- top = node(5)
- count = 1
Stack: 5 -> NULL

Query 2: push(3)
- new node(3)
- node(3)->next = node(5)
- top = node(3)
- count = 2
Stack: 3 -> 5 -> NULL

Query 3: push(4)
- new node(4)
- node(4)->next = node(3)
- top = node(4)
- count = 3
Stack: 4 -> 3 -> 5 -> NULL

Query 4: peek()
- stack is not empty (top != NULL)
- returns top->data = 4

Query 5: pop()
- stack is not empty
- temp = top (node 4)
- poppedData = 4
- top = top->next (node 3)
- delete temp
- count = 2
Stack: 3 -> 5 -> NULL
- returns 4

Query 6: size()
- returns count = 2

Query 7: isEmpty()
- top != NULL
- returns false
*/
