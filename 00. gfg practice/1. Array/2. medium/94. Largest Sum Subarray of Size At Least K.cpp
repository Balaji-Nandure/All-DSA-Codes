/*
PROBLEM: Largest Sum Subarray of Size At Least K

Custom Greedy + Sliding Window Approach

-----------------------------------------------------

INTUITION

Maintain:
1. Current running sum
2. Window size at least k
3. Remove harmful negative prefix greedily

-----------------------------------------------------

IDEA

Once window size becomes >= k:

If left-side accumulated prefix becomes negative,
remove it because:
negative contribution only decreases total sum.

This behaves similarly to Kadane logic.

-----------------------------------------------------

TIME COMPLEXITY:
O(n)

SPACE COMPLEXITY:
O(1)

-----------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
GREEDY + SLIDING WINDOW
=====================================================

TC: O(n)
SC: O(1)

🔥 CUSTOM GREEDY APPROACH
- Single pass solution
- No extra space needed
- Combines Kadane intuition with sliding window

🧠 KEY INSIGHT:
After maintaining minimum size k,
remove negative accumulated prefix greedily
because negative prefix hurts future subarray sum.

🎯 ALGORITHM:
1. Expand window by adding elements
2. When window size >= k, track maximum
3. Accumulate removable prefix
4. If prefix becomes negative, remove it
*/

class GreedySolution {
public:

    long long maxSumWithK(
        long long a[],
        long long n,
        long long k
    ) {
        
        long long i = 0;
        
        long long sum = 0;
        
        long long mx = LLONG_MIN;
        
        // Accumulated removable prefix
        long long last = 0;
        
        for (long long j = 0; j < n; j++) {
            
            // Expand window
            sum += a[j];
            
            // Window size exactly k
            if (j - i + 1 == k) {
                
                mx = max(mx, sum);
            }
            
            // Window size > k
            else if (j - i + 1 > k) {
                
                mx = max(mx, sum);
                
                // Add left prefix candidate
                last += a[i];
                
                i++;
                
                // Remove harmful prefix
                if (last < 0) {
                    
                    sum -= last;
                    
                    last = 0;
                    
                    mx = max(mx, sum);
                }
            }
        }
        
        return mx;
    }
};



/*
=====================================================
FINAL GFG CLASS
=====================================================
*/

class Solution {
public:

    long long maxSumWithK(
        long long a[],
        long long n,
        long long k
    ) {
        
        GreedySolution obj;
        
        return obj.maxSumWithK(a, n, k);
    }
};


/*
-----------------------------------------------------

🧠 KEY OBSERVATION

Negative prefix hurts future subarray sum.

So:
after maintaining minimum size k,
remove negative accumulated prefix greedily.

-----------------------------------------------------

PATTERN:
Sliding Window + Kadane Greedy Intuition

-----------------------------------------------------
*/


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

This is a BEAUTIFUL hybrid problem:

Kadane
+
Sliding Window

-----------------------------------------------------

KEY OBSERVATION:

For every window of size k:
either:
    take exactly k elements

or:
    extend with previous positive sum

-----------------------------------------------------

SIMILAR PATTERN:
Maximum subarray with constraints

-----------------------------------------------------

🎯 TAKEAWAY:

Sometimes problems require:
    combining multiple techniques

This problem shows:
    Kadane for preprocessing
    Sliding window for main logic

-----------------------------------------------------
*/
