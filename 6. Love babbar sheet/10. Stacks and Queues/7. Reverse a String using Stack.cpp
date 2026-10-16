/**
 * Problem: Reverse a String using Stack
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Reverse an Array / String" in the Arrays chapter, we used two pointers swapping in-place.
 * - Here, the reversal is explicitly achieved through the structural property of a Stack:
 *   Last-In, First-Out (LIFO) inherently inverts the sequence of any streamed data.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - By pushing each character of string S onto a stack, the first character sits at the bottom
 *   and the last character sits at the top.
 * - Popping characters sequentially reconstructs the string in reverse order.
 * 
 * TIME COMPLEXITY:
 * - O(N) where N is length of the string (N pushes + N pops).
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for the stack.
 */

#include <iostream>
#include <stack>
#include <string>

std::string reverseStringUsingStack(std::string s) {
    std::stack<char> st;

    // Push all characters onto stack
    for (char c : s) {
        st.push(c);
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Overwrite string from left to right using elements popped from top of stack.
    for (int i = 0; i < (int)s.size(); i++) {
        s[i] = st.top();
        st.pop();
    }

    return s;
}

int main() {
    std::string str = "GeeksforGeeks";
    std::cout << "Original: " << str << "\n";
    std::string rev = reverseStringUsingStack(str);
    std::cout << "Reversed: " << rev << "\n";
    return 0;
}
