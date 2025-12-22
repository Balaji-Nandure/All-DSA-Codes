/*
 * Problem: Print All Subsequences of a String
 *
 * Generate and print all possible subsequences of a given string.
 * A subsequence maintains relative order but may skip characters.
 * Example: "abc" → "", "a", "b", "c", "ab", "ac", "bc", "abc"
 *
 * Time: O(2^n * n) - 2^n subsequences, each printed in O(n)
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Take element before recursive call
void printSubsequences(int i, string &ans, string &s){
    // Base case: processed all characters
    if(i == s.size()){
        // Print empty string as "NULL" for clarity
        if(ans.size() == 0) {
            cout << "NULL" << endl;
            return;
        }else{
            cout << ans << endl;
            return;
        }
    }
    // TAKE: Include current character in subsequence
    ans.push_back(s[i]);
    printSubsequences(i+1, ans, s);
    // BACKTRACK: Remove current character to restore state
    ans.pop_back();

    // NOT TAKE: Skip current character
    printSubsequences(i+1, ans, s);
}

// Approach 2: Not take before take (prints in reverse order)
void printSubsequences2(int i, string &ans, string &s){
    // Base case: processed all characters
    if(i == s.size()){
        if(ans.size() == 0) {
            cout << "NULL" << endl;
            return;
        }else{
            cout << ans << endl;
            return;
        }
    }

    // NOT TAKE: Skip current character first
    printSubsequences2(i+1, ans, s);

    // TAKE: Include current character
    ans.push_back(s[i]);
    printSubsequences2(i+1, ans, s);
    // BACKTRACK: Restore state after recursive call
    ans.pop_back();
}

int main() {

    string s = "abc";
    string ans = "";

    printSubsequences2(0, ans, s);
}