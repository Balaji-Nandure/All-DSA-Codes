// Problem: Find the First Repeated Word in a String
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/find-first-repeated-character4108/1
// Article: https://www.geeksforgeeks.org/dsa/find-first-repeated-word-string/
// Difficulty: Easy
// Topic: String, Hash Set, Tokenization, Early Termination

/*
Problem Statement:
Given a string containing a sequence of words separated by spaces.
Find the first repeated word in the string.
The "first repeated word" is defined as the word whose SECOND OCCURRENCE appears 
earliest in the sequence. If no word is repeated, return "NoRepetition".

Also include the character-level variant: "Find the first repeated character in a string".

Example 1:
Input: s = "Ravi had been saying that he had been there"
Output: "had"
Explanation: "had" is repeated before "been".

Example 2:
Input: s = "Ravi had been saying that"
Output: "NoRepetition"

Example 3 (Character Variant):
Input: s = "geeksforgeeks"
Output: "e"

Constraints:
- 1 <= s.length() <= 10^5
- String contains English letters and spaces.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 3 (Find Duplicate Characters):
//   * We counted global frequencies of all characters across the entire string.
// - In Problem 29 (First Repeated Word / Character):
//   * We do NOT need to wait until the end of the string!
//   * The requirement is TEMPORAL PRIORITY: Whichever item reaches frequency 2 FIRST 
//     in streaming order is the answer.
//   * Hash Set lookup allows instant O(1) early exit upon the first collision!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Double Pass Frequency Count
//   - Pass 1: Count total frequencies of all words in hash map.
//   - Pass 2: Find the first word with frequency > 1.
//   - Why WRONG: This finds the word whose FIRST occurrence appears earliest, 
//     NOT the word that repeats earliest!
//     E.g., "A B C B A": 'A' appears first, but 'B' REPEATS FIRST!
//
// Approach 2: Streaming Hash Set Lookup (Optimal & Chosen)
//   - Maintain an `unordered_set<string> seenWords`.
//   - Stream tokens using `stringstream`.
//   - For each word:
//       * If `seenWords.count(word)`: Return `word` IMMEDIATELY!
//       * Else: `seenWords.insert(word)`.
//   - Return `"NoRepetition"` if end of stream is reached.
//   - Complexity: O(N) time, O(U) space where U is number of unique words.

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Word-Level Variant: Find First Repeated Word
    // -------------------------------------------------------------------------
    string firstRepeatedWord(const string& s) {
        unordered_set<string> seen;
        stringstream ss(s);
        string word;

        while (ss >> word) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // The instant an element is already present in `seen`, its second occurrence
            // has just arrived in streaming order. Early exit with the answer!
            if (seen.find(word) != seen.end()) {
                return word;
            }
            seen.insert(word);
        }

        return "NoRepetition";
    }

    // -------------------------------------------------------------------------
    // Character-Level Variant (GFG Practice Problem): Find First Repeated Char
    // -------------------------------------------------------------------------
    string firstRepChar(string s) {
        bool seen[256] = {false};

        for (char ch : s) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // First character whose 2nd occurrence is hit
            if (seen[(unsigned char)ch]) {
                return string(1, ch);
            }
            seen[(unsigned char)ch] = true;
        }

        return "-1";
    }
};

int main() {
    Solution sol;
    string s1 = "Ravi had been saying that he had been there";
    cout << "First repeated word in \"" << s1 << "\":\n-> " 
         << sol.firstRepeatedWord(s1) << "\n\n";

    string s2 = "geeksforgeeks";
    cout << "First repeated character in \"" << s2 << "\":\n-> " 
         << sol.firstRepChar(s2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N) where N is string length. Each word/character is checked and inserted once.
- Space Complexity: O(U) auxiliary space where U is the number of distinct words (or O(1) for 256 boolean array).

Key Takeaways:
- "First repeated" means earliest second-occurrence timestamp, which is solved by streaming 
  hash set lookup, distinct from two-pass global frequency maps.
*/
