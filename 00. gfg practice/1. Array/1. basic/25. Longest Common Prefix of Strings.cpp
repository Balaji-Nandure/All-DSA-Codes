/*
 * Problem: Longest Common Prefix of Strings
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/longest-common-prefix-of-strings/0
 * 
 * Given an array of strings arr[]. Return the longest common prefix among each 
 * and every strings present in the array. If there's no prefix common in all the strings, return "".
 * 
 * Examples:
 * Input: arr[] = ["geeksforgeeks", "geeks", "geek", "geezer"]
 * Output: "gee"
 * Explanation: "gee" is the longest common prefix in all the given strings.
 * 
 * Input: arr[] = ["hello", "world"]
 * Output: ""
 * Explanation: There's no common prefix in the given strings.
 * 
 * Constraints:
 * 1 ≤ |arr| ≤ 10^3
 * 1 ≤ |arr[i]| ≤ 10^3
 * 
 * Expected Time Complexity: O(n * m)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Find the shortest string in the array (longest possible prefix length)
 * - Compare each character position across all strings
 * - If any string has different character at a position, stop there
 * - The common prefix is the substring up to the last matching position
 * - Edge case: if array is empty, return empty string
 * 
 * Time: O(n * m) - n strings, m is average string length
 * Space: O(1) - constant extra space (excluding output string)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& arr) {
        if (arr.empty()) return "";
        
        string shortest = arr[0];
        int minLen = shortest.length();
        
        // Find the shortest string
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i].length() < minLen) {
                minLen = arr[i].length();
                shortest = arr[i];
            }
        }
        
        string prefix = "";
        
        // Compare each character position
        for (int i = 0; i < minLen; i++) {
            char current = shortest[i];
            
            // Check if all strings have this character at position i
            for (int j = 0; j < arr.size(); j++) {
                if (arr[j][i] != current) {
                    return prefix;
                }
            }
            
            prefix += current;
        }
        
        return prefix;
    }
};
