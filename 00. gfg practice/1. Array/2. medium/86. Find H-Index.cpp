/*
Problem: Find H-Index

GFG: https://www.geeksforgeeks.org/problems/find-h-index--165609/1

Description:
You are given an array citations[], where each element citations[i] represents the number of citations received by the ith paper of a researcher. You have to calculate the researcher's H-index.
The H-index is defined as the maximum value H, such that the researcher has published at least H papers, and all those papers have citation value greater than or equal to H.

Examples:

Input: citations[] = [3, 0, 5, 3, 0]
Output: 3
Explanation: There are at least 3 papers with citation counts of 3, 5, and 3, all having citations greater than or equal to 3.

Input: citations[] = [5, 1, 2, 4, 1]
Output: 2
Explanation: There are 3 papers (with citation counts of 5, 2, and 4) that have 2 or more citations. However, the H-Index cannot be 3 because there aren't 3 papers with 3 or more citations.

Input: citations[] = [0, 0]
Output: 0
Explanation: The H-index is 0 because there are no papers with at least 1 citation.

Constraints:
1 ≤ citations.size() ≤ 10^6
0 ≤ citations[i] ≤ 10^6

Approach (Counting / Bucket Technique):
H-index = maximum H such that at least H papers have citations >= H

Key observation: H-index can NEVER exceed number of papers (n)

Algorithm:
1. Create bucket count[0...n]
2. For every citation c:
   if c >= n: bucket[n]++
   else: bucket[c]++
3. Traverse from n -> 0, maintaining papers count
4. First h where papers >= h is answer

Why it works:
- Uses frequency counting instead of sorting
- O(n) time vs O(n log n) for sorting
- Bounds citations by n since H-index ≤ n

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
        
        int n = citations.size();
        
        vector<int> bucket(n + 1, 0);
        
        // Count frequencies
        for (int c : citations) {
            
            if (c >= n) {
                bucket[n]++;
            } else {
                bucket[c]++;
            }
        }
        
        int papers = 0;
        
        // Traverse from high -> low
        for (int h = n; h >= 0; h--) {
            
            papers += bucket[h];
            
            if (papers >= h) {
                return h;
            }
        }
        
        return 0;
    }
};
