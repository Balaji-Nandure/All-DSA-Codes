/*
GeeksforGeeks: Balanced Splits of a Binary String
Difficulty: Easy

Given binary string s . find the maximum number of substrings it can be splitted into such that all substrings have equal number of 0s and 1s. If it is not possible to split s satisfying the conditions then return -1.

Examples:

Input: s = "0100110101"
Output: 4
Explanation: 
The required substrings are 01, 0011, 01 and 01.

Input: s = "0111100010"
Output: 3

Input: s = "0010"
Output: -1

Constraints:
1 <= s.length <= 10^5
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    /*
     * Problem: Balanced Splits of a Binary String
     * 
     * Find the maximum number of substrings s can be split into
     * such that each has equal number of 0s and 1s.
     * 
     * Time Complexity: O(N) - single pass scan
     * Space Complexity: O(1) - constant auxiliary space
     */
    int maxSubStr(string str) {
        int ans = 0;
        int balance = 0;
        
        for (char c : str) {
            if (c == '0') {
                balance++;
            } else 
                balance--;
            }
            
            // Whenever balance is 0, we found a balanced substring
            if (balance == 0) {
                ans++;
            }
        }
        
        // If final balance is not 0, the string cannot be split into balanced substrings
        if (balance != 0) {
            return -1;
        }
        
        return ans;
    }
};

/*
Approach: Greedy Balanced Count
- We traverse the binary string from left to right.
- We maintain a `balance` counter, incrementing it by 1 for '0' and decrementing it by 1 for '1'.
- Whenever `balance` reaches 0, it indicates that the current prefix (since the last split point) contains an equal number of '0's and '1's.
- To maximize the number of splits, we greedily increment our count (`ans`) as soon as `balance == 0`.
- After traversing the entire string, we must check if the final `balance` is 0. If it is not, the total number of '0's and '1's in the string was not equal, making a valid partition impossible. In this case, we return -1.
- Otherwise, we return the total count of splits.

Complexity:
- Time Complexity: O(N) where N is the length of the string, since we iterate through the string exactly once.
- Space Complexity: O(1) auxiliary space as we only use two integer variables (`ans`, `balance`).
*/
