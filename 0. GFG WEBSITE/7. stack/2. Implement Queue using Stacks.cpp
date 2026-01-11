/*
Problem:
Implement Queue using Stacks

Implement a Queue using Stacks.
Queue should support:
- push(x)
- pop()
- peek()
- empty()

Rules:
- Use only stack operations.
- FIFO behavior must be maintained.

Example:
push(1)
push(2)
peek() → 1
pop()  → 1
empty() → false

Approach (Optimal – Two Stacks, Lazy Transfer):
- Use two stacks:
  stIn  → for push operations
  stOut → for pop / peek operations
- push(x):
  Push directly into stIn.
- pop() / peek():
  If stOut is empty, move all elements from stIn to stOut.
  This reverses the order and exposes the front element.
- empty():
  Queue is empty if both stacks are empty.

Why this works:
- Each element moves from stIn to stOut at most once.
- Amortized O(1) operations.
- Correct FIFO order is preserved.

GeeksforGeeks:
https://www.geeksforgeeks.org/implement-queue-using-stacks/

LeetCode:
https://leetcode.com/problems/implement-queue-using-stacks/

Time Complexity:
Push   → O(1)
Pop    → O(1) amortized
Peek   → O(1) amortized
Empty  → O(1)

Space Complexity:
O(N)
*/

class MyQueue {
    private:
        stack<int> stIn;
        stack<int> stOut;
    
    public:
        MyQueue() {}
    
        void push(int x) {
            // Always push to input stack
            stIn.push(x);
        }
    
        int pop() {
            // If output stack is empty, transfer elements
            if (stOut.empty()) {
                while (!stIn.empty()) {
                    stOut.push(stIn.top());
                    stIn.pop();
                }
            }
            int ans = stOut.top();
            stOut.pop();
            return ans;
        }
    
        int peek() {
            // Ensure front element is on top of stOut
            if (stOut.empty()) {
                while (!stIn.empty()) {
                    stOut.push(stIn.top());
                    stIn.pop();
                }
            }
            return stOut.top();
        }
    
        bool empty() {
            return stIn.empty() && stOut.empty();
        }
    };
    