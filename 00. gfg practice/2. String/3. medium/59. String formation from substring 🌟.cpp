/*
    Problem Name: String formation from substring
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a string s, determine whether it can be formed by repeating one of its substrings multiple times.
    Return true if possible, otherwise return false.

    Expected Complexities:
    Time Complexity: O(N), where N is the length of the string `s`.
    Space Complexity: O(N) to store the LPS array.

    Love Babbar Style Approach:
    1. KMP Algorithm Concept: We can determine if a string is composed of repeating substrings by using the Longest Prefix Suffix (LPS) array from the KMP pattern matching algorithm.
    2. LPS Array: The LPS array stores the length of the longest proper prefix that is also a suffix. We compute the LPS array for the entire string `s`.
    3. Mathematical Deduction: 
       - Let `l` be the last value of the LPS array (`lps[n-1]`), which represents the length of the longest proper prefix which is also a suffix of the entire string.
       - If the string is formed by repeating a substring, the length of that fundamental substring will be `n - l`.
       - For the string to be perfectly formed by repeating this fundamental substring, the total length `n` must be perfectly divisible by `n - l` (i.e., `n % (n - l) == 0`).
       - Also, we must ensure `l > 0`, because if `l == 0`, no proper prefix is a suffix, meaning it cannot be formed by repetitions.
    4. Result: Return true if the condition `l > 0 && n % (n - l) == 0` is satisfied, otherwise return false.

    Dry Run:
    Input: s = "abab"
    - n = 4.
    - LPS array construction:
      a  b  a  b
      0  0  1  2
    - Last value of LPS array: l = lps[3] = 2.
    - Substring length: n - l = 4 - 2 = 2.
    - Check condition: l > 0 (2 > 0) is true.
    - Check divisibility: n % (n - l) -> 4 % 2 == 0 is true.
    Result: true (The substring is "ab").
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
  public:
    int isRepeat(string s) {
        int n = s.length();
        if (n == 0) return 0;
        
        vector<int> lps(n, 0);
        int len = 0;
        int i = 1;
        
        while (i < n) {
            if (s[i] == s[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        
        int l = lps[n - 1];
        
        // If the length of the longest prefix suffix is > 0
        // and the remaining length divides n perfectly
        if (l > 0 && n % (n - l) == 0) {
            return 1;
        }
        
        return 0;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            string s;
            cin >> s;
            Solution ob;
            cout << ob.isRepeat(s) << "\n";
        }
    }
    return 0;
}
