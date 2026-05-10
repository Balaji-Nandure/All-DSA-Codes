/*
Problem: Buy Maximum Stocks

GFG: https://www.geeksforgeeks.org/problems/buy-maximum-stocks--141631/1

Description:
In a stock market, there is a product with its infinite stocks. The stock prices are given for N days, where price[i] denotes the price of the stock on the ith day.
There is a rule that a customer can buy at most i stock on the ith day.
If a customer has an amount of k amount of money initially. Find out the maximum number of stocks a customer can buy.

Examples:

Input: price[] = [10,7,19], k = 45
Output: 4 
Explanation: A customer purchases 1 stock on day 1, 2 stocks on day 2 and 1 stock on day 3 for 10, 7 * 2 = 14 and 19 respectively. Hence, total amount is 10 + 14 + 19 = 43 and number of stocks purchased is 4.

Input: price[] = [7,10, 4], k = 100
Output: 6
Explanation: Buy all three days 

Constraints:
1 ≤ N ≤ 10^4
1 ≤ price[i] ≤ 10^4
1 ≤ k ≤ 10^4

Approach (Greedy Sorting):
This is a greedy optimization problem where we need to maximize stock quantity.

Key insight:
- To maximize quantity, buy cheaper stocks first
- On day i, can buy at most i+1 stocks (0-based indexing)
- Sort by price ascending, then buy maximum possible from cheapest

Algorithm:
1. Create pairs of {price[i], i+1} for each day
2. Sort pairs by price ascending
3. For each day in sorted order:
   - Calculate affordable quantity: min(allowedStocks, k/price)
   - Add to total stocks
   - Reduce remaining money

Time Complexity: O(n log n)
Space Complexity: O(n)

Pattern: Greedy + Sorting
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
GREEDY SORTING APPROACH
=====================================================

TC: O(n log n)
SC: O(n)

🔥 GREEDY APPROACH
- Buy cheaper stocks first to maximize quantity
- Sort by price ascending
- Buy maximum possible from each day

🧠 KEY INSIGHT:
To maximize total stocks:
- Always buy cheapest available stocks first
- This leaves more money for more stocks
- Classic greedy optimization

🎯 ALGORITHM:
1. Store {price, maxAllowedStocks} for each day
2. Sort by price ascending
3. Buy maximum possible from cheapest day
4. Update remaining money

⚡ GREEDY LOGIC:
For each day:
quantity = min(allowedStocks, k/price)
total += quantity
k -= quantity * price
*/

class Solution {
public:

    // TC: O(n log n)
    // SC: O(n)

    int buyMaximumProducts(int n, vector<int> &price, int k) {

        vector<pair<int,int>> stocks;

        // Store:
        // {price, max stocks allowed}
        for(int i = 0; i < n; i++) {

            stocks.push_back({price[i], i + 1});
        }

        // Cheapest first
        sort(stocks.begin(), stocks.end());

        int answer = 0;

        for(auto &it : stocks) {

            int stockPrice = it.first;

            int allowedStocks = it.second;

            // Maximum affordable stocks
            int quantity =
            min(allowedStocks,
                k / stockPrice);

            answer += quantity;

            k -= quantity * stockPrice;
        }

        return answer;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    MAXIMIZE QUANTITY
    + BUDGET CONSTRAINT
    + DIFFERENT COSTS

Think immediately:
    GREEDY - BUY CHEAPEST FIRST

-----------------------------------------------------

KEY OBSERVATIONS:

1. Cheaper items give more quantity per money
2. Sorting by cost enables greedy selection
3. Day constraint: at most i+1 stocks on day i

-----------------------------------------------------

COMMON MISTAKES:

1. Forgetting day limit = i+1
2. Buying expensive stocks first
3. Not using min(allowed, affordable)
4. Using wrong sorting order

-----------------------------------------------------

SIMILAR PROBLEMS

- Maximum items with budget
- Greedy optimization problems
- Resource allocation with constraints

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Maximize quantity/count
- Limited budget
- Different costs

Think:
Greedy - Buy Cheapest First

Algorithm:
1. Sort by cost ascending
2. Buy maximum possible from cheapest
3. Update remaining budget

-----------------------------------------------------
*/
