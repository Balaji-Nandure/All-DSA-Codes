vector<int> candyStore(int candies[], int n, int k) {
    /*
    Problem:
    Minimum and Maximum Candy Cost.

    Rule:
    - For every candy bought, you get at most k candies for free.
    - Free candies are the cheapest available (for min cost)
      or the costliest available (for max cost), depending on strategy.

    Approach (Sorting + Two Pointers):
    1. Sort the candy prices.
    2. Minimum Cost:
       - Buy cheapest candy.
       - Get k most expensive candies free.
       - Move left pointer forward by 1 (bought)
       - Move right pointer backward by k (free)
    3. Maximum Cost:
       - Buy most expensive candy.
       - Get k cheapest candies free.
       - Move right pointer backward by 1 (bought)
       - Move left pointer forward by k (free)

    Time: O(n log n)
    Space: O(1)
    */

    sort(candies, candies + n);

    int minCost = 0;
    int maxCost = 0;

    // Minimum cost calculation
    int buy = 0, free = n - 1;
    while (buy <= free) {
        minCost += candies[buy];
        buy++;
        free -= k;
    }

    // Maximum cost calculation
    buy = n - 1;
    free = 0;
    while (free <= buy) {
        maxCost += candies[buy];
        buy--;
        free += k;
    }

    return {minCost, maxCost};
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/minimum-and-maximum-candy-cost/0

LeetCode:
Not available as a standalone problem
*/
