/*
GeeksforGeeks: String Mirror
Difficulty: Easy

You are given a string s of length n. You need to choose an integer k (1 <= k <= n), such that you can perform the following operation:
- Take the prefix of the string of length k.
- Append the reverse of the picked prefix to itself.

Find the lexicographically smallest string you can get by choosing a k.

Examples:

Input: s = "bvdfndkn"
Output: "bb"
Explanation: If we choose k = 1, the prefix of length k will be "b", and the reverse of this prefix will be "b" itself, when we append both we get "bb", "bb" is the lexicographically smallest string you can get. If you choose k > 1, the resulting string will not be lexicographically smaller than "bb".

Input: s = "casd"
Output: "caac"
Explanation: 
For k = 1, we get cc
For k = 2, we get caac
For k = 3, we get cassac
For k = 4, we get casddsac
Out of all these, the smallest one is "caac"

Constraints:
1 <= n <= 10^5
s contains lower case English alphabets
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
     * Problem: String Mirror
     * 
     * Find the lexicographically smallest string obtainable by mirroring a prefix of length k.
     * 
     * Time Complexity: O(N) - single pass to find prefix, plus reversal
     * Space Complexity: O(N) - to store the resulting mirrored string
     */
    string stringMirror(string s) {
        int n = s.length();
        if (n == 0) return "";
        
        string prefix = "";
        prefix += s[0];
        
        // Greedy choice of prefix:
        // 1. If s[1] >= s[0], choosing k > 1 will make the string lexicographically larger than choosing k = 1.
        //    For example: "bbba" -> k=1 gives "bb", k=2 gives "bbbb", so we should stop at k=1.
        // 2. Otherwise, we can keep adding characters as long as they are less than or equal to the previous character.
        for (int i = 1; i < n; i++) {
            if (i == 1 && s[i] >= s[i-1]) {
                break;
            }
            if (s[i] <= s[i-1]) {
                prefix += s[i];
            } else {
                break;
            }
        }
        
        string reversed_prefix = prefix;
        reverse(reversed_prefix.begin(), reversed_prefix.end());
        
        return prefix + reversed_prefix;
    }
};

/*
Approach: Greedy Prefix Selection
- To construct the lexicographically smallest mirrored string:
  1. We want the prefix to consist of characters that are as small as possible.
  2. For the second character (index 1): if `s[1] >= s[0]`, then appending `s[1]` will yield a mirrored string that is lexicographically larger than or equal to the mirror of `s[0]` alone. For instance, if `s = "bba"`, `k = 1` yields `"bb"`, whereas `k = 2` yields `"bbbb"`. Hence, if `s[1] >= s[0]`, we immediately stop and choose `k = 1`.
  3. For subsequent characters (`i >= 2`): we can continue extending our prefix as long as `s[i] <= s[i-1]`. A decreasing character sequence helps minimize the mirrored output. Even equal characters (`s[i] == s[i-1]`) are beneficial here as the mirroring reflection will place smaller characters earlier.
  4. Once `s[i] > s[i-1]`, we must stop, because adding a larger character will strictly make the resulting string lexicographically larger.
- After constructing the prefix, we reverse it and concatenate it to the end of the original prefix.

Complexity:
- Time Complexity: O(N) in the worst case, where N is the length of the string, as we do a single pass to build the prefix and another to reverse it.
- Space Complexity: O(N) to store the prefix and the final mirrored string.
*/
