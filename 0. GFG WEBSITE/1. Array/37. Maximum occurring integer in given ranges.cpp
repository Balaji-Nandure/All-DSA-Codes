/*
 * Problem: Maximum occurring integer in given ranges
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/maximum-occurred-integer-n-ranges/
 * Practice: https://practice.geeksforgeeks.org/problems/maximum-occured-integer4602/1
 * 
 * Given n ranges of the form L and R, the task is to find the maximum occurring 
 * integer in all the ranges. If more than one such integer exists, print the 
 * smallest one.
 * 
 * Example 1:
 * Input: L[] = {1, 4, 9, 13, 21}, R[] = {15, 8, 12, 20, 30}, n = 5
 * Output: 4
 * Explanation: 
 * Ranges: [1,15], [4,8], [9,12], [13,20], [21,30]
 * Integer 4 appears in ranges [1,15] and [4,8], so count = 2
 * Integer 5 appears in ranges [1,15] and [4,8], so count = 2
 * Integer 6 appears in ranges [1,15] and [4,8], so count = 2
 * Integer 7 appears in ranges [1,15] and [4,8], so count = 2
 * Integer 8 appears in ranges [1,15] and [4,8], so count = 2
 * Integer 9 appears in ranges [1,15] and [9,12], so count = 2
 * Integer 10 appears in ranges [1,15] and [9,12], so count = 2
 * Integer 11 appears in ranges [1,15] and [9,12], so count = 2
 * Integer 12 appears in ranges [1,15] and [9,12], so count = 2
 * Integer 13 appears in ranges [1,15] and [13,20], so count = 2
 * Integer 14 appears in ranges [1,15] and [13,20], so count = 2
 * Integer 15 appears in ranges [1,15] and [13,20], so count = 2
 * Actually, let's count properly:
 * 4 appears in [1,15] and [4,8] = 2 times
 * 5 appears in [1,15] and [4,8] = 2 times
 * ... many integers appear 2 times
 * But 4 is the smallest with max count, so output is 4
 * 
 * Example 2:
 * Input: L[] = {1, 5}, R[] = {3, 7}, n = 2
 * Output: 5
 * Explanation: 
 * Ranges: [1,3], [5,7]
 * Integer 5 appears in range [5,7], count = 1
 * Actually, let's check: [1,3] covers 1,2,3. [5,7] covers 5,6,7
 * No overlap, so each integer appears once. Smallest is 1, but wait...
 * Actually, 5 appears only in [5,7], so count = 1
 * But 1 appears in [1,3], so count = 1
 * Since both have same count, return smallest = 1
 * Wait, let me re-read: "maximum occurring integer" - if multiple have same max, return smallest
 * 
 * Constraints:
 * - 1 <= n <= 10^6
 * - 0 <= L[i], R[i] <= 10^6
 * 
 * Approach:
 * - Method 1: Difference Array / Prefix Sum (Optimal) - O(n + maxR) time, O(maxR) space
 *   Use difference array: increment at L[i], decrement at R[i]+1
 *   Compute prefix sum to get count for each integer
 *   Find integer with maximum count (smallest if tie)
 * 
 * - Method 2: Brute Force - O(n * (maxR - minL)) time, O(maxR) space
 *   For each integer in range, count how many ranges contain it
 * 
 * - Method 3: Sweep Line - O(n log n) time, O(n) space
 *   Sort all endpoints, sweep and count
 * 
 * Time: O(n + maxR) - difference array (optimal method)
 * Space: O(maxR) - difference array
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Expected Approach] Difference Array / Prefix Sum - O(n + maxR) Time and O(maxR) Space
    int maxOccured(vector<int>& L, vector<int>& R, int n) {
        // Find maximum value in R array to determine array size
        int maxR = *max_element(R.begin(), R.end());
        
        // Difference array: diff[i] represents change at position i
        // We'll use size maxR + 2 to handle R[i] + 1
        vector<int> diff(maxR + 2, 0);
        
        // For each range [L[i], R[i]]
        for (int i = 0; i < n; i++) {
            diff[L[i]]++;        // Start of range: increment
            diff[R[i] + 1]--;    // End of range + 1: decrement
        }
        
        // Compute prefix sum to get actual count for each integer
        int maxCount = 0;
        int result = 0;
        int currentCount = 0;
        
        for (int i = 0; i <= maxR; i++) {
            currentCount += diff[i];
            
            // Update maximum count and result
            if (currentCount > maxCount) {
                maxCount = currentCount;
                result = i;
            }
        }
        
        return result;
    }
    
    // APPROACH 2: Alternative Implementation with Explicit Array
    int maxOccuredAlt(vector<int>& L, vector<int>& R, int n) {
        int maxR = *max_element(R.begin(), R.end());
        
        // Count array to store frequency of each integer
        vector<int> count(maxR + 1, 0);
        
        // Mark all integers in each range
        for (int i = 0; i < n; i++) {
            for (int j = L[i]; j <= R[i]; j++) {
                count[j]++;
            }
        }
        
        // Find integer with maximum count (smallest if tie)
        int maxCount = 0;
        int result = 0;
        
        for (int i = 0; i <= maxR; i++) {
            if (count[i] > maxCount) {
                maxCount = count[i];
                result = i;
            }
        }
        
        return result;
    }
    
    // APPROACH 3: Using Map (for sparse ranges) - O(n * avg_range_length) Time and O(unique) Space
    int maxOccuredMap(vector<int>& L, vector<int>& R, int n) {
        unordered_map<int, int> count;
        
        // Count occurrences for each integer in all ranges
        for (int i = 0; i < n; i++) {
            for (int j = L[i]; j <= R[i]; j++) {
                count[j]++;
            }
        }
        
        // Find integer with maximum count (smallest if tie)
        int maxCount = 0;
        int result = INT_MAX;
        
        for (auto& [num, cnt] : count) {
            if (cnt > maxCount) {
                maxCount = cnt;
                result = num;
            } else if (cnt == maxCount && num < result) {
                result = num;
            }
        }
        
        return result;
    }
    
    // APPROACH 4: Sweep Line Algorithm - O(n log n) Time and O(n) Space
    int maxOccuredSweepLine(vector<int>& L, vector<int>& R, int n) {
        vector<pair<int, int>> events;
        
        // Create events: (position, type)
        // type = 1 for start, type = -1 for end
        for (int i = 0; i < n; i++) {
            events.push_back({L[i], 1});   // Start of range
            events.push_back({R[i] + 1, -1}); // End of range (exclusive)
        }
        
        // Sort events by position
        sort(events.begin(), events.end());
        
        int maxCount = 0;
        int result = 0;
        int currentCount = 0;
        int prevPos = -1;
        
        for (auto& [pos, type] : events) {
            // If we have a valid position range
            if (prevPos != -1 && prevPos < pos) {
                // Check all integers in [prevPos, pos-1]
                if (currentCount > maxCount) {
                    maxCount = currentCount;
                    result = prevPos;  // Smallest integer in this range
                }
            }
            
            currentCount += type;
            prevPos = pos;
        }
        
        return result;
    }
    
    // APPROACH 5: Optimized Difference Array (Single Pass)
    int maxOccuredOptimized(vector<int>& L, vector<int>& R, int n) {
        int maxR = *max_element(R.begin(), R.end());
        vector<int> diff(maxR + 2, 0);
        
        // Build difference array
        for (int i = 0; i < n; i++) {
            diff[L[i]]++;
            if (R[i] + 1 <= maxR) {
                diff[R[i] + 1]--;
            }
        }
        
        // Find maximum in single pass
        int maxCount = diff[0];
        int result = 0;
        
        for (int i = 1; i <= maxR; i++) {
            diff[i] += diff[i - 1];  // Prefix sum
            
            if (diff[i] > maxCount) {
                maxCount = diff[i];
                result = i;
            }
        }
        
        return result;
    }
    
    // [Naive Approach] Brute Force - O(n * (maxR - minL)) Time and O(1) Space
    int maxOccuredBrute(vector<int>& L, vector<int>& R, int n) {
        int minL = *min_element(L.begin(), L.end());
        int maxR = *max_element(R.begin(), R.end());
        
        int maxCount = 0;
        int result = minL;
        
        // For each integer in the range
        for (int num = minL; num <= maxR; num++) {
            int count = 0;
            
            // Count how many ranges contain this integer
            for (int i = 0; i < n; i++) {
                if (num >= L[i] && num <= R[i]) {
                    count++;
                }
            }
            
            // Update result if this integer has more occurrences
            if (count > maxCount) {
                maxCount = count;
                result = num;
            }
        }
        
        return result;
    }
};

int main() {
    Solution sol;
    
    // Test case 1
    vector<int> L1 = {1, 4, 9, 13, 21};
    vector<int> R1 = {15, 8, 12, 20, 30};
    int n1 = 5;
    cout << "Test 1: " << sol.maxOccured(L1, R1, n1) << endl;  // Expected: 4
    
    // Test case 2
    vector<int> L2 = {1, 5};
    vector<int> R2 = {3, 7};
    int n2 = 2;
    cout << "Test 2: " << sol.maxOccured(L2, R2, n2) << endl;  // Expected: 1 (or 5, depends on interpretation)
    
    // Test case 3: Overlapping ranges
    vector<int> L3 = {1, 2, 3};
    vector<int> R3 = {3, 3, 3};
    int n3 = 3;
    cout << "Test 3: " << sol.maxOccured(L3, R3, n3) << endl;  // Expected: 3
    
    // Test case 4: Single range
    vector<int> L4 = {5};
    vector<int> R4 = {10};
    int n4 = 1;
    cout << "Test 4: " << sol.maxOccured(L4, R4, n4) << endl;  // Expected: 5
    
    return 0;
}

