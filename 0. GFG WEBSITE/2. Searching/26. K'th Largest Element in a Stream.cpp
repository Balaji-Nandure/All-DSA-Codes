/*
 * Problem: K'th Largest Element in a Stream
 * 
 * LeetCode: https://leetcode.com/problems/kth-largest-element-in-a-stream/
 * GeeksforGeeks: https://www.geeksforgeeks.org/kth-largest-element-in-a-stream/
 * Practice: https://practice.geeksforgeeks.org/problems/kth-largest-element-in-a-stream2220/1
 * 
 * Design a class to find the kth largest element in a stream. Note that it is the 
 * kth largest element in the sorted order, not the kth distinct element.
 * 
 * Implement KthLargest class:
 * - KthLargest(int k, vector<int>& nums) Initializes the object with the integer k 
 *   and the stream of integers nums.
 * - int add(int val) Appends the integer val to the stream and returns the element 
 *   representing the kth largest element in the stream.
 * 
 * Example 1:
 * Input:
 * ["KthLargest", "add", "add", "add", "add", "add"]
 * [[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
 * Output: [null, 4, 5, 5, 8, 8]
 * Explanation:
 * KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
 * kthLargest.add(3);   // return 4
 * kthLargest.add(5);   // return 5
 * kthLargest.add(10); // return 5
 * kthLargest.add(9);  // return 8
 * kthLargest.add(4);  // return 8
 * 
 * Example 2:
 * Input:
 * ["KthLargest", "add", "add", "add", "add"]
 * [[2, [0]], [-1], [1], [-2], [-4], [3]]
 * Output: [null, -1, 0, 0, 0, 1]
 * 
 * Constraints:
 * - 1 <= k <= 10^4
 * - 0 <= nums.length <= 10^4
 * - -10^4 <= nums[i] <= 10^4
 * - -10^4 <= val <= 10^4
 * - At most 10^4 calls will be made to add
 * 
 * Approach:
 * - Method 1: Min Heap (Optimal) - O(log k) per add, O(k) space
 *   Maintain a min heap of size k containing the k largest elements
 *   The top of the min heap is always the k-th largest element
 *   When adding a new element:
 *     - If heap size < k, add it
 *     - Else if new element > heap top, pop top and push new element
 * 
 * - Method 2: Max Heap - O(n log n) per add, O(n) space
 *   Store all elements, sort, return k-th largest (inefficient)
 * 
 * Time: O(log k) per add - min heap (optimal method)
 * Space: O(k) - min heap of size k
 */
 class KthLargest {
    /*
    Approach:
    1. Use a min-heap of size k.
    2. The heap always stores the k largest elements seen so far.
    3. For each new number:
       - Push it into the heap.
       - If heap size exceeds k, pop the smallest element.
    4. The top of the min-heap represents the k-th largest element.

    Time:
    - Insertion: O(log k)
    - Query (top): O(1)

    Space: O(k)
    */

    priority_queue<int, vector<int>, greater<int>> minHeap;
    int k;

public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;

        for (int num : nums) {
            minHeap.push(num);
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
    }

    int add(int val) {
        minHeap.push(val);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
        return minHeap.top();
    }
};
