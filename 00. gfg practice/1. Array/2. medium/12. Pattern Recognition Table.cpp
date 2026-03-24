/*
Problem: Pattern Recognition Table

Description: A table to recognize common array patterns and their optimal solutions.

Pattern Recognition Table:

| Problem                     | Pattern               | Optimal Approach       | Time Complexity | Space Complexity |
|-----------------------------|-----------------------|---------------------|------------------|-------------------|
| Missing number              | Cyclic sort           | Place at index      | O(n)           | O(1)           |
| First missing positive      | Cyclic sort           | Place at index      | O(n)           | O(1)           |
| Find duplicate             | Cyclic sort           | Place at index      | O(n)           | O(1)           |
| Set mismatch               | Cyclic sort           | Place at index      | O(n)           | O(1)           |
| All missing numbers         | Cyclic sort           | Place at index      | O(n)           | O(1)           |
| Sort 0,1,2              | Dutch National Flag     | 3 pointers          | O(n)           | O(1)           |
| Peak element              | Binary search          | Compare neighbors     | O(log n)        | O(1)           |
| Union of sorted arrays     | Two-pointer           | Merge technique      | O(n+m)         | O(n+m)         |
| Maximum subarray sum       | Kadane's algorithm     | Track max ending    | O(n)           | O(1)           |
| Subarray with sum K        | Prefix sum + hashmap  | Store prefix sums    | O(n)           | O(n)           |
| Count inversions          | Modified merge sort    | Count during merge   | O(n log n)      | O(n)           |
| Minimum jumps             | Greedy                | Track farthest      | O(n)           | O(1)           |
| Rotate array              | Reverse algorithm       | 3 reverses         | O(n)           | O(1)           |
| Maximum product subarray  | Track max/min products | Handle negatives     | O(n)           | O(1)           |

Common Patterns:
1. **Cyclic Sort**: Place elements at correct indices
2. **Two Pointers**: Merge sorted arrays, sliding window
3. **Dutch National Flag**: 3-way partitioning
4. **Binary Search**: Divide and conquer on sorted data
5. **Prefix Sum**: Precompute cumulative sums
6. **Hash Map**: Fast lookups and frequency counting
7. **Greedy**: Make locally optimal choices
8. **Dynamic Programming**: Build solutions from subproblems

Key Insight:
If numbers are 1 to n → Think Cyclic Sort

This table serves as a quick reference for recognizing patterns and applying optimal solutions.
*/

#include <bits/stdc++.h>
using namespace std;

/*
This file serves as a pattern recognition reference table.
It contains common array problems and their optimal approaches.
Use this as a quick guide when solving array problems.
*/
