/*
GeeksforGeeks: Array Duplicates
Difficulty: Easy

Problem:
Given an array arr[] of size n, containing elements from the range 1 to n, and each element appears at most twice.
Return an array of all the integers that appear twice.

Note: You can return the elements in any order but the driver code will print them in sorted order.

Examples:
Input: arr[] = [2, 3, 1, 2, 3]
Output: [2, 3] 
Explanation: 2 and 3 occur more than once in the given array.

Input: arr[] = [3, 1, 2] 
Output: []
Explanation: There is no repeating element in the array, so the output is empty.

Core Idea:
Since we need to count the frequency of elements, a Hash Map (`unordered_map`) is naturally a valid choice. 
However, because we are strictly given that the elements are bounded between `1` and `n`, we can use a much faster and more efficient approach: a `vector` as a Direct Access Map!
We can create a `vector<int> freq` of size `n + 1` where the index represents the number itself, and the value at that index represents its count.
This behaves identically to a map but completely avoids the heavy overhead of hashing.

Approach:
1. Get the size of the array `n = arr.size()`.
2. Initialize a `vector<int> freq(n + 1, 0)` to act as our frequency map.
3. Initialize an empty `vector<int> result` to store duplicates.
4. Traverse the array `arr`. For every element `x`:
   - Increment its frequency: `freq[x]++`.
   - If its frequency becomes exactly `2` (meaning we just found its duplicate), push `x` into `result`.
     (Checking `== 2` ensures we only push the element once, even if it were to appear more than twice).
5. Return the `result` vector.

Time Complexity: O(N), where N is the size of the array. We perform a single fast pass over the array.
Space Complexity: O(N) auxiliary space to store the frequency vector, which is completely acceptable and expected for mapping counting approaches.

GFG Link: https://www.geeksforgeeks.org/problems/find-duplicates-in-an-array/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> duplicates(vector<int> arr) {
        int n = arr.size();
        
        // Use a vector as a direct access map for frequencies
        vector<int> freq(n + 1, 0);
        vector<int> result;
        
        for (int num : arr) {
            freq[num]++;
            
            // If we've seen this number exactly twice now, it's a duplicate
            if (freq[num] == 2) {
                result.push_back(num);
            }
        }
        
        return result;
    }
};

/*
Dry Run — Example 1:
Input: arr = [2, 3, 1, 2, 3]
n = 5
freq vector initialized to size 6 with all 0s: [0, 0, 0, 0, 0, 0]

1. num = 2
   freq[2]++ -> freq[2] = 1
   Not equal to 2.
   
2. num = 3
   freq[3]++ -> freq[3] = 1
   Not equal to 2.
   
3. num = 1
   freq[1]++ -> freq[1] = 1
   Not equal to 2.
   
4. num = 2
   freq[2]++ -> freq[2] = 2
   freq[2] == 2 -> Push 2 to result.
   result = [2]
   
5. num = 3
   freq[3]++ -> freq[3] = 2
   freq[3] == 2 -> Push 3 to result.
   result = [2, 3]

Output: [2, 3]
*/
