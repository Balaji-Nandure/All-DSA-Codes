/*
 * Problem: Maximum Score Words Formed by Letters
 * 
 * LeetCode 1255: Maximum Score Words Formed by Letters
 * 
 * Given a list of words, list of single letters (might be duplicated), 
 * and score of every character.
 * 
 * Return the maximum score of any valid set of words formed by using 
 * the given letters (words[i] cannot be used two or more times).
 * 
 * It is not necessary to use all characters in letters and each letter 
 * can only be used once. Score of letters 'a', 'b', 'c', ... ,'z' is 
 * given by score[0], score[1], ... , score[25] respectively.
 * 
 * Example 1:
 * Input: words = ["dog","cat","dad","good"], 
 *        letters = ["a","a","c","d","d","d","g","o","o"], 
 *        score = [1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]
 * Output: 23
 * Explanation:
 * Score  a=1, c=9, d=5, g=3, o=2
 * Given letters, we can form the words "dad" (5+1+5) and "good" (3+2+2+5) 
 * with a score of 23.
 * Words "dad" and "dog" only get a score of 21.
 * 
 * Example 2:
 * Input: words = ["xxxz","ax","bx","cx"], 
 *        letters = ["z","a","b","c","x","x","x"], 
 *        score = [4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0]
 * Output: 27
 * Explanation:
 * Score  a=4, b=4, c=4, x=5, z=4
 * Given letters, we can form the words "ax" (4+5), "bx" (4+5) and "cx" (4+5) 
 * with a score of 27.
 * Word "xxxz" only get a score of 25.
 * 
 * Constraints:
 * - 1 <= words.length <= 14
 * - 1 <= words[i].length <= 15
 * - 1 <= letters.length <= 100
 * - letters[i].length == 1
 * - score.length == 26
 * - 0 <= score[i] <= 10
 * - words[i], letters[i] contains only lower case English letters.
 * 
 * Approach:
 * - Use backtracking to try all subsets of words
 * - For each word, decide whether to include it or not
 * - Track available letters using a frequency map
 * - Before including a word, check if we have enough letters to form it
 * - Calculate score for each word and track maximum score
 * - Backtrack by restoring letter counts after exploring
 * 
 * Time: O(2^n * m) where n = words.length, m = average word length
 * Space: O(26) = O(1) for frequency map + O(n) recursion stack
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    // Calculate score for a word
    int calculateWordScore(const string& word, const vector<int>& score) {
        int wordScore = 0;
        for (char c : word) {
            wordScore += score[c - 'a'];
        }
        return wordScore;
    }
    
    // Check if we can form a word with available letters
    bool canFormWord(const string& word, vector<int>& letterCount) {
        vector<int> wordCount(26, 0);
        // Count letters needed for the word
        for (char c : word) {
            wordCount[c - 'a']++;
        }
        // Check if we have enough letters
        for (int i = 0; i < 26; i++) {
            if (wordCount[i] > letterCount[i]) {
                return false;
            }
        }
        return true;
    }
    
    // Backtracking to find maximum score
    void backtrack(int idx, vector<string>& words, vector<int>& letterCount,
                const vector<int>& score, int currentScore, int& maxScore) {
        // Base case: processed all words
        if (idx == (int)words.size()) {
            maxScore = max(maxScore, currentScore);
            return;
        }
        
        // NOT PICK: Skip current word
        backtrack(idx + 1, words, letterCount, score, currentScore, maxScore);
        
        // PICK: Try to include current word
        string word = words[idx];
        if (canFormWord(word, letterCount)) {
            // Calculate score for this word
            int wordScore = calculateWordScore(word, score);
            
            // Use letters: decrement counts
            for (char c : word) {
                letterCount[c - 'a']--;
            }
            
            // Recurse with updated score and letter counts
            backtrack(idx + 1, words, letterCount, score, 
                    currentScore + wordScore, maxScore);
            
            // Backtrack: restore letter counts
            for (char c : word) {
                letterCount[c - 'a']++;
            }
        }
    }
    
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        // Build frequency map of available letters
        vector<int> letterCount(26, 0);
        for (char c : letters) {
            letterCount[c - 'a']++;
        }
        
        int maxScore = 0;
        backtrack(0, words, letterCount, score, 0, maxScore);
        return maxScore;
    }
};
 