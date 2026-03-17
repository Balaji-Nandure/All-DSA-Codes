/*
PROBLEM: Sum of Distinct Elements for Limited Range (GFG)

Given:
- arr[] of size n
- 1 ≤ arr[i] ≤ n

Return:
- Sum of all DISTINCT elements

EXAMPLE:
arr = [5,1,2,4,6,7,3,6,7]
→ distinct = {1,2,3,4,5,6,7}
→ sum = 28

--------------------------------------------------

APPROACH (Optimal - In-place Marking / Index Mapping)

Idea:
- Since values are in range [1, n], we can use array itself as visited
- For each element x:
    → go to index (abs(x) - 1)
    → mark it negative (visited)
- If already negative → duplicate, skip
- Add only first-time visited values

--------------------------------------------------

WHY IT WORKS:
- Uses array as hash map
- No extra space needed (O(1))
- Each element processed once

--------------------------------------------------

TIME COMPLEXITY: O(n)
SPACE COMPLEXITY: O(1)

GFG LINK: https://www.geeksforgeeks.org/problems/sum-of-distinct-elements-for-a-limited-range/
LEETCODE LINK: Similar → https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int sumOfDistinct(vector<int>& arr) {
        
        int n = arr.size();
        int sum = 0;
        
        for(int i = 0; i < n; i++){
            
            int val = abs(arr[i]);
            int idx = val - 1;
            
            // first time visit
            if(arr[idx] > 0){
                sum += val;
                arr[idx] = -arr[idx]; // mark visited
            }
        }
        
        return sum;
    }
};
