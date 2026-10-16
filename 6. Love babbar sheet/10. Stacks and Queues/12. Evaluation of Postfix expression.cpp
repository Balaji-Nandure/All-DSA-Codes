/**
 * Problem: Evaluation of Postfix Expression
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In Infix evaluation, we had to handle operator precedence and parenthesis matching using two stacks.
 * - In Postfix (Reverse Polish Notation), operators follow their operands, meaning evaluation order
 *   is strictly unambiguous and requires only a single operand stack without any precedence rules.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Single Operand Stack:
 *   - Read string from left to right.
 *   - When an operand is encountered, push it onto the stack.
 *   - When an operator is encountered:
 *     - Pop `val2` (the right operand) first!
 *     - Pop `val1` (the left operand) second!
 *     - Compute `result = val1 (op) val2` and push back onto the stack.
 *   - At the end, the stack top contains the evaluated expression.
 * 
 * TIME COMPLEXITY:
 * - O(N) where N is length of the postfix expression.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for the operand stack.
 */

#include <iostream>
#include <stack>
#include <string>
#include <cctype>

int evaluatePostfix(const std::string& exp) {
    std::stack<int> st;

    for (int i = 0; i < (int)exp.length(); i++) {
        if (exp[i] == ' ') continue;

        // If operand
        if (isdigit(exp[i])) {
            st.push(exp[i] - '0');
        } else {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // The first popped element is the RIGHT-hand operand; the second popped is the LEFT-hand operand!
            int val2 = st.top(); st.pop();
            int val1 = st.top(); st.pop();

            switch (exp[i]) {
                case '+': st.push(val1 + val2); break;
                case '-': st.push(val1 - val2); break;
                case '*': st.push(val1 * val2); break;
                case '/': st.push(val1 / val2); break;
            }
        }
    }

    return st.top();
}

int main() {
    std::string exp = "231*+9-";
    // 2 + (3 * 1) - 9 = 5 - 9 = -4
    std::cout << exp << " = " << evaluatePostfix(exp) << "\n"; // -4

    return 0;
}
