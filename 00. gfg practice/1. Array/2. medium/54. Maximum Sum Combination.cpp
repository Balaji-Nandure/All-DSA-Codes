/*
================================================================================
PROBLEM STATEMENT & EXAMPLES
================================================================================

PROBLEM: Maximum Sum Combination (GFG)

Given two integer arrays a[] and b[] of equal size. A sum combination is formed
by adding one element from a[] and one from b[], using each index pair (i, j)
at most once. Find the top k maximum sum combinations in non-increasing order.

Example 1:
Input: a[] = [3, 2], b[] = [1, 4], k = 2
Output: [7, 6]
Explanation: Possible sums: 3+1=4, 3+4=7, 2+1=3, 2+4=6
             Top 2 are: 7, 6

Example 2:
Input: a[] = [1, 4, 2, 3], b[] = [2, 5, 1, 6], k = 3
Output: [10, 9, 9]
Explanation: Top 3 sums: 4+6=10, 3+6=9, 4+5=9

Constraints:
1 ≤ a.size() = b.size() ≤ 10^5
1 ≤ k ≤ a.size()
1 ≤ a[i], b[i] ≤ 10^4

GFG: https://www.geeksforgeeks.org/problems/maximum-sum-combination/1
================================================================================
*/


// ============================================================
// APPROACH 1: BRUTE FORCE (Generate All Pairs)
// Time: O(n² log n), Space: O(n²)
// ============================================================
/*
HOW IT WORKS:
1. Generate all possible pairs (i, j)
2. Calculate sum for each pair
3. Store all sums, sort in descending order
4. Return top k sums

WHY THIS WORKS:
- Simple and straightforward approach
- Generates all n² possible combinations
- Sorting gives us top k elements

EXAMPLE / DRY RUN:
a[] = [3, 2], b[] = [1, 4], k = 2

Generate all pairs:
(0,0): a[0] + b[0] = 3 + 1 = 4
(0,1): a[0] + b[1] = 3 + 4 = 7
(1,0): a[1] + b[0] = 2 + 1 = 3
(1,1): a[1] + b[1] = 2 + 4 = 6

All sums: [4, 7, 3, 6]

Sort descending: [7, 6, 4, 3]

Top k=2: [7, 6] ✓

Issues:
- For n=10^5, generates 10^10 pairs (memory overflow)
- O(n²) space not feasible for large inputs
*/
class Solution1 {
public:
    vector<int> topKSumPairs(vector<int>& a, vector<int>& b, int k) {
        
        int n = a.size();
        vector<int> sums;
        
        // Generate all possible sums
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                sums.push_back(a[i] + b[j]);
            }
        }
        
        // Sort in descending order
        sort(sums.begin(), sums.end(), greater<int>());
        
        // Take top k
        vector<int> result(sums.begin(), sums.begin() + k);
        return result;
    }
};


