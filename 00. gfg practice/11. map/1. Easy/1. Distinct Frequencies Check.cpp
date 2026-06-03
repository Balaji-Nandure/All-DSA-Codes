/*
GeeksforGeeks: Distinct Frequencies Check
Difficulty: Easy

Problem:
Given an array arr[] of integers, the task is to check whether the frequency of the elements in the array is unique or not. 
Or in other words, there are no two distinct numbers in array with equal frequency. 
If all the frequency is unique then return true, else return false.

Examples:
Input: arr[] = [1, 1, 2, 5, 5]
Output: false
Explanation:
The array contains 2 (1’s), 1 (2’s) and 2 (5’s), since the number of frequency of 1 and 5 are the same i.e. 2 times. 
Therefore, this array does not satisfy the condition.

Input: arr[] = [2, 2, 5, 10, 1, 2, 10, 5, 10, 2]
Output: true
Explanation:
Number of 1’s -> 1
Number of 2’s -> 4
Number of 5’s -> 2
Number of 10’s -> 3.
Since the number of occurrences of elements present in the array is unique, this array satisfy the condition.

Input: arr[] = [1, 1, 1]
Output: true
Explanation:
Number of 1's -> 3. Only one frequency exists, so all frequencies are unique.

Core Idea:
To verify that all element frequencies are strictly distinct, we can break this into two sub-problems:
1. Count the frequency of every element. A Hash Map (`unordered_map`) is ideal for mapping an element to its occurrence count.
2. Verify that none of these frequencies repeat. A Hash Set (`unordered_set`) is perfect for this! We can try to insert every frequency into the set. If we ever encounter a frequency that already exists in the set, we immediately know the frequencies are NOT unique.

Approach:
1. Initialize an `unordered_map<int, int> freqMap` and iterate through the array to populate it with element counts.
2. Initialize an `unordered_set<int> freqSet`.
3. Iterate through all the key-value pairs in `freqMap`.
   - Check if the value (the frequency) is already present in `freqSet`.
   - If it is, return `false`.
   - If it is not, insert the frequency into `freqSet`.
4. If the loop completes successfully without returning `false`, return `true`.

Time Complexity: O(N) where N is the number of elements in the array. We traverse the array once to build the map, and traverse the map once (which is at most N elements) to build the set. Hash Map and Hash Set lookups are amortized O(1).
Space Complexity: O(N) to store the elements and their frequencies in the Hash Map, and the frequencies in the Hash Set.

GFG Link: https://www.geeksforgeeks.org/problems/unique-frequencies-of-not/1
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
  public:
    bool isFrequencyUnique(vector<int>& arr) {
        // code here
        unordered_map<int, int> freq;
        for(int x: arr) {
            freq[x]++;
        }
        
        unordered_set<int> st;
        for(auto &x : freq) {
            int curfreq = x.second;
            
            if(st.count(curfreq)) return false;
            
            st.insert(curfreq);
        }
        
        
        return true;
    }
};

/*
Dry Run — Example 1:
Input: arr[] = [1, 1, 2, 5, 5]

1. Build freqMap:
   arr[0]=1 -> freqMap[1]=1
   arr[1]=1 -> freqMap[1]=2
   arr[2]=2 -> freqMap[2]=1
   arr[3]=5 -> freqMap[5]=1
   arr[4]=5 -> freqMap[5]=2
   Resulting Map: {1: 2, 2: 1, 5: 2}
   
2. Check uniqueness with freqSet:
   freqSet is initially empty {}.
   
   - entry: {1: 2}. currentFreq = 2.
     Is 2 in freqSet? No.
     freqSet.insert(2) -> {2}.
     
   - entry: {2: 1}. currentFreq = 1.
     Is 1 in freqSet? No.
     freqSet.insert(1) -> {2, 1}.
     
   - entry: {5: 2}. currentFreq = 2.
     Is 2 in freqSet? YES!
     return false.
     
Output: false
*/
