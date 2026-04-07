/*
================================================================================
PROBLEM STATEMENT & EXAMPLES
================================================================================

PROBLEM: Top K Frequent Elements in Array (GFG)

Given a non-empty integer array, find and return the top k elements which have
the highest frequency in the array.

Note: If two numbers have the same frequency, the larger number should be
given the higher priority.

Example 1:
Input: arr[] = [3, 1, 4, 4, 5, 2, 6, 1], k = 2
Output: [4, 1]
Explanation: Frequency of 4 is 2, frequency of 1 is 2.
             Same frequency, so 4 > 1 → output [4, 1]

Example 2:
Input: arr[] = [7, 10, 11, 5, 2, 5, 5, 7, 11, 8, 9], k = 4
Output: [5, 11, 7, 10]
Explanation: Frequencies: 5→3, 11→2, 7→2, 10→1
             Sorted by freq (desc) then by value (desc): [5, 11, 7, 10]

Constraints:
1 ≤ arr.size() ≤ 10^5
1 ≤ arr[i] ≤ 10^5
1 ≤ k ≤ no. of distinct elements

GFG: https://www.geeksforgeeks.org/problems/top-k-frequent-elements-in-array/1
================================================================================
*/


// ============================================================
// APPROACH 1: SORT BY FREQUENCY & VALUE
// Time: O(n + d log d), Space: O(d)
// ============================================================
/*
HOW IT WORKS:
1. Count frequency of each element using map
2. Convert pairs {value, frequency} into vector
3. Sort by:
   - Primary: frequency (descending)
   - Secondary: value (descending) for ties
4. Extract first k elements

WHY THIS WORKS:
- Sorting directly gives us ordered result
- Custom comparator handles frequency + tiebreaker logic
- Simple and straightforward

EXAMPLE / DRY RUN:
arr = [3, 1, 4, 4, 5, 2, 6, 1], k = 2

Step 1: Count frequencies
freq = {1→2, 2→1, 3→1, 4→2, 5→1, 6→1}

Step 2: Create pairs {value, frequency}
pairs = {(1,2), (2,1), (3,1), (4,2), (5,1), (6,1)}

Step 3: Sort by frequency desc, then value desc
Comparator: if freq same, larger value comes first

Sorting:
(1,2) vs (4,2)   → freq same, 4 > 1, so (4,2) first
(3,1) vs (5,1)   → freq same, 5 > 3, so (5,1) first
(5,1) vs (6,1)   → freq same, 6 > 5, so (6,1) first

Final sorted: [(4,2), (1,2), (6,1), (5,1), (3,1), (2,1)]

Step 4: Extract top k=2
result = [4, 1] ✓

Another Example:
arr = [7, 10, 11, 5, 2, 5, 5, 7, 11, 8, 9], k = 4

freq = {2→1, 5→3, 7→2, 8→1, 9→1, 10→1, 11→2}

pairs = {(2,1), (5,3), (7,2), (8,1), (9,1), (10,1), (11,2)}

After sorting by freq desc, val desc:
[(5,3), (11,2), (7,2), (10,1), (9,1), (8,1), (2,1)]

Top k=4: [5, 11, 7, 10] ✓
*/
class Solution1 {
public:
    vector<int> topKFreq(vector<int> &arr, int k) {
        
        // Step 1: Count frequencies
        unordered_map<int, int> freq;
        for(int num : arr) {
            freq[num]++;
        }
        
        // Step 2: Create vector of {value, frequency} pairs
        vector<pair<int, int>> pairs;
        for(auto &p : freq) {
            pairs.push_back({p.first, p.second});  // {value, freq}
        }
        
        // Step 3: Sort by frequency (desc), then value (desc)
        sort(pairs.begin(), pairs.end(), [](const pair<int,int> &a, const pair<int,int> &b) {
            // If frequencies different, sort by frequency descending
            if(a.second != b.second) {
                return a.second > b.second;
            }
            // If frequencies same, sort by value descending
            return a.first > b.first;
        });
        
        // Step 4: Extract top k elements
        vector<int> result;
        for(int i = 0; i < k; i++) {
            result.push_back(pairs[i].first);
        }
        
        return result;
    }
};


