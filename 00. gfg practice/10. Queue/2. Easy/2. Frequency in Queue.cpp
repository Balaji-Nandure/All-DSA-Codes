/*
GeeksforGeeks: Frequency in Queue
Difficulty: Easy

Problem:
The task is to write two functions for a queue, insert(q, k) and findFrequency(q, k). 
The first function inserts a given item k and the second function finds the frequency of a given item k.
If the item is not present in the queue, return -1.

Examples:
Input: insert[] = 1 2 3 4 5 2 3 1 , findFreq[] = 1 3 2 9 10
Output: 2 2 2 -1 -1
Explanation:
After inserting 1, 2, 3, 4, 5, 2, 3 and 1 into the queue, frequency of 1 is 2, 3 is 2 and 2 is 2.
Since 9 and 10 are not there in the queue we output -1 for them.

Core Idea (Optimized/Efficient Approach):
Our previous approach ran in O(N) time for every `findFrequency` query by rotating the queue. For M queries, this took O(N * M) time.
To make it optimally efficient, we can achieve O(1) query time by using an `unordered_map` to keep track of frequencies as elements are inserted.
To handle multiple test cases cleanly on the GFG platform (since global variables persist across test cases), we can simply check if the queue is empty during `insert`. If it is, it means a brand new test case is starting, and we can `clear()` our frequency map!

Approach:
1. Declare a global `unordered_map<int, int> freqMap`.
2. `insert(queue<int> &q, int k)`:
   - If `q.empty()` is true, it implies a new test case. Call `freqMap.clear()`.
   - Call `q.push(k)`.
   - Increment the frequency: `freqMap[k]++`.
3. `findFrequency(queue<int> &q, int k)`: 
   - Since our map always knows the state of the queue, we can just check `freqMap`.
   - If `freqMap[k] > 0`, return `freqMap[k]`.
   - Else, return `-1`.

Time Complexity: 
- `insert`: O(1) on average.
- `findFrequency`: O(1) on average.
Overall time complexity for M queries drops from O(N * M) to O(M).
Space Complexity: O(N) to store the unique elements and their frequencies in the map.

GFG Link: https://www.geeksforgeeks.org/problems/frequency-in-queue/1
*/

#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

// Global map to store frequencies.
unordered_map<int, int> freqMap;

class Solution {
public:
    // Function to insert element into the queue
    void insert(queue<int> &q, int k) {
        // If the queue is empty, a new testcase has started. Clear previous testcase data.
        if (q.empty()) {
            freqMap.clear();
        }
        
        q.push(k);
        freqMap[k]++;
    }
    
    // Function to find frequency of an element
    // return the frequency of k
    int findFrequency(queue<int> &q, int k) {
        // O(1) lookup
        if (freqMap.find(k) != freqMap.end() && freqMap[k] > 0) {
            return freqMap[k];
        }
        return -1;
    }
};

/*
Dry Run — Example 1:
insert[] = [1, 2, 3], findFreq[] = [1, 9]

1. insert(1):
   q is empty -> freqMap.clear().
   q = [1], freqMap[1] = 1

2. insert(2):
   q = [1, 2], freqMap[2] = 1

3. insert(3):
   q = [1, 2, 3], freqMap[3] = 1

4. findFrequency(1):
   Looks up freqMap[1]. Exists and > 0.
   Returns 1. Takes O(1) time.
   
5. findFrequency(9):
   Looks up freqMap[9]. Doesn't exist.
   Returns -1. Takes O(1) time.
*/
