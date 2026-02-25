/*
 * Problem: Bus Ticket Change
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/bus-ticket-change/1
 * 
 * You are given an array arr[] representing passengers in a queue. Each bus ticket 
 * costs 5 coins, and arr[i] denotes the note a passenger uses to pay (which can be 
 * 5, 10, or 20). You must serve the passengers in the given order and always 
 * provide the correct change so that each passenger effectively pays exactly 5 coins. 
 * Your task is to determine whether it is possible to serve all passengers in the 
 * queue without ever running out of change.
 * 
 * Examples:
 * Input: arr[] = [5, 5, 5, 10, 20]
 * Output: true
 * Explanation: From the first 3 customers, we collect three $5 bills in order.
 *              From the fourth customer, we collect a $10 bill and give back a $5.
 *              From the fifth customer, we give a $10 bill and a $5 bill.
 *              Since all customers got correct change we return true.
 * 
 * Input: arr[] = [5, 5, 10, 10, 20]
 * Output: false
 * Explanation: From the first two customers in order, we collect two $5 bills. 
 *              For the next two customers in order, we collect a $10 bill and give back a $5 bill. 
 *              For the last customer, we can not give the change of $15 back because we only have two $10 bills. 
 *              Since not every customer received the correct change, the answer is false.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * arr[i] contains only [5, 10, 20]
 * 
 * Expected Time Complexity: O(N)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Track count of $5 and $10 bills available for change
 * - For $5: just increment count5
 * - For $10: need one $5 to give change, increment count10
 * - For $20: prefer to give one $10 and one $5, or three $5 if no $10 available
 * - Return false if unable to provide exact change at any point
 * - Greedy approach to minimize $5 usage for $20 changes
 * 
 * Time: O(N) - single pass through array
 * Space: O(1) - constant counters
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canServe(vector<int>& arr) {
        
        int count5 = 0;
        int count10 = 0;
        
        for (int x : arr) {
            
            if (x == 5) {
                count5++;
            }
            else if (x == 10) {
                
                if (count5 == 0) return false;
                
                count5--;
                count10++;
            }
            else {  // x == 20
                
                if (count10 > 0 && count5 > 0) {
                    count10--;
                    count5--;
                }
                else if (count5 >= 3) {
                    count5 -= 3;
                }
                else {
                    return false;
                }
            }
        }
        
        return true;
    }
};
