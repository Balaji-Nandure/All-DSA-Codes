// Problem: Program to Generate All Possible Valid IP Addresses from String
// Link (GFG): https://www.geeksforgeeks.org/problems/generate-ip-addresses/1
// Article: https://www.geeksforgeeks.org/dsa/program-generate-possible-valid-ip-addresses-given-string/
// Difficulty: Medium
// Topic: String, Backtracking, Parsing, IPv4 Validation

/*
Problem Statement:
Given a string s containing only digits, restore it by returning all possible valid 
IPv4 addresses. The order of the output does not matter.

A valid IPv4 address consists of exactly 4 integers separated by single dots ('.').
Each integer:
  1. Must be in the range [0, 255].
  2. Cannot contain leading zeros (e.g., "0" is valid, but "01" and "001" are invalid).

Example 1:
Input: s = "25525511135"
Output: ["255.255.11.135", "255.255.111.35"]

Example 2:
Input: s = "0000"
Output: ["0.0.0.0"]

Example 3:
Input: s = "101023"
Output: ["1.0.10.23", "1.0.102.3", "10.1.0.23", "10.10.2.3", "101.0.2.3"]

Constraints:
- 1 <= s.length() <= 20
- s consists only of digits ('0'-'9').
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Word Break (Problem 17):
//   * A string was split into an ARBITRARY number of dictionary pieces.
// - In Valid IP Address Generation:
//   * A string must be partitioned into EXACTLY 4 PIECES (octets).
//   * Each octet has a strict character length constraint: between 1 and 3 characters.
//   * Therefore, there are at most 3 * 3 * 3 = 27 possible partition configurations, 
//     making the search space effectively CONSTANT O(1) in size!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// 3-Cut Exhaustive Validation (Optimal & Chosen):
//   - An IPv4 address requires placing 3 dots.
//   - Partition string `s` into 4 segments of lengths `len1`, `len2`, `len3`, `len4`:
//       * `1 <= len1, len2, len3, len4 <= 3`
//       * `len1 + len2 + len3 + len4 == s.length()`.
//   - Validation check for segment `seg`:
//       1. Length must be between 1 and 3.
//       2. If `seg.length() > 1 && seg[0] == '0'`: Invalid (leading zero).
//       3. Value must be `<= 255`: `stoi(seg) <= 255`.
//   - If all 4 segments pass, join with '.' and add to result.
//   - Complexity: O(1) time (at most 27 candidates evaluated), O(1) auxiliary space.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    // Helper function: Validates an individual IPv4 octet segment
    bool isValidPart(const string& part) {
        int len = part.length();
        if (len < 1 || len > 3) return false;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Guard against leading zeros: "0" is valid, but "01", "001" are invalid IPv4 octets!
        if (len > 1 && part[0] == '0') return false;

        int val = stoi(part);
        return val >= 0 && val <= 255;
    }

public:
    vector<string> genIp(string s) {
        vector<string> result;
        int n = s.length();

        // IPv4 string must have between 4 and 12 digits
        if (n < 4 || n > 12) {
            return result;
        }

        // Loop over lengths of the first 3 segments
        for (int l1 = 1; l1 <= 3 && l1 < n; ++l1) {
            for (int l2 = 1; l2 <= 3 && l1 + l2 < n; ++l2) {
                for (int l3 = 1; l3 <= 3 && l1 + l2 + l3 < n; ++l3) {
                    int l4 = n - (l1 + l2 + l3);

                    // Fourth segment must also be of length between 1 and 3
                    if (l4 >= 1 && l4 <= 3) {
                        string p1 = s.substr(0, l1);
                        string p2 = s.substr(l1, l2);
                        string p3 = s.substr(l1 + l2, l3);
                        string p4 = s.substr(l1 + l2 + l3, l4);

                        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                        // All 4 octets must simultaneously satisfy range [0, 255] and no leading zero
                        if (isValidPart(p1) && isValidPart(p2) && isValidPart(p3) && isValidPart(p4)) {
                            result.push_back(p1 + "." + p2 + "." + p3 + "." + p4);
                        }
                    }
                }
            }
        }

        return result;
    }
};

int main() {
    Solution sol;
    string s1 = "25525511135";
    vector<string> ips1 = sol.genIp(s1);
    cout << "Valid IPs for \"" << s1 << "\":\n";
    for (const string& ip : ips1) cout << ip << "\n";
    cout << "\n";

    string s2 = "101023";
    vector<string> ips2 = sol.genIp(s2);
    cout << "Valid IPs for \"" << s2 << "\":\n";
    for (const string& ip : ips2) cout << ip << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(1) constant time. At most 3 * 3 * 3 = 27 combinations are evaluated.
- Space Complexity: O(1) auxiliary space (excluding the output vector).

Key Takeaways:
- When the number of split points is small and fixed (3 dots), nested loops are vastly 
  simpler and faster than general recursion trees.
*/
