int maxDistance(vector<int>& arr) {
    /*
    Problem:
    Find the maximum distance between two occurrences of the same element
    in an array.
    Distance is defined as the absolute difference between indices.

    Approach (First Index Mapping / Canonical Index Tracking):
    1. Traverse the array from left to right.
    2. For each element:
       - If it is seen for the first time, store its index.
       - If it is already seen, compute distance:
             current_index - first_occurrence_index
         and update the maximum distance.
    3. Return the maximum distance found.

    This follows value → first index mapping:
    - Each value maps to its earliest position.
    - Later occurrences maximize distance greedily.

    Time: O(n)
    Space: O(n)
    */

    unordered_map<int, int> firstIndex; // value -> first occurrence index
    int maxDist = 0; // maximum distance

    for (int i = 0; i < arr.size(); i++) { // traverse the array
        // if the element is not in the map, add it to the map
        // First occurrence
        if (firstIndex.find(arr[i]) == firstIndex.end()) {
            firstIndex[arr[i]] = i; // add the element to the map
        }
        // Repeated occurrence → update distance
        else {
            maxDist = max(maxDist, i - firstIndex[arr[i]]); // update the maximum distance
        }
    }
    return maxDist; // return the maximum distance
}
/*
GeeksforGeeks:
https://www.geeksforgeeks.org/maximum-distance-two-occurrences-element-array/

LeetCode:
No direct equivalent problem.
(Conceptually related to index-mapping / first occurrence tracking)
*/

