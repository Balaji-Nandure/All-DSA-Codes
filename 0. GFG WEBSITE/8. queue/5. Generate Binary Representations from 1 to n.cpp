/*
Problem:
Generate Binary Representations from 1 to N

Given a number N, generate binary representations of all numbers
from 1 to N and return them as strings.

Rules:
- Output binary values in increasing order from 1 to N.
- Leading zeros are not allowed.

Example:
Input:
N = 5

Output:
["1", "10", "11", "100", "101"]

Approach (Optimized – Queue / BFS Pattern):
- Use a queue to generate binary numbers in order.
- Start by pushing "1" into the queue.
- For each number:
  - Pop front string.
  - Add it to the result.
  - Append '0' and '1' to generate next binary numbers.
- This follows level order traversal of a binary tree (0/1).

GeeksforGeeks:
https://www.geeksforgeeks.org/generate-binary-numbers-1-n/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

class Solution {
public:
    vector<string> generateBinary(int n) {

        vector<string> ans;
        queue<string> q;
        
        q.push("1");

        for (int i = 1; i <= n; i++) {

            string curr = q.front();
            q.pop();

            ans.push_back(curr);

            q.push(curr + "0");
            q.push(curr + "1");
        }

        return ans;
    }
};
        