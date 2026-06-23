/*
    Problem Name: Valid Compressed String
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    A special compression mechanism can arbitrarily delete 0 or more characters and replace them with the deleted character count.
    Given two strings, S and T where S is a normal string and T is a compressed string, determine if the compressed string T is valid for the plaintext string S. 

    Expected Complexities:
    Time Complexity: O(|T|), as we iterate through the compressed string and advance the pointer for the original string.
    Space Complexity: O(1), since we only use a few variables for pointers and counting.

    Love Babbar Style Approach:
    1. Two Pointers: We use two pointers, `i` to traverse the original string `S` and `j` to traverse the compressed string `T`. Both start at index 0.
    2. Traversal: We loop as long as `i < S.length()` and `j < T.length()`.
       - Case 1: If `T[j]` is a digit (from '0' to '9'), we extract the complete number by reading consecutive digits. Let this number be `count`. We advance `j` past the digits, and we advance `i` by `count` (effectively skipping `count` deleted characters in `S`).
       - Case 2: If `T[j]` is a character, we compare it directly with `S[i]`. If they do not match, we return 0 (invalid compression). If they do match, we increment both `i` and `j` by 1.
    3. Boundary Checks: If at any point skipping `count` characters causes `i` to go beyond the length of `S`, we return 0.
    4. Result: After the loop terminates, both pointers must have exactly reached the end of their respective strings (`i == S.length()` and `j == T.length()`) for the compression to be perfectly valid. If so, return 1, else return 0.

    Dry Run:
    Input: S = "GEEKSFORGEEKS", T = "G7G3S"
    Initialization: i = 0, j = 0
    Iteration:
    - j = 0, T[0] = 'G'. Matches S[0] = 'G'. i = 1, j = 1.
    - j = 1, T[1] = '7'. Extract number: count = 7. j becomes 2. i becomes 1 + 7 = 8.
    - j = 2, T[2] = 'G'. Matches S[8] = 'G'. i = 9, j = 3.
    - j = 3, T[3] = '3'. Extract number: count = 3. j becomes 4. i becomes 9 + 3 = 12.
    - j = 4, T[4] = 'S'. Matches S[12] = 'S'. i = 13, j = 5.
    End of loop.
    Check: i == 13 (S.length()), j == 5 (T.length()).
    Result: 1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
  public:
    int checkCompressed(string S, string T) {
        int i = 0; // Pointer for S
        int j = 0; // Pointer for T
        int n = S.length();
        int m = T.length();
        
        while (i < n && j < m) {
            if (isdigit(T[j])) {
                int count = 0;
                // Extract the full number
                while (j < m && isdigit(T[j])) {
                    count = count * 10 + (T[j] - '0');
                    j++;
                }
                i += count;
            } else {
                // It's a character, so it must match exactly
                if (S[i] != T[j]) {
                    return 0;
                }
                i++;
                j++;
            }
        }
        
        // Both strings must be completely traversed
        return (i == n && j == m);
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            string S, T;
            cin >> S >> T;
            Solution ob;
            cout << ob.checkCompressed(S, T) << "\n";
        }
    }
    return 0;
}
