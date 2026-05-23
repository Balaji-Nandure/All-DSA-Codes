/*
Problem: Winner of an election

GFG: https://www.geeksforgeeks.org/problems/winner-of-an-election-where-votes-are-represented-as-candidate-names-1587115621/1

Description:
Given array of n candidate names (votes), find candidate with max votes.
If tie, return lexicographically smaller name.

Examples:

Input: arr[] = {john,johnny,jackie,johnny,john,jackie,jamie,jamie,john,johnny,jamie,johnny,john}
Output: john 4

Input: arr[] = {andy,blake,clark}
Output: andy 1

Constraints:
1 ≤ n ≤ 10^5

Approach (Map):
- Count votes using map (sorted keys for lexicographic tie-breaking)
- Track max votes; on tie, map's sorted order gives smaller name first

Dry Run: arr = {john, johnny, john, johnny, john}
  Map: {john:3, johnny:2}  (map keeps sorted order)
  Iterate: john(3) → winner, johnny(2) → skip
  Result: "john 3" ✅

Time Complexity: O(n log n) — map insertions
Space Complexity: O(n) — map entries
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(n log n)  SC: O(n)
    vector<string> winner(string arr[], int n) {

        map<string, int> votes;  // sorted map for lexicographic order

        for(int i = 0; i < n; i++) votes[arr[i]]++;

        string winnerName = "";
        int maxVotes = 0;

        for(auto& p : votes) {
            if(p.second > maxVotes) {
                maxVotes = p.second;
                winnerName = p.first;
            }
        }

        return {winnerName, to_string(maxVotes)};
    }
};
