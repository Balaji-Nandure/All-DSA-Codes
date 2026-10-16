// Problem: Find Duplicate Characters in a String
// Link: NA (Direct GFG Standard Interview Question)
// Article: https://www.geeksforgeeks.org/dsa/print-all-the-duplicates-in-the-input-string/
// Difficulty: Easy
// Topic: String, Hashing, Frequency Array

/*
Problem Statement:
Given a string s, print all the duplicate characters and their respective counts 
in the string. Only characters that appear more than once should be printed.

Example 1:
Input: s = "geeksforgeeks"
Output:
'e' count = 4
'g' count = 2
'k' count = 2
's' count = 2

Example 2:
Input: s = "test string"
Output:
't' count = 3
's' count = 2

Constraints:
- 1 <= s.length() <= 10^5
- String can contain ASCII printable characters (alphanumeric, spaces, symbols).
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 2 (Check Palindrome):
//   * Character identity was compared pairwise based on spatial positions (left vs right).
// - In Problem 3 (Find Duplicate Characters):
//   * Spatial position does not matter at all; we only care about GLOBAL FREQUENCY across the entire string!
//   * Because character alphabets are small and finite (ASCII is 128 or 256 characters), 
//     we can replace heavy hash tables with a fixed-size `int freq[256]` array. 
//     This gives true O(1) space and zero hash collisions.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Sorting
//   - Sort the string: `sort(s.begin(), s.end())`. Consecutive identical characters are duplicates.
//   - Complexity: O(N log N) time, O(1) or O(N) space.
//   - Why Suboptimal: Destroys original string ordering and is slower than linear scanning.
//
// Approach 2: Hash Map (`std::unordered_map<char, int>`)
//   - Count frequencies in map, then iterate and print counts > 1.
//   - Complexity: O(N) average time, O(U) space where U is distinct characters.
//   - Why Good: Flexible if characters are arbitrary Unicode.
//
// Approach 3: Fixed-Size Frequency Array (Optimal & Chosen)
//   - Maintain `int count[256] = {0}` representing all extended ASCII characters.
//   - In a single pass, increment `count[(unsigned char)ch]++`.
//   - In a second pass over the 256 buckets, collect every character where `count[i] > 1`.
//   - Complexity: O(N + 256) = O(N) time, O(256) = O(1) auxiliary space!
//   - Why this approach: Pure array indexing avoids all hashing overhead, pointer chasing, 
//     and dynamic allocations.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct DuplicateInfo {
    char ch;
    int count;
};

class Solution {
public:
    vector<DuplicateInfo> findDuplicates(const string& s) {
        vector<DuplicateInfo> duplicates;

        // Fixed-size frequency array for all 256 ASCII characters
        int freq[256] = {0};

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Direct ASCII index mapping: Cast to (unsigned char) to prevent negative index
        // errors if extended ASCII characters (128-255) are encountered in signed char systems!
        for (char ch : s) {
            freq[(unsigned char)ch]++;
        }

        // Iterate through all possible ASCII characters to find duplicates
        for (int i = 0; i < 256; ++i) {
            if (freq[i] > 1) {
                duplicates.push_back({(char)i, freq[i]});
            }
        }

        return duplicates;
    }
};

int main() {
    Solution sol;
    string s = "geeksforgeeks";

    cout << "Duplicates in \"" << s << "\":\n";
    vector<DuplicateInfo> dups = sol.findDuplicates(s);
    for (const auto& d : dups) {
        cout << "'" << d.ch << "' -> count: " << d.count << "\n";
    }

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N + 256) = O(N) linear time, where N is length of string.
- Space Complexity: O(256) = O(1) auxiliary space (fixed-size array of 256 integers).

Key Takeaways:
- Always use `(unsigned char)` when indexing arrays with `char` to guard against negative indices.
- Fixed-size frequency array is always faster and leaner than `unordered_map` for ASCII inputs.
*/
