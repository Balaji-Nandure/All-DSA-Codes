/*
GeeksforGeeks: Gadgets of Doraland
Difficulty: Easy

Problem:
In Doraland, people have unique Identity Numbers called D-id. Doraemon owns the most popular gadget shop. 
He has only K gadgets left and has decided to sell his gadgets to his most frequent customers only. 
N customers visit his shop and D-id of each customer is given in an array. 
In case two or more people have visited his shop the same number of times, he gives priority to the customer with a higher D-id. 
Find the D-ids of people he sells his K gadgets to.

Examples:
Input: N = 6, array[] = {1, 1, 1, 2, 2, 3}, K = 2
Output: 1 2
Explanation: Customers with D-id 1 and 2 are most frequent.

Input: N = 8, array[] = {1, 1, 2, 2, 3, 3, 3, 4}, K = 2
Output: 3 2
Explanation: People with D-id 1 and 2 have visited shop 2 times. 
Therefore, in this case, the answer includes the D-id 2 as 2 > 1.

Core Idea:
We need to find the Top K frequent elements, but with a custom tie-breaking rule: if frequencies are equal, the larger D-id gets priority.
This is a classic use case for a Heap (Priority Queue) combined with a Hash Map.
1. The Hash Map counts the frequency of each D-id.
2. The Max-Heap stores pairs of `(frequency, D-id)`.
In C++, a `priority_queue` of pairs naturally compares the first element (frequency) and, if they are equal, compares the second element (D-id). This perfectly matches our requirement: higher frequency comes first, and on a tie, higher D-id comes first.

Approach:
1. Initialize an `unordered_map<int, int>` to store the frequency of each D-id.
2. Iterate through the `array` and populate the map.
3. Initialize a `priority_queue<pair<int, int>> pq` (Max-Heap).
4. Iterate through the map and push `{frequency, D-id}` for each entry into the max-heap.
5. Create a `vector<int> result` to store the output.
6. Pop the top `K` elements from the max-heap and add their D-ids (the second element of the pair) to the `result`.
7. Return `result`.

Time Complexity: O(N + U log U), where N is the number of elements in the array and U is the number of unique elements. The U log U comes from inserting U elements into the priority queue. Since U <= N, it is bounded by O(N log N).
Space Complexity: O(U) for the hash map and the priority queue, which is O(N) in the worst case.

GFG Link: https://www.geeksforgeeks.org/problems/gadgets-of-doraland/1
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> TopK(vector<int>& array, int k) {
        // Step 1: Count frequencies of each D-id
        unordered_map<int, int> freqMap;
        for (int id : array) {
            freqMap[id]++;
        }
        
        // Step 2: Push to Max-Heap. 
        // Max-Heap of pairs automatically sorts by first element (freq), then second element (id).
        priority_queue<pair<int, int>> pq;
        for (auto& entry : freqMap) {
            pq.push({entry.second, entry.first});
        }
        
        // Step 3: Extract top K elements
        vector<int> result;
        for (int i = 0; i < k; i++) {
            if (pq.empty()) break;
            
            result.push_back(pq.top().second);
            pq.pop();
        }
        
        return result;
    }
};

/*
Dry Run — Example 2:
Input: N = 8, array[] = {1, 1, 2, 2, 3, 3, 3, 4}, K = 2

1. Count frequencies:
   freqMap:
   1 -> 2
   2 -> 2
   3 -> 3
   4 -> 1

2. Push to Max-Heap (pq):
   pq.push({2, 1})
   pq.push({2, 2})
   pq.push({3, 3})
   pq.push({1, 4})
   
   Internal Max-Heap order (highest freq first, then highest id):
   Top -> {3, 3}  (Freq: 3, ID: 3)
          {2, 2}  (Freq: 2, ID: 2)
          {2, 1}  (Freq: 2, ID: 1)
          {1, 4}  (Freq: 1, ID: 4)

3. Extract top K = 2 elements:
   - Iteration 1:
     pq.top() = {3, 3}. Add 3 to result.
     pq.pop()
     result = [3]
     
   - Iteration 2:
     pq.top() = {2, 2}. Add 2 to result.
     pq.pop()
     result = [3, 2]

4. Return result: [3, 2]

Output: [3, 2]
*/
