/*
Problem: Left out candies

Approach:
1. Compute sum of 1 to n → S = n(n+1)/2
2. Remove full rounds → remaining = m % S
3. Find largest k such that k(k+1)/2 <= remaining
4. Answer = remaining - k(k+1)/2

Time Complexity: O(log n)
Space Complexity: O(1)

GFG: https://www.geeksforgeeks.org/problems/left-out-candies/1
*/

class Solution {
  public:
    int leftCandies(int n, int m) {
        
        long long S = 1LL * n * (n + 1) / 2;

        // Step 1: Remaining after full rounds
        long long rem = m % S;

        // Step 2: Binary search for k
        long long low = 0, high = n, k = 0;

        while (low <= high) {
            long long mid = (low + high) / 2;
            long long sum = mid * (mid + 1) / 2;

            if (sum <= rem) {
                k = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        // Step 3: leftover candies
        return rem - (k * (k + 1) / 2);
    }
};
