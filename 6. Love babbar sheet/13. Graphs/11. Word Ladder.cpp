/**
 * Problem: Word Ladder (Shortest Transformation Sequence Length)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Graph nodes are words rather than integers or grid coordinates.
 * - Edges are implicit: an edge exists between two words if and only if they differ by exactly 1 character.
 * - Generating all pairwise word differences takes O(N^2 * L), which can TLE. Instead, mutating each character in O(26 * L) per visited word yields extreme performance.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Breadth-First Search (BFS) on Implicit String Mutation:
 *   - Why BFS? We need the SHORTEST transformation sequence in an unweighted state space.
 *   - Store all dictionary words in an `unordered_set<string> wordSet` for O(1) membership lookups.
 *   - Queue holds `pair<string, int>` (current word, path length).
 *   - For each dequeued word, iterate through all characters `0 <= i < L`, try replacing with 'a' through 'z'.
 *   - If the mutated word exists in `wordSet`:
 *     - If it matches `endWord`, return `current_length + 1`.
 *     - Otherwise, push into queue and ERASE from `wordSet` (acting as the visited set to prevent redundant cycles).
 * 
 * TIME COMPLEXITY:
 * - O(M * 26 * L * L) where M is number of words, L is word length (string hashing and copying takes O(L)).
 * 
 * SPACE COMPLEXITY:
 * - O(M * L) for the word set and BFS queue.
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
    std::unordered_set<std::string> dict(wordList.begin(), wordList.end());
    if (dict.find(endWord) == dict.end()) return 0;

    std::queue<std::pair<std::string, int>> q;
    q.push({beginWord, 1});

    while (!q.empty()) {
        auto [word, steps] = q.front();
        q.pop();

        if (word == endWord) return steps;

        // Try mutating every character of the current word
        for (int i = 0; i < (int)word.length(); i++) {
            char originalChar = word[i];

            for (char ch = 'a'; ch <= 'z'; ch++) {
                if (ch == originalChar) continue;
                word[i] = ch;

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Look up mutated word in dictionary and erase immediately to mark visited in O(1) without re-expansion.
                if (dict.find(word) != dict.end()) {
                    if (word == endWord) return steps + 1;
                    q.push({word, steps + 1});
                    dict.erase(word); // Prevent visiting this word again
                }
            }

            word[i] = originalChar; // Backtrack character
        }
    }

    return 0; // Target word unreachable
}

int main() {
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

    int result = ladderLength(beginWord, endWord, wordList);
    std::cout << "Shortest transformation sequence length: " << result << "\n"; // Expected: 5 (hit -> hot -> dot -> dog -> cog)

    return 0;
}
