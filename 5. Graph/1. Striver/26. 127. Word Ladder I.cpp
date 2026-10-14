// Problem: 127. Word Ladder (Word Ladder I)
// Link (LeetCode): https://leetcode.com/problems/word-ladder/
// Link (GFG): https://www.geeksforgeeks.org/problems/word-ladder/1
// Difficulty: Hard
// Topic: Graph, BFS, Shortest Path, Hash Set, Queue, String

/*
Problem Statement:
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a 
sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
- Every adjacent pair of words differs by a single letter.
- Every si for 1 <= i <= k is in wordList. (Note: beginWord does not need to be in wordList).
- sk == endWord.

Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the 
shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.

Example 1:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> "cog", 
which is 5 words long.

Example 2:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.

Constraints:
- 1 <= beginWord.length <= 10
- endWord.length == beginWord.length
- 1 <= wordList.length <= 5000
- wordList[i].length == beginWord.length
- beginWord, endWord, and wordList[i] consist of lowercase English letters.
- beginWord != endWord
- All the words in wordList are unique.
*/

// Approach: Breadth First Search (BFS)
// 1. Why BFS?
//    - We need the SHORTEST transformation sequence length in an unweighted graph where every 
//      valid 1-letter change represents an edge of weight 1.
//    - BFS explores level-by-level; the first time endWord is reached, the number of levels/steps 
//      is guaranteed to be minimum.
// 2. Generating Neighbors Efficiently:
//    - Comparing the current word against all N words in wordList takes O(N * L).
//    - Instead, for each character position (L positions), replace it with all 26 alphabet characters 
//      ('a' through 'z').
//    - This generates 26 * L variations. Since L <= 10, 26 * 10 = 260 is very small!
//    - Look up each variation in an unordered_set in O(L) time.
// 3. Cycle Prevention / Visited Marking:
//    - When a valid next word is found in the set, push {word, steps + 1} to the queue.
//    - Immediately erase the word from the set! This ensures no word is ever revisited via 
//      a longer path or loop.
// 4. Algorithm Steps:
//    Step 1: Insert all words from wordList into an unordered_set.
//    Step 2: Initialize queue with {beginWord, 1} and erase beginWord from set.
//    Step 3: While queue is not empty:
//            - Pop {word, steps}. If word == endWord, return steps.
//            - For each position i in word and for ch from 'a' to 'z':
//              - Substitute word[i] = ch.
//              - If substituted word exists in set:
//                - Erase it from set and push {word, steps + 1} into queue.
//              - Restore original character word[i].
//    Step 4: If queue empties without reaching endWord, return 0.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // Step 1: Store all dictionary words in an unordered_set for O(1) lookups
        unordered_set<string> st(wordList.begin(), wordList.end());

        // Edge case: if endWord is not in wordList, transformation is impossible
        if (st.find(endWord) == st.end()) {
            return 0;
        }

        // Step 2: BFS queue storing {current_word, sequence_length}
        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        st.erase(beginWord); // Mark beginWord as visited

        // Step 3: BFS traversal
        while (!q.empty()) {
            auto [word, steps] = q.front();
            q.pop();

            // Destination reached: return shortest sequence length
            if (word == endWord) {
                return steps;
            }

            // Try changing every character from 'a' to 'z'
            for (int i = 0; i < (int)word.length(); i++) {
                char original = word[i];

                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;
 
                    // If the transformed word is valid and not yet visited
                    if (st.find(word) != st.end()) {
                        st.erase(word); // Erase from set to mark as visited
                        q.push({word, steps + 1});
                    }
                }

                // Restore original character for next iterations
                word[i] = original;
            }
        }

        // If endWord was not reachable
        return 0;
    }
};

/*
Time Complexity: O(N * L * 26)
- Inserting words into set: O(N * L).
- In the worst case, each word is pushed into and popped from the queue at most once: N words.
- For each word of length L, we test 26 possible letters at each of the L positions: 26 * L checks.
- Each set lookup/erasure takes O(L) string hashing time.
- Total Time Complexity: O(N * L * 26 * L) = O(N * L^2 * 26).
- Given L <= 10 and N <= 5000, 5000 * 100 * 26 ≈ 1.3 * 10^7 operations (runs comfortably within 100ms).

Space Complexity: O(N * L)
- unordered_set storing N words of length L: O(N * L).
- BFS queue storing up to N words: O(N * L).
- Total Auxiliary Space: O(N * L).

Key Insights:
1. Why Generating 26 * L Variants is Superior:
   - Comparing against all words in wordList takes O(N * L) for each state.
   - Generating 26 * L mutations takes only O(26 * L * L) which is constant for L <= 10.
   - For N = 5000, 260 is vastly smaller than 5000!
2. In-place Erase as Visited:
   - Erasing directly from the set eliminates the need for a separate visited set, saving space
     and lookups.
3. Word Ladder 1 vs Word Ladder 2:
   - Word Ladder 1 asks for the LENGTH of the shortest sequence (standard BFS).
   - Word Ladder 2 asks for ALL the shortest transformation sequences (BFS to find shortest level + DFS/backtracking to reconstruct paths).
*/
