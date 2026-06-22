/*
GeeksforGeeks: Excel Column Name from Number
Difficulty: Medium

Problem:
Given a positive integer n, return its corresponding Excel column title.
In Excel, column titles follow this pattern:
A, B, C, ..., Z, AA, AB, ..., AZ, BA, ..., ZZ, AAA, AAB, ...

Examples:
Input: n = 28
Output: AB
Explanation: 1 to 26 are A to Z, then 27 is AA and 28 is AB.

Input: n = 13
Output: M

Input: n = 5473578
Output: KYJZF

Constraints:
1 <= n <= 10^9

Core Idea:
- The Excel column numbering is similar to a base-26 representation.
- In standard base-26, digits range from 0 to 25.
- However, Excel uses 1-based indexing from A (1) to Z (26), and there is no 0 digit.
- To bridge this gap, we can subtract 1 from n (i.e. n = n - 1) at each step. This maps:
  - 1 -> 0 (which becomes 'A')
  - 26 -> 25 (which becomes 'Z')
- By decrementing n at the beginning of each step, the remainder `n % 26` maps perfectly to the characters 'A' through 'Z'.
- After extracting the character, we divide n by 26 to move to the next digit.
- Since we extract characters from least significant (rightmost) to most significant (leftmost), the result is built backwards and must be reversed at the end.

Approach:
1. Initialize an empty string `result` to store the title.
2. Loop while `n > 0`:
   - Decrement `n` by 1 (`n--`) to adjust for 1-based indexing.
   - Find the remainder `rem = n % 26`.
   - Calculate character: `(char)('A' + rem)` and append it to `result`.
   - Update `n` to `n / 26`.
3. Reverse `result` to restore the correct order.
4. Return `result`.

Time Complexity: O(log_26(n)) — Since we divide n by 26 in each iteration, the loop runs logarithmic times.
Space Complexity: O(1) auxiliary space (excluding the string used to return the output).

GFG Link: https://www.geeksforgeeks.org/problems/excel-column-name2411/1
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string colName(long long int n) {
        string result = "";
        
        while (n > 0) {
            // Adjust for 1-based indexing
            n--;
            
            // Extract the current character
            result.push_back((char)('A' + (n % 26)));
            
            // Move to the next digit
            n /= 26;
        }
        
        // Reverse the result since we built it from right to left
        reverse(result.begin(), result.end());
        
        return result;
    }
};

/*
Dry Run — Example:
n = 28

1. n > 0 is true.
   - n-- -> n = 27
   - char = 'A' + (27 % 26) = 'A' + 1 = 'B'
   - result = "B"
   - n /= 26 -> n = 1

2. n > 0 is true.
   - n-- -> n = 0
   - char = 'A' + (0 % 26) = 'A' + 0 = 'A'
   - result = "BA"
   - n /= 26 -> n = 0

3. n > 0 is false. Loop terminates.

Reverse result -> "AB".
Output: "AB"
*/
