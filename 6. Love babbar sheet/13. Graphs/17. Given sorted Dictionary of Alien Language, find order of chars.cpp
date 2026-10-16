/**
 * Problem: Alien Dictionary (Order of Characters from Sorted Alien Dictionary)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - The graph structure is NOT explicitly given as an edge list or matrix.
 * - The order of characters must be deduced by comparing lexicographically adjacent strings.
 * - If string A appears before string B, the first differing character in A has lower priority than the corresponding character in B (directed edge: `A[k] -> B[k]`).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Character-Level DAG Construction + Kahn's Topological Sort:
 *   1. Track all unique characters present in the dictionary.
 *   2. For each consecutive pair of words `dict[i]` and `dict[i+1]`:
 *      - Find the first mismatched character index `j`.
 *      - Add directed edge `dict[i][j] -> dict[i+1][j]` and increment in-degree of `dict[i+1][j]`.
 *      - Corner Case: If `dict[i]` has `dict[i+1]` as a prefix but is longer (e.g. "apple" before "app"), the dictionary is invalid; return `""`.
 *   3. Execute Kahn's algorithm on the character graph.
 *   4. If the resulting topological order contains all unique characters, return it as the alphabet order string; otherwise, cycle exists (invalid dictionary).
 * 
 * TIME COMPLEXITY:
 * - O(N * L + K) where N is number of words, L is average word length, and K is number of unique characters.
 * 
 * SPACE COMPLEXITY:
 * - O(K + E) for adjacency list and in-degrees (K <= 26).
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>

std::string findOrder(std::vector<std::string>& dict, int N, int K) {
    std::unordered_map<char, std::unordered_set<char>> adj;
    std::unordered_map<char, int> inDegree;

    // Initialize all K unique characters
    for (int i = 0; i < K; i++) {
        char ch = 'a' + i;
        adj[ch] = {};
        inDegree[ch] = 0;
    }

    // Build directed edges from adjacent words
    for (int i = 0; i < N - 1; i++) {
        const std::string& w1 = dict[i];
        const std::string& w2 = dict[i + 1];

        // Prefix invalidation check: e.g. "abc" before "ab" is invalid
        if (w1.length() > w2.length() && w1.rfind(w2, 0) == 0) {
            return "";
        }

        int len = std::min(w1.length(), w2.length());
        for (int j = 0; j < len; j++) {
            if (w1[j] != w2[j]) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // First mismatch between adjacent sorted words defines character precedence: w1[j] -> w2[j].
                if (adj[w1[j]].find(w2[j]) == adj[w1[j]].end()) {
                    adj[w1[j]].insert(w2[j]);
                    inDegree[w2[j]]++;
                }
                break; // Only the first mismatched character provides ordering information
            }
        }
    }

    std::queue<char> q;
    for (const auto& [ch, deg] : inDegree) {
        if (deg == 0) {
            q.push(ch);
        }
    }

    std::string order = "";
    while (!q.empty()) {
        char u = q.front();
        q.pop();
        order += u;

        for (char v : adj[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    if ((int)order.length() < K) {
        return ""; // Cycle detected, contradictory ordering
    }
    return order;
}

int main() {
    int N = 5, K = 4;
    std::vector<std::string> dict = {"baa", "abcd", "abca", "cab", "cad"};

    std::string alphabet = findOrder(dict, N, K);
    std::cout << "Alien Alphabet Order: " << alphabet << "\n"; // Expected: b d a c

    return 0;
}
