/*
 * Problem: Find Median from Data Stream
 * 
 * LeetCode: https://leetcode.com/problems/find-median-from-data-stream/
 * GeeksforGeeks: https://www.geeksforgeeks.org/median-of-stream-of-integers-running-integers/
 * Practice: https://practice.geeksforgeeks.org/problems/find-median-in-a-stream-1587115620/1
 * 
 * The median is the middle value in an ordered integer list. If the size of the 
 * list is even, there is no middle value, and the median is the mean of the two 
 * middle values.
 * 
 * Implement the MedianFinder class:
 * - MedianFinder() initializes the MedianFinder object.
 * - void addNum(int num) adds the integer num from the data stream to the data structure.
 * - double findMedian() returns the median of all elements so far.
 * 
 * Example 1:
 * Input:
 * ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
 * [[], [1], [2], [], [3], []]
 * Output: [null, null, null, 1.5, null, 2.0]
 * Explanation:
 * MedianFinder medianFinder = new MedianFinder();
 * medianFinder.addNum(1);    // arr = [1]
 * medianFinder.addNum(2);    // arr = [1, 2]
 * medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
 * medianFinder.addNum(3);    // arr[1, 2, 3]
 * medianFinder.findMedian(); // return 2.0
 * 
 * Example 2:
 * Input:
 * ["MedianFinder", "addNum", "findMedian", "addNum", "findMedian"]
 * [[], [2], [], [3], []]
 * Output: [null, null, 2.0, null, 2.5]
 * 
 * Constraints:
 * - -10^5 <= num <= 10^5
 * - There will be at least one element in the data structure before calling findMedian.
 * - At most 5 * 10^4 calls will be made to addNum and findMedian.
 * 
 * Approach:
 * - Method 1: Two Heaps (Optimal) - O(log n) add, O(1) find, O(n) space
 *   Use max heap for lower half and min heap for upper half
 *   Maintain balance: maxHeap.size() == minHeap.size() or maxHeap.size() == minHeap.size() + 1
 * 
 * - Method 2: Insertion Sort - O(n) add, O(1) find, O(n) space
 *   Keep array sorted, insert in correct position
 * 
 * - Method 3: Multiset - O(log n) add, O(n) find, O(n) space
 *   Use balanced BST, find median by iterating
 * 
 * Time: O(log n) per addNum, O(1) per findMedian - two heaps (optimal method)
 * Space: O(n) - storing all numbers
 */

#include <bits/stdc++.h>
using namespace std;
class MedianFinder {
private:
    // Max heap for left half
    priority_queue<int> maxHeap;

    // Min heap for right half
    priority_queue<int, vector<int>, greater<int>> minHeap;

public:
    MedianFinder() {}

    // Adds a number into the data structure
    void addNum(int num) {
        if(maxHeap.empty() || num < maxHeap.top()){
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }

        // Step 3: Balance the heaps so that maxHeap either equals minHeap in size or has just one more element
        if (maxHeap.size() > minHeap.size() + 1) {
            // If maxHeap is too large, move its top to minHeap
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if (minHeap.size() > maxHeap.size()) {
            // If minHeap has more, move its top to maxHeap
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    // Finds and returns the median of all inserted numbers
    double findMedian() {
        // Case 1: Odd number of elements, maxHeap has the extra element
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        }

        // Case 2: Even number of elements, median is the average of two middle values
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};
    