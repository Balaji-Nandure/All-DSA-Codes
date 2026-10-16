/**
 * Problem: Arithmetic Expression Evaluation (Infix Evaluation)
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Simple linear scans cannot evaluate mathematical expressions because operators have varying precedence
 *   and parentheses override operator order.
 * - Here, we parse and evaluate standard Infix expressions in a single pass using Dijkstra's Two-Stack Algorithm.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Two-Stack Shunting Algorithm:
 *   - `values`: Stores integer operands.
 *   - `ops`: Stores operators (`+`, `-`, `*`, `/`, `(`).
 * - Precedence Rules:
 *   - High precedence (`*`, `/` = 2) must execute before lower precedence (`+`, `-` = 1).
 *   - When reading an operator `op`: while `ops.top()` has precedence >= `op`, apply `ops.top()` to top two values.
 *   - Open parenthesis `(` is pushed onto `ops`.
 *   - Close parenthesis `)` forces evaluation of all operators until matching `(` is popped.
 * 
 * TIME COMPLEXITY:
 * - O(N): Each token is pushed and popped at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(N) for values and ops stacks.
 */

#include <iostream>
#include <stack>
#include <string>
#include <cctype>

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int evaluateInfix(const std::string& tokens) {
    std::stack<int> values;
    std::stack<char> ops;

    for (int i = 0; i < (int)tokens.length(); i++) {
        if (tokens[i] == ' ') continue;

        if (tokens[i] == '(') {
            ops.push(tokens[i]);
        } else if (isdigit(tokens[i])) {
            int val = 0;
            while (i < (int)tokens.length() && isdigit(tokens[i])) {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }
            i--; // Step back after multi-digit parse
            values.push(val);
        } else if (tokens[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty()) ops.pop(); // Pop '('
        } else {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // While the operator on stack top has equal or higher precedence, resolve it first.
            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(tokens[i]);
        }
    }

    // Flush remaining operators
    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

int main() {
    std::string expr1 = "10 + 2 * 6";
    std::string expr2 = "100 * ( 2 + 12 ) / 14";

    std::cout << expr1 << " = " << evaluateInfix(expr1) << "\n"; // 22
    std::cout << expr2 << " = " << evaluateInfix(expr2) << "\n"; // 100

    return 0;
}
