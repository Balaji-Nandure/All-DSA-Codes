/*
GeeksforGeeks: Distinct Permutations of a String
Difficulty: Medium

Problem:
Given a string s, which may contain duplicate characters, your task is to generate and return an array of all unique permutations of the string. You can return your answer in any order.

Examples:
Input: s = "ABC"
Output: ["ABC", "ACB", "BAC", "BCA", "CAB", "CBA"]
Explanation: Given string ABC has 6 unique permutations.

Input: s = "AAA"
Output: ["AAA"]
Explanation: No other unique permutations can be formed as all the characters are same.

Core Idea:
Generating permutations is a classic Backtracking problem. 
To handle duplicates (like "AAB"), we must ensure we don't pick the exact same character for the exact same position multiple times during our recursive exploration.
The most optimal way to handle this—without using a slow Hash Set to filter duplicates at the very end—is:
1. Sort the string initially. This forces all identical characters to sit adjacent to each other.
2. During backtracking, if the current character is the same as the previous character, AND the previous character was NOT used in the current branch (meaning we literally just finished exploring an entire tree with it in this exact position), we skip it!

(Note: In C++, `std::next_permutation` automatically handles duplicates when called in a `do-while` loop on a sorted string. However, the Backtracking method below is the fundamental algorithmic approach expected in DSA technical interviews to prove you understand recursion branches).

Approach:
1. Sort the input string `S` to group duplicates.
2. Use a `visited` boolean `vector` to track which character indices are currently actively included in our building string.
3. In the `backtrack` function:
   - Base Case: If the `current` string length equals `S.length()`, we've formed a full permutation. Add it to results and return.
   - Loop `i` from 0 to N-1:
     - If `visited[i]` is true, skip (character already in use).
     - **Duplicate Skipping Magic:** `if (i > 0 && S[i] == S[i-1] && !visited[i-1]) continue;`
     - Mark `visited[i] = true`.
     - Append `S[i]` to `current`.
     - Recursively call `backtrack`.
     - Backtrack: Pop from `current` and set `visited[i] = false`.
4. Return the results.

Time Complexity: O(N * N!), where N is the length of the string. There are at most N! unique permutations, and copying each to the result array takes O(N) time.
Space Complexity: O(N) auxiliary stack space for the recursion depth, and O(N) for the `visited` vector and `current` string.

GFG Link: https://www.geeksforgeeks.org/problems/permutations-of-a-given-string2041/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    void backtrack(string& S, string& current, vector<bool>& visited, vector<string>& result) {
        // Base case: Full permutation formed
        if (current.length() == S.length()) {
            result.push_back(current);
            return;
        }
        
        for (int i = 0; i < S.length(); i++) {
            // If character is already used in the current permutation branch, skip it
            if (visited[i]) continue;
            
            // Skip duplicates:
            // If it's the same as the previous char, and the previous char is NOT visited 
            // (meaning we just finished an entire recursive tree using that previous identical char in THIS exact slot), 
            // we must skip it to prevent identical duplicate permutations.
            if (i > 0 && S[i] == S[i - 1] && !visited[i - 1]) {
                continue;
            }
            
            // Choose
            visited[i] = true;
            current.push_back(S[i]);
            
            // Explore
            backtrack(S, current, visited, result);
            
            // Un-choose (Backtrack)
            current.pop_back();
            visited[i] = false;
        }
    }

public:
    vector<string> find_permutation(string S) {
        vector<string> result;
        
        // Sorting is crucial so duplicate characters sit next to each other
        sort(S.begin(), S.end());
        
        vector<bool> visited(S.length(), false);
        string current = "";
        
        backtrack(S, current, visited, result);
        
        return result;
    }
};

/*
Dry Run — Example:
Input: S = "AAB" (already sorted)
visited = [F, F, F]

Call backtrack():
1. i=0 ('A'):
   visited = [T, F, F], current = "A"
   Call backtrack():
     i=0: visited. Skip.
     i=1 ('A'): 
       visited = [T, T, F], current = "AA"
       Call backtrack():
         i=0, i=1: visited. Skip.
         i=2 ('B'): 
           visited = [T, T, T], current = "AAB" -> ADDED TO RESULT
           Backtrack -> visited = [T, T, F], current = "AA"
       Backtrack -> visited = [T, F, F], current = "A"
     i=2 ('B'):
       visited = [T, F, T], current = "AB"
       Call backtrack():
         i=0: visited.
         i=1 ('A'):
           visited = [T, T, T], current = "ABA" -> ADDED TO RESULT
           Backtrack -> visited = [T, F, T], current = "AB"
       Backtrack -> visited = [T, F, F], current = "A"
   Backtrack -> visited = [F, F, F], current = ""
   
2. i=1 ('A'):
   Duplicates check: S[1] == S[0] ('A'=='A'), and visited[0] is FALSE!
   (Because we just finished the entire tree starting with S[0] and un-visited it).
   We SKIP i=1 completely! This successfully prevents us from generating "AAB" and "ABA" a second time!

3. i=2 ('B'):
   visited = [F, F, T], current = "B"
   Call backtrack():
     i=0 ('A'):
       visited = [T, F, T], current = "BA"
       Call backtrack():
         i=1 ('A'):
           visited = [T, T, T], current = "BAA" -> ADDED TO RESULT
           Backtrack
       Backtrack
     i=1 ('A'):
       Duplicates check: S[1] == S[0], visited[0] is FALSE! -> SKIP!
   Backtrack -> visited = [F, F, F], current = ""

Final Result: ["AAB", "ABA", "BAA"]
*/
