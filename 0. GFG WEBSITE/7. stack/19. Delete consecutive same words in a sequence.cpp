/*
Problem:
Delete Consecutive Same Words in a Sequence

Given a sequence of words, remove all consecutive duplicate words
while maintaining the original order.

Rules:
- Only consecutive duplicates are removed.
- Non-consecutive duplicates are allowed.

Example:
Input:
["hello", "hello", "world", "world", "test"]

Output:
["hello", "world", "test"]

Approach:
- Traverse the sequence linearly.
- Keep track of the previous word.
- Add current word only if it is different from the previous one.

GeeksforGeeks:
https://www.geeksforgeeks.org/delete-consecutive-words-sequence/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(1) extra (output excluded)
*/

class Solution {
public:
    vector<string> removeConsecutiveSame(vector<string>& words) {

        vector<string> ans;

        for (int i = 0; i < words.size(); i++) {
            if (i == 0 || words[i] != words[i - 1]) {
                ans.push_back(words[i]);
            }
        }

        return ans;
    }
};
    