#include <bits/stdc++.h>
using namespace std;

/*
 * @brief   Print N-bit binary numbers having more 1s than 0s (GeeksforGeeks)
 * @link    https://practice.geeksforgeeks.org/problems/print-n-bit-binary-numbers-having-more-1s-than-0s/1
 *
 * Problem Statement:
 *   Given a positive integer n. Your task is to generate a string list of all n-bit binary numbers where,
 *   for any prefix of the number, there are more or an equal number of 1's than 0's.
 *   The numbers should be sorted in decreasing order of magnitude.
 *
 * Approach (Backtracking / Recursion - Love Babbar Style):
 *   1. We need to construct strings of length `n` from left to right.
 *   2. For any step, we can either append '1' or '0'.
 *   3. To maintain the condition "more or equal number of 1's than 0's in any prefix":
 *      - We can always place '1' at any position (as it only increases the count of 1s).
 *      - We can place '0' only if the count of 1s strictly exceeds the count of 0s before placing it (so that after placing, count of 1s >= count of 0s).
 *   4. To get the output in decreasing order of magnitude:
 *      - We should always branch on '1' first and then '0'. This naturally generates lexicographically larger strings first (decreasing order of magnitude).
 *
 * Constraints:
 *   1 <= n <= 15
 *
 * Complexity Analysis:
 *   - Time Complexity: O(2^N) - In the worst case, we explore valid paths. The total number of valid strings is related to Catalan/dyck paths, bounded by 2^N.
 *   - Space Complexity: O(N) - Maximum depth of the recursion stack.
 */

class Solution {
private:
    void solve(int n, int count1, int count0, string temp, vector<string> &ans) {
        // Base Case: when the string reaches length n
        if (temp.length() == n) {
            ans.push_back(temp);
            return;
        }

        // Choice 1: Always try to add '1' first (to maintain descending order of magnitude)
        solve(n, count1 + 1, count0, temp + '1', ans);

        // Choice 2: Add '0' only if number of 1's is strictly greater than number of 0's
        if (count1 > count0) {
            solve(n, count1, count0 + 1, temp + '0', ans);
        }
    }

public:
    vector<string> NBitBinary(int n) {
        vector<string> ans;
        string temp = "";
        solve(n, 0, 0, temp, ans);
        return ans;
    }
};

// Driver code (optional, for local testing)
int main() {
    Solution sol;
    int n = 3;
    vector<string> res = sol.NBitBinary(n);
    cout << "N-bit binary numbers having more 1s than 0s for n = " << n << ":" << endl;
    for (string s : res) {
        cout << s << " ";
    }
    cout << endl;
    return 0;
}
