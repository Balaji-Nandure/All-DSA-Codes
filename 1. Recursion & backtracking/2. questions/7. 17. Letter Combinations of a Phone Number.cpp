/*
 * Problem: Letter Combinations of a Phone Number
 * 
 * LeetCode 17: Letter Combinations of a Phone Number
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/possible-words-from-phone-digits/0
 *
 * Given a string containing digits from 2-9, return all possible letter combinations.
 * Mapping: 2->abc, 3->def, 4->ghi, 5->jkl, 6->mno, 7->pqrs, 8->tuv, 9->wxyz
 *
 * Example: "23" -> ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *
 * Time: O(4^n * n) - 4^n combinations (max 4 letters per digit), each copied in O(n)
 * Space: O(n) - recursion stack depth is n
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Mapping of digits to corresponding letters (old phone keypad)
const string mapping[] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9
};

void letterCombinations(string digits, int idx, string &current, vector<string>& result) {
    // Base case: processed all digits, add current combination
    if (idx == digits.size()) {
        result.push_back(current);
        return;
    }
    // Get letters corresponding to current digit
    int digit = digits[idx] - '0';
    string letters = mapping[digit];
    // Try each letter for current digit
    for (char c : letters) {
        current.push_back(c);
        // Recurse for next digit
        letterCombinations(digits, idx + 1, current, result);
        // Backtrack: remove current letter to try next
        current.pop_back();
    }
}

int main() {
    string digits;
    cin >> digits;
    vector<string> result;
    letterCombinations(digits, 0, "", result);
    for (const string& s : result) {
        cout << s << endl;
    }
    return 0;
}
