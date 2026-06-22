/*
GeeksforGeeks: Generate IP Addresses
Difficulty: Medium

Problem:
Given a string s containing only digits, your task is to restore it by returning all possible valid IP address combinations.
You can return your answer in any order.
A valid IP address must be in the form of A.B.C.D, where A, B, C, and D are numbers from 0-255 (inclusive).
Note: The numbers cannot be 0 prefixed unless they are 0. 
      For example, 1.1.2.11 and 0.11.21.1 are valid IP addresses while 01.1.2.11 and 00.11.21.1 are not.
If there are no possible valid IP addresses, return an empty list.

Examples:
Input: s = "255678166"
Output: ["25.56.78.166", "255.6.78.166", "255.67.8.166", "255.67.81.66"]

Input: s = "25505011535"
Output: []

Constraints:
1 <= s.length() <= 16
s contains only digits.

Core Idea:
- An IP address consists of exactly 4 parts separated by 3 dots: A.B.C.D.
- Each part must be of length 1 to 3, and represent a number between 0 and 255.
- No part can have leading zeros (e.g. "05" is invalid, but "0" is valid).
- A valid IP address string length must be between 4 and 12 characters. If s.length() < 4 or s.length() > 12, we can immediately return an empty list.
- Since we have exactly 4 parts, we can check all possible part combinations by nesting 3 loops to determine the lengths of the first 3 parts (len1, len2, len3).
- The 4th part will take the remaining characters (len4 = n - len1 - len2 - len3).
- If all 4 parts are valid, we concatenate them with '.' and add the combination to our result.

Validation Criteria for a part:
- 1 <= part.length() <= 3
- If part.length() > 1, the first character must not be '0' (no leading zeros).
- The numerical value of the part must be <= 255.

Time Complexity: O(1) constant time since there are at most 3 * 3 * 3 = 27 part length combinations to check.
Space Complexity: O(1) auxiliary space (excluding the output string vector).

GFG Link: https://www.geeksforgeeks.org/problems/generate-ip-addresses/1
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper function to validate if a substring is a valid IP address part
    bool isValid(const string& part) {
        // Must be between 1 and 3 characters
        if (part.length() < 1 || part.length() > 3) {
            return false;
        }
        // No leading zeros unless the part is exactly "0"
        if (part.length() > 1 && part[0] == '0') {
            return false;
        }
        // Value must be <= 255
        int val = stoi(part);
        return val >= 0 && val <= 255;
    }
public:
    vector<string> genIp(string s) {
        vector<string> result;
        int n = s.length();
        
        // A valid IP address length must be between 4 and 12 characters
        if (n < 4 || n > 12) {
            return result;
        }
        
        // Try all combinations of lengths for the 4 parts
        for (int len1 = 1; len1 <= 3; len1++) {
            for (int len2 = 1; len2 <= 3; len2++) {
                for (int len3 = 1; len3 <= 3; len3++) {
                    int len4 = n - len1 - len2 - len3;
                    
                    // The 4th part must also have a valid length
                    if (len4 >= 1 && len4 <= 3) {
                        string part1 = s.substr(0, len1);
                        string part2 = s.substr(len1, len2);
                        string part3 = s.substr(len1 + len2, len3);
                        string part4 = s.substr(len1 + len2 + len3, len4);
                        
                        // If all 4 parts are valid, form the IP address
                        if (isValid(part1) && isValid(part2) && isValid(part3) && isValid(part4)) {
                            result.push_back(part1 + "." + part2 + "." + part3 + "." + part4);
                        }
                    }
                }
            }
        }
        
        return result;
    }
};

/*
Dry Run — Example:
s = "255678166", n = 9

Nested loops check different part lengths:
1. len1 = 3, len2 = 1, len3 = 2, len4 = 3 (3+1+2+3 = 9)
   - part1 = s.substr(0, 3) = "255" -> Valid
   - part2 = s.substr(3, 1) = "6"   -> Valid
   - part3 = s.substr(4, 2) = "78"  -> Valid
   - part4 = s.substr(6, 3) = "166" -> Valid
   - Result added: "255.6.78.166"

2. len1 = 3, len2 = 2, len3 = 1, len4 = 3 (3+2+1+3 = 9)
   - part1 = "255" -> Valid
   - part2 = "67"  -> Valid
   - part3 = "8"   -> Valid
   - part4 = "166" -> Valid
   - Result added: "255.67.8.166"

3. len1 = 3, len2 = 2, len3 = 2, len4 = 2 (3+2+2+2 = 9)
   - part1 = "255" -> Valid
   - part2 = "67"  -> Valid
   - part3 = "81"  -> Valid
   - part4 = "66"  -> Valid
   - Result added: "255.67.81.66"

4. len1 = 2, len2 = 2, len3 = 2, len4 = 3 (2+2+2+3 = 9)
   - part1 = "25"  -> Valid
   - part2 = "56"  -> Valid
   - part3 = "78"  -> Valid
   - part4 = "166" -> Valid
   - Result added: "25.56.78.166"

All valid combinations are generated and added.
Output: ["25.56.78.166", "255.6.78.166", "255.67.8.166", "255.67.81.66"]
*/
