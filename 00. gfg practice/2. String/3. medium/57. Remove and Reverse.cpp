/*
    Problem Name: Remove and Reverse
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a string S which consists of only lowercase English alphabets, you have to perform the below operations:
    If the string S contains any repeating character, remove the first repeating character and reverse the string and again perform the above operation on the modified string, otherwise, you stop.
    You have to find the final string.

    Expected Complexities:
    Time Complexity: O(|S|), where |S| is the length of the string.
    Space Complexity: O(K) where K <= 26 for frequency array.

    Love Babbar Style Approach:
    1. Observation: Simulating the process naively by removing and reversing the string takes O(N^2) time. However, reversing the string simply means we start reading characters from the opposite end. 
    2. Two Pointers & Frequency Array: We can use two pointers `i` (start) and `j` (end), along with a `dir` variable to track the current direction (0 for left-to-right, 1 for right-to-left). We also maintain a `freq` array of size 26 to track character counts.
    3. Traversal:
       - If `dir == 0`, we check the character at `S[i]`. If it's a repeating character (`freq > 1`), we "remove" it by decrementing its frequency, marking `S[i]` as removed (e.g., '#'), moving `i++`, and changing direction `dir = 1`. If not repeating, we just move `i++`.
       - If `dir == 1`, we check the character at `S[j]`. If it's a repeating character, we "remove" it, mark `S[j]` as removed, move `j--`, and change direction `dir = 0`. If not repeating, we just move `j--`.
    4. Result Construction: After the loop finishes (`i > j`), we collect all the non-removed characters from the string.
       - If the final direction `dir == 1`, it means the string is currently in a reversed state logically, so we reverse the collected string before returning it.
       - Otherwise, we return it as is.

    Dry Run:
    Input: S = "abab"
    - Frequency: 'a': 2, 'b': 2. Pointers: i = 0, j = 3, dir = 0.
    - dir=0: S[0]='a', freq=2. Remove 'a'. freq['a']=1. S[0]='#'. i=1, dir=1.
    - dir=1: S[3]='b', freq=2. Remove 'b'. freq['b']=1. S[3]='#'. j=2, dir=0.
    - dir=0: S[1]='b', freq=1. Not repeating. i=2.
    - dir=0: S[2]='a', freq=1. Not repeating. i=3.
    - Loop ends since i > j.
    - Remaining characters: S[1]='b', S[2]='a'. Formed string: "ba".
    - Final dir=0, so no final reversal needed.
    Result: "ba"
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    string removeReverse(string S) {
        int n = S.length();
        vector<int> freq(26, 0);
        
        for (char ch : S) {
            freq[ch - 'a']++;
        }
        
        int i = 0, j = n - 1;
        int dir = 0; // 0 for left-to-right, 1 for right-to-left
        
        while (i <= j) {
            if (dir == 0) {
                if (freq[S[i] - 'a'] > 1) {
                    freq[S[i] - 'a']--;
                    S[i] = '#';
                    dir = 1;
                }
                i++;
            } else {
                if (freq[S[j] - 'a'] > 1) {
                    freq[S[j] - 'a']--;
                    S[j] = '#';
                    dir = 0;
                }
                j--;
            }
        }
        
        string ans = "";
        for (char ch : S) {
            if (ch != '#') {
                ans += ch;
            }
        }
        
        if (dir == 1) {
            reverse(ans.begin(), ans.end());
        }
        
        return ans;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            string S;
            cin >> S;
            Solution ob;
            cout << ob.removeReverse(S) << "\n";
        }
    }
    return 0;
}
