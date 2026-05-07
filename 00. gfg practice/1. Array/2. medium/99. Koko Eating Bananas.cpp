/*
Problem: Koko Eating Bananas

GFG: https://www.geeksforgeeks.org/problems/koko-eating-bananas/

Description:
Koko is given an array arr[], where each element represents a pile of bananas. She has exactly k hours to eat all the bananas.

Each hour, Koko can choose one pile and eat up to s bananas from it.

If a pile has at least s bananas, she eats exactly s bananas.
If a pile has fewer than s bananas, she eats the entire pile in that hour.
Koko can only eat from one pile per hour.

Your task is to find the minimum value of s (bananas per hour) such that Koko can finish all the piles within k hours.

Examples:

Input: arr[] = [5, 10, 3], k = 4
Output: 5
Explanation: If Koko eats at the rate of 5 bananas per hour:
First pile of 5 bananas will be finished in 1 hour.
Second pile of 10 bananas will be finished in 2 hours.
Third pile of 3 bananas will be finished in 1 hour.
Therefore, Koko can finish all piles of bananas in 1 + 2 + 1 = 4 hours.

Input: arr[] = [5, 10, 15, 20], k = 7
Output: 10
Explanation: If Koko eats at the rate of 10 bananas per hour, it will take 6 hours to finish all the piles.

Constraints:
1 ≤ arr.size() ≤ k ≤ 10^6
1 ≤ arr[i] ≤ 10^6

Approach (Binary Search on Answer):
This is a classic binary search problem where we need to find the minimum eating speed.

Key insight:
- If speed increases, required hours decreases (monotonic behavior)
- We can binary search on the answer (speed)
- For each speed, calculate total hours needed and check if ≤ k

Algorithm:
1. Search space: speed from 1 to max(arr)
2. For each mid speed:
   - Calculate total hours needed using ceil(pile/speed)
   - If total hours ≤ k: speed is possible, try smaller
   - Else: speed is too slow, increase speed
3. Return minimum possible speed

Time Complexity: O(n * log(max(arr)))
Space Complexity: O(1)

Pattern: Binary Search on Answer
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
BINARY SEARCH ON ANSWER
=====================================================

TC: O(n * log(max(arr)))
SC: O(1)

🔥 BINARY SEARCH APPROACH
- Search on possible eating speeds
- Monotonic behavior enables binary search
- O(log n) optimization over linear search

🧠 KEY INSIGHT:
If speed increases:
required hours decreases

This monotonic relationship allows binary search on answer.

🎯 ALGORITHM:
1. Search range: [1, max(arr)]
2. For each mid speed:
   - Calculate total hours needed
   - If hours ≤ k: possible answer
   - Else: need more speed
3. Return minimum possible speed

⚡ HOURS CALCULATION:
Use formula: (pile + speed - 1) / speed
This is equivalent to ceil(pile / speed)
*/

class Solution {
public:

    int minEatingSpeed(vector<int>& arr, int k) {
        
        // Search space for eating speed: [1, max_pile_size]
        int low = 1, high = 0;
        for (int p : arr) high = max(high, p);
        
        int ans = high;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            long long hours = 0;
            
            // Calculate total hours needed at speed 'mid'
            for (int p : arr) {
                // Integer equivalent of ceil(p / mid)
                hours += (p + mid - 1) / mid;
            }
            
            if (hours <= k) {
                ans = mid;          // Valid speed, try to minimize it
                high = mid - 1;
            } else {
                low = mid + 1;      // Too slow, need higher speed
            }
        }
        return ans;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever question says:
    minimum/maximum possible value
    satisfying condition
    monotonic behavior

Think immediately:
    BINARY SEARCH ON ANSWER

-----------------------------------------------------

KEY OBSERVATIONS:

1. Speed ↑ → Hours ↓ (monotonic)
2. Can check feasibility in O(n)
3. Binary search gives O(log n) optimization

-----------------------------------------------------

COMMON MISTAKES:

1. Using normal division instead of ceil
   Wrong: pile / speed
   Correct: (pile + speed - 1) / speed

2. Integer overflow in total hours
   Use long long for hours calculation

3. Binary searching on indices instead of answer
   Search on speed values, not array indices

-----------------------------------------------------

SIMILAR PROBLEMS

- Minimum Number of Days to Make M Bouquets
- Capacity to Ship Packages
- Split Array Largest Sum
- Binary Search on Answer pattern

-----------------------------------------------------
*/
