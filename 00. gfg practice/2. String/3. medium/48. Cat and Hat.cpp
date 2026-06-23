/*
    Problem Name: Cat and Hat
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    You are given a string s, you need to return True if the words "cat" and "hat" appear same number of times in s, otherwise return False.
    Note: s contains only lowercase English alphabets.

    Expected Complexities:
    Time Complexity: O(N), where N is the length of string s.
    Space Complexity: O(1)

    Love Babbar Style Approach:
    1. Base Case: If the length of the string is less than 3, neither "cat" nor "hat" can exist, so their count will both be 0, return true.
    2. Initialization: We initialize two variables `cat_count` and `hat_count` to 0.
    3. Traversal: We traverse the string from index 0 to `s.length() - 3`.
       - If the 3 characters starting at index `i` form "cat", we increment `cat_count`.
       - If the 3 characters starting at index `i` form "hat", we increment `hat_count`.
    4. Result: Return whether `cat_count` is equal to `hat_count`.

    Dry Run:
    Input: s = "catinahat"
    Initialization: cat_count = 0, hat_count = 0
    Iteration:
    - i = 0: "cat" -> matches "cat", cat_count = 1
    - i = 1: "ati" -> no match
    - i = 2: "tin" -> no match
    - i = 3: "ina" -> no match
    - i = 4: "nah" -> no match
    - i = 5: "aha" -> no match
    - i = 6: "hat" -> matches "hat", hat_count = 1
    End of loop.
    Result: cat_count (1) == hat_count (1) -> return True.
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
  public:
    bool cat_hat(string str) {
        int n = str.length();
        if (n < 3) return true; // 0 occurrences for both
        
        int cat_count = 0;
        int hat_count = 0;
        
        for (int i = 0; i <= n - 3; i++) {
            if (str[i] == 'c' && str[i+1] == 'a' && str[i+2] == 't') {
                cat_count++;
            } else if (str[i] == 'h' && str[i+1] == 'a' && str[i+2] == 't') {
                hat_count++;
            }
        }
        
        return cat_count == hat_count;
    }
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        Solution ob;
        if (ob.cat_hat(s))
            cout << "True\n";
        else
            cout << "False\n";
    }
    return 0;
}
