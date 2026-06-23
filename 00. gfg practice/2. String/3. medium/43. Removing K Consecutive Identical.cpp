#include <bits/stdc++.h>
using namespace std;

/*
 * @brief   Removing K Consecutive Identical / Reduced String (GeeksforGeeks)
 * @link    https://practice.geeksforgeeks.org/problems/removing-k-consecutive-identical-characters/1
 *
 * Problem Statement:
 *   Given a string s and an integer k, the task is to reduce the string by removing k consecutive
 *   identical characters. The removal operation can be performed any number of times until it is
 *   no longer possible.
 *
 * Core Intuition / Idea:
 *   - We need to process characters one by one. If we encounter k consecutive identical characters,
 *     we must remove them.
 *   - When characters are removed, the surrounding characters are brought together. This might form
 *     a new set of k consecutive identical characters.
 *   - A stack is perfect for this "nested/recursive" removal.
 *   - Instead of storing just characters, we can store pairs of {character, consecutive count} in the stack.
 *     This allows us to know if the count has reached k in O(1) time.
 *   - If the count reaches k, we simply pop the character group.
 *
 * Approach (Love Babbar Style - 3 Golden Steps):
 *   1️⃣ **Stack of Pairs:** Traverse the string `s`. For each character `c`:
 *       - If stack is not empty and the top character is equal to `c`, increment the frequency count on top of the stack.
 *       - Else, push a new pair `{c, 1}` onto the stack.
 *   2️⃣ **Threshold Check (K):** After updating, if the top element's count equals `k`, pop it from the stack.
 *       This effectively removes the k consecutive identical characters.
 *   3️⃣ **Rebuild Result:** Reconstruct the remaining string from the stack by repeating the characters by their count,
 *       and then reverse the final string (since stack processing is LIFO).
 *
 * Complexity Analysis:
 *   - Time Complexity (TC): O(N) where N is the length of string `s`. Each character is pushed and popped at most once.
 *   - Space Complexity (SC): O(N) in the worst case for stack storage.
 *
 * Dry Run:
 *   k = 2, s = "geegsforgeeeks"
 *   - i=0: 'g' -> stack: [('g', 1)]
 *   - i=1: 'e' -> stack: [('g', 1), ('e', 1)]
 *   - i=2: 'e' -> matches top ('e') -> stack top count becomes 2 -> equals k(2) -> pop. stack: [('g', 1)]
 *   - i=3: 'g' -> matches top ('g') -> stack top count becomes 2 -> equals k(2) -> pop. stack: []
 *   - i=4: 's' -> stack: [('s', 1)]
 *   - i=5: 'f' -> stack: [('s', 1), ('f', 1)]
 *   - i=6: 'o' -> stack: [('s', 1), ('f', 1), ('o', 1)]
 *   - i=7: 'r' -> stack: [('s', 1), ('f', 1), ('o', 1), ('r', 1)]
 *   - i=8: 'g' -> stack: [... ('g', 1)]
 *   - i=9: 'e' -> stack: [... ('e', 1)]
 *   - i=10: 'e' -> stack top becomes ('e', 2) -> pop.
 *   - i=11: 'e' -> stack: [... ('e', 1)]
 *   - i=12: 'k' -> stack: [... ('e', 1), ('k', 1)]
 *   - i=13: 's' -> stack: [... ('e', 1), ('k', 1), ('s', 1)]
 *   - Rebuild stack from bottom to top: "sforgeks".
 */

class Solution {
public:
    string reducedString(int k, string s) {
        if (k == 1) return ""; // If k is 1, all characters will be removed
        
        stack<pair<char, int>> st;
        
        for (char c : s) {
            if (!st.empty() && st.top().first == c) {
                st.top().second++;
            } else {
                st.push({c, 1});
            }
            
            // If the top element reaches consecutive count of k, pop/remove it
            if (st.top().second == k) {
                st.pop();
            }
        }
        
        // Reconstruct string from stack
        string ans = "";
        while (!st.empty()) {
            ans.append(st.top().second, st.top().first);
            st.pop();
        }
        
        // Reverse string as stack is LIFO
        reverse(ans.begin(), ans.end());
        
        return ans;
    }
};

// Driver code (optional, for local testing)
int main() {
    Solution sol;
    vector<pair<int, string>> tests = {
        {2, "geeksforgeeks"}, // Expected: gksforgks
        {2, "geegsforgeeeks"}, // Expected: sforgeks
        {2, "abbac"}          // Expected: c
    };
    
    for (auto &t : tests) {
        cout << "k=" << t.first << ", s=" << t.second 
             << " -> Reduced: " << sol.reducedString(t.first, t.second) << endl;
    }
    return 0;
}
