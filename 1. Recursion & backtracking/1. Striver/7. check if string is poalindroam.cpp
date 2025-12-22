/*
 * Problem: Check if String is Palindrome
 *
 * Check if a string reads the same forwards and backwards using recursion.
 *
 * Time: O(n) - we check n/2 character pairs
 * Space: O(n) - recursion stack depth is n/2
 */

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Two pointers (left and right)
bool isPalindrome1(string &s, int l, int r){
    // Base case: if pointers cross, all characters matched
    if (l >= r) return true;
    // If characters don't match, not a palindrome
    if (s[l] != s[r]) return false;
    // Recursively check inner substring
    return isPalindrome1(s, l+1, r-1);
} 

// Approach 2: Single pointer (calculate right from left)
bool isPalindrome2(string &s, int i){
    // Base case: if we've checked half the string
    if (i >= s.size()/2) return true;
    // Compare character at i with character at (size-i-1)
    if (s[i] != s[s.size()-i-1]) return false;
    // Recursively check next position
    return isPalindrome2(s, i+1);
}

signed main() {
    string s = "madam";
    cout << isPalindrome1(s, 0, s.size()-1) << endl;

    cout << isPalindrome2(s, 0) << endl;
    return 0;
}