/*
GeeksforGeeks: Validate an IP Address
Difficulty: Medium

Problem:
You are given a string s in the form of an IPv4 Address. Your task is to validate an IPv4 Address, if it is valid return true otherwise return false.
IPv4 addresses are canonically represented in dot-decimal notation, which consists of four decimal numbers, each ranging from 0 to 255, separated by dots.
Note: Here we are considering numbers only from 0 to 255 and any additional leading zeroes will be considered invalid.

Examples:
Input: s = "222.111.111.111"
Output: true
Explanation: All four decimal numbers lie in the mentioned range.

Input: s = "5555..555"
Output: false
Explanation: Not a valid IPv4 address, as the middle two portions are missing (empty).

Input: s = "0.0.0.255"
Output: true

Core Idea:
To validate an IPv4 address, we must strictly enforce the following rules:
1. It must be composed of exactly 4 parts separated by exactly 3 dots.
2. Each part must not be empty.
3. Each part must contain only numeric digits (no letters, spaces, or negative signs).
4. Each part must be a number between 0 and 255 (inclusive).
5. No part can contain leading zeroes unless the part itself is exactly "0" (e.g., "01" is invalid).

Approach:
1. Write a helper function `isValidPart(string part)` that checks:
   - If the string is empty or length > 3, return false.
   - If any character is not a digit (`isdigit`), return false.
   - If length > 1 and the first character is '0', return false (leading zero check).
   - Convert the string to an integer and check if it's <= 255.
2. In the main function, iterate through the string character by character.
   - Accumulate characters into a `part` string.
   - When a dot `.` is encountered, increment a `dots` counter, validate the `part`, and reset `part`.
3. After the loop, validate the final `part` (since the string doesn't end with a dot).
4. Finally, verify that we encountered exactly 3 dots and processed exactly 4 parts.

Time Complexity: O(N) where N is the length of the string. We scan each character exactly once. Given N <= 15, this is virtually instantaneous O(1).
Space Complexity: O(1) auxiliary space, as we only store small substrings of maximum length 3.

GFG Link: https://www.geeksforgeeks.org/problems/validate-an-ip-address-1587115621/1
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Solution {
private:
    bool isValidPart(const string& part) {
        // Must not be empty and cannot exceed 3 characters ("255" is 3 chars)
        if (part.empty() || part.length() > 3) {
            return false;
        }
        
        // Must consist strictly of digits
        for (char c : part) {
            if (!isdigit(c)) {
                return false;
            }
        }
        
        // Must not have leading zeroes (e.g. "01" or "00" are invalid, but "0" is valid)
        if (part.length() > 1 && part[0] == '0') {
            return false;
        }
        
        // Value must be between 0 and 255
        // (Safe to use stoi since we already verified it's numeric and length <= 3)
        int val = stoi(part);
        if (val > 255) {
            return false;
        }
        
        return true;
    }

public:
    int isValid(string str) {
        int dots = 0;
        int parts_count = 0;
        string part = "";
        
        for (char c : str) {
            if (c == '.') {
                dots++;
                // Validate the part accumulated so far
                if (!isValidPart(part)) {
                    return false;
                }
                parts_count++;
                part = ""; // Reset for the next part
            } else {
                part += c;
            }
        }
        
        // Validate the final accumulated part
        if (!isValidPart(part)) {
            return false;
        }
        parts_count++;
        
        // A valid IP must have exactly 3 dots and 4 parts
        return (dots == 3 && parts_count == 4);
    }
};

/*
Dry Run — Example 2:
Input: s = "5555..555"

1. char = '5' -> part = "5"
2. char = '5' -> part = "55"
3. char = '5' -> part = "555"
4. char = '5' -> part = "5555"
5. char = '.' -> dots = 1
   - isValidPart("5555"): length > 3 -> Returns false!
   
Function immediately returns false.

Dry Run — Leading Zeroes Edge Case:
Input: s = "192.168.01.1"

1. "192" passes, dots = 1, parts_count = 1
2. "168" passes, dots = 2, parts_count = 2
3. "01" hits '.' -> isValidPart("01"):
   - length > 1 AND starts with '0' -> Returns false!
   
Function immediately returns false.
*/
