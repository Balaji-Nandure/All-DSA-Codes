void sortZeroOne(vector<int>& arr) {

    // Sort a Binary Array
    // Move all zeros to end of array
    // Separate Even and Odd Numbers
    // Separate Negative and Positive Numbers
    
    /*
    Approach:
    1. Use two pointers:
       - left  starts from beginning
       - right starts from end
    2. While left < right:
       - If arr[left] == 0 → left++
       - Else if arr[right] == 1 → right--
       - Else:
         - arr[left] == 1 and arr[right] == 0 → swap them
         - Move both pointers
    3. This partitions all 0s to the left and 1s to the right.

    Time: O(n)
    Space: O(1)
    */

    int left = 0;
    int right = arr.size() - 1;

    while (left < right) {
        if (arr[left] == 0) {
            left++;
        }
        else if (arr[right] == 1) {
            right--;
        }
        else {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }
}
