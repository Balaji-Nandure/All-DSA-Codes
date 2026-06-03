/*
GeeksforGeeks: Multiply two strings
Difficulty: Medium

Problem:
Given two numbers as strings s1 and s2. Calculate their Product.
Note: The numbers can be negative and You are not allowed to use any built-in function or convert the strings to integers. There can be zeros in the beginning of the numbers. You don't need to specify '+' sign in the beginning of positive numbers.

Examples:
Input: s1 = "0033", s2 = "2"
Output: "66"
Explanation: 33 * 2 = 66

Input: s1 = "11", s2 = "23"
Output: "253"
Explanation: 11 * 23  = 253

Input: s1 = "123", s2 = "0"
Output: "0"

Core Idea:
This problem is a classic application of the "School Mathematics" multiplication algorithm.
Just like we multiply huge numbers on paper, we can multiply strings character by character.
The mathematical rule states that the maximum number of digits in the product of two numbers of lengths `N` and `M` will be `N + M`.
Thus, we can use a `vector<int>` of size `N + M` to hold our positional digit values!

When multiplying a digit from `s1` at index `i` and a digit from `s2` at index `j`:
- The core product belongs exactly at the position `i + j + 1` in our result array.
- The carry-over belongs at the position `i + j` in our result array (one spot to the left).
By looping backwards (right to left) through both strings, we can perfectly simulate standard grade-school multiplication and cleanly handle carries without overflowing any variables!

Approach:
1. Extract signs: If `s1` or `s2` starts with `-`, record it and slice the string to remove the sign.
2. Strip leading zeros from both strings. If either string evaluates to empty (meaning it was just "0"), return "0" immediately.
3. Initialize a `vector<int> result` of size `N + M` initialized to 0.
4. Loop `i` from `N-1` down to 0, and `j` from `M-1` down to 0:
   - Multiply the two characters: `mul = (s1[i] - '0') * (s2[j] - '0')`.
   - Add this multiplication to whatever value was already sitting in our result array at that position: `sum = mul + result[i + j + 1]`.
   - Update the current position with the last digit: `result[i + j + 1] = sum % 10`.
   - Add the carry to the next leftward position: `result[i + j] += sum / 10`.
5. Iterate through the `result` vector, skip any leading zeros, and append the digits to a final string.
6. If the mathematically combined sign is negative, prepend a `-` to the final string and return it.

Time Complexity: O(N * M) where N and M are the lengths of s1 and s2. The nested loops iterate exactly N * M times. With max lengths 10^3, this is 10^6 operations, completely optimal.
Space Complexity: O(N + M) auxiliary space to store the result vector array.

GFG Link: https://www.geeksforgeeks.org/problems/multiply-two-strings/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string multiplyStrings(string s1, string s2) {
        // 1. Extract Signs
        int sign1 = 1, sign2 = 1;
        if (s1.length() > 0 && s1[0] == '-') {
            sign1 = -1;
            s1 = s1.substr(1);
        }
        if (s2.length() > 0 && s2[0] == '-') {
            sign2 = -1;
            s2 = s2.substr(1);
        }
        
        // 2. Strip leading zeros
        int start1 = 0;
        while (start1 < s1.length() && s1[start1] == '0') start1++;
        s1 = s1.substr(start1);
        
        int start2 = 0;
        while (start2 < s2.length() && s2[start2] == '0') start2++;
        s2 = s2.substr(start2);
        
        // If either number is effectively 0, product is 0
        if (s1.empty() || s2.empty()) return "0";
        
        int n = s1.length();
        int m = s2.length();
        
        // Product of lengths N and M can have at most N + M digits
        // (Using vector over standard array for max safety and performance)
        vector<int> result(n + m, 0);
        
        // 3. School Mathematics Multiplication
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int mul = (s1[i] - '0') * (s2[j] - '0');
                
                // Add the previous carry to current multiplication
                int sum = mul + result[i + j + 1];
                
                // Store digit at current position
                result[i + j + 1] = sum % 10;
                
                // Store carry at the next (leftward) position
                result[i + j] += sum / 10;
            }
        }
        
        // 4. Convert vector back to string
        string final_res = "";
        int i = 0;
        
        // Skip leading zeros in the result array (if any)
        while (i < result.size() && result[i] == 0) {
            i++;
        }
        
        while (i < result.size()) {
            final_res += to_string(result[i]);
            i++;
        }
        
        // 5. Apply the final mathematical sign
        if (sign1 * sign2 == -1) {
            final_res = "-" + final_res;
        }
        
        return final_res;
    }
};

/*
Dry Run — Example: 
s1 = "11", s2 = "23"

N = 2, M = 2. 
result array size = N + M = 4 -> [0, 0, 0, 0]

Iteration 1: i=1 ('1'), j=1 ('3')
  mul = 1 * 3 = 3
  sum = 3 + result[3] (0) = 3
  result[3] = 3 % 10 = 3
  result[2] += 3 / 10 = 0
  result array: [0, 0, 0, 3]
  
Iteration 2: i=1 ('1'), j=0 ('2')
  mul = 1 * 2 = 2
  sum = 2 + result[2] (0) = 2
  result[2] = 2 % 10 = 2
  result[1] += 2 / 10 = 0
  result array: [0, 0, 2, 3]
  
Iteration 3: i=0 ('1'), j=1 ('3')
  mul = 1 * 3 = 3
  sum = 3 + result[2] (2) = 5
  result[2] = 5 % 10 = 5
  result[1] += 5 / 10 = 0
  result array: [0, 0, 5, 3]

Iteration 4: i=0 ('1'), j=0 ('2')
  mul = 1 * 2 = 2
  sum = 2 + result[1] (0) = 2
  result[1] = 2 % 10 = 2
  result[0] += 2 / 10 = 0
  result array: [0, 2, 5, 3]
  
Final array: [0, 2, 5, 3].
Skip leading zero. Build string -> "253".
Output: 253.
*/
