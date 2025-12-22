/*
 * Problem: Palindrome Partitioning
 * 
 * LeetCode 131: Palindrome Partitioning
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/palindromic-patitioning4845/1
 *
 * Given a string s, partition s such that every substring is a palindrome.
 * Return all possible palindrome partitioning of s.
 * 
 * Example: s = "aab"
 * Output: [["a","a","b"],["aa","b"]]
 *
 * Time: O(2^n * n) - exponential, each partition checked in O(n)
 * Space: O(n) - recursion stack depth
 */

#include <bits/stdc++.h>
using namespace std;

// Check if substring s[l...r] is palindrome
bool isPalindrome(string &s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

void solve(int start, string &s, vector<string> &curr, 
           vector<vector<string>> &result) {
    // Base case: processed entire string, add current partition
    if (start == (int)s.size()) {
        result.push_back(curr);
        return;
    }

    // Try all possible ending positions for current partition
    for (int end = start; end < (int)s.size(); end++) {
        // Check if substring s[start...end] is palindrome
        if (isPalindrome(s, start, end)) {
            // Add this palindrome substring to current partition
            curr.push_back(s.substr(start, end - start + 1));
            // Recurse to partition remaining string (from end+1)
            solve(end + 1, s, curr, result);
            // Backtrack: remove substring to try other partitions
            curr.pop_back();
        }
    }
}

vector<vector<string>> partition(string s) {
    vector<vector<string>> result;
    vector<string> curr;
    solve(0, s, curr, result);
    return result;
}

void printResult(vector<vector<string>> &result) {
    for (auto &partition : result) {
        cout << "[";
        for (int i = 0; i < (int)partition.size(); i++) {
            cout << "\"" << partition[i] << "\"";
            if (i < (int)partition.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n";
}

int main() {
    string s = "aabb";
    cout << "Input: s = \"" << s << "\"\n";
    vector<vector<string>> res = partition(s);
    printResult(res);
    cout << "\n";

    // Test case 2
    string s2 = "a";
    cout << "Input: s = \"" << s2 << "\"\n";
    vector<vector<string>> res2 = partition(s2);
    printResult(res2);
    cout << "\n";

    return 0;
}