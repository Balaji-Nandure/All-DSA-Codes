/*
 * Problem: Letter Combinations of a Phone Number
 * 
 * LeetCode 17: Letter Combinations of a Phone Number
 * GeeksforGeeks: https://www.geeksforgeeks.org/iterative-letter-combinations-of-a-phone-number/
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Mapping of digits to corresponding letters
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
    // Base case: all digits processed
    if (idx == digits.size()) {
        result.push_back(current);
        return;
    }
    int digit = digits[idx] - '0';
    string letters = mapping[digit];
    for (char c : letters) {
        current.push_back(c);
        letterCombinations(digits, idx + 1, current, result);
        // backtrack
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
