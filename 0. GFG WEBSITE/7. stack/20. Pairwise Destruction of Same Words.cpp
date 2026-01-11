/*
Problem:
String Manipulation (Pairwise Destruction of Same Words)

Given a sequence of words arr[], whenever two consecutive identical
words appear, they destroy each other.
This process continues until no such consecutive pair exists.

Find the number of words left after all possible destructions.

Rules:
- Destruction is pairwise.
- Chain reactions are possible after removals.

Example:
Input:
["ab", "aa", "aa", "bcd", "ab"]

Process:
aa aa → destroyed
Remaining → ab bcd ab

Output:
3

Approach (Using Stack):
- Traverse the sequence from left to right.
- Use a stack to keep track of remaining words.
- If current word is same as stack top, pop the top (pair destroyed).
- Otherwise, push the current word.
- Stack automatically handles chain reactions.

GeeksforGeeks:
https://www.geeksforgeeks.org/string-manipulation/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

class Solution {
    public:
        int removeConsecutiveSame(vector<string>& arr) {
    
            stack<string> st;
    
            for (string& w : arr) {
                if (!st.empty() && st.top() == w) {
                    st.pop();
                } else {
                    st.push(w);
                }
            }
    
            return st.size();
        }
    };
    