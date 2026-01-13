/*
Problem:
Connect N Ropes with Minimum Cost

Given N ropes of different lengths, connect them into one rope.
The cost of connecting two ropes is equal to the sum of their lengths.
Find the minimum total cost required to connect all ropes.

Rules:
- At each step, you can connect any two ropes.
- After connecting, the new rope has length = sum of the two ropes.
- You must minimize total cost.

Example:
Input:
ropes = [4, 3, 2, 6]

Process:
2 + 3 = 5   (cost = 5)
4 + 5 = 9   (cost = 9)
6 + 9 = 15  (cost = 15)

Total Cost = 5 + 9 + 15 = 29

Approach (Optimal – Min Heap / Greedy):
- This is a classic greedy problem (same idea as Huffman Coding).
- Always connect the two smallest ropes first.
- Use a min-heap to efficiently get the two smallest lengths.
- Add their sum to total cost and push it back into heap.
- Repeat until one rope remains.

Why this works:
- Combining smaller ropes earlier avoids repeatedly adding large lengths,
  which would increase overall cost.

GeeksforGeeks:
https://www.geeksforgeeks.org/connect-n-ropes-minimum-cost/

LeetCode:
https://leetcode.com/problems/minimum-cost-to-connect-sticks/

Time Complexity:
O(N log N)

Space Complexity:
O(N)
*/

class Solution {
public:
    int minCost(vector<int>& ropes) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int x : ropes) {
            pq.push(x);
        }
        int cost = 0;
        while (pq.size() > 1) {
            int a = pq.top(); pq.pop();
            int b = pq.top(); pq.pop();

            int sum = a + b;
            cost += sum;

            pq.push(sum);
        }
        return cost;
    }
};
    