// ============================================================
// APPROACH 2: MAX HEAP (Priority Queue)
// Time: O(n + d log d), Space: O(d)
// ============================================================
/*
HOW IT WORKS:
1. Count frequencies in map
2. Push all {frequency, value} pairs into max heap
3. Max heap automatically sorts by:
   - Primary: frequency (for pairs, first element compared first)
   - Secondary: value (if frequencies are equal)
4. Extract top k from heap

WHY THIS WORKS:
- Max heap is ordered by first element of pair
- When frequencies are equal, second element breaks tie
- Heap extraction is O(log d) per element

KEY: In C++, pair comparison works lexicographically:
- (2, 5) vs (2, 3) → 2==2, so compare 5 vs 3 → (2,5) > (2,3)
- (3, 5) vs (2, 10) → 3 > 2 → (3,5) is larger

EXAMPLE / DRY RUN:
arr = [3, 1, 4, 4, 5, 2, 6, 1], k = 2

Step 1: Count frequencies
freq = {1→2, 2→1, 3→1, 4→2, 5→1, 6→1}

Step 2: Build max heap {freq, value}
Insert (2, 1), (1, 2), (1, 3), (2, 4), (1, 5), (1, 6)

Heap structure (max heap on first element, then second):
                (2,4)
               /    \
            (2,1)   (1,6)
           /   \    /
        (1,2) (1,3)(1,5)

At top: (2,4) because freq 2 is max

Step 3: Extract k times
Extract 1: (2,4) → add 4
           Heap now at (2,1) as top
Extract 2: (2,1) → add 1

result = [4, 1] ✓
*/
class Solution2 {
public:
    vector<int> topKFreq(vector<int> &arr, int k) {
        
        // Step 1: Count frequencies
        unordered_map<int, int> freq;
        for(int num : arr) {
            freq[num]++;
        }
        
        // Step 2: Max Heap with {frequency, value}
        priority_queue<pair<int, int>> pq;  // Max heap
        
        for(auto &p : freq) {
            pq.push({p.second, p.first});  // {freq, value}
        }
        
        // Step 3: Extract top k
        vector<int> result;
        
        while(k--) {
            auto top = pq.top();
            pq.pop();
            result.push_back(top.second);  // Push value, not frequency
        }
        
        return result;
    }
};


