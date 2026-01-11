/*
Problem:
Create a Customized Data Structure with O(1) Operations

Design a data structure that supports the following operations in O(1) time:
- AddElement(x)        : Add an element at the end
- RemoveLastElement()  : Remove the last element
- GetLastElement()     : Return the last element
- GetMin()             : Return the minimum element present

Rules:
- All operations must run in O(1) time.
- Use standard data structures only.

Example:
AddElement(5)
AddElement(3)
AddElement(7)
GetMin()         → 3
GetLastElement() → 7
RemoveLastElement()
GetMin()         → 3

Approach:
- Use two stacks:
  mainStack → stores all elements
  minStack  → stores current minimums
- While adding:
  - Push to mainStack
  - Push to minStack if empty or x <= current min
- While removing:
  - If removed element equals top of minStack, pop minStack too
- GetMin is always available at top of minStack

Why this works:
- minStack always tracks minimum till current state
- Each element is pushed and popped at most once
- Constant time for all operations

GeeksforGeeks:
https://www.geeksforgeeks.org/design-a-stack-that-supports-getmin-in-o1-time-and-o1-extra-space/

LeetCode:
https://leetcode.com/problems/min-stack/

Time Complexity:
O(1) for all operations

Space Complexity:
O(N)
*/

class CustomDS {
    private:
        stack<int> mainStack;
        stack<int> minStack;
    
    public:
        void AddElement(int x) {
            mainStack.push(x);
            if (minStack.empty() || x <= minStack.top()) {
                minStack.push(x);
            }
        }
    
        void RemoveLastElement() {
            if (mainStack.empty()) return;
    
            int val = mainStack.top();
            mainStack.pop();
    
            if (!minStack.empty() && val == minStack.top()) {
                minStack.pop();
            }
        }
    
        int GetLastElement() {
            if (mainStack.empty()) return -1;
            return mainStack.top();
        }
    
        int GetMin() {
            if (minStack.empty()) return -1;
            return minStack.top();
        }
    };
    