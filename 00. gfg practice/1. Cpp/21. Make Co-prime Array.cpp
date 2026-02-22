/*
 * Problem: Make Co-prime Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/make-co-prime-array/0
 * 
 * Given an array of elements, find the minimum number of insertions to convert the given 
 * array into a co-prime array adjacent pair-wise.
 * 
 * Examples:
 * Input: arr[] = [2, 7, 28]
 * Output: 1
 * Explanation: Here, 1st pair = {2, 7} are co-primes(gcd(2, 7) = 1). 
 *              2nd pair = [7, 28] are not co-primes, insert 9 between them. 
 *              gcd(7, 9) = 1 and gcd(9, 28) = 1.
 * 
 * Input: arr[] = [5, 10, 20]
 * Output : 2
 * Explanation: Here, there is no pair which are co-primes. Insert 7 between (5, 10) 
 *              and 1 between (10, 20).
 * 
 * Constraints:
 * 1 <= arr.size() <= 10^6
 * 1 <= arr[i] <= 10^6
 * 
 * Expected Time Complexity: O(n * log(max(arr)))
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - For each adjacent pair in the array, check if they are co-prime (gcd = 1)
 * - If a pair is not co-prime, we need to insert at least one element between them
 * - The key insight is that we can always find a number that is co-prime with both neighbors
 * - For any two numbers a and b that are not co-prime, we can insert 1 (which is co-prime with everything)
 * - However, we might be able to find a better solution by checking if there exists a number 
 *   that can make both pairs co-prime simultaneously
 * - For simplicity and guarantee, we can use 1 as the insertion number when needed
 * - Count the number of adjacent pairs that are not co-prime
 * 
 * Time: O(n * log(max(arr))) - O(n) pairs with O(log(max)) for gcd calculation
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minInsertions(vector<int>& arr) {
        int insertions = 0;
        
        for (int i = 0; i < arr.size() - 1; i++) {
            // Check if current adjacent pair is co-prime
            if (__gcd(arr[i], arr[i + 1]) != 1) {
                insertions++;
                // After insertion, we need to check the new pair formed
                // Since we can insert 1 (which is co-prime with everything),
                // both new pairs will be co-prime
                // So we can skip the next element as it's now co-prime with our insertion
                // But we still need to check the pair after that
                // So we don't modify i, just continue checking normally
            }
        }
        
        return insertions;
    }
};
