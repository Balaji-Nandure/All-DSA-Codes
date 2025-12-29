/*
 * Problem: K Most Frequent Words in a File
 * 
 * LeetCode: https://leetcode.com/problems/top-k-frequent-words/
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-k-most-frequent-words-from-a-file/
 * Practice: https://practice.geeksforgeeks.org/problems/k-most-frequent-words/1
 * 
 * Given an array of strings words and an integer k, return the k most frequent strings.
 * Return the answer sorted by the frequency from highest to lowest. 
 * Sort the words with the same frequency by their lexicographical order.
 * 
 * Example 1:
 * Input: words = ["i","love","leetcode","i","love","coding"], k = 2
 * Output: ["i","love"]
 * Explanation: "i" and "love" are the two most frequent words.
 *               Note that "i" comes before "love" due to a lower alphabetical order.
 * 
 * Example 2:
 * Input: words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
 * Output: ["the","is","sunny","day"]
 * Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
 *              with the number of occurrence being 4, 3, 2 and 1 respectively.
 * 
 * Constraints:
 * - 1 <= words.length <= 500
 * - 1 <= words[i].length <= 10
 * - words[i] consists of lowercase English letters.
 * - k is in the range [1, The number of unique words[i]]
 * 
 * Approach:
 * - Method 1: Hash Map + Custom Comparator + Sorting (Optimal) - O(n log n) time, O(n) space
 *   Count frequencies, sort by frequency (descending) then lexicographically (ascending)
 * 
 * - Method 2: Hash Map + Min Heap - O(n log k) time, O(n) space
 *   Use min heap with custom comparator to maintain k most frequent words
 *   Comparator: first by frequency (ascending), then lexicographically (descending)
 * 
 * - Method 3: Hash Map + Max Heap - O(n log n) time, O(n) space
 *   Insert all words in max heap, pop k times
 * 
 * Time: O(n log n) - hash map + sorting (optimal for clarity)
 * Space: O(n) - hash map and result array
 */

#include <bits/stdc++.h>
using namespace std;

void processText(const string& text, int k) {
    
    // Store Frequencies of all words
    unordered_map<string, int> freqMap;
    istringstream iss(text);
    for (string word; iss >> word;) freqMap[word]++;
    
    // Store frequency map items in a priority queue (or min heap)
    // with frequency as key
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
    for (auto x : freqMap) {
        pq.emplace(x.second, x.first);
        if (pq.size() > k) pq.pop();
    }
    
    // Get the top frequenty items 
    vector<pair<int, string>> res;
    while (!pq.empty()) {
        res.push_back(pq.top());
        pq.pop();
    }
    
    // Reverse to get the desired order
    reverse(res.begin(), res.end());
    return res;
}
