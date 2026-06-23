/*
    Problem Name: All Palindromic Partitions
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a string s, find all possible ways to partition it such that every substring in the partition is a palindrome.

    Expected Complexities:
    Time Complexity: O(N * 2^N), where N is the length of the string. In the worst case (like "aaaa..."), there are 2^(N-1) possible partitions, and copying each to the result takes O(N).
    Space Complexity: O(N * 2^N) to store all valid partitions.

    Love Babbar Style Approach:
    1. Backtracking/DFS: We want to generate all possible combinations of partitions. This is a classic backtracking problem.
    2. Recursive Function: We create a recursive function `solve(index, current_partition, result)`:
       - Base Case: If `index` reaches the end of the string `s`, we have found a valid partition. We add `current_partition` to our `result` and return.
       - Iteration: We loop `j` from `index` to `s.length() - 1`. We check if the substring `s[index...j]` is a palindrome.
       - If it is a palindrome, we add this substring to `current_partition`, and recursively call `solve(j + 1)`.
       - Backtrack: After the recursive call returns, we remove the substring from `current_partition` to explore other possibilities.
    3. Palindrome Check: A simple helper function is used to verify if a given substring is a palindrome.
    4. Result: After the backtracking is complete, `result` will contain all possible palindromic partitions.

    Dry Run:
    Input: s = "abcba"
    - `solve(0)`:
      - j=0: "a" is palindrome. Add "a". Call `solve(1)`.
        - j=1: "b" is palindrome. Add "b". Call `solve(2)`.
          - j=2: "c" is palindrome. Add "c". Call `solve(3)`.
            - j=3: "b" is palindrome. Add "b". Call `solve(4)`.
              - j=4: "a" is palindrome. Add "a". Call `solve(5)`. -> Base case reached! Add ["a", "b", "c", "b", "a"]. Backtrack.
            - j=4: "ba" not palindrome.
          - j=3: "cb" not palindrome.
          - j=4: "cba" not palindrome.
        - j=2: "bc" not palindrome.
        - j=3: "bcb" is palindrome. Add "bcb". Call `solve(4)`.
          - j=4: "a" is palindrome. Add "a". Call `solve(5)`. -> Base case reached! Add ["a", "bcb", "a"]. Backtrack.
      - j=4: "abcba" is palindrome. Add "abcba". Call `solve(5)`. -> Base case reached! Add ["abcba"]. Backtrack.
    Result: [["a", "b", "c", "b", "a"], ["a", "bcb", "a"], ["abcba"]]
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
  private:
    bool isPalindrome(const string& s, int start, int end) {
        while (start <= end) {
            if (s[start++] != s[end--]) {
                return false;
            }
        }
        return true;
    }
    
    void solve(int index, const string& s, vector<string>& current, vector<vector<string>>& res) {
        if (index == s.length()) {
            res.push_back(current);
            return;
        }
        
        for (int i = index; i < s.length(); ++i) {
            if (isPalindrome(s, index, i)) {
                current.push_back(s.substr(index, i - index + 1));
                solve(i + 1, s, current, res);
                current.pop_back(); // Backtrack
            }
        }
    }

  public:
    vector<vector<string>> allPalindromicPerms(string S) {
        vector<vector<string>> res;
        vector<string> current;
        solve(0, S, current, res);
        return res;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            string S;
            cin >> S;
            Solution ob;
            vector<vector<string>> ptr = ob.allPalindromicPerms(S);
            for (int i = 0; i < ptr.size(); i++) {
                for (int j = 0; j < ptr[i].size(); j++) {
                    cout << ptr[i][j] << " ";
                }
                cout << "\n";
            }
        }
    }
    return 0;
}