// ============================================================
// APPROACH 2: MAX HEAP (Optimal) ⭐
// Time: O(n log n + k log k), Space: O(k)
// ============================================================
/*
HOW IT WORKS:
1. Sort both arrays in DESCENDING order
   - This ensures largest elements are at front

2. Largest possible sum = a[0] + b[0]
   - Start with this pair in max heap

3. For current best pair (i, j), next candidates are:
   - (i+1, j) - use next larger element from a
   - (i, j+1) - use next larger element from b

4. Use visited set to avoid processing same pair twice

5. Extract top k sums from heap

WHY THIS WORKS:
- Monotonicity: After sorting descending, if we pick from (i,j):
  • a[i+1] + b[j] will always be < a[i] + b[j]
  • a[i] + b[j+1] will always be < a[i] + b[j]
  
- We only explore O(k) pairs instead of n²

- Similar to "Merge K Sorted Lists" or "Find K Pairs with Smallest Sum"

KEY INSIGHT:
Don't generate all pairs. Use the sorted property to expand
the search space incrementally, always choosing the best unused pair.

EXAMPLE / DRY RUN:
a[] = [3, 2], b[] = [1, 4], k = 2

Step 1: Sort both arrays descending
a[] = [3, 2]
b[] = [4, 1]

Step 2: Initialize
pq = {(3+4=7, (0,0))}
visited = {(0,0)}

Step 3: Extract top 1
- Pop (7, (0,0)) → Add 7 to result
- Check neighbors:
  • (1,0): a[1]+b[0] = 2+4 = 6 → Push to pq
  • (0,1): a[0]+b[1] = 3+1 = 4 → Push to pq
- visited = {(0,0), (1,0), (0,1)}
- pq = {(6, (1,0)), (4, (0,1))}
- result = [7]

Step 4: Extract top 2
- Pop (6, (1,0)) → Add 6 to result
- Check neighbors:
  • (2,0): out of bounds
  • (1,1): a[1]+b[1] = 2+1 = 2 → Push to pq
- visited = {(0,0), (1,0), (0,1), (1,1)}
- pq = {(4, (0,1)), (2, (1,1))}
- result = [7, 6]

k=2 complete → Return [7, 6] ✓

Another Example:
a[] = [1,4,2,3], b[] = [2,5,1,6], k = 3

Step 1: Sort both descending
a[] = [4, 3, 2, 1]
b[] = [6, 5, 2, 1]

Step 2: Initialize
pq = {(4+6=10, (0,0))}

Step 3-5: Extract top 3
Extract 1: 10 ✓ Add (1,0)→4+5=9 and (0,1)→3+6=9
Extract 2: 9 (from either (1,0) or (0,1))
Extract 3: 9 (from the other)

result = [10, 9, 9] ✓
*/
class Solution {  // Main Solution - Use this one
public:
    vector<int> topKSumPairs(vector<int>& a, vector<int>& b, int k) {
        
        int n = a.size();
        
        // Sort both arrays in DESCENDING order
        sort(a.begin(), a.end(), greater<int>());
        sort(b.begin(), b.end(), greater<int>());
        
        // Max Heap: {sum, {i, j}}
        // By default, priority_queue is max heap for pairs
        priority_queue<pair<int, pair<int, int>>> pq;
        
        // Set to track visited pairs (avoid duplicates)
        set<pair<int, int>> visited;
        
        // Start with largest possible sum
        pq.push({a[0] + b[0], {0, 0}});
        visited.insert({0, 0});
        
        vector<int> result;
        
        // Extract top k sums
        while(k-- > 0 && !pq.empty()) {
            
            // Get best sum
            auto top = pq.top();
            pq.pop();
            
            int sum = top.first;
            int i = top.second.first;
            int j = top.second.second;
            
            // Add to result
            result.push_back(sum);
            
            // Explore neighbor 1: (i+1, j)
            if(i + 1 < n && visited.find({i + 1, j}) == visited.end()) {
                pq.push({a[i + 1] + b[j], {i + 1, j}});
                visited.insert({i + 1, j});
            }
            
            // Explore neighbor 2: (i, j+1)
            if(j + 1 < n && visited.find({i, j + 1}) == visited.end()) {
                pq.push({a[i] + b[j + 1], {i, j + 1}});
                visited.insert({i, j + 1});
            }
        }
        
        return result;
    }
};


/*
================================================================================
SUMMARY & COMPARISON
================================================================================

APPROACH 1 - Brute Force:
✗ Memory Limit Exceeded for large n (10^5 → 10^10 combinations)
✗ Time Complexity O(n² log n) too slow
✓ Correct logic, but not scalable

APPROACH 2 - Max Heap: ⭐ OPTIMAL
✓ Time: O(n log n + k log k) — Sorting + heap operations
✓ Space: O(k) — Only store k pairs in heap + visited set
✓ Handles n up to 10^5 easily
✓ Only extracts necessary sums, not all n² combinations

WHEN TO USE EACH:
- Brute Force: Only for n ≤ 100 and small k
- Heap: Required for production code (n up to 10^5)

KEY LEARNING:
When asked to find "top k" from potentially n² elements:
1. Don't generate all elements
2. Use sorting + heap to explore incrementally
3. Rely on monotonic properties to prune search space

SIMILAR PROBLEMS:
- LeetCode 373: Find K Pairs with Smallest Sum
  (Same logic, just sort ascending and use min heap)
- LeetCode 1439: Find the Kth Smallest Sum of a Matrix
- GFG: K Largest Elements

HEAP PATTERNS TO REMEMBER:
1. Use max heap when: Want largest k elements
2. Use min heap when: Want smallest k elements
3. Use set/map to: Track visited states (avoid duplicates)
4. Expand neighbors systematically to: Ensure we don't miss candidates

================================================================================
*/