// ============================================================
// APPROACH 3: MIN HEAP (Space Optimized for streaming data)
// Time: O(n + d log k), Space: O(k)
// ============================================================
/*
HOW IT WORKS:
1. Count frequencies
2. Use MIN HEAP of size k
3. Maintain only top k frequent elements in heap
4. Compare new element with min of heap:
   - If freq > min.freq OR (freq == min.freq AND val > min.val)
     → Add to heap, remove min
5. Extract all elements from heap

WHY THIS WORKS:
- Only maintain k elements in heap (space optimized)
- Min heap ensures smallest of top-k is at root
- Any element larger than root replaces it
- Final heap contains top k elements

WHEN TO USE:
- When k << d (k is much smaller than distinct elements)
- For streaming data (elements come one by one)
- Space constraints

EXAMPLE / DRY RUN:
arr = [3, 1, 4, 4, 5, 2, 6, 1], k = 2

freq = {1→2, 2→1, 3→1, 4→2, 5→1, 6→1}

Step 1: Insert first k elements
Insert (2, 1): heap = [(2, 1)]
Insert (1, 2): heap = [(1, 2)] (min heap, so 1 at top)

Step 2: Process remaining elements
Check (1, 3):
  top = (1, 2), new = (1, 3)
  freq same (1==1), but 3 > 2, so REPLACE
  Remove (1, 2), heap = [(1, 3)]

Check (2, 4):
  top = (1, 3), new = (2, 4)
  freq new > freq top (2 > 1), so REPLACE
  Remove (1, 3), add (2, 4)
  heap = [(2, 4)] initially
  After heapify: need to compare with other element if exists
  For k=2, our second element: we need to track

Actually, let me redo this more carefully:

heap = [(2, 1), (1, 2)] with heap property - min heap

When checking (1, 3):
- min in heap = (1, 2)
- freq(1,3) == 1, but val(3) > val(2)
- So replace: heap = [(2, 1), (1, 3)]

When checking (2, 4):
- min in heap = (1, 3)
- freq(2,4) > freq(1,3), so replace: remove (1,3), add (2,4)
- heap = [(2, 1), (2, 4)]
- After heapify, min = (2, 1) (frequency comparison, both 2)

When checking (1, 5):
- min in heap = (2, 1)
- freq(1,5) < freq(2,1) and freq(1,5) < freq(2,4), so don't add

When checking (1, 6):
- min in heap = (2, 1)
- freq(1,6) < 2, so don't add

Final heap: [(2, 1), (2, 4)]
Extract both: [4, 1] ✓

Notice in min heap with comparator:
- (2, 1) vs (2, 4) → freq same, so compare 1 vs 4 → (2,1) is smaller
- Min to root: (2, 1)
*/
class Solution3 {
public:
    vector<int> topKFreq(vector<int> &arr, int k) {
        
        // Step 1: Count frequencies
        unordered_map<int, int> freq;
        for(int num : arr) {
            freq[num]++;
        }
        
        // Step 2: Min Heap with custom comparator
        // Store {frequency, value}
        auto cmp = [](const pair<int,int> &a, const pair<int,int> &b) {
            if(a.first != b.first) {
                return a.first > b.first;  // Min heap on frequency
            }
            return a.second > b.second;     // If tied, min heap on value
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        
        // Step 3: Maintain heap of size k
        for(auto &p : freq) {
            pq.push({p.second, p.first});  // {freq, value}
            
            // Keep only k elements
            if(pq.size() > k) {
                pq.pop();  // Remove minimum
            }
        }
        
        // Step 4: Extract all elements from heap
        vector<int> result;
        while(!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }
        
        // Min heap extraction gives ascending order, reverse for descending
        reverse(result.begin(), result.end());
        
        return result;
    }
};


// ============================================================
// APPROACH 4: BUCKET SORT (Most Optimal) ⭐
// Time: O(n), Space: O(n + d)
// ============================================================
/*
HOW IT WORKS:
1. Count frequencies (O(n))
2. Create buckets indexed by frequency (0 to n)
3. For each {value, freq}, place in bucket[freq]
4. Traverse buckets from highest to lowest frequency
5. Extract k elements sorted by (freq desc, value desc)

WHY THIS WORKS:
- Avoids comparison-based sorting O(d log d)
- Uses frequency as direct index (counting sort technique)
- Maximum frequency ≤ n, so max n+1 buckets
- Linear time to iterate buckets

KEY INSIGHT:
Frequency can only be 1 to n, so we can use frequency as array index
instead of sorting.

EXAMPLE / DRY RUN:
arr = [3, 1, 4, 4, 5, 2, 6, 1], k = 2
n = 8

Step 1: Count frequencies
freq = {1→2, 2→1, 3→1, 4→2, 5→1, 6→1}

Step 2: Create buckets indexed by frequency [0...8]
bucket[0] = []
bucket[1] = [2, 3, 5, 6]  (elements with freq 1)
bucket[2] = [1, 4]        (elements with freq 2)
bucket[3] = []
...
bucket[8] = []

Step 3: Traverse buckets from highest to lowest
Start from bucket[8], bucket[7], ..., bucket[2]

bucket[2] has [1, 4]
Sort this bucket by value descending: [4, 1]
Extract k=2: result = [4, 1] ✓

Step 4: If needed more, go to bucket[1]
bucket[1] has [2, 3, 5, 6]
Sort by value desc: [6, 5, 3, 2]
Extract as needed

Another Example:
arr = [7, 10, 11, 5, 2, 5, 5, 7, 11, 8, 9], k = 4

freq = {2→1, 5→3, 7→2, 8→1, 9→1, 10→1, 11→2}

buckets:
bucket[1] = [2, 8, 9, 10] sorted desc: [10, 9, 8, 2]
bucket[2] = [7, 11]        sorted desc: [11, 7]
bucket[3] = [5]            sorted desc: [5]

Traverse from bucket[3] down:
bucket[3]: [5] → take 1: result = [5]
bucket[2]: [11, 7] → take 2: result = [5, 11, 7]
bucket[1]: [10, ...] → take 1: result = [5, 11, 7, 10]

Final: [5, 11, 7, 10] ✓
*/
class Solution {  // Main Solution - Use this one
public:
    vector<int> topKFreq(vector<int> &arr, int k) {
        
        int n = arr.size();
        
        // Step 1: Count frequencies
        unordered_map<int, int> freq;
        for(int num : arr) {
            freq[num]++;
        }
        
        // Step 2: Create buckets indexed by frequency
        // bucket[i] = list of elements with frequency i
        vector<vector<int>> buckets(n + 1);
        
        for(auto &p : freq) {
            int value = p.first;
            int frequency = p.second;
            buckets[frequency].push_back(value);
        }
        
        // Step 3: Traverse buckets from highest to lowest frequency
        vector<int> result;
        
        for(int freq_idx = n; freq_idx >= 1 && result.size() < k; freq_idx--) {
            
            // Sort elements in this bucket by value (descending)
            sort(buckets[freq_idx].begin(), buckets[freq_idx].end(), greater<int>());
            
            // Add elements to result
            for(int value : buckets[freq_idx]) {
                if(result.size() < k) {
                    result.push_back(value);
                }
            }
        }
        
        return result;
    }
};


/*
================================================================================
SUMMARY & COMPARISON
================================================================================

APPROACH 1 - Sort:
✓ Simple to understand
✓ Time O(n + d log d) acceptable
✗ Extra space for vector and sorting

APPROACH 2 - Max Heap:
✓ Clean implementation
✓ Time O(n + d log d)
✓ Heap naturally handles frequency ordering
✗ Same time as sorting

APPROACH 3 - Min Heap (Size k):
✓ Space optimized when k << d
✓ Time O(n + d log k) better when k small
✓ Ideal for streaming data
✓ Can handle elements on the fly
✗ Slightly complex min heap setup with comparator

APPROACH 4 - Bucket Sort: ⭐ OPTIMAL
✓ Time O(n) linear - no comparison needed
✓ Avoids log factor completely
✓ Uses frequency as direct index
✓ Best for this specific problem
✗ Need to sort within buckets (but typically few elements per bucket)

WHEN TO USE EACH:
- Interview quick answer: Approach 2 (max heap) - clean code
- Production optimized: Approach 4 (bucket sort) - O(n)
- Streaming data: Approach 3 (min heap k)
- Teaching: Approach 1 (sorting) - most intuitive

KEY INSIGHTS:
1. Max Heap naturally handles both frequency and value tiebreaker
2. Pair comparison in C++ is lexicographic
3. Bucket sort when constraint value is limited
4. Min heap useful when k is small compared to d

SIMILAR PROBLEMS:
- LeetCode 347: Top K Frequent Elements (same)
- LeetCode 692: Top K Frequent Words (with strings + frequency)
- LeetCode 1481: Least Number of Unique Integers after K Removals

================================================================================
*/
