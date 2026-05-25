/*
Problem: Reversing the equation

GFG: https://www.geeksforgeeks.org/problems/reversing-the-equation2205/1

Description:
Given a valid mathematical equation containing:
- numbers
- +, -, *, /

Reverse the equation such that:
- order of terms/operators reverses
- numbers themselves remain unchanged

Examples:

Input:
S = "20-3+5*2"

Output:
"2*5+3-20"

--------------------------------------------------

Input:
S = "5+2*56-2/4"

Output:
"4/2-56*2+5"

Constraints:
1 ≤ s.size() ≤ 10^5

Approach:
- Traverse from right to left
- Extract complete numbers
- Append them to answer
- Then append operator

Why reverse traversal?
- Numbers must remain unchanged
- Only equation order should reverse

Dry Run:
S = "20-3+5*2"

Right to left:

2  -> ans="2"
*  -> ans="2*"
5  -> ans="2*5"
+  -> ans="2*5+"
3  -> ans="2*5+3"
-  -> ans="2*5+3-"
20 -> ans="2*5+3-20"

Answer = "2*5+3-20" ✅

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(n)
    string reverseEqn(string s) {

        string ans = "";

        int i = s.size() - 1;

        while(i >= 0) {

            string num = "";

            // Extract number
            while(i >= 0 && isdigit(s[i])) {

                num = s[i] + num;

                i--;
            }
            
            ans += num;

            // Add operator
            if(i >= 0) {

                ans += s[i];

                i--;
            }
        }

        return ans;
    }
};