/*
Problem: Ticket Sellers

GFG: https://www.geeksforgeeks.org/problems/ticket-sellers/1

Description: You are given an array arr[] of ticket sellers where the ith ticket seller has arr[i] tickets. The price of a ticket is the number of tickets remaining with the ticket seller. They are allowed to sell at most k tickets. Find the maximum amount they can earn by selling k tickets. The amount of tickets of each seller is provided in array arr[]. Give the answer modulo 10^9 + 7.

Examples:

Input: arr[] = [4, 3, 6, 2, 4] , k=3
Output: 15
Explaination: Consider 0 based indexing. For first two turns the 2nd seller sells. For the third turn either 0th or 2nd seller can sell. So the total becomes 6 + 5 + 4 = 15.
Input: arr[] = [5, 3, 5, 2, 4, 4] , k=2
Output: 10
Explaination: The turns are taken by 0th and 2nd seller. 5 + 5 = 10 is the maximum amount.

Constraints:
1 ≤ arr.size() ≤ 105
1 ≤ arr[i], k ≤ 106

Approach:
Optimal Approach:
1. Build max heap using heapify (O(n))
2. Sell k tickets:
      take max
      add to answer
      decrease and push back
3. Return answer % mod

Why it works:
- Max heap always gives the seller with highest ticket price
- After selling, seller's ticket count decreases by 1
- We push back if they still have tickets for future sales
- This greedy approach maximizes revenue at each step

Time Complexity: O(n + k log n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxAmount(vector<int>& arr, int k) {
        long long mod = 1e9 + 7;

        // Step 1: Heapify (build max heap)
        priority_queue<int> pq(arr.begin(), arr.end());

        long long ans = 0;

        // Step 2: Sell k tickets
        while (k-- && !pq.empty()) {
            int top = pq.top();
            pq.pop();

            ans = (ans + top) % mod;

            if (top - 1 > 0) {
                pq.push(top - 1);
            }
        }

        return ans;
    }
};
