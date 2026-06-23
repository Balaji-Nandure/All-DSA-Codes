/*
    Problem Name: Alternate Vowel and Consonant String
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a string s of lowercase english characters. Return the lexicographically (alphabetically) smallest string after rearranging characters of the given string such that the vowels and consonants occupy alternate positions.
    If it is not possible to form such a string, return "-1".

    Expected Complexities:
    Time Complexity: O(N), where N is the length of the string. The character counts take O(N) and appending takes O(N).
    Space Complexity: O(1) auxiliary space, as we only use two frequency arrays of size 26.

    Love Babbar Style Approach:
    1. Frequency Count: We create two frequency arrays, one for vowels and one for consonants, to keep track of character counts. We also keep a tally of total vowels `V` and total consonants `C`.
    2. Validity Check: For an alternating sequence to be possible, the difference between the number of vowels and consonants cannot exceed 1. If `abs(V - C) > 1`, we immediately return "-1".
    3. Determining the First Character: 
       - If `V > C`, a vowel MUST come first.
       - If `C > V`, a consonant MUST come first.
       - If `V == C`, we can start with either. To achieve the lexicographically smallest string, we compare the smallest available vowel with the smallest available consonant. The one that comes first alphabetically will be the starting character type.
    4. Building the String: We use a loop of length `N`. Based on whose `turn` it is, we iterate through our frequency array (from 'a' to 'z'), pick the first available character of that type, append it to our result, decrement its frequency, and switch the `turn`.
    5. Result: Because we always pick the first available character from 'a' to 'z', the resulting string will naturally be the lexicographically smallest.

    Dry Run:
    Input: s = "aeroplane"
    - Vowels (V): 5 ('a'=2, 'e'=2, 'o'=1)
    - Consonants (C): 4 ('l'=1, 'n'=1, 'p'=1, 'r'=1)
    - Check: |5 - 4| = 1 <= 1. Valid.
    - Start: V > C, so turn = 0 (vowel).
    Iteration:
    - turn = 0 (vowel): smallest available is 'a'. Result = "a". turn = 1.
    - turn = 1 (cons): smallest available is 'l'. Result = "al". turn = 0.
    - turn = 0 (vowel): smallest available is 'a'. Result = "ala". turn = 1.
    - turn = 1 (cons): smallest available is 'n'. Result = "alan". turn = 0.
    - turn = 0 (vowel): smallest available is 'e'. Result = "alane". turn = 1.
    - turn = 1 (cons): smallest available is 'p'. Result = "alanep". turn = 0.
    - turn = 0 (vowel): smallest available is 'e'. Result = "alanepe". turn = 1.
    - turn = 1 (cons): smallest available is 'r'. Result = "alaneper". turn = 0.
    - turn = 0 (vowel): smallest available is 'o'. Result = "alanepero". turn = 1.
    Result: "alanepero"
*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Solution {
  private:
    bool isVowel(char ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

  public:
    string rearrange(string S, int N) {
        vector<int> v_freq(26, 0);
        vector<int> c_freq(26, 0);
        int V = 0, C = 0;
        
        for (char ch : S) {
            if (isVowel(ch)) {
                v_freq[ch - 'a']++;
                V++;
            } else {
                c_freq[ch - 'a']++;
                C++;
            }
        }
        
        if (abs(V - C) > 1) {
            return "-1";
        }
        
        int turn = 0; // 0 for vowel, 1 for consonant
        
        if (V > C) {
            turn = 0;
        } else if (C > V) {
            turn = 1;
        } else {
            // Compare smallest vowel and smallest consonant
            int v_min = -1, c_min = -1;
            for (int i = 0; i < 26; i++) {
                if (v_freq[i] > 0) {
                    v_min = i;
                    break;
                }
            }
            for (int i = 0; i < 26; i++) {
                if (c_freq[i] > 0) {
                    c_min = i;
                    break;
                }
            }
            if (v_min < c_min) {
                turn = 0;
            } else {
                turn = 1;
            }
        }
        
        string ans = "";
        for (int i = 0; i < N; i++) {
            if (turn == 0) {
                for (int j = 0; j < 26; j++) {
                    if (v_freq[j] > 0) {
                        ans += (char)(j + 'a');
                        v_freq[j]--;
                        break;
                    }
                }
                turn = 1;
            } else {
                for (int j = 0; j < 26; j++) {
                    if (c_freq[j] > 0) {
                        ans += (char)(j + 'a');
                        c_freq[j]--;
                        break;
                    }
                }
                turn = 0;
            }
        }
        
        return ans;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            string s;
            cin >> s;
            Solution ob;
            cout << ob.rearrange(s, n) << "\n";
        }
    }
    return 0;
}
