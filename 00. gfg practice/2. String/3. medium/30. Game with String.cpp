/*
GeeksforGeeks: Game with String
Difficulty: Medium

Problem:
Given a string s consisting of lowercase alphabets and an integer k, 
find the minimum possible value of the string after removing exactly k characters.
The value of the string is defined as the sum of the squares of the frequencies of each distinct character present in the string.

Examples:
Input: s = "abbccc", k = 2
Output: 6
Explaination: We remove two 'c' to get the value as 1^2 + 2^2 + 1^2 = 6.

Input: s = "aaab", k = 2
Output: 2
Explaination: We remove two 'a'. Now we get the value as 1^2 + 1^2 = 2.

Constraints:
0 <= k <= s.length() <= 10^5

Core Idea:
- We want to minimize the sum of squares of frequencies. Since f(x) = x^2 grows rapidly as x increases, 
  to minimize the total sum, we must greedily reduce the largest frequency at any given step.
- Therefore, for each of the k character removals, we:
  1. Find the character with the maximum frequency.
  2. Decrement its frequency by 1.
- We can implement this optimal greedy choice using a Max-Heap (Priority Queue):
  - Count frequencies of all lowercase English alphabets.
  - Insert all non-zero frequencies into a max priority queue.
  - Pop the largest frequency, decrement it by 1, and push it back if it's still > 0. Repeat this k times.
  - Finally, sum up the squares of all remaining frequencies.

Approach:
1. Count the occurrences of each character in an array `freq` of size 26.
2. Push all non-zero frequencies into a max-priority queue `pq`.
3. Loop `k` times:
   - Pop the top element `max_freq` from `pq`.
   - Push `max_freq - 1` back into `pq` if `max_freq - 1 > 0`.
4. Calculate the sum of squares of all elements remaining in `pq`.
5. Return the calculated sum.

Time Complexity: O(N + k * log(26)) = O(N + k) where N is the length of s. Since the alphabet size is constant (26), operations on priority queue take O(1) time.
Space Complexity: O(1) auxiliary space since the frequency array and priority queue store at most 26 elements.

GFG Link: https://www.geeksforgeeks.org/problems/game-with-string4100/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minValue(string s, int k) {
        vector<int> freq(26, 0);
        
        // Step 1: Count frequency of each character
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        // Step 2: Push all non-zero frequencies into a max-priority queue
        priority_queue<int> pq;
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                pq.push(freq[i]);
            }
        }
        
        // Step 3: Greedily decrement the highest frequency character k times
        while (k > 0 && !pq.empty()) {
            int max_freq = pq.top();
            pq.pop();
            
            if (max_freq - 1 > 0) {
                pq.push(max_freq - 1);
            }
            k--;
        }
        
        // Step 4: Calculate the sum of squares of remaining frequencies
        int result = 0;
        while (!pq.empty()) {
            int val = pq.top();
            pq.pop();
            result += val * val;
        }
        
        return result;
    }
};

/*
Dry Run — Example:
s = "abbccc", k = 2

1. Frequencies:
   'a': 1
   'b': 2
   'c': 3
   All others 0.

2. Priority Queue initial state:
   pq = {3, 2, 1}

3. Decrement loop (k = 2):
   - k = 2:
     - Pop max_freq = 3.
     - Push max_freq - 1 = 2.
     - pq becomes {2, 2, 1}.
   - k = 1:
     - Pop max_freq = 2.
     - Push max_freq - 1 = 1.
     - pq becomes {2, 1, 1}.
   - k = 0: Loop terminates.

4. Sum of Squares:
   - Pop 2 -> result = 0 + 2^2 = 4
   - Pop 1 -> result = 4 + 1^2 = 5
   - Pop 1 -> result = 5 + 1^2 = 6

Output: 6
*/
