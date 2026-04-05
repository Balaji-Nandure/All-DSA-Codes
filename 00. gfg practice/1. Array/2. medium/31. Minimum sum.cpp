/*
Problem: Minimum sum

GFG: https://www.geeksforgeeks.org/problems/minimum-sum/1

Statement:
Given an array arr[] consisting of digits (0..9), form two numbers using all the digits
such that their sum is minimized. Return the minimum possible sum as a string with no
leading zeroes.

Key idea (greedy):
1) Sort digits ascending.
2) Put digits at even indices into the first number, odd indices into the second number.
   This keeps the most significant digits as small as possible in both numbers.
3) The sum can be huge (up to 1e6 digits), so add them as strings.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string minSum(vector<int> &arr) {
        sort(arr.begin(), arr.end());

        string num1 = "", num2 = "";

        // Distribute digits alternately
        for (int i = 0; i < (int)arr.size(); i++) {
            if (i % 2 == 0)
                num1 += char(arr[i] + '0');
            else
                num2 += char(arr[i] + '0');
        }

        // Return their sum
        return addStrings(num1, num2);
    }

private:
    // Function to add two numeric strings
    string addStrings(string a, string b) {
        string res = "";
        int i = (int)a.size() - 1;
        int j = (int)b.size() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;

            if (i >= 0) sum += a[i--] - '0';
            if (j >= 0) sum += b[j--] - '0';

            res.push_back(char((sum % 10) + '0'));
            carry = sum / 10;
        }

        reverse(res.begin(), res.end());
        
        // No leading zeroes required by the problem statement
        int k = 0;
        while (k + 1 < (int)res.size() && res[k] == '0') k++;
        if (k) res.erase(0, k);

        return res;
    }
};

/*
Complexity:
Time:  O(n log n) for sorting + O(n) for string addition
Space: O(n) for the two strings
*/

