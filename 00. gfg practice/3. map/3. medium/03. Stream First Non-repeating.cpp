/*
    Problem Name: Stream First Non-repeating
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a string s consisting of only lowercase alphabets, for each index i in the string (0 <= i < n), find the first non-repeating character in the prefix s[0..i]. If no such character exists, use '#'.

    Expected Complexities:
    Time Complexity: O(N), where N is the length of the string. Each character is pushed and popped from the queue at most once.
    Space Complexity: O(N) in the worst case for the queue, but practically bounded heavily, and O(26) for the frequency array, thus O(N) overall.

    Love Babbar Style Approach:
    1. Tracking Frequencies and Order: We need two things to solve this: the count of each character to know if it's repeating, and the order of characters to know which one came "first".
    2. Data Structures: 
       - An integer array (or map) `freq` of size 26 to keep track of character frequencies.
       - A `queue` to keep track of the stream of characters in the order they arrived.
    3. Processing the Stream: We iterate through each character in the string `s`:
       - First, we increment the frequency of the current character in our `freq` array.
       - Second, we push the current character into our `queue`.
       - Third, we check the character at the front of the queue. If its frequency is greater than 1, it means it is repeating and can no longer be our answer. We pop it from the queue. We repeat this checking process until the front character has a frequency of exactly 1, or the queue becomes empty.
    4. Building the Result: After the cleanup, if the queue is empty, there is no non-repeating character, so we append `#` to our answer. If the queue is not empty, the front element is our first non-repeating character, so we append it.
    5. Result: Return the final string.

    Dry Run:
    Input: s = "aabc"
    - i = 0 ('a'): freq['a']=1. queue=['a']. Front 'a' freq=1. Append 'a'. ans="a"
    - i = 1 ('a'): freq['a']=2. queue=['a', 'a']. Front 'a' freq=2 (repeating), pop it. Next front 'a' freq=2 (repeating), pop it. queue is empty. Append '#'. ans="a#"
    - i = 2 ('b'): freq['b']=1. queue=['b']. Front 'b' freq=1. Append 'b'. ans="a#b"
    - i = 3 ('c'): freq['c']=1. queue=['b', 'c']. Front 'b' freq=1. Append 'b'. ans="a#bb"
    Result: "a#bb"
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Solution {
  public:
    string FirstNonRepeating(string s) {
        vector<int> freq(26, 0);
        queue<char> q;
        string ans = "";
        
        for (char c : s) {
            freq[c - 'a']++;
            q.push(c);
            
            while (!q.empty()) {
                if (freq[q.front() - 'a'] > 1) {
                    q.pop();
                } else {
                    break;
                }
            }
            
            if (q.empty()) {
                ans += '#';
            } else {
                ans += q.front();
            }
        }
        
        return ans;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            string s;
            cin >> s;
            Solution ob;
            cout << ob.FirstNonRepeating(s) << "\n";
        }
    }
    return 0;
}
