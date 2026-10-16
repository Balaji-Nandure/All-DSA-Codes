/**
 * Problem: Design Stack getMin() in O(1) time and O(1) extra space
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A standard Min-Stack uses an auxiliary stack `min_st` that duplicates space (O(N) extra space).
 * - Here, we are strictly constrained to O(1) AUXILIARY SPACE while maintaining O(1) time for getMin(),
 *   requiring a mathematical encoding trick to store both the value and the historical minimum state in a single number.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Mathematical Value Encoding:
 *   - Let `minEle` be the current minimum element.
 *   - If new element `x < minEle`:
 *     - We push an encoded modified value: `val = 2 * x - minEle`.
 *     - Notice that since `x < minEle`, `2 * x - minEle < x`.
 *     - Therefore, whenever `st.top() < minEle`, it acts as a sentinel flag signaling that the top is an encoded value!
 *     - Then update `minEle = x`.
 *   - On pop():
 *     - If `st.top() < minEle`, the actual value was `minEle`.
 *     - To restore previous `minEle`: `prev_min = 2 * minEle - st.top()`.
 * 
 * TIME COMPLEXITY:
 * - push(x): O(1)
 * - pop(): O(1)
 * - top(): O(1)
 * - getMin(): O(1)
 * 
 * SPACE COMPLEXITY:
 * - O(1) auxiliary space (uses only the single primary stack and one integer `minEle`).
 */

#include <iostream>
#include <stack>

class SpecialMinStack {
private:
    std::stack<long long> st;
    long long minEle;

public:
    SpecialMinStack() : minEle(0) {}

    void push(int x) {
        if (st.empty()) {
            minEle = x;
            st.push(x);
            return;
        }

        if (x < minEle) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Push encoded value (2*x - minEle) which is guaranteed to be < x, then update minEle to x.
            st.push(2LL * x - minEle);
            minEle = x;
        } else {
            st.push(x);
        }
    }

    int pop() {
        if (st.empty()) {
            std::cout << "Stack Underflow!\n";
            return -1;
        }

        long long topVal = st.top();
        st.pop();

        if (topVal < minEle) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Encoded marker detected: actual popped item is minEle, previous minEle is restored via formula.
            int actualVal = minEle;
            minEle = 2LL * minEle - topVal;
            return actualVal;
        } else {
            return topVal;
        }
    }

    int top() const {
        if (st.empty()) return -1;
        long long topVal = st.top();
        // If encoded, actual top is stored in minEle
        if (topVal < minEle) {
            return minEle;
        }
        return topVal;
    }

    int getMin() const {
        if (st.empty()) return -1;
        return minEle;
    }

    bool empty() const {
        return st.empty();
    }
};

int main() {
    SpecialMinStack s;
    s.push(3);
    s.push(5);
    std::cout << "Min: " << s.getMin() << "\n"; // 3
    s.push(2);
    s.push(1);
    std::cout << "Min: " << s.getMin() << "\n"; // 1
    std::cout << "Popped: " << s.pop() << "\n"; // 1
    std::cout << "Min after pop: " << s.getMin() << "\n"; // 2
    std::cout << "Top: " << s.top() << "\n"; // 2

    return 0;
}
