#include <bits/stdc++.h>
using namespace std;

/*
 * @brief   PascalCase Pattern Matching (GeeksforGeeks)
 * @link    https://practice.geeksforgeeks.org/problems/pascalcase-pattern-matching/1
 *
 * Problem Statement:
 *   Given a dictionary of words arr[] where each word follows PascalCase notation,
 *   print/return all words in the dictionary that match with a given pattern pat consisting
 *   of uppercase characters only.
 *   A word matches the pattern if the sequence of its uppercase letters, when concatenated,
 *   forms a string that has pat as a prefix.
 *
 * Approach (Love Babbar Style - 3 Golden Steps):
 *   1️⃣ **Extract UpperCase sequence:** For each word in arr[], we scan its characters.
 *       Whenever we find an uppercase character, we append it to a temporary string.
 *   2️⃣ **Prefix matching:** We check if the temporary uppercase string starts with the pattern string `pat`.
 *       This means `temp.size() >= pat.size()` and `temp.substr(0, pat.size()) == pat`.
 *   3️⃣ **Return Results:** If a word matches, add it to our result list. If no words match,
 *       the driver code or the function should return an empty list (some GFG versions print -1 if the list is empty).
 *
 * Constraints:
 *   1 <= arr.size() <= 1000
 *   1 <= pat.size() <= 100
 *   1 <= arr[i].size() <= 100
 *
 * Complexity Analysis:
 *   - Time Complexity: O(N * L) where N is the number of words in arr and L is the max length of a word.
 *     We process each character of each word at most once.
 *   - Space Complexity: O(L) to store the uppercase string for each word.
 */

class Solution {
public:
    vector<string> pascalCase(vector<string>& arr, string pat) {
        vector<string> ans;
        int pat_len = pat.size();
        
        for (const string &word : arr) {
            string upper_seq = "";
            for (char c : word) {
                if (isupper(c)) {
                    upper_seq += c;
                }
            }
            
            // Check if 'pat' is a prefix of 'upper_seq'
            if (upper_seq.size() >= pat_len && upper_seq.substr(0, pat_len) == pat) {
                ans.push_back(word);
            }
        }
        
        return ans;
    }
};

// Driver code (optional, for local testing)
int main() {
    Solution sol;
    vector<string> arr1 = {"WelcomeGeek", "WelcomeToGeeksForGeeks", "GeeksForGeeks"};
    string pat1 = "WTG";
    vector<string> res1 = sol.pascalCase(arr1, pat1);
    
    cout << "Test 1 Matches: ";
    for (string s : res1) cout << s << " ";
    cout << endl;

    vector<string> arr2 = {"Hi", "Hello", "HelloWorld", "HiTech", "HiGeek", "HiTechWorld", "HiTechCity", "HiTechLab"};
    string pat2 = "HA";
    vector<string> res2 = sol.pascalCase(arr2, pat2);
    
    cout << "Test 2 Matches (should be empty): ";
    for (string s : res2) cout << s << " ";
    cout << endl;

    return 0;
}
