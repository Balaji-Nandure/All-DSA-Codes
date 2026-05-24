/*
Problem: Bracket Numbers

GFG: https://www.geeksforgeeks.org/problems/bracket-numbers3145/1

Description:
Given a string containing brackets,
assign a number to each opening bracket.

Rules:
- Every opening bracket gets a new increasing number
- Corresponding closing bracket gets the same number
- Return numbers in the order brackets appear

Examples:

Input:
s = "(aa(bdc))p(dee)"

Output:
1 2 2 1 3 3

Explanation:

Bracket sequence:
(        -> 1
   (     -> 2
   )     -> 2
)        -> 1
(        -> 3
)        -> 3

--------------------------------------------------

Input:
s = "(((()("

Output:
1 2 3 4 4 5

Constraints:
1 ≤ s.size() ≤ 10^5

Approach (Stack):
- Opening bracket '(':
    assign new number
    push into stack
    add to answer

- Closing bracket ')':
    top of stack belongs to this bracket
    add top to answer
    pop stack

Why Stack?
- Brackets follow LIFO order
- Latest opened bracket closes first

Dry Run:
s = "(aa(bdc))"

count = 1

'(':
  push 1
  ans = [1]

'(':
  push 2
  ans = [1,2]

')':
  top = 2
  ans = [1,2,2]
  pop

')':
  top = 1
  ans = [1,2,2,1]
  pop

Final Answer:
[1,2,2,1] ✅

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(n)
    vector<int> bracketNumbers(string &s) {

        vector<int> ans;

        stack<int> st;

        int count = 1;

        for(char ch : s) {

            // Opening bracket
            if(ch == '(') {

                st.push(count);

                ans.push_back(count);

                count++;
            }

            // Closing bracket
            else if(ch == ')') {

                ans.push_back(st.top());

                st.pop();
            }
        }

        return ans;
    }
};