/*
    Problem Name: Postfix Evaluation
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 150

    Problem Statement:
    Given an array of strings `arr[]` representing a valid arithmetic expression in Postfix Notation (Reverse Polish Notation),
    evaluate the expression and return an integer representing its value.

    Notes:
    - Division between two integers computes the floor value: floor(5 / 3) = 1, floor(-5 / 3) = -2.
    - Operators supported: "+", "-", "*", "/", "^" (exponentiation).

    Examples:
    Input: arr = ["2", "3", "1", "*", "+", "9", "-"]
    Output: -4
    Explanation: 2 + (3 * 1) - 9 = 5 - 9 = -4.

    Input: arr = ["2", "3", "^", "10", "+"]
    Output: 18
    Explanation: 2 ^ 3 + 10 = 8 + 10 = 18.

    Constraints:
    3 <= arr.size() <= 10^3
    arr[i] is an operator (+, -, *, /, ^) or an integer in range [-10^4, 10^4]

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(N) (operand stack space)

    Approach: Operand Stack Evaluation (Optimal O(N) Time, O(N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Postfix expressions are evaluated naturally using a Stack:
       - Operands are pushed onto the stack.
       - When an operator is encountered:
         * Pop the top two elements: `val2` (second operand) and `val1` (first operand).
         * Compute `result = val1 (op) val2`.
         * Push `result` back onto the stack.
    2. Floor Division Handling:
       - C++ integer division truncates toward zero (-5 / 3 = -1).
       - To achieve true floor division (-5 / 3 = -2):
         If remainder is non-zero and operands have opposite signs, decrement result by 1.
    3. Exponentiation (`^`):
       - Compute power `pow(val1, val2)` using binary exponentiation.
    4. At the end of traversal, `st.top()` contains the final evaluated expression value.
    5. Time: O(N), Space: O(N).

    DRY RUN:
    Example: arr = ["2", "3", "1", "*", "+", "9", "-"]
    - "2": push(2) -> st = [2]
    - "3": push(3) -> st = [2, 3]
    - "1": push(1) -> st = [2, 3, 1]
    - "*": val2 = 1, val1 = 3 -> 3 * 1 = 3 -> push(3) -> st = [2, 3]
    - "+": val2 = 3, val1 = 2 -> 2 + 3 = 5 -> push(5) -> st = [5]
    - "9": push(9) -> st = [5, 9]
    - "-": val2 = 9, val1 = 5 -> 5 - 9 = -4 -> push(-4) -> st = [-4]
    - Final result = -4.
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

// ============================================================================
// Approach: Stack-Based Postfix Evaluation (Optimal O(N) Time, O(N) Space)
// ============================================================================
class SolutionStack {
private:
    // Helper function for floor division (handles negative numbers correctly)
    int floorDiv(int a, int b) {
        int res = a / b;
        int rem = a % b;
        if (rem != 0 && ((a < 0) ^ (b < 0))) {
            res--;
        }
        return res;
    }

    // Helper function for exponentiation
    long long power(long long base, long long exp) {
        long long res = 1;
        while (exp > 0) {
            if (exp & 1) res *= base;
            base *= base;
            exp >>= 1;
        }
        return res;
    }

    bool isOperator(const string& s) {
        return (s == "+" || s == "-" || s == "*" || s == "/" || s == "^");
    }

public:
    int evaluate(vector<string>& arr) {
        stack<int> st;

        for (const string& token : arr) {
            if (isOperator(token)) {
                int val2 = st.top(); st.pop();
                int val1 = st.top(); st.pop();

                if (token == "+") {
                    st.push(val1 + val2);
                } else if (token == "-") {
                    st.push(val1 - val2);
                } else if (token == "*") {
                    st.push(val1 * val2);
                } else if (token == "/") {
                    st.push(floorDiv(val1, val2));
                } else if (token == "^") {
                    st.push((int)power(val1, val2));
                }
            } else {
                // Token is an operand (number)
                st.push(stoi(token));
            }
        }

        return st.top();
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int evaluate(vector<string>& arr) {
        SolutionStack solver;
        return solver.evaluate(arr);
    }
};
