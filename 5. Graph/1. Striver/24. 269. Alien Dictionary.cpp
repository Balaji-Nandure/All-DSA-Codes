// Problem: 269. Alien Dictionary
// Link (LeetCode): https://leetcode.com/problems/alien-dictionary/ (Premium)
// Link (GFG): https://www.geeksforgeeks.org/problems/alien-dictionary/1
// Difficulty: Hard
// Topic: Graph, BFS, Kahn's Algorithm, Topological Sort, Directed Graph, In-degree, String

/*
Problem Statement:
Given a sorted dictionary of an alien language having N words of size K (where characters are from the 
first K characters of the English alphabet):
Find the order of characters in the alien language.

If multiple orders are valid, return any valid order.
If the ordering is impossible/contradictory (cycle exists or invalid prefix), return an empty string "".

Example 1:
Input: words = ["baa", "abcd", "abca", "cab", "cad"], k = 4
Output: "bdac"
Explanation:
- "baa" comes before "abcd" -> 'b' appears before 'a' (b -> a)
- "abcd" comes before "abca" -> 'd' appears before 'a' (d -> a)
- "abca" comes before "cab" -> 'a' appears before 'c' (a -> c)
- "cab" comes before "cad" -> 'b' appears before 'd' (b -> d)
Order of characters: b -> d -> a -> c => "bdac".

Example 2:
Input: words = ["caa", "aaa", "aab"], k = 3
Output: "cab"
Explanation:
- "caa" before "aaa" -> 'c' appears before 'a' (c -> a)
- "aaa" before "aab" -> 'a' appears before 'b' (a -> b)
Order: c -> a -> b => "cab".

Example 3 (Invalid Order / Prefix Edge Case):
Input: words = ["abc", "ab"]
Output: ""
Explanation: "ab" is a prefix of "abc". A longer word cannot appear before a shorter prefix in a sorted dictionary.

Constraints:
- 1 <= N <= 10^4
- 1 <= K <= 26
- 1 <= words[i].length <= 100
- All characters in words are lowercase English letters.
*/

// Approach: Graph Construction + Kahn's Algorithm (Topological Sort)
// 1. Problem Formulation:
//    - We have words listed in lexicographically sorted order.
//    - If word1 appears before word2, compare them character by character.
//    - At the FIRST position where word1[j] != word2[j]:
//      * word1[j] must precede word2[j] in the alien alphabet!
//      * This establishes a directed dependency edge: word1[j] -> word2[j].
//      * Stop comparing word1 and word2 after the first mismatch.
// 2. Prefix Edge Case:
//    - If word2 is a proper prefix of word1 (e.g. "apple" before "app"), the ordering is invalid -> return "".
// 3. Finding the Alphabet Order (Topological Sort):
//    - The problem reduces to finding a linear order for the directed graph (Topological Sort).
//    - Apply Kahn's Algorithm (BFS):
//      Step 1: Calculate in-degree for all K vertices.
//      Step 2: Push vertices with in-degree 0 into a queue.
//      Step 3: Pop node, append (char)(node + 'a') to result string.
//              Decrement in-degree of its neighbors; if in-degree == 0, push to queue.
//      Step 4: If result.size() < K, a cycle exists (contradiction) -> return "".
//              Otherwise, return result.

#include <bits/stdc++.h>
using namespace std;

// GFG Format: with given 'k' characters ('a' to 'a' + k - 1)
class Solution {
public:
    string findOrder(vector<string>& words, int k) {
        vector<vector<int>> adj(k);

        // Step 1: Compare adjacent words to build directed edges
        for (int i = 0; i < (int)words.size() - 1; i++) {
            string s1 = words[i];
            string s2 = words[i + 1];
            int len = min(s1.length(), s2.length());
            bool foundMismatch = false;

            for (int j = 0; j < len; j++) {
                if (s1[j] != s2[j]) {
                    // s1[j] must come before s2[j] in alphabet order
                    adj[s1[j] - 'a'].push_back(s2[j] - 'a');
                    foundMismatch = true;
                    break; // Only the first differing character determines relative order
                }
            }

            // Prefix edge case: e.g. "abcd" before "ab" is invalid
            if (!foundMismatch && s1.length() > s2.length()) {
                return "";
            }
        }

        // Step 2: Calculate in-degree for all k vertices (Striver's loop)
        vector<int> indegree(k, 0);
        for (int i = 0; i < k; i++) {
            for (auto it : adj[i]) {
                indegree[it]++;
            }
        }

        // Step 3: Push all characters with in-degree == 0 into queue
        queue<int> q;
        for (int i = 0; i < k; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        string order = "";

        // Step 4: BFS Traversal (Kahn's Algorithm)
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            order += (char)(node + 'a');

            for (auto it : adj[node]) {
                indegree[it]--;
                if (indegree[it] == 0) {
                    q.push(it);
                }
            }
        }

        // If order contains all k characters, valid DAG -> return order
        // If order.size() < k, cycle exists -> return ""
        if ((int)order.size() == k) {
            return order;
        }

        return "";
    }
};

/*
Time Complexity: O(N * L + K)
- N = number of words, L = maximum length of a word.
- Comparing adjacent words: O(N * L) in the worst case.
- Calculating in-degrees and Kahn's BFS: O(K + E), where K <= 26 and E <= K^2.
- Overall Time Complexity: O(N * L + K)

Space Complexity: O(K + E)
- Adjacency list: at most K vertices and K*(K-1) edges.
- In-degree array: O(K).
- Queue: O(K).
- Since K <= 26, auxiliary graph space is O(1) in practice.
- Overall Auxiliary Space: O(K + E).

Key Insights:
1. Why Only Compare Adjacent Words?
   - If A < B and B < C, then by transitivity A < C.
   - We only need to compare each word with its immediate next neighbor (words[i] and words[i+1]).
2. First Differing Character Only:
   - In dictionary sorting, once the first mismatch is found (e.g., "abcd" vs "abza" -> 'c' vs 'z'),
     all subsequent characters are irrelevant for relative character ordering.
3. Two Failure Modes:
   - Prefix violation: A longer word comes before its shorter prefix ("abcd" before "ab") -> invalid.
   - Cyclic dependency: Characters form a loop (e.g. 'a' -> 'b' and 'b' -> 'a') -> Kahn's returns < K nodes.
*/
