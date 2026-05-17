/*
Problem: Unique Numbers

GFG: https://www.geeksforgeeks.org/problems/unique-numbers3529/1

Description:
Given a range [L, R], return all numbers whose digits are all unique
(no digit repeats inside the same number).

Examples:

Input: L = 10, R = 20
Output: 10 12 13 14 15 16 17 18 19 20

Input: L = 1, R = 9
Output: 1 2 3 4 5 6 7 8 9

Constraints:
1 <= L <= R <= 10^4

Approach:
For each number in [L, R], check whether any digit repeats.
Use a small frequency array of size 10 while extracting digits.

If a digit appears twice, that number is not unique.
Otherwise, include it in the answer.

Time Complexity: O((R - L + 1) * digits) ~ O(N)
Space Complexity: O(1)

Pattern: Digit Processing / Hashing (Fixed Size)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  
    // Helper: returns true if all digits in x are unique
    bool hasUniqueDigits(int x) {
        vector<int> freq(10, 0);

        while (x > 0) {
            int digit = x % 10;

            freq[digit]++;
            if (freq[digit] > 1) {
                return false;
            }

            x /= 10;
        }

        return true;
    }
  
    vector<int> uniqueNumbers(int L, int R) {
        vector<int> ans;

        for (int num = L; num <= R; num++) {
            if (hasUniqueDigits(num)) {
                ans.push_back(num);
            }
        }

        return ans;
    }
};

