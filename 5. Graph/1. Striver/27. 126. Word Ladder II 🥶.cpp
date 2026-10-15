// Problem: 126. Word Ladder II
// Link (LeetCode): https://leetcode.com/problems/word-ladder-ii/
// Link (GFG): https://www.geeksforgeeks.org/problems/word-ladder-ii/1
// Difficulty: Hard
// Topic: Graph, BFS, DFS, Backtracking, Shortest Path, Hash Map

/*
Problem Statement:
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a 
sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
- Every adjacent pair of words differs by a single letter.
- Every si for 1 <= i <= k is in wordList. (Note: beginWord does not need to be in wordList).
- sk == endWord.

Given two words, beginWord and endWord, and a dictionary wordList, return ALL the shortest 
transformation sequences from beginWord to endWord, or an empty list if no such sequence exists. 
Each sequence should be returned as a list of the words [beginWord, s1, s2, ..., sk].

Example 1:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
Explanation: There are 2 shortest transformation sequences of length 5.

Example 2:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: []
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.

Constraints:
- 1 <= beginWord.length <= 5
- endWord.length == beginWord.length
- 1 <= wordList.length <= 500
- wordList[i].length == beginWord.length
- beginWord, endWord, and wordList[i] consist of lowercase English letters.
- beginWord != endWord
- All the words in wordList are unique.
- The sum of all shortest transformation sequences does not exceed 10^5.
*/

// Comparison of Approaches:
// 1. Approach 1 (Queue of Paths - Striver G-30):
//    - Store entire path vectors in the BFS queue.
//    - At each level, maintain `usedOnLevel` and erase from set only when transitioning to next level.
//    - Simple and accepted on GFG, but causes MLE (Memory Limit Exceeded) on LeetCode due to copying paths.
// 2. Approach 2 (Optimized: BFS Distance Map + Backtracking DFS - Striver G-31):
//    - Step 1: Run standard BFS storing single words to map the shortest level to each word: mpp[word] = level.
//    - Step 2: Backtrack using DFS from endWord backwards to beginWord!
//              From current word at level L, only explore neighbors with level L - 1.
//    - When beginWord is reached, reverse the collected sequence and push to ans.
//    - Highly memory efficient and fully passes LeetCode!

#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Approach 2 (Optimal / LeetCode Accepted): BFS Level Map + Backtracking DFS
// =========================================================================
class Solution {
private:
    unordered_map<string, int> mpp; // Stores {word, level/distance}
    vector<vector<string>> ans;
    string bWord;

    void dfs(string word, vector<string>& seq) {
        // Base case: Reached the beginWord
        if (word == bWord) {
            reverse(seq.begin(), seq.end());
            ans.push_back(seq);
            reverse(seq.begin(), seq.end()); // Backtrack
            return;
        }

        int steps = mpp[word];
        int sz = word.size();

        // Explore all previous words that could transition into 'word' (level steps - 1)
        for (int i = 0; i < sz; i++) {
            char original = word[i];
            for (char ch = 'a'; ch <= 'z'; ch++) {
                word[i] = ch;

                // Move backward only to words with level == steps - 1
                if (mpp.find(word) != mpp.end() && mpp[word] + 1 == steps) {
                    seq.push_back(word);
                    dfs(word, seq);
                    seq.pop_back(); // Backtrack
                }
            }
            word[i] = original;
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<string> q;
        bWord = beginWord;

        // Step 1: BFS to find the shortest level for each reachable word
        q.push(beginWord);
        mpp[beginWord] = 1;
        st.erase(beginWord);

        while (!q.empty()) {
            string word = q.front();
            int steps = mpp[word];
            q.pop();

            // Destination reached: no need to search deeper levels
            if (word == endWord) break;

            for (int i = 0; i < (int)word.size(); i++) {
                char original = word[i];
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;

                    if (st.count(word)) {
                        q.push(word);
                        st.erase(word);
                        mpp[word] = steps + 1;
                    }
                }
                word[i] = original;
            }
        }

        // Step 2: If endWord is reachable, reconstruct all shortest paths using reverse DFS
        if (mpp.find(endWord) != mpp.end()) {
            vector<string> seq;
            seq.push_back(endWord);
            dfs(endWord, seq);
        }

        return ans;
    }
};

// =========================================================================
// Approach 1 (Queue of Paths - Striver G-30 / GFG Accepted)
// =========================================================================
class SolutionGFG {
public:
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<vector<string>> q;
        q.push({beginWord});

        vector<string> usedOnLevel;
        usedOnLevel.push_back(beginWord);
        int level = 0;
        vector<vector<string>> ans;

        while (!q.empty()) {
            vector<string> vec = q.front();
            q.pop();

            // Erase all words used in the previous level
            if (vec.size() > (size_t)level) {
                level++;
                for (auto& it : usedOnLevel) {
                    st.erase(it);
                }
                usedOnLevel.clear();
            }

            string word = vec.back();

            // Destination reached
            if (word == endWord) {
                if (ans.size() == 0) {
                    ans.push_back(vec);
                } else if (ans[0].size() == vec.size()) {
                    ans.push_back(vec);
                }
            }

            for (int i = 0; i < (int)word.length(); i++) {
                char original = word[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    word[i] = c;
                    if (st.find(word) != st.end()) {
                        vec.push_back(word);
                        q.push(vec);
                        usedOnLevel.push_back(word);
                        vec.pop_back();
                    }
                }
                word[i] = original;
            }
        }
        return ans;
    }
};

/*
Time Complexity:
- BFS Step: O(N * L * 26) to map level of each word.
- DFS Backtracking Step: O(P * L) where P is the number of shortest paths.
- Overall Time Complexity: O(N * L * 26 + P * L).

Space Complexity:
- Hash Map `mpp`: O(N * L) storing level of each word.
- Hash Set `st`: O(N * L).
- BFS Queue: O(N * L).
- DFS Recursion Stack: O(L) max depth.
- Overall Auxiliary Space: O(N * L).

Key Insights:
1. Why Erase Only After the Level Ends (Approach 1):
   - Multiple shortest paths can use the same word at the SAME level (e.g. "hot" -> "dot" and "lot" both leading to "cog").
   - If a word is erased immediately, another valid path at the same level will miss it.
2. Why Approach 2 Prevents MLE:
   - Storing entire paths in the queue duplicates strings exponentially across levels.
   - Decoupling distance mapping (BFS with single strings) from path reconstruction (DFS backwards) 
     eliminates memory bloat, making it optimal for LeetCode.
*/
