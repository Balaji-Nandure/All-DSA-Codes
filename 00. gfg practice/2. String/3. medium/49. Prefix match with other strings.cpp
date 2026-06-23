/*
    Problem Name: Prefix match with other strings
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an array of strings arr[], a string str and an integer k. Find the count of strings in arr[] whose prefix of length k matches with the k-length prefix of str.

    Expected Complexities:
    Time Complexity: O(n * k), where n is the number of strings and k is the length of prefix.
    Space Complexity: O(k) for extracting the prefix substring.

    Love Babbar Style Approach:
    1. Base Case: If the given `k` is greater than the length of `str`, it's impossible to form a prefix of length `k`. Hence, return 0.
    2. Initialization: Extract the prefix of length `k` from `str` and store it in `target`. Initialize a `count` variable to 0.
    3. Traversal: Iterate over each string in `arr`:
       - Check if the length of the current string is at least `k`.
       - Check if its prefix of length `k` matches the `target`.
       - If both conditions are met, increment `count`.
    4. Result: Return the final `count`.

    Dry Run:
    Input: arr = ["abba", "abbb", "abbc", "abbd", "abaa", "abca"], str = "abbg", k = 3
    - str.length() = 4 >= 3, valid.
    - target = str.substr(0, 3) = "abb".
    Iteration:
    - "abba": length 4 >= 3, prefix = "abb". Matches target! count = 1.
    - "abbb": length 4 >= 3, prefix = "abb". Matches target! count = 2.
    - "abbc": length 4 >= 3, prefix = "abb". Matches target! count = 3.
    - "abbd": length 4 >= 3, prefix = "abb". Matches target! count = 4.
    - "abaa": length 4 >= 3, prefix = "aba". Does not match.
    - "abca": length 4 >= 3, prefix = "abc". Does not match.
    Result: Return 4.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
  public:
    // Function to handle the vector of strings (if GFG template uses vector)
    int klengthpref(vector<string>& arr, int k, string str) {
        if (k > str.length()) {
            return 0;
        }
        
        string target = str.substr(0, k);
        int count = 0;
        
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i].length() >= k && arr[i].substr(0, k) == target) {
                count++;
            }
        }
        
        return count;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            vector<string> arr(n);
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            int k;
            cin >> k;
            string str;
            cin >> str;
            
            Solution ob;
            cout << ob.klengthpref(arr, k, str) << "\n";
        }
    }
    return 0;
}
