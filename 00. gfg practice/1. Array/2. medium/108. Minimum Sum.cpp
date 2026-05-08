/*
Problem: Minimum Sum

GFG: https://www.geeksforgeeks.org/problems/minimum-sum4058/1

Description:
Given an array arr[ ] consisting of digits, your task is to form two numbers using all the digits such that their sum is minimized. Return the minimum possible sum as a string with no leading zeroes.

Examples:

Input: arr[] = [6, 8, 4, 5, 2, 3]
Output: "604"
Explanation: The minimum sum is formed by numbers 358 and 246.

Input: arr[] = [5, 3, 0, 7, 4]
Output: "82"
Explanation: The minimum sum is formed by numbers 35 and 047.

Input: arr[] = [9, 4]
Output: "13"
Explanation: The minimum sum is formed by numbers 9 and 4.

Constraints:
1 ≤ arr.size() ≤ 10^6
0 ≤ arr[i] ≤ 9

Approach (Greedy + String Addition):
This is a greedy problem where we need to minimize the sum of two numbers formed from digits.

Key insight:
- To minimize sum, smaller digits should occupy higher place values
- Sort digits in ascending order
- Distribute digits alternately between two numbers
- Add the two numbers using string addition to avoid overflow

Algorithm:
1. Sort the array in ascending order
2. Create two numbers by alternate placement:
   - Smallest digit goes to first number
   - Next smallest goes to second number
   - Continue alternately
3. Add the two numbers using string addition
4. Remove leading zeros from result

Time Complexity: O(n log n)
Space Complexity: O(n)

Pattern: Greedy + String Manipulation
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
GREEDY + STRING ADDITION
=====================================================

TC: O(n log n)
SC: O(n)

🔥 GREEDY APPROACH
- Sort digits to minimize place values
- Alternate distribution for balanced numbers
- String addition to handle large numbers

🧠 KEY INSIGHT:
To minimize sum:
- Small digits should have high place values
- Balance digits between two numbers
- Avoid integer overflow with string addition

🎯 ALGORITHM:
1. Sort digits ascending
2. Alternate distribution between two numbers
3. String addition for final sum
4. Remove leading zeros

⚡ GREEDY LOGIC:
Smallest digit gets highest place value
by being distributed to numbers alternately.
*/

class Solution {
public:

    // Add two large numbers represented as strings
    string addStrings(string a, string b) {

        int i = a.size() - 1;
        int j = b.size() - 1;

        int carry = 0;

        string ans = "";

        while(i >= 0 || j >= 0 || carry) {

            int sum = carry;

            if(i >= 0)
                sum += a[i--] - '0';

            if(j >= 0)
                sum += b[j--] - '0';

            ans.push_back((sum % 10) + '0');

            carry = sum / 10;
        }

        reverse(ans.begin(), ans.end());

        // Remove leading zeros
        int idx = 0;

        while(idx < ans.size() - 1 && ans[idx] == '0') {

            idx++;
        }

        return ans.substr(idx);
    }

    // TC: O(n log n)
    // SC: O(n)

    string minSum(vector<int> &arr) {

        sort(arr.begin(), arr.end());

        string num1 = "";
        string num2 = "";

        // Alternate distribution
        for(int i = 0; i < arr.size(); i++) {

            if(i % 2 == 0)
                num1.push_back(arr[i] + '0');
            else
                num2.push_back(arr[i] + '0');
        }

        return addStrings(num1, num2);
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    MINIMIZE SUM OF TWO NUMBERS
    + DIGIT MANIPULATION

Think immediately:
    GREEDY + ALTERNATE PLACEMENT

-----------------------------------------------------

KEY OBSERVATIONS:

1. Small digits should have high place values
2. Balanced distribution reduces overall sum
3. String addition avoids overflow issues

-----------------------------------------------------

COMMON MISTAKES:

1. Using integer datatype (overflow risk)
2. Not removing leading zeros from result
3. Putting all small digits in same number
4. Not balancing digit distribution

-----------------------------------------------------

SIMILAR PROBLEMS

- Minimum sum of two numbers
- Digit rearrangement problems
- Greedy number formation

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Minimize sum of formed numbers
- Digits need to be distributed

Think:
1. Sort digits ascending
2. Alternate distribution
3. String addition

-----------------------------------------------------
*/
