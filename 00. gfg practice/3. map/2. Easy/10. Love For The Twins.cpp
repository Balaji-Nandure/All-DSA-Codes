/*
Problem: Love For The Twins

Given an Array of Integers Arr of length N, you have to count number of elements of the array that can be counted as pair of equal elements.

Constraints:
1 <= N <= 10^5
1 <= Arr[i] <= 10^5

--------------------------------------------------

Pattern:
Hashing / Frequency Count

--------------------------------------------------

Key Observation:
- We need to find exactly how many elements can be successfully paired with an identical element.
- If an element appears `f` times overall, it can form `f / 2` complete pairs (utilizing integer division).
- Each complete pair consists of 2 elements, meaning exactly `(f / 2) * 2` elements of this specific value will successfully find a twin.
- We can compute the frequencies of all distinct elements in O(N) using a Hash Map, and mathematically sum up their paired elements.

--------------------------------------------------

Approach:
1. Initialize an `unordered_map<int, int> count` to keep track of element frequencies.
2. Iterate through the input array and increment the count for each element: `count[num]++`.
3. Initialize an `ans` counter to 0 to store the total number of paired elements.
4. Iterate through the key-value pairs in the `count` map:
    a. For each distinct element, extract its frequency `f = pair.second`.
    b. Add `(f / 2) * 2` to `ans`.
5. Return the final `ans`.

--------------------------------------------------

Time Complexity: O(N) as we traverse the array once and hash map updates take O(1) time on average. Iterating through the map at the end takes at most O(N) time.
Space Complexity: O(N) to reliably store the frequencies of the distinct elements in the hash map.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/love-for-the-twins2402/1
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // Overload for traditional array signature
    int getTwinCount(int N, int Arr[]) {
        unordered_map<int, int> count;
        
        // Count the frequency of each element
        for (int i = 0; i < N; ++i) {
            count[Arr[i]]++;
        }
        
        int paired_elements = 0;
        
        // Calculate the number of elements that form a twin pair
        for (auto const& pair : count) {
            paired_elements += (pair.second / 2) * 2;
        }
        
        return paired_elements;
    }
}
