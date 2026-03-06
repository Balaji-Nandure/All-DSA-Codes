/*
 * Problem: Frogs and Jumps
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/frogs-and-jumps/1
 * 
 * N frogs are positioned at one end of the pond. All frogs want to reach the other 
 * end of the pond as soon as possible. The pond has some leaves arranged in a 
 * straight line. Each frog has the strength to jump exactly K leaves. For example, 
 * a frog having strength 2 will visit the leaves 2, 4, 6, ... etc. while crossing the pond.
 * 
 * Given the strength of each frog and the number of leaves, your task is to find 
 * the number of leaves that not be visited by any of the frogs when all frogs have 
 * reached the other end of the pond.
 * 
 * Examples:
 * Input: N = 3, leaves = 4, frogs[] = {3, 2, 4}
 * Output: 1
 * Explanation: Leaf 1 will not be visited by any frog.
 * 
 * Input: N = 3, leaves = 6, frogs[] = {1, 3, 5}
 * Output: 0
 * Explanation: First frog will visit all the leaves so no leaf is left unvisited.
 * 
 * Constraints:
 * 1 ≤ N, leaves, frogs[i] ≤ 10^5
 * 
 * Expected Time Complexity: O(N*log(leaves))
 * Expected Auxiliary Space: O(leaves)
 * 
 * Approach:
 * - Use sieve-like approach to mark visited leaves
 * - Create boolean array to track visited leaves
 * - Use unordered_set to handle duplicate frog strengths
 * - For each unique frog strength K, mark multiples K, 2K, 3K, ... <= leaves
 * - Count leaves that remain unvisited
 * - If any frog has strength 1, all leaves are visited (optimization)
 * 
 * Time: O(N*log(leaves)) - sieve marking for each frog
 * Space: O(leaves) - visited array
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int unvisitedLeaves(int N, int leaves, vector<int>& frogs) {
        
        vector<bool> visited(leaves + 1, false);
        
        unordered_set<int> uniqueFrogs(frogs.begin(), frogs.end());
        
        for (int k : uniqueFrogs) {
            
            if (k > leaves) continue;
            
            for (int i = k; i <= leaves; i += k) {
                visited[i] = true;
            }
        }
        
        int count = 0;
        
        for (int i = 1; i <= leaves; i++) {
            if (!visited[i]) count++;
        }
        
        return count;
    }
};
