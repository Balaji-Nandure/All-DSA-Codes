/*
Delete Array Elements

Difficulty: Easy
Accuracy: 44.05%
Submissions: 16K+
Points: 2

Given an array arr[] and a number k. The task is to delete k elements that are 
smaller than the next element (i.e., we delete arr[i] if arr[i] < arr[i+1]) 
or become smaller than the next because the next element is deleted.

Examples:

Input: arr[] = [20, 10, 25, 30, 40], k = 2
Output: [25, 30, 40]
Explanation: First we delete 10 because it follows arr[i] < arr[i+1]. 
Then we delete 20 because 25 is moved next to it and it also starts following the condition.

Input: arr[] = [3, 100, 1], k = 1
Output: [100, 1]

Constraints:
2 ≤ arr.size() ≤ 10^6
1 ≤ k < arr.size()
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> deleteElements(vector<int>& arr, int k) {
    stack<int> st;
    
    for(int i = 0; i < arr.size(); i++) {
        // While stack is not empty, we have deletions left, 
        // and top of stack is smaller than current element
        while(!st.empty() && k > 0 && st.top() < arr[i]) {
            st.pop();
            k--;
        }
        st.push(arr[i]);
    }
    
    // Build result from stack
    vector<int> result(st.size());
    for(int i = st.size() - 1; i >= 0; i--) {
        result[i] = st.top();
        st.pop();
    }
    
    return result;
}